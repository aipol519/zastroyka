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
	
	UFUNCTION()
	void Play();

	UFUNCTION()
	void Faster();

	UFUNCTION()
	void Slower();

	UFUNCTION()
	void SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef);

	UFUNCTION()
	void Initialize();

	UFUNCTION()
	TimeMode GetCurrentTimeMode();

	UFUNCTION()
	int16 GetDayOfWeek();
	
	UFUNCTION()
	int16 GetDay();

	UFUNCTION()
	int16 GetMonth();

	UFUNCTION()
	int16 GetYear();

private:
	
	UFUNCTION()
	void UpdateDate();

	UPROPERTY()
	TEnumAsByte<TimeMode> CurrentTimeMode;

	UPROPERTY()
	int16 DayOfWeek;
	
	UPROPERTY()
	int16 Day;

	UPROPERTY()
	int16 Month;

	UPROPERTY()
	int16 Year;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UFUNCTION()
	void TimeTick();
	
	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY()
	class UHUDWidgetUMG* HUDWidgetRef;
};
