// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LI2D_GameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDimensionChanged, bool, DimensionIsOne);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePauseChanged, bool, NewPauseStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonSequenceSucceeded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonSequenceFailed);

/**
 * 
 */
UCLASS()
class LI2D_API ALI2D_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	ALI2D_GameStateBase();

public:
	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	double TimeDimensionOne;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	double TimeDimensionTwo;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetTimeAsPercentage();
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetGameIsPaused(bool GamePausedIn);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ChangeDimension();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void CheckButtonSequence(class ALI2D_TriggerBase* ButtonReferenceIn);
	
	UPROPERTY(BlueprintAssignable)
	FOnDimensionChanged OnDimensionChanged;

	UPROPERTY(BlueprintAssignable)
	FOnGamePauseChanged OnGamePauseChanged;

	UPROPERTY(BlueprintAssignable)
	FOnButtonSequenceSucceeded OnButtonSequenceSucceeded;

	UPROPERTY(BlueprintAssignable)
	FOnButtonSequenceFailed OnButtonSequenceFailed;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
   	// Called when the game starts or when spawned
   	virtual void BeginPlay() override;

private:
	double Clockwork;
	int32 DayTick;
	bool bIsGamePaused;

	TArray<int32> ButtonOrderSequence = {3, 1, 6, 4, 2, 5};
	int32 ArrayRowToCheck = 0;
};
