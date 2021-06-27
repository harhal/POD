// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TimeLine.h"
#include "Engine/DeveloperSettings.h"
#include "PODTimeLinesSettings.generated.h"

USTRUCT()
struct FTimeLineCollisionConversion
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> Synchronous_CollisionChannel;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TimeLineA_CollisionChannel;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> TimeLineB_CollisionChannel;
};

UCLASS(config=PODTimeLines, defaultconfig, meta=(DisplayName="TimeLines"))
class POINTOFDIVARICATION_API UPODTimeLinesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:	
	UPROPERTY(Config, EditAnywhere, Category=Timelines)
	TArray<FTimeLineCollisionConversion> TimeLineCollisionConversions;

	ECollisionChannel ConvertCollisionChannel(ECollisionChannel CollisionChannel, ETimeLine TimeLine) const;

private:
	mutable TMap<ECollisionChannel, FTimeLineCollisionConversion> ChannelsConversions;

	mutable TSet<ECollisionChannel> NonconvertibleChannels;
	
	TArray<ECollisionChannel> CollectTimeLineChannels(ETimeLine TimeLine) const;

	static ECollisionChannel ConvertTimeLineChannel(const FTimeLineCollisionConversion& TimeLineCollisionConversion,
	                                            ETimeLine TimeLine);
};