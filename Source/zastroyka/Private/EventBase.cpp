// Fill out your copyright notice in the Description page of Project Settings.


#include "EventBase.h"

#include "EventWigdetUMG.h"
#include "HUDWidgetUMG.h"
#include "Time.h"
#include "Engine/Engine.h"

UEventBase::UEventBase()
{
	
}

//bool UEventBase::IsReadyToExecute()
//{
//	return true;
//}

void UEventBase::Execute()
{
	EventWidgetRef->ShowUp(this);
	CurrentTimeRef->Play();
}

void UEventBase::ReadingEventDone()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Reading Event Done");
	if (Name.Contains("Game Tip") || Name == "Welcome to ZASTROYKA")
	{
		AppearChance = 0.0f;
	}
	else
	{
		//some stuff
	}
	
	//end game test
	if (Name == "test6")
	{
		DefaultGameStateRef->CurrentStat.Money -= 1;
		DefaultGameStateRef->CheckEndGameState();
	}

	CurrentTimeRef->Play();
	HUDWidgetRef->UpdateVisibleStat();
}

void UEventBase::Initialize(FString _Name, FString _Description, FStat _ChangedStat, float _AppearChance, ADefaultGameState* _DefaultGameStateRef)
{
	Name = _Name;
	Description = _Description;
	ChangedStat = _ChangedStat;
	AppearChance = _AppearChance;
	DefaultGameStateRef = _DefaultGameStateRef;
	//
	EventWidgetRef = DefaultGameStateRef->EventWidgetRef;
	HUDWidgetRef = DefaultGameStateRef->HUDWidgetRef;
	CurrentTimeRef = DefaultGameStateRef->CurrentTimeRef;
}

float UEventBase::GetAppearChance()
{
	return AppearChance;
}

FString UEventBase::GetName()
{
	return Name;
}

FString UEventBase::GetDescription()
{
	return Description;
}