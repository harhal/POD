// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Portable.h"
#include "TimeLine.h"
#include "Components/ActorComponent.h"
#include "CarryProcessor.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class POINTOFDIVARICATION_API UCarryProcessor : public UActorComponent
{
	GENERATED_BODY()

public:
	UCarryProcessor();
	
	UFUNCTION(BlueprintCallable)
	void ProcessInput(const FTransform& Input);
	
	void StartCarry(TScriptInterface<IPortable> PortableItem);
	
	void StopCarry();

	UPROPERTY(EditDefaultsOnly)
	float SearchDistance;

	UPROPERTY(EditDefaultsOnly)
	FVector CarryOffset;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<ETimeLine, TEnumAsByte<ECollisionChannel>> TraceCollisionChannels;

	TScriptInterface<IPortable> CarryingItem;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
