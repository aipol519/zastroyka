// Fill out your copyright notice in the Description page of Project Settings.


#include "EventBase.h"

#include "EventWigdetUMG.h"
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
	CurrentTimeRef->Play();
	//some stuff for example blocking background there?
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

void UEventBase::SetEventWidgetRef(UEventWigdetUMG* _EventWidgetRef)
{
	EventWidgetRef = _EventWidgetRef;
}

void UEventBase::SetCurrentTimeRef(UTime* _CurrentTimeRef)
{
	CurrentTimeRef = _CurrentTimeRef;
}
