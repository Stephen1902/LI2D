// Copyright 2023 DME Games

#include "LI2D_InteractionComp.h"
#include "InteractionWidget.h"
#include "LI2D_TriggerBase.h"
#include "Player/LI2DCharacter.h"

ULI2D_InteractionComp::ULI2D_InteractionComp()
{	// This component does not need to tick, set to false to improve performance
	UActorComponent::SetComponentTickEnabled(false);

	// Set up default parameters
	InteractionDistance = 200.f;
	InteractionNameText = FText::FromString("Interaction Object");
	InteractionUseText = FText::FromString("Interact");

	// Set the widget so it only appears in local space at a specific size
	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(600, 100);
	bDrawAtDesiredSize = true;

	// Set the component as active but keep it hidden
	UActorComponent::SetActive(true);
	SetHiddenInGame(true);
}

void ULI2D_InteractionComp::Deactivate()
{
	Super::Deactivate();
}

void ULI2D_InteractionComp::RefreshWidget()
{
	//Make sure the widget is initialized, and that we are displaying the right values (these may have changed)
	if (UInteractionWidget* InteractionWidget = Cast<UInteractionWidget>(GetUserWidgetObject()))
	{
		InteractionWidget->UpdateInteractionWidget(this);
	}
}

void ULI2D_InteractionComp::BeginFocus(const TObjectPtr<ALI2DCharacter> Character)
{
	if (!IsActive() || !GetOwner() || !Character)
	{
		return;
	}

	// Check that the trigger this item is attached to hasn't already been activated, don't display if it hasn't
	if (const ALI2D_TriggerBase* CompOwner = Cast<ALI2D_TriggerBase>(GetOwner()))
	{
		if (CompOwner->GetShowInteractionComp()) { return; }
	}
	
	OnBeginFocus.Broadcast(Character);

	SetHiddenInGame(false);

	// Get all primitive components attached to the viewed actor
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetOwner()->GetComponents(PrimitiveComponents, false);
	for (const auto& VisualComp : PrimitiveComponents)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
		{
			Prim->SetRenderCustomDepth(true);
		}
	}

	RefreshWidget();
}

void ULI2D_InteractionComp::EndFocus(const TObjectPtr<ALI2DCharacter> Character)
{
	OnEndFocus.Broadcast(Character);

	SetHiddenInGame(true);

	TArray<TObjectPtr<UPrimitiveComponent>> PrimitiveComponents;
	GetOwner()->GetComponents(PrimitiveComponents, false);
	for (auto& VisualComp : PrimitiveComponents)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
		{
			Prim->SetRenderCustomDepth(false);
		}
	}
}

void ULI2D_InteractionComp::Interact(const TObjectPtr<ALI2DCharacter> Character)
{
	// Check if the item is one from the custom base class, called the interacted function
	if (ALI2D_TriggerBase* OwningActor = Cast<ALI2D_TriggerBase>(GetOwner()))
	{
		OwningActor->ItemInteractedWith();
	}
	OnInteract.Broadcast(Character);
}
