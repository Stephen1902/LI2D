// Copyright 2023 DME Games


#include "LI2D_TriggeredBase.h"

// Sets default values
ALI2D_TriggeredBase::ALI2D_TriggeredBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ALI2D_TriggeredBase::AddActiveTrigger()
{
	ActiveTriggers += 1;

	if (ActiveTriggers >= TriggersNeededToActivate)
	{
		OnItemTriggered();
	}	
}

void ALI2D_TriggeredBase::RemoveActiveTrigger()
{
	// Check to ensure the active triggers cannot go below zero
	ActiveTriggers = FMath::Clamp(ActiveTriggers, 0, ActiveTriggers - 1);
}

// Called when the game starts or when spawned
void ALI2D_TriggeredBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALI2D_TriggeredBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

