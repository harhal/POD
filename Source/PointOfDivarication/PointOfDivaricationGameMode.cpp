// Copyright Epic Games, Inc. All Rights Reserved.

#include "PointOfDivaricationGameMode.h"
#include "PointOfDivaricationHUD.h"
#include "PointOfDivaricationCharacter.h"
#include "UObject/ConstructorHelpers.h"

APointOfDivaricationGameMode::APointOfDivaricationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APointOfDivaricationHUD::StaticClass();
}
