// Fill out your copyright notice in the Description page of Project Settings.

#include "Time.h"
#include "HUDWidgetUMG.h"
#include "DefaultGameState.h"
#include "Engine/Engine.h"

// Sets default values
UTime::UTime()
{
	HUDWidgetRef = nullptr;
	DefaultGameStateRef = nullptr;
	DayOfWeek = 0;
	Day = 0;
	Month = 0;
	Year = 0;
	CurrentTimeMode = NORMAL;
	PreviousTimeMode = NORMAL;
}

void UTime::TimeTick()
{
	UpdateDate();
	HUDWidgetRef->UpdateVisibleDate();
	DefaultGameStateRef->CheckEvents();
}

void UTime::SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef)
{
	HUDWidgetRef = _HUDWidgetRef;
	HUDWidgetRef->UpdateVisibleStat();
	HUDWidgetRef->UpdateVisibleDate();
}

void UTime::Initialize()
{;
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());
	DayOfWeek = 1;
	Day = 1;
	Month = 1;
	Year = 1960;
	CurrentTimeMode = NORMAL;
	
	DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 1.0f, true);

	//Play();
}

TimeMode UTime::GetCurrentTimeMode()
{
	return CurrentTimeMode;
}

void UTime::UpdateDate()
{
	switch (Month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (Day < 31)
		{
			++Day;
		}
		else
		{
			++Month;
			Day = 1;
		}
		break;
	case 2:
		if ((div(Year, 400).rem == 0) || ((div(Year, 100).rem != 0) && (div(Year, 4).rem == 0)))
		{
			if (Day < 29)
			{
				++Day;
			}
			else
			{
				++Month;
				Day = 1;
			}
		}
		else
		{
			if (Day < 28)
			{
				++Day;
			}
			else
			{
				++Month;
				Day = 1;
			}
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (Day < 30)
		{
			++Day;
		}
		else
		{
			++Month;
			Day = 1;
		}
		break;
	default:
		++Year;
		Month = 1;
		Day = 1;
		break;
	}
	if (DayOfWeek < 7)
	{
		++DayOfWeek;
	}
	else
	{
		DayOfWeek = 1;
		DefaultGameStateRef->UpdateStat();
		HUDWidgetRef->UpdateVisibleStat();
	}
}

void UTime::Play()
{
	switch (CurrentTimeMode)
	{
	case NORMAL:
	case SLOW:
	case FAST:
		PreviousTimeMode = CurrentTimeMode;
		CurrentTimeMode = PAUSE;
		DefaultGameStateRef->WorldRef->GetTimerManager().PauseTimer(TimerHandle);
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Pause");
		break;
	case PAUSE:
		CurrentTimeMode = PreviousTimeMode;
		switch (CurrentTimeMode)
		{
		case NORMAL:
			DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 1.0f, true);
			//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Normal");
			break;
		case SLOW:
			DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 3.0f, true);
			//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Slow");
			break;
		case FAST:
			DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 0.3f, true);
			//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Fast");
		default:
			break;
		}
		break;
	default:
		break;
	}

	HUDWidgetRef->SetTimeButtonsStyle();
}

void UTime::Slower()
{
	switch (CurrentTimeMode)
	{
	case FAST:
		CurrentTimeMode = NORMAL;
		DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 1.0f, true);
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Normal");
		break;
	case NORMAL:
		CurrentTimeMode = SLOW;
		DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 3.0f, true);
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Slow");
	case SLOW:
	default:
		break;
	}

	HUDWidgetRef->SetTimeButtonsStyle();
}

void UTime::Faster()
{
	switch (CurrentTimeMode)
	{
	case SLOW:
		CurrentTimeMode = NORMAL;
		DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 1.0f, true);
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Normal");
		break;
	case NORMAL:
		CurrentTimeMode = FAST;
		DefaultGameStateRef->WorldRef->GetTimerManager().SetTimer(TimerHandle, this, &UTime::TimeTick, 0.3f, true);
		//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Fast");
	case FAST:
	default:
		break;
	}

	HUDWidgetRef->SetTimeButtonsStyle();
}

int16 UTime::GetDay()
{
	return Day;
}

int16 UTime::GetMonth()
{
	return Month;
}

int16 UTime::GetYear()
{
	return Year;
}

int16 UTime::GetDayOfWeek()
{
	return DayOfWeek;
}