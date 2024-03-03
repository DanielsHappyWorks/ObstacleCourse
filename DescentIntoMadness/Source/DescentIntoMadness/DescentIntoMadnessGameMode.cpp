// Copyright Epic Games, Inc. All Rights Reserved.

#include "DescentIntoMadnessGameMode.h"
#include "DescentIntoMadnessCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADescentIntoMadnessGameMode::ADescentIntoMadnessGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
