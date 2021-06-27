// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "PODTimeLinesSettings.h"
#include "Components/ActorComponent.h"
#include "TimeLineProcessor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class POINTOFDIVARICATION_API UTimeLineProcessor : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetTimeLine(ETimeLine TimeLine);

	UFUNCTION(BlueprintPure)
	ETimeLine GetTimeLine() const;

private:
	UPROPERTY()
	ETimeLine CurrentTimeLine = ETimeLine::Synchronous;

	UPROPERTY()
	TArray<UPrimitiveComponent*> CachedOwnCollisions;
};
