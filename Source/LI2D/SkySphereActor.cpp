// Copyright 2023 DME Games


#include "SkySphereActor.h"

#include "Components/LightComponent.h"
#include "Curves/CurveLinearColor.h"
#include "Engine/DirectionalLight.h"
#include "Framework/LI2D_GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASkySphereActor::ASkySphereActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));
	MeshComponent->SetupAttachment(RootComp);
	MeshComponent->SetRelativeScale3D(FVector(400.f));

	bColoursBySunPosition = true;
	CloudSpeed = 1.0f;
	SunBrightness = 50.f;
	CloudOpacity = 0.7f;
	StarBrightness = 0.1f;

}

// Called when the game starts or when spawned
void ASkySphereActor::BeginPlay()
{
	Super::BeginPlay();

	// Get the existing material and make it a dynamic material
	const TObjectPtr<UMaterialInterface> CurrentMat = MeshComponent->GetMaterial(0);
	SkyMaterial = UMaterialInstanceDynamic::Create(CurrentMat, this);
	if (SkyMaterial == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SkySphereActor failed to get SkyMaterial"));
	}
	
	// Get the directional light actor in the world, if it exists
	TArray<TObjectPtr<AActor>> FoundLights;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADirectionalLight::StaticClass(), FoundLights);

	if (FoundLights.Num() > 0)
	{
		DirectionalLight = Cast<ADirectionalLight>(FoundLights[0]);
	}

	// Get the Game State Reference
	GameStateRef = Cast<ALI2D_GameStateBase>(GetWorld()->GetGameState());
	if (!GameStateRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Get Game State in SkySphereActor"));
	}

}

// Called every frame
void ASkySphereActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GameStateRef)
	{
		RefreshMaterial();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 0.f, FColor::Red, TEXT("Sky Sphere does not have GameStateRef"));
	}

}

void ASkySphereActor::RefreshMaterial()
{
	if (DirectionalLight)
	{
		// Get the current world time as a percentage of a 24 hour cycle and set the directional light accordingly
		const double TimeAsPercentage = GameStateRef->GetTimeAsPercentage();
		DirectionalLight->SetActorRotation(FRotator(TimeAsPercentage, 0.f, 0.f));
	}/*
		// Amend the Light Direction
		const FVector DirectionalLightXVector = UKismetMathLibrary::Conv_RotatorToVector(DirectionalLight->GetActorRotation());
		SkyMaterial->SetVectorParameterValue(TEXT("Light direction"), DirectionalLightXVector);

		// Amend the Sun Color
		const FLinearColor NewSunColour = DirectionalLight->GetLightComponent()->LightColor;
		SkyMaterial->SetVectorParameterValue(TEXT("Sun color"), NewSunColour);

		// Check where the sun should be in the sky
		const FRotator CurrentLightRotation = DirectionalLight->GetActorRotation();
		const float ClampedHeight = UKismetMathLibrary::MapRangeUnclamped(CurrentLightRotation.Pitch, 0.f, -90.f, 0.f, 1.f);

		// Set material parameters on the skybox
		SkyMaterial->SetVectorParameterValue(TEXT("Horizon color"), HorizonColourCurve->GetClampedLinearColorValue(ClampedHeight));
		SkyMaterial->SetVectorParameterValue(TEXT("Zenith color"), ZenithColourCurve->GetClampedLinearColorValue(ClampedHeight));
		SkyMaterial->SetVectorParameterValue(TEXT("Cloud color"), CloudColourCurve->GetClampedLinearColorValue(ClampedHeight));
		const float HorizonLerp = UKismetMathLibrary::Lerp(3.f, 7.f, FMath::Abs(ClampedHeight));
		SkyMaterial->SetScalarParameterValue(TEXT("Horizon falloff"), HorizonLerp);
		SkyMaterial->SetScalarParameterValue(TEXT("Cloud speed"), CloudSpeed);
		SkyMaterial->SetScalarParameterValue(TEXT("Sun brightness"), SunBrightness);
		const float SunHeightPicker = UKismetMathLibrary::SelectFloat(UKismetMathLibrary::Abs(ClampedHeight), 0, ClampedHeight < 0.f);
		SkyMaterial->SetScalarParameterValue(TEXT("Sun height"), SunHeightPicker);
		SkyMaterial->SetScalarParameterValue(TEXT("Cloud opacity"), CloudOpacity);
		SkyMaterial->SetScalarParameterValue(TEXT("Stars brightness"), StarBrightness);
	}
	else
	{
		
	}*/
}

