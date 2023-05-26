// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LI2DCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS(config=Game)
class ALI2DCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Post-Process control */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Post Process", meta = (AllowPrivateAccess = "true"))
	class UPostProcessComponent* PostProcessComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Post Process", meta = (AllowPrivateAccess = "true"))
	FPostProcessSettings PostProcessDimensionOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Post Process", meta = (AllowPrivateAccess = "true"))
	FPostProcessSettings PostProcessDimensionTwo;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Dimension Control Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* DimensionControlAction;
	
	/** Player widget to display on screen */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Widgets, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<class ULI2D_PlayerWidget> InGameWidgetRef;
	TObjectPtr<ULI2D_PlayerWidget> InGameWidget;

	/** Main Menu Widget to display on screen */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Widgets, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ULI2D_PlayerWidget> MainMenuWidgetRef;
	TObjectPtr<ULI2D_PlayerWidget> MainMenuWidget;

	/** Pause Widget to display on screen */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Widgets, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<ULI2D_PlayerWidget> PauseWidgetRef;
	TObjectPtr<ULI2D_PlayerWidget> PauseWidget;

	/** Time in seconds between each check for an interaction component */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Gameplay, meta=(AllowPrivateAccess = "true"))
	double TimeBetweenInteractionCheck = 0.1f;
public:
	ALI2DCharacter();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void QuitToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void StartMainGame();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	
private:
	TObjectPtr<class ALI2D_GameStateBase> GameStateRef;
	TObjectPtr<class ALI2D_PlayerController> PlayerControllerRef;
	void GetReferences();
	void CreateWidgets();

	// Called when the Game State broadcasts that the game is paused
	UFUNCTION()
	void GameHasBeenPaused(bool PausedStatusIn);

	// Called when the game state broadcasts it has changed the dimension
	UFUNCTION()
	void DimensionHasChanged(bool DimensionIsOne);

	// A check so that the main menu opens on game start, not the pause menu
	bool bGameHasStarted = true;

	// Called when the player presses the pause button
	void Paused();
	bool bGameIsPaused = false;

	// Time since the last interaction check took place
	double TimeSinceLastInteractionCheck = 0.f;
	double LineTraceDistance = 500.f;
	void DoInteractionCheck();
	// The currently viewed component
	UPROPERTY()
	TObjectPtr<class ULI2D_InteractionComp> ViewedInteractionComponent;
	void FoundNewInteractionComp(TObjectPtr<ULI2D_InteractionComp> InteractionCompIn);
	void CouldntFindInteractionComp();
	TObjectPtr<ULI2D_InteractionComp> GetViewedInteractionComp() const { return ViewedInteractionComponent; } 
public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();
	
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	void TryInteract();
	
	bool bHasDimensionControl;
	void TryDimensionChange();
};

