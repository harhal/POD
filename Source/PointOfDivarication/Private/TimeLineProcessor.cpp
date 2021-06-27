// Fill out your copyright notice in the Description page of Project Settings.

#include "TimeLineProcessor.h"

void UTimeLineProcessor::SetTimeLine(ETimeLine TimeLine)
{
	const UPODTimeLinesSettings* TimeLinesSettings = GetDefault<UPODTimeLinesSettings>();

	GetOwner()->ForEachComponent<UPrimitiveComponent>(true,
		[TimeLine, TimeLinesSettings](UPrimitiveComponent* PrimitiveComponent)
	{
		const ECollisionChannel PrevCollisionChannel = PrimitiveComponent->BodyInstance.GetObjectType();
		const ECollisionChannel NewCollisionChannel = TimeLinesSettings->ConvertCollisionChannel(PrevCollisionChannel, TimeLine);

		if (NewCollisionChannel == ECC_MAX)
		{
			return;
		}
			
		PrimitiveComponent->BodyInstance.SetObjectType(NewCollisionChannel);

		for (const FTimeLineCollisionConversion& TimeLineCollisionConversion : TimeLinesSettings->TimeLineCollisionConversions)
		{
			PrimitiveComponent->BodyInstance.SetResponseToChannel(TimeLineCollisionConversion.TimeLineA_CollisionChannel, TimeLine == ETimeLine::TimeLineB ? ECR_Ignore : ECR_Block);
			PrimitiveComponent->BodyInstance.SetResponseToChannel(TimeLineCollisionConversion.TimeLineB_CollisionChannel, TimeLine == ETimeLine::TimeLineA ? ECR_Ignore : ECR_Block);
		}		
	});
	
	CurrentTimeLine = TimeLine;
}

ETimeLine UTimeLineProcessor::GetTimeLine() const
{
	return CurrentTimeLine;
}
