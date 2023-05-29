// Copyright 2023 DME Games


#include "LI2D_TriggerBase.h"
#include "InteractionWidget.h"
#include "LI2D_InteractionComp.h"
#include "LI2D_TriggeredBase.h"

// Sets default values
ALI2D_TriggerBase::ALI2D_TriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionComp = CreateDefaultSubobject<ULI2D_InteractionComp>(TEXT("Interaction Comp"));
	InteractionComp->SetupAttachment(RootComp);

	static ConstructorHelpers::FClassFinder<UInteractionWidget> FoundWidget(TEXT("/Game/UI/WBP_Interaction"));
	if (FoundWidget.Succeeded())
	{
		InteractionComp->SetWidgetClass(FoundWidget.Class);
	}
}

void ALI2D_TriggerBase::ItemInteractedWith()
{
	// Don't allow an only once triggered item to be triggered again
	if ((!bItemIsTriggered || bItemCanReverse))
	{
		if (!bItemIsTriggered)
		{
			bItemIsTriggered = true;
			InteractionComp->EndFocus(nullptr);
			if (ItemToTrigger)
			{
				ItemToTrigger->AddActiveTrigger();
			}
		}
		else if (bItemCanReverse)
		{
			bItemIsTriggered = false;
			if (ItemToTrigger)
			{
				ItemToTrigger->RemoveActiveTrigger();
			}

		}
		
		// Call the blueprint event
		OnItemHasBeenInteractedWith();
	}
}

// Called when the game starts or when spawned
void ALI2D_TriggerBase::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ALI2D_TriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

