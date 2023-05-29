// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "LI2D_WorldItemBase.h"
#include "GameFramework/Actor.h"
#include "LI2D_TriggerBase.generated.h"

UCLASS()
class LI2D_API ALI2D_TriggerBase : public ALI2D_WorldItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALI2D_TriggerBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class ULI2D_InteractionComp> InteractionComp;

	// Whether or not this item can be reversed ie a lever
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	bool bItemCanReverse = false;
	
	// If there is an item triggered by this one
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Set Up", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<class ALI2D_TriggeredBase> ItemToTrigger;
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ItemInteractedWith();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void ResetThisItem() {bItemIsTriggered = false;}

	// When an item has been interacted with, for BP
	UFUNCTION(BlueprintImplementableEvent)
	void OnItemHasBeenInteractedWith();

	bool GetShowInteractionComp() const { return bItemIsTriggered; }
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Whether or not his item has been triggered
	bool bItemIsTriggered = false;	
};
