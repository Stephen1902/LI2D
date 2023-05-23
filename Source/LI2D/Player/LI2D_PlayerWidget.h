// Copyright 2023 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LI2D_PlayerWidget.generated.h"

/**
 * 
 */
UCLASS()
class LI2D_API ULI2D_PlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	TObjectPtr<class ALI2D_GameStateBase> GameStateRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	TObjectPtr<class ALI2DCharacter> PlayerRef;
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void SetTimeToWidget(FText& NewTimeToDisplay);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void GetUpdateWidget(bool& ShouldUpdate) { ShouldUpdate = bUpdateWidget; }

	void SetPlayerRef(TObjectPtr<ALI2DCharacter> PlayerRefIn);
private:
	bool bUpdateWidget = false;
	FText TimeAsText;
	
	UFUNCTION()
	void UpdateInGameTimeText(FText NewTimeIn);
	
};
