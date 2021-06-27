// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TimeLineSplitTrigger.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FTimeLineSplitDelegate, ETimeLine, MainSplitTimeLine);

// This class does not need to be modified.
UINTERFACE()
class UTimeLineSplitTrigger : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POINTOFDIVARICATION_API ITimeLineSplitTrigger
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void InitSplitTrigger(AActor* Owner, const FTimeLineSplitDelegate& CallTimeLineSplit);
};
