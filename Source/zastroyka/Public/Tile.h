// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileSet.h"
#include "UObject/NoExportTypes.h"
#include "Tile.generated.h"

enum ETileType { GREEN, ROAD, BUILDING_ALLOWED, BUILDING_RESTRICTED, BUILDING_SELECTABLE };

UCLASS()
class ZASTROYKA_API UTile : public UObject
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	UTile();
	//ATile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected);

	void ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, bool _BuildFlag);

	FPaperTileInfo TileInfo;
	FPaperTileInfo GetTileInfo();

	void Initialize(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected);

	FPaperTileInfo SetTileInfoIndex(int _Index);

	bool IsTileConnected;
	int16 XTileCoord;
	int16 YTileCoord;

	TEnumAsByte<ETileType> TileType;
};
