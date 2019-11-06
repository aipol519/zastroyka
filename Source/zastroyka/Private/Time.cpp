// Fill out your copyright notice in the Description page of Project Settings.


#include "Time.h"

Time::Time(unsigned short _Day, unsigned short _Month, unsigned short _Year)
{
	Day = _Day;
	Month = _Month;
	Year = _Year;
	CurrentTimeMode = NORMAL;

	//GameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	TimeTimeline = NewObject<UTimelineComponent>();
	TimeTimeline->CreationMethod = EComponentCreationMethod::Native;

	TimeTimeline->SetLooping(true);
	TimeTimeline->SetTimelineLength(1.0f);
	TimeTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);

	FOnTimelineEvent TimelineEvent;
	TimelineEvent.BindUFunction(TimeTimeline, FName("TimelineTick"));

	TimeTimeline->AddEvent(0.0f, TimelineEvent);

	TimeTimeline->SetPlaybackPosition(0.0f, false);
	TimeTimeline->SetPlayRate(1.0f);

	Play();
}

Time::~Time()
{
}

void Time::TimelineTick()
{

}

void Time::Play()
{
	switch (CurrentTimeMode)
	{
	case NORMAL:
		CurrentTimeMode = PAUSE;
		TimeTimeline->Stop();
		break;
	case SLOW:
	case FAST:
		CurrentTimeMode = NORMAL;
		TimeTimeline->SetPlayRate(1.0f);
		break;
	case PAUSE:
		CurrentTimeMode = NORMAL;
		TimeTimeline->Play();
		break;
	}
}

void Time::Slower()
{
	switch (CurrentTimeMode)
	{
	case SLOW:
		CurrentTimeMode = NORMAL;
		TimeTimeline->SetPlayRate(1.0f);
		break;
	case NORMAL:
	case FAST:
		CurrentTimeMode = SLOW;
		TimeTimeline->SetPlayRate(0.3f);
	default:
		break;
	}
}

void Time::Faster()
{
	switch (CurrentTimeMode)
	{
	case FAST:
		CurrentTimeMode = NORMAL;
		TimeTimeline->SetPlayRate(1.0f);
		break;
	case NORMAL:
	case SLOW:
		CurrentTimeMode = FAST;
		TimeTimeline->SetPlayRate(3.0f);
	default:
		break;
	}
}