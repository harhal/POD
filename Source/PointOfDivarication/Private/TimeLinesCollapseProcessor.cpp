// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeLinesCollapseProcessor.h"

#include "TimeLineInterface.h"
#include "Kismet/GameplayStatics.h"

void UTimeLinesCollapseProcessor::CollapseTimeLine(ETimeLine MainTimeLine)
{
	TArray<AActor*> TimeLinesActors;
	UGameplayStatics::GetAllActorsWithInterface(this, UTimeLineInterface::StaticClass(), TimeLinesActors);

	for (AActor* Actor : TimeLinesActors)
	{
		const ETimeLine ActorTimeLine = ITimeLineInterface::Execute_GetTimeLine(Actor);

		if (ActorTimeLine == ETimeLine::Synchronous)
		{
			continue;
		}
		
		if (ActorTimeLine != MainTimeLine)
		{
			Actor->Destroy();
		}
		else
		{
			ITimeLineInterface::Execute_SetTimeLine(Actor, ETimeLine::Synchronous);
		}		
	}
}
