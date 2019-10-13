// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

UCLASS()
class ZASTROYKA_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AGamePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	void EnableBuildMode();
	void DisableBuildMode();
	
	FVector MouseWorldPosition;
	FString TestOutput;
	FHitResult HitResult;
	int16 XTileCoord, YTileCoord;

	class ADefaultGameState* DefaultGameStateRef;

};
