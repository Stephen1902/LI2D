// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LI2D_WorldItemBase.generated.h"

UENUM(BlueprintType)
enum class EDimensionType : uint8
{
	DimOneOnly  UMETA(DisplayName="Dimension One Only"),
	DimTwoOnly  UMETA(DisplayName="Dimension Two Only"),
	DimBoth     UMETA(DisplayName="Both Dimensions")
};

UCLASS()
class LI2D_API ALI2D_WorldItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALI2D_WorldItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> RootComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	// Which dimension this item is designed to be shown in in the world
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	EDimensionType DimensionType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="References", meta=(AllowPrivateAccess="true"))
	TObjectPtr<class ALI2D_GameStateBase> GameStateRef;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void DimensionHasChanged(bool DimensionIsOneIn);

};
