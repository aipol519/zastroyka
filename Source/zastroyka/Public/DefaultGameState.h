// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FTile.h"
#include "FBuilding.h"

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
	void SetDefaultBuildings();
	void SelectBuilding(FString _BuildingID);
	void ToggleBuildMode(bool _IsBuildModeEnabled);

	int16 ConvertCoordinateToIndex(int16 _i, int16 _j);

	class APlayerPawn* GetPlayerRef();

	TArray<FTile*> Tiles;
	TMap<FString, FBuilding*> Buildings;

	FBuilding* SelectedBuilding;

	int16 XMapSize, YMapSize;
	bool IsBuildModeEnabled;

	FPaperTileInfo TileInfo;
	void MoveSelectionZone(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord);
	int16 BuildingLength, BuildingWidth;
	bool IsBuildingMapRestricted;

	void RefreshConnectionMap();
	void CheckTileConnection(int16 _XTileCoord, int16 _YTileCoord);
	int16 temp;

	void Action(int16 _XTileCoord, int16 _YTileCoord);
	void PlaceBuilding(int16 _XTileCoord, int16 _YTileCoord);

	class UPaperTileMapComponent* MainTilemapComponent;
	class UPaperTileSet* DefaultTileset;
	
};
