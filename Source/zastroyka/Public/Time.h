// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Time.generated.h"


UENUM()
enum TimeMode { PAUSE, SLOW, NORMAL, FAST };

UCLASS()
class ZASTROYKA_API ATime : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATime();
	ATime(unsigned short _Day, unsigned short _Month, unsigned short _Year);
	void Play();
	void Faster();
	void Slower();
	UPROPERTY()
	TEnumAsByte<TimeMode> CurrentTimeMode;
	unsigned short Day, Month, Year;

	UPROPERTY()
	class UTimelineComponent* TimeTimeline;

	void TimelineTick();

	class ADefaultGameState* GameStateRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
