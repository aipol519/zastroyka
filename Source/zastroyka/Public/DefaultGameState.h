// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FTile.h"

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DefaultGameState.generated.h"

UCLASS()
class ZASTROYKA_API ADefaultGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	ADefaultGameState();

	void SetDefaultTiles();
	void EnableBuildMode();
	void DisableBuildMode();

	int16 ConvertCoordinateToIndex(int16 _i, int16 _j);

	class APlayerPawn* GetPlayerRef();

	TArray<FTile*> Tiles;

	int16 XMapSize, YMapSize;
	bool IsBuildModeEnabled;

	class UPaperTileMapComponent* MainTilemapComponent;
	class UPaperTileSet* DefaultTileset;
	
};
