// Copyright Epic Games, Inc. All Rights Reserved.

#include "LI2DCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LI2D_PlayerController.h"
#include "LI2D_PlayerWidget.h"
#include "LI2D/Framework/LI2D_GameStateBase.h"


//////////////////////////////////////////////////////////////////////////
// ALI2DCharacter

ALI2DCharacter::ALI2DCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ALI2DCharacter::QuitToMainMenu()
{
	// Game should be displaying the pause menu 
	bGameHasStarted = false;
	if (PauseWidget && MainMenuWidget && PlayerControllerRef)
	{
		PauseWidget->RemoveFromParent();
		MainMenuWidget->AddToViewport();
		PlayerControllerRef->SetInputMode(FInputModeUIOnly());
	}

	// TODO Save game functionality
}

void ALI2DCharacter::StartMainGame()
{
	// TODO Check for saved game and load it

	if (MainMenuWidget && InGameWidget && PlayerControllerRef)
	{
		// The start game button has been clicked.  Start the game.
		bGameHasStarted = true;
	
		MainMenuWidget->RemoveFromParent();
		InGameWidget->AddToViewport();
		PlayerControllerRef->SetInputMode(FInputModeGameOnly());
		GameStateRef->SetGameIsPaused(false);
	}
}

void ALI2DCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	GetReferences();

	// Create all of the widgets used in game
	CreateWidgets();
	
	// Open the main menu on game start
	if (MainMenuWidget && PlayerControllerRef)
	{
		MainMenuWidget->AddToViewport();
		PlayerControllerRef->SetInputMode(FInputModeUIOnly());
	}
	
}

void ALI2DCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TimeSinceLastInteractionCheck -= DeltaSeconds;
	if (TimeSinceLastInteractionCheck < 0.f)
	{
		DoInteractionCheck();
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ALI2DCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALI2DCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALI2DCharacter::Look);

		// Pausing
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ALI2DCharacter::Paused);
	}
}

void ALI2DCharacter::GetReferences()
{
	// Try to get the Game State
	GameStateRef = Cast<ALI2D_GameStateBase>(GetWorld()->GetGameState());
	// Bind delegate from Game State about the paused status of the game
	if (GameStateRef)
	{
		GameStateRef->OnGamePauseChanged.AddDynamic(this, &ALI2DCharacter::GameHasBeenPaused);
	}

	// Try to get the player controller
	PlayerControllerRef = Cast<ALI2D_PlayerController>(GetController());
}

void ALI2DCharacter::CreateWidgets()
{
	if (InGameWidgetRef)
	{
		InGameWidget = CreateWidget<ULI2D_PlayerWidget>(GetWorld(), InGameWidgetRef);
		InGameWidget->SetPlayerRef(this);
	}

	if (PauseWidgetRef)
	{
		PauseWidget = CreateWidget<ULI2D_PlayerWidget>(GetWorld(), PauseWidgetRef);
		PauseWidget->SetPlayerRef(this);
	}

	if (MainMenuWidgetRef)
	{
		MainMenuWidget = CreateWidget<ULI2D_PlayerWidget>(GetWorld(), MainMenuWidgetRef);
		MainMenuWidget->SetPlayerRef(this);
	}
}

void ALI2DCharacter::GameHasBeenPaused(bool PausedStatusIn)
{
	// Check that the game is actually running before showing any widgets
	if (bGameHasStarted)
	{
		if (InGameWidget && PauseWidget && MainMenuWidget && PlayerControllerRef)
		bGameIsPaused = PausedStatusIn;
		// If the game has been paused, open the pause menu
		if (PausedStatusIn)
		{
			InGameWidget->RemoveFromParent();
			PauseWidget->AddToViewport();
			PlayerControllerRef->SetInputMode(FInputModeGameAndUI());
			PlayerControllerRef->SetShowMouseCursor(true);
		}
		else
		{
			// Otherwise, open the in game widget
			PauseWidget->RemoveFromParent();
			InGameWidget->AddToViewport();
			PlayerControllerRef->SetInputMode(FInputModeGameOnly());
			PlayerControllerRef->SetShowMouseCursor(false);
		}
	}
}

void ALI2DCharacter::Paused()
{
	if (GameStateRef)
	{
		if (bGameIsPaused)
		{
			bGameIsPaused = false;
		}
		else
		{
			bGameIsPaused = true;
		}
		GameStateRef->SetGameIsPaused(bGameIsPaused);
	}
}

void ALI2DCharacter::DoInteractionCheck()
{
}

void ALI2DCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALI2DCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALI2DCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ALI2DCharacter::GetHasRifle()
{
	return bHasRifle;
}