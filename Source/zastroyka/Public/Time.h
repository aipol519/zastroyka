// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Time.generated.h"

enum TimeMode { PAUSE, SLOW, NORMAL, FAST };

UCLASS()
class ZASTROYKA_API UTime : public UObject
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	UTime();
public:
	void Play();
	void Faster();
	void Slower();

	void SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef);
	void Initialize();

	void UpdateDate();

	TEnumAsByte<TimeMode> CurrentTimeMode;
	unsigned short Day, Month, Year;

	FTimerHandle TimerHandle;
	
	void TimeTick();

	class UWorld* WorldRef;
	class ADefaultGameState* DefaultGameStateRef;
	class UHUDWidgetUMG* HUDWidgetRef;
};
