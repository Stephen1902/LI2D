// Copyright 2023 DME Games


#include "LI2D_WorldItemBase.h"

#include "Framework/LI2D_GameStateBase.h"

// Sets default values
ALI2D_WorldItemBase::ALI2D_WorldItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComp->SetupAttachment(RootComp);
	
}

// Called when the game starts or when spawned
void ALI2D_WorldItemBase::BeginPlay()
{
	Super::BeginPlay();

	GameStateRef = Cast<ALI2D_GameStateBase>(GetWorld()->GetGameState());

	if (GameStateRef)
	{
		GameStateRef->OnDimensionChanged.AddDynamic(this, &ALI2D_WorldItemBase::DimensionHasChanged);
	}
}

// Called every frame
void ALI2D_WorldItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALI2D_WorldItemBase::DimensionHasChanged(bool DimensionIsOneIn)
{
	if (DimensionIsOneIn == VisibleDimensionOne)
	{
		MeshComp->SetVisibility(true);
	}
	else
	{
		MeshComp->SetVisibility(false);
	}
}

