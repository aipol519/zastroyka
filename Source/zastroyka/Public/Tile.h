// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileSet.h"
#include "UObject/NoExportTypes.h"
#include "Tile.generated.h"

UENUM()
enum ETileType { GREEN_TILE, ROAD_TILE, BUILDING_ALLOWED_TILE, BUILDING_RESTRICTED_TILE, BUILDING_SELECTABLE_TILE };

UCLASS()
class ZASTROYKA_API UTile : public UObject
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	UTile();
	//ATile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected);

	void ChangeInBuildDestroyMode(UPaperTileMapComponent* _MainTilemapComponent, bool _BuildFlag);

	UPROPERTY()
	FPaperTileInfo TileInfo;
	FPaperTileInfo GetTileInfo();

	void Initialize(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected);

	void PlaceRoad(int16 _XTileCoord, int16 _YTileCoord);
	
	FPaperTileInfo SetTileInfoIndex(int _Index);

	UPROPERTY()
	bool IsTileConnected;

	UPROPERTY()
	int16 XTileCoord;

	UPROPERTY()
	int16 YTileCoord;

	UPROPERTY()
	TEnumAsByte<ETileType> TileType;
};
