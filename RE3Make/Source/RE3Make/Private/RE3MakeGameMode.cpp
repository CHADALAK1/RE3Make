// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "RE3Make.h"
#include "RE3MakeGameMode.h"
#include "RE3MakeCharacter.h"

ARE3MakeGameMode::ARE3MakeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
