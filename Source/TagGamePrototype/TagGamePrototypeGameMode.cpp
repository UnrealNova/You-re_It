// Copyright Epic Games, Inc. All Rights Reserved.

#include "TagGamePrototypeGameMode.h"
#include "TagGamePrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATagGamePrototypeGameMode::ATagGamePrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
