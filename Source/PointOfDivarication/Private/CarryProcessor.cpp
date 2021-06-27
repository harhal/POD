// Fill out your copyright notice in the Description page of Project Settings.


#include "CarryProcessor.h"
#include "DrawDebugHelpers.h"
#include "TimeLineInterface.h"

UCarryProcessor::UCarryProcessor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCarryProcessor::ProcessInput(const FTransform& Input)
{
	if (IsValid(CarryingItem.GetObject()))
	{
		StopCarry();
		return;
	}

	FHitResult HitResult;
	const FVector& StartTracePoint = Input.GetLocation();
	const FVector& EndTracePoint = StartTracePoint + Input.TransformVector(FVector::ForwardVector * SearchDistance);
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams::DefaultQueryParam;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	ETimeLine TimeLine = ITimeLineInterface::Execute_GetTimeLine(GetOwner());
	ECollisionChannel TraceCollisionChannel = TraceCollisionChannels[TimeLine];
	
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTracePoint, EndTracePoint, TraceCollisionChannel, CollisionQueryParams);

	if (HitResult.Distance < 0 || HitResult.Distance > SearchDistance)
	{
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor))
	{
		return;
	}

	if (!HitActor->Implements<UPortable>())
	{
		return;
	}
	
	StartCarry(HitActor);
}

void UCarryProcessor::StartCarry(TScriptInterface<IPortable> PortableItem)
{
	CarryingItem = PortableItem;
	IPortable::Execute_SetCarryState(CarryingItem.GetObject(), GetOwner(), true);
}

void UCarryProcessor::StopCarry()
{
	IPortable::Execute_SetCarryState(CarryingItem.GetObject(), GetOwner(), false);
	CarryingItem = nullptr;
}

// Called every frame
void UCarryProcessor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(CarryingItem.GetObject()))
	{
		return;
	}

	const ETimeLine OwnerTimeLine = ITimeLineInterface::Execute_GetTimeLine(GetOwner());
	const ETimeLine ObjectTimeLine = ITimeLineInterface::Execute_GetTimeLine(CarryingItem.GetObject());
	if (OwnerTimeLine != ETimeLine::Synchronous && ObjectTimeLine != ETimeLine::Synchronous && OwnerTimeLine != ObjectTimeLine)
	{
		StopCarry();
		return;
	}

	FTransform CarryPointTransform = GetOwner()->GetTransform();
	CarryPointTransform.SetLocation(CarryPointTransform.GetLocation() + CarryPointTransform.Rotator().RotateVector(CarryOffset));

	IPortable::Execute_Carry(CarryingItem.GetObject(), GetOwner(), CarryPointTransform);
}

