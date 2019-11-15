// Fill out your copyright notice in the Description page of Project Settings.

#include "Time.h"
#include "HUDWidgetUMG.h"
#include "DefaultGameState.h"

// Sets default values
UTime::UTime()
{
	HUDWidgetRef = nullptr;
	DefaultGameStateRef = nullptr;
}

void UTime::TimeTick()
{
	DefaultGameStateRef->UpdateStat();
	HUDWidgetRef->UpdateVisibleStat();
}

void UTime::SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef)
{
	HUDWidgetRef = _HUDWidgetRef;
	HUDWidgetRef->UpdateVisibleStat();
	HUDWidgetRef->UpdateVisibleIncome();
}

void UTime::Initialize()
{
	WorldRef = GetWorld();
	DefaultGameStateRef = Cast<ADefaultGameState>(WorldRef->GetGameState());
	Day = 1;
	Month = 1;
	Year = 1950;
	CurrentTimeMode = NORMAL;
	
	WorldRef->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimeTick, 1.0f, true);
}



void UTime::Play()
{
	switch (CurrentTimeMode)
	{
	case NORMAL:
		CurrentTimeMode = PAUSE;
		WorldRef->GetTimerManager().PauseTimer(TimeTimer);
		break;
	case SLOW:
	case FAST:
		CurrentTimeMode = NORMAL;
		WorldRef->GetTimerManager().UnPauseTimer(TimeTimer);
		WorldRef->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimeTick, 1.0f, true);
		break;
	case PAUSE:
		CurrentTimeMode = NORMAL;
		WorldRef->GetTimerManager().UnPauseTimer(TimeTimer);
		break;
	}
}

void UTime::Slower()
{
	switch (CurrentTimeMode)
	{
	case SLOW:
		CurrentTimeMode = NORMAL;
		WorldRef->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimeTick, 1.0f, true);
		break;
	case NORMAL:
	case FAST:
		CurrentTimeMode = SLOW;
		WorldRef->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimeTick, 3.0f, true);
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
		WorldRef->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimeTick, 1.0f, true);
		break;
	case NORMAL:
	case SLOW:
		CurrentTimeMode = FAST;
		WorldRef->GetTimerManager().SetTimer(TimeTimer, this, &UTime::TimeTick, 0.3f, true);
	default:
		break;
	}
}