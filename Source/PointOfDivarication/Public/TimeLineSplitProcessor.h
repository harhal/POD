// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "TimeLine.h"
#include "Components/ActorComponent.h"
#include "TimeLineSplitProcessor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POINTOFDIVARICATION_API UTimeLineSplitProcessor : public UActorComponent
{
	GENERATED_BODY()

public:
	UTimeLineSplitProcessor();

	UFUNCTION()
	void OnTimeLineSplitTriggered(ETimeLine MainSplitTimeLine);

private:
	virtual void InitializeComponent() override;
	
	UPROPERTY(EditDefaultsOnly, meta = (MustImplement = TimeLineSplitTrigger))
	TArray<TSubclassOf<UObject>> TriggersClasses;

	TArray<TScriptInterface<class ITimeLineSplitTrigger>> Triggers;
};
