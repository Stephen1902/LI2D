// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkySphereActor.generated.h"

UCLASS()
class LI2D_API ASkySphereActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkySphereActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<USceneComponent> RootComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<UMaterialInstanceDynamic> SkyMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<class ADirectionalLight> DirectionalLight;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<class UCurveLinearColor> HorizonColourCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<UCurveLinearColor> ZenithColourCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Set Up")
	TObjectPtr<UCurveLinearColor> CloudColourCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "References")
	TObjectPtr<class ALI2D_GameStateBase> GameStateRef; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	double SunBrightness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	double CloudSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	double CloudOpacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	double StarBrightness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	bool bRefreshMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	bool bColoursBySunPosition;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void RefreshMaterial();
};
