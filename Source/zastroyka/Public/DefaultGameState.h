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
	void ToggleBuildMode(bool _IsBuildModeEnabled);

	int16 ConvertCoordinateToIndex(int16 _i, int16 _j);

	class APlayerPawn* GetPlayerRef();

	TArray<FTile*> Tiles;

	int16 XMapSize, YMapSize;
	bool IsBuildModeEnabled;

	FPaperTileInfo TileInfo;
	void UpdateTileMap(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord);
	TArray<bool> BuildingMap;
	bool IsBuildingMapRestricted;

	class UPaperTileMapComponent* MainTilemapComponent;
	class UPaperTileSet* DefaultTileset;
	
};