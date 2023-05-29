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

	DimensionType = EDimensionType::DimBoth;
	
}

// Called when the game starts or when spawned
void ALI2D_WorldItemBase::BeginPlay()
{
	GameStateRef = Cast<ALI2D_GameStateBase>(GetWorld()->GetGameState());

	if (GameStateRef)
	{
		GameStateRef->OnDimensionChanged.AddDynamic(this, &ALI2D_WorldItemBase::DimensionHasChanged);
	}
	
	Super::BeginPlay();


}

// Called every frame
void ALI2D_WorldItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALI2D_WorldItemBase::DimensionHasChanged(bool DimensionIsOneIn)
{
	if (DimensionIsOneIn && DimensionType == EDimensionType::DimOneOnly || !DimensionIsOneIn && DimensionType == EDimensionType::DimTwoOnly)
	{
		MeshComp->SetVisibility(true, true);
		MeshComp->SetCollisionResponseToChannels(ECollisionResponse::ECR_Block);
	}
	else if (DimensionType != EDimensionType::DimBoth)
	{
		MeshComp->SetVisibility(false, true);
		MeshComp->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
	}
}

