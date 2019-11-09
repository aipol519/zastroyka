// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "zastroykaGameModeBase.generated.h"

UCLASS()
class ZASTROYKA_API AzastroykaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AzastroykaGameModeBase();

	virtual void Tick(float DeltaSeconds) override;
	
	class ADefaultGameState* DefaultGameStateRef;

};
