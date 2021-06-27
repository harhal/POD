// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeLineSplitProcessor.h"

#include "TimeLineInterface.h"
#include "TimeLineSplitTrigger.h"

UTimeLineSplitProcessor::UTimeLineSplitProcessor()
{
	bWantsInitializeComponent = true;
}

void UTimeLineSplitProcessor::InitializeComponent()
{
	Super::InitializeComponent();

	if (!ensureAlways(GetOwner()->Implements<UTimeLineInterface>()))
	{
		return;
	}
		
	FTimeLineSplitDelegate OnTimeLineSplitTriggered;
	OnTimeLineSplitTriggered.BindDynamic(this, &UTimeLineSplitProcessor::OnTimeLineSplitTriggered);

	for (const TSubclassOf<UObject>& TriggerClass : TriggersClasses)
	{
		TScriptInterface<ITimeLineSplitTrigger> Trigger = NewObject<UObject>(this, TriggerClass);
		ITimeLineSplitTrigger::Execute_InitSplitTrigger(Trigger.GetObject(), GetOwner(), OnTimeLineSplitTriggered);
	}
}

void UTimeLineSplitProcessor::OnTimeLineSplitTriggered(ETimeLine MainSplitTimeLine)
{
	if (ITimeLineInterface::Execute_GetTimeLine(GetOwner()) != ETimeLine::Synchronous)
	{
		return;
	}

	const FTransform& ObjectTransform = GetOwner()->GetTransform();

	ITimeLineInterface::Execute_SetTimeLine(GetOwner(), MainSplitTimeLine);

	UWorld* World = GetWorld();
	
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Template = GetOwner();
	ActorSpawnParameters.bDeferConstruction = true;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* Clone = World->SpawnActor<AActor>(GetOwner()->GetClass(), ActorSpawnParameters);

	const ETimeLine SecondSplitTimeLine = MainSplitTimeLine == ETimeLine::TimeLineA ? ETimeLine::TimeLineB : ETimeLine::TimeLineA;
	
	ITimeLineInterface::Execute_SetTimeLine(Clone, SecondSplitTimeLine);

	Clone->FinishSpawning(ObjectTransform);
	
	ITimeLineInterface::Execute_SetTimeLine(Clone, SecondSplitTimeLine);

	Clone->SetActorTransform(ObjectTransform);
}
