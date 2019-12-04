// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DefaultGameState.h"

#include "UObject/NoExportTypes.h"
#include "EventBase.generated.h"

/**
 * 
 */
UCLASS()
class ZASTROYKA_API UEventBase : public UObject
{
	GENERATED_BODY()

public:
	
	UEventBase();

	//UFUNCTION()
	//bool IsReadyToExecute();

	UFUNCTION()
	void Initialize(FString _Name, FString _Description, FStat _ChangedStat, float _AppearChance);
	
	UFUNCTION()
	void Execute();

	UFUNCTION()
	float GetAppearChance();
	
private:
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	FStat ChangedStat;
	
	UPROPERTY()
	float AppearChance;

	UPROPERTY()
	ADefaultGameState* _DefaultGameStateRef;
	
};
