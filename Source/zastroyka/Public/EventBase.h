// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	UFUNCTION()
	bool IsReadyToExecute();

	UFUNCTION()
	void Execute();

	FFloat16 AppearChance;
};
