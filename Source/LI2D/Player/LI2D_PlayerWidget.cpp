// Copyright 2023 DME Games

#include "LI2D_PlayerWidget.h"
#include "LI2DCharacter.h"
#include "LI2D/Framework/LI2D_GameStateBase.h"

bool ULI2D_PlayerWidget::Initialize()
{
	GameStateRef = Cast<ALI2D_GameStateBase>(UUserWidget::GetWorld()->GetGameState());
	
	return Super::Initialize();
}

void ULI2D_PlayerWidget::SetTimeToWidget(FText& NewTimeToDisplay)
{
	bUpdateWidget = false;
	NewTimeToDisplay = TimeAsText;
}

void ULI2D_PlayerWidget::SetPlayerRef(const TObjectPtr<ALI2DCharacter> PlayerRefIn)
{
	PlayerRef = PlayerRefIn;
}

void ULI2D_PlayerWidget::UpdateInGameTimeText(FText NewTimeIn)
{
	bUpdateWidget = true;
	TimeAsText = NewTimeIn;
}
