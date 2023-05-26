// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LI2D_WorldItemBase.generated.h"

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
	
	// if true, is only visible when the game is set to dimension one, otherwise dimension two
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	bool VisibleDimensionOne = true;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TObjectPtr<class ALI2D_GameStateBase> GameStateRef;

	UFUNCTION()
	void DimensionHasChanged(bool DimensionIsOneIn);

};
