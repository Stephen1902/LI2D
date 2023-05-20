// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "LI2D_GameStateBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDateChanged, FText, NewCurrentDate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, FText, NewCurrentTime);

/**
 * 
 */
UCLASS()
class LI2D_API ALI2D_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	ALI2D_GameStateBase();

public:
	// Speed at which one day takes to complete
	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	float TimeUnit;

	// UPROPERTY so they can be set up in blueprint to edit start time / date easily
	UPROPERTY(EditDefaultsOnly, Category = "SetUp", meta=(ClampMax="59.0"))
	float Seconds;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp", meta=(ClampMax="59.0"))
	float Minutes;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp", meta=(ClampMax="23.0"))
	float Hours;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp", meta=(ClampMin="1", ClampMax="31"))
	int32 Day;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp", meta=(ClampMin="1", ClampMax="12"))
	int32 Month;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp", meta=(ClampMin="1"))
	int32 Year;

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	float GetTimeAsPercentage();

	float GetTimeUnit() const { return TimeUnit; }
	float GetTimeMultiplier() const { return TimeUnitMultiplier; }
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	bool GetIsGamePaused() const { return bIsGamePaused; }

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	FText AdjustGameSpeed(bool IncreaseGameSpeed);

	UPROPERTY(BlueprintAssignable)
	FOnDateChanged OnDateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnTimeChanged OnTimeChanged;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
   	// Called when the game starts or when spawned
   	virtual void BeginPlay() override;

private:
	int32 CurrentGameSpeed;
	float Clockwork;
	int32 DayTick;
	bool bIsGamePaused;
	float TimeUnitMultiplier;

	void SetClockworkAndDayTick(float DeltaTime);
	void SetGameTime();
	void CalculateGameDate();

	TArray<FString> TextDays = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th", "31st"};
	TArray<FString> TextMonths = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

};
