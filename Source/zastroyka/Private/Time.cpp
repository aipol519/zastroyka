// Fill out your copyright notice in the Description page of Project Settings.


#include "Time.h"
#include "HUDWidgetUMG.h"
#include "Components/TimelineComponent.h"
#include "DefaultGameState.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
UTime::UTime()
{

}

void UTime::TimelineTick()
{
	DefaultGameStateRef->UpdateStat();
	HUDWidgetRef->UpdateVisibleStat();
}

void UTime::SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef)
{


	HUDWidgetRef = _HUDWidgetRef;
	TimelineTick();
}

void UTime::Initialize()
{
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());
	Day = 1;
	Month = 1;
	Year = 1950;
	CurrentTimeMode = NORMAL;

	GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 1.0f, true);
	
	//TimeTimeline = NewObject<UTimelineComponent>(this, FName("TimeTimeLine"));
	//TimeTimeline->CreationMethod = EComponentCreationMethod::Native;

	//TimeTimeline->SetLooping(true);
	//TimeTimeline->SetTimelineLength(1.0f);
	//TimeTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);

	//FOnTimelineEvent TimelineEvent;
	//TimelineEvent.BindUFunction(UGameplayStatics::GetGameMode(GetWorld()), FName("TimelineTick"));

	//TimeTimeline->AddEvent(0.0f, TimelineEvent);

	//TimeTimeline->SetPlaybackPosition(0.0f, false);
	//TimeTimeline->SetPlayRate(1.0f);
	//
	//
	//TimeTimeline->PlayFromStart();
}



void UTime::Play()
{
	switch (CurrentTimeMode)
	{
	case NORMAL:
		CurrentTimeMode = PAUSE;
		GetWorld()->GetTimerManager().ClearTimer(TimeTimer);
		break;
	case SLOW:
	case FAST:
		CurrentTimeMode = NORMAL;
		GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 1.0f, true);
		break;
	case PAUSE:
		CurrentTimeMode = NORMAL;
		GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 1.0f, true);
		break;
	}
}

void UTime::Slower()
{
	switch (CurrentTimeMode)
	{
	case SLOW:
		CurrentTimeMode = NORMAL;
		GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 1.0f, true);
		break;
	case NORMAL:
	case FAST:
		CurrentTimeMode = SLOW;
		GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 3.0f, true);
	default:
		break;
	}
}

void UTime::Faster()
{
	switch (CurrentTimeMode)
	{
	case FAST:
		CurrentTimeMode = NORMAL;
		GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 1.0f, true);
		break;
	case NORMAL:
	case SLOW:
		CurrentTimeMode = FAST;
		GetWorld()->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimelineTick, 0.3f, true);
	default:
		break;
	}
}