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

	UFUNCTION()
	void RightMouseButtonDownOnce();

	UFUNCTION()
	void RightMouseButtonUp();

	UFUNCTION()
	void RightMouseButtonDownContinious(float _Value);

	UFUNCTION()
	bool IsMouseMoving();

	UFUNCTION()
	void LeftMouseButtonDownOnce();

	UFUNCTION()
	void LeftMouseButtonUp();

	UFUNCTION()
	void LeftMouseButtonDownContinious(float _Value);

	UFUNCTION()
	int16 GetMouseXCoord();

	UFUNCTION()
	int16 GetMouseYCoord();

private:
	
	UPROPERTY()
	FVector MouseWorldPosition;

	UPROPERTY()
	FVector2D MouseStartScreenPosition;

	UPROPERTY()
	FVector2D MouseCurrentScreenPosition;

	UPROPERTY()
	FHitResult HitResult;

	UPROPERTY()
	int16 XTileCoord;

	UPROPERTY()
	int16 YTileCoord;

	UPROPERTY()
	int16 PrevXTileCoord;

	UPROPERTY()
	int16 PrevYTileCoord;

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

};
