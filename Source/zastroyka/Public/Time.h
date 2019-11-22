// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Time.generated.h"

UENUM()
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

	UPROPERTY()
	TEnumAsByte<TimeMode> CurrentTimeMode;

	UPROPERTY()
	int16 Day;

	UPROPERTY()
	int16 Month;

	UPROPERTY()
	int16 Year;

	UPROPERTY()
	FTimerHandle TimerHandle;
	
	void TimeTick();

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY()
	class UHUDWidgetUMG* HUDWidgetRef;
};
