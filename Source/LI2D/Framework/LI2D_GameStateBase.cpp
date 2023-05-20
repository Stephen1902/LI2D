// Copyright 2023 DME Games


#include "LI2D_GameStateBase.h"

#include "Kismet/KismetMathLibrary.h"

ALI2D_GameStateBase::ALI2D_GameStateBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeUnit = 2.f;  //TODO Restore to a better setting for day / night cycle
	Seconds = 0.f;
	Minutes = 30.f;
	Hours = 6.f;
	Day = 31;
	Month = 12;
	Year = 2000;
	Clockwork = 0.f;
	CurrentGameSpeed = 3;
	TimeUnitMultiplier = 1.0f;

	bIsGamePaused = false;
}

void ALI2D_GameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!bIsGamePaused)
	{
		SetClockworkAndDayTick(DeltaTime);
		SetGameTime();
		CalculateGameDate();
	}
}

void ALI2D_GameStateBase::BeginPlay()
{
	Super::BeginPlay();
		
	Clockwork = (Seconds / 3600) + (Minutes / 60) + Hours;
	SetGameTime();
	CalculateGameDate();
}

float ALI2D_GameStateBase::GetTimeAsPercentage()
{
	const float ClockworkAsPercentage = 1.f - ((24.f - Clockwork) / 24.f);
	return ((ClockworkAsPercentage * 360.f) + 90.f); 
}

FText ALI2D_GameStateBase::AdjustGameSpeed(bool IncreaseGameSpeed)
{
	if (IncreaseGameSpeed)
	{
		CurrentGameSpeed += 1;
	}
	else
	{
		CurrentGameSpeed -= 1;
	}

	CurrentGameSpeed = FMath::Clamp(CurrentGameSpeed, 0, 5);

	switch (CurrentGameSpeed)
	{
	case 0:
		bIsGamePaused = true;
		TimeUnitMultiplier = 0.f;
		return FText::FromString("||");
		break;
	case 1:
		TimeUnitMultiplier = 1.5f;
		break;
	case 2:
		TimeUnitMultiplier = 1.25f;
		break;
	case 3:
	default:
		TimeUnitMultiplier = 1.0f;
		break;
	case 4:
		TimeUnitMultiplier = 0.5f;
		break;
	case 5:
		TimeUnitMultiplier = 0.125f;
		break;		
	}

	bIsGamePaused = false;
	return FText::FromString(FString::FromInt(CurrentGameSpeed));
}


void ALI2D_GameStateBase::SetClockworkAndDayTick(float DeltaTime)
{
	const float DeltaTimeUnit = DeltaTime / (TimeUnit * TimeUnitMultiplier);
	const float DeltaClockwork = DeltaTimeUnit + Clockwork;
	
	DayTick = UKismetMathLibrary::FMod(DeltaClockwork, 24.f, Clockwork);
}

void ALI2D_GameStateBase::SetGameTime()
{
	// 3600 seconds in one hour
	const float ClockworkInSeconds = Clockwork * 3600.f;

	const int32 SecondsRemainder = UKismetMathLibrary::FMod(ClockworkInSeconds, 60.f, Seconds);
	const int32 MinutesRemainder = UKismetMathLibrary::FMod(SecondsRemainder, 60.f, Minutes);
	UKismetMathLibrary::FMod(MinutesRemainder, 24.f, Hours);

	FString LeadingZeroHours = "";
	if (Hours < 10)
	{
		LeadingZeroHours = "0";
	}
	FString LeadingZeroMinutes = "";
	if (Minutes < 10)
	{
		LeadingZeroMinutes = "0";
	}
	
	const FString StringToConvert = LeadingZeroHours + FString::FromInt(Hours) + ":" + LeadingZeroMinutes + FString::FromInt(Minutes); 
	OnTimeChanged.Broadcast(FText::FromString(StringToConvert));
}

void ALI2D_GameStateBase::CalculateGameDate()
{
	Day += DayTick;
	
	if (Day > UKismetMathLibrary::DaysInMonth(Year, Month))
	{
		Day = 1;
		Month += 1;
		
		if (Month > 12)
		{
			Month = 1;
			Year += 1;
		}
	}

	const FString StringToConvert = TextDays[Day - 1] + " " + TextMonths[Month - 1] + " " + FString::FromInt(Year);
	OnDateChanged.Broadcast(FText::FromString(StringToConvert));
}

