// Copyright 2023 DME Games


#include "InteractionWidget.h"


void UInteractionWidget::UpdateInteractionWidget(class ULI2D_InteractionComp* InteractionComponent)
{
	OwningInteractionComponent = InteractionComponent;
	OnUpdateInteractionWidget();
}