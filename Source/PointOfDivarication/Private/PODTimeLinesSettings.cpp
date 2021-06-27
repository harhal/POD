#include "PODTimeLinesSettings.h"

#include "Algo/Transform.h"

ECollisionChannel UPODTimeLinesSettings::ConvertCollisionChannel(ECollisionChannel CollisionChannel, ETimeLine TimeLine) const
{
	if (NonconvertibleChannels.Contains(CollisionChannel))
	{
		return ECC_MAX;
	}
	
	if (ChannelsConversions.Contains(CollisionChannel))
	{
		return ConvertTimeLineChannel(ChannelsConversions[CollisionChannel], TimeLine);
	}
	
	const FTimeLineCollisionConversion* Transition = TimeLineCollisionConversions.FindByPredicate(
		[CollisionChannel](const FTimeLineCollisionConversion& TimeLineCollisionTransition)
	{
		return CollisionChannel == ConvertTimeLineChannel(TimeLineCollisionTransition, ETimeLine::Synchronous) ||
			CollisionChannel == ConvertTimeLineChannel(TimeLineCollisionTransition, ETimeLine::TimeLineA)||
			CollisionChannel == ConvertTimeLineChannel(TimeLineCollisionTransition, ETimeLine::TimeLineB);
	});
	
	if (!Transition)
	{
		NonconvertibleChannels.Add(CollisionChannel);
		return ECC_MAX;
	}
	
	ChannelsConversions.Add(CollisionChannel, *Transition);
	
	return ConvertTimeLineChannel(*Transition, TimeLine);
}

TArray<ECollisionChannel> UPODTimeLinesSettings::CollectTimeLineChannels(ETimeLine TimeLine) const
{
	TArray<ECollisionChannel> TimeLineChannels;
	Algo::Transform(TimeLineCollisionConversions, TimeLineChannels,
		[TimeLine](const FTimeLineCollisionConversion& TimeLineCollisionConversion)
		{
			return ConvertTimeLineChannel(TimeLineCollisionConversion, TimeLine);
		});

	return TimeLineChannels;
}

ECollisionChannel UPODTimeLinesSettings::ConvertTimeLineChannel(const FTimeLineCollisionConversion& TimeLineCollisionConversion, ETimeLine TimeLine)
{
	switch (TimeLine)
	{
	case ETimeLine::Synchronous:
		return TimeLineCollisionConversion.Synchronous_CollisionChannel;
	case ETimeLine::TimeLineA:
		return TimeLineCollisionConversion.TimeLineA_CollisionChannel;
	case ETimeLine::TimeLineB:
		return TimeLineCollisionConversion.TimeLineB_CollisionChannel;
	default:
		return ECC_MAX;
	}
}
