// Fill out your copyright notice in the Description page of Project Settings.


#include "EventBase.h"

UEventBase::UEventBase()
{
	
}

//bool UEventBase::IsReadyToExecute()
//{
//	return true;
//}

void UEventBase::Execute()
{
	
}

void UEventBase::Initialize(FString _Name, FString _Description, FStat _ChangedStat, float _AppearChance)
{
	Name = _Name;
	Description = _Description;
	ChangedStat = _ChangedStat;
	AppearChance = _AppearChance;
}

float UEventBase::GetAppearChance()
{
	return AppearChance;
}
