// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TimeLine.h"
#include "Components/ActorComponent.h"
#include "TimeLinesCollapseProcessor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POINTOFDIVARICATION_API UTimeLinesCollapseProcessor : public UActorComponent
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void CollapseTimeLine(ETimeLine MainTimeLine);
};
