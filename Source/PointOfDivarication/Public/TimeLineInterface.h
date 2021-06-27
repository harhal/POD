// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TimeLine.h"
#include "UObject/Interface.h"
#include "TimeLineInterface.generated.h"

UINTERFACE()
class UTimeLineInterface : public UInterface
{
	GENERATED_BODY()
};

class POINTOFDIVARICATION_API ITimeLineInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ETimeLine GetTimeLine() const;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetTimeLine(ETimeLine SetTimeLine);
};
