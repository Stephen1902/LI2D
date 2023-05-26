// Copyright 2023 DME Games


#include "LI2D_GameStateBase.h"

ALI2D_GameStateBase::ALI2D_GameStateBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeDimensionOne = 9.f;
	TimeDimensionTwo = 21.f;
	Clockwork = 0.f;

	bIsGamePaused = false;
}

void ALI2D_GameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ALI2D_GameStateBase::BeginPlay()
{
	Super::BeginPlay();
		
	Clockwork = TimeDimensionOne;

	OnDimensionChanged.Broadcast(true);

	// Pause the game so that nothing happens until the player comes off the main menu
	SetGameIsPaused(true);
}

float ALI2D_GameStateBase::GetTimeAsPercentage()
{
	const float ClockworkAsPercentage = 1.f - ((24.f - Clockwork) / 24.f);
	return ((ClockworkAsPercentage * 360.f) + 90.f); 
}

void ALI2D_GameStateBase::SetGameIsPaused(bool GamePausedIn)
{
	bIsGamePaused = GamePausedIn;
	OnGamePauseChanged.Broadcast(bIsGamePaused);
}

void ALI2D_GameStateBase::ChangeDimension()
{
	if (Clockwork == TimeDimensionOne)
	{
		Clockwork = TimeDimensionTwo;
		OnDimensionChanged.Broadcast(false);
	}
	else
	{
		Clockwork = TimeDimensionOne;
		OnDimensionChanged.Broadcast(true);
	}

	
}
