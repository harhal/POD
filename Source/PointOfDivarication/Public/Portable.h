// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Portable.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCarryMoveDelegate, AActor*, Instigator);

// This class does not need to be modified.
UINTERFACE()
class UPortable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class POINTOFDIVARICATION_API IPortable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void Carry(AActor* Instigator, const FTransform& CarryPoint);
	
	UFUNCTION(BlueprintNativeEvent)
	void SetCarryState(AActor* Instigator, bool bCarry);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SubscribeOnCarryMove(const FOnCarryMoveDelegate& OnCarryMove);
};
