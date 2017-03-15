// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Peliohjelmointi1.h"
#include "Peliohjelmointi1GameMode.h"
#include "Peliohjelmointi1Character.h"

APeliohjelmointi1GameMode::APeliohjelmointi1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
