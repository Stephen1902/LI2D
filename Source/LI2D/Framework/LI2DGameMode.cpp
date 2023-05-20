// Copyright Epic Games, Inc. All Rights Reserved.

#include "LI2DGameMode.h"
#include "../Player/LI2DCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALI2DGameMode::ALI2DGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
