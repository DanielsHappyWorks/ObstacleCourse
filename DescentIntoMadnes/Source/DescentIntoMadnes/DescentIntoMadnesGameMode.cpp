// Copyright Epic Games, Inc. All Rights Reserved.

#include "DescentIntoMadnesGameMode.h"
#include "DescentIntoMadnesCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADescentIntoMadnesGameMode::ADescentIntoMadnesGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
