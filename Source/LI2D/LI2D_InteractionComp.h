// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "LI2D_InteractionComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, class ALI2DCharacter*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, class ALI2DCharacter*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, class ALI2DCharacter*, Player);

/**
 * 
 */
UCLASS()
class LI2D_API ULI2D_InteractionComp : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	ULI2D_InteractionComp();

	// Distance the player can interact with this component from
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	double InteractionDistance;

	// Name of this item to be displayed on screen
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FText InteractionNameText;

	// Text to be displayed which explains the action ie "Turn On" with a lamp
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	FText InteractionUseText;

	//Delegates
	
	//[local + server] Called when the player presses the interact key whilst focusing on this interactable actor
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginFocus OnBeginFocus;

	//[local + server] Called when the player releases the interact key, stops looking at the interactable actor, or gets too far away after starting an interact
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndFocus OnEndFocus;

	//[local + server] Called when the player has interacted with the item for the required amount of time
	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnInteract OnInteract;

protected:
	// Called when the game starts
	virtual void Deactivate() override;

public:
	/** Refresh the interaction widget */
	void RefreshWidget();
	
	//Called on the client when the players interaction check trace begins/ends hitting this item
	void BeginFocus(TObjectPtr<ALI2DCharacter> Character);
	void EndFocus(TObjectPtr<ALI2DCharacter> Character);

	void Interact(TObjectPtr<ALI2DCharacter> Character);
	
};
