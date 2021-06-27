// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PointOfDivaricationHUD.generated.h"

UCLASS()
class APointOfDivaricationHUD : public AHUD
{
	GENERATED_BODY()

public:
	APointOfDivaricationHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

