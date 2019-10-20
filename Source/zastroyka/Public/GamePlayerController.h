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
	virtual void SetupInputComponent() override;

public:

	AGamePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	void RightMouseButtonDownOnce();
	void RightMouseButtonUp();

	void RightMouseButtonDownContinious(float _Value);

	bool IsMouseMoving();

	FVector MouseWorldPosition;

	FVector2D MouseStartScreenPosition;
	FVector2D MouseCurrentScreenPosition;

	FHitResult HitResult;
	int16 XTileCoord, YTileCoord;

	class ADefaultGameState* DefaultGameStateRef;

};
