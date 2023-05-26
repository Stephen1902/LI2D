// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "LI2D_WorldItemBase.h"
#include "GameFramework/Actor.h"
#include "LI2D_TriggeredBase.generated.h"

UCLASS()
class LI2D_API ALI2D_TriggeredBase : public ALI2D_WorldItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALI2D_TriggeredBase();

	void AddActiveTrigger();
	void RemoveActiveTrigger();

	UPROPERTY(EditAnywhere, Category = "Set up")
	int32 TriggersNeededToActivate = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void OnItemTriggered();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 ActiveTriggers = 0;
};
