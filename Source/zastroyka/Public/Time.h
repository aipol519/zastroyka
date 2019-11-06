// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"

enum TimeMode { PAUSE, SLOW, NORMAL, FAST };

/**
 * 
 */
class ZASTROYKA_API Time
{
public:
	Time(unsigned short _Day, unsigned short _Month, unsigned short _Year);
	~Time();
	void Play();
	void Faster();
	void Slower();
	TimeMode CurrentTimeMode;
	unsigned short Day, Month, Year;
	
	UPROPERTY()
	class UTimelineComponent* TimeTimeline;
	
	void TimelineTick();

	class ADefaultGameState* GameStateRef;
};
