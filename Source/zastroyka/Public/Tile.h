// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileSet.h"
#include "UObject/NoExportTypes.h"
#include "Tile.generated.h"

UENUM()
enum ETileType { GREEN_TILE, ROAD_TILE, BUILDING_SELECTABLE_TILE, BUILDING_RESTRICTED_TILE, BUILDING_ALLOWED_TILE
};

UCLASS()
class ZASTROYKA_API UTile : public UObject
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	UTile();

	UFUNCTION()
	void ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, const bool& _BuildFlag);

	UPROPERTY()
	FPaperTileInfo TileInfo;

	UFUNCTION()
	FPaperTileInfo GetTileInfo();

	UFUNCTION()
	void Initialize(const int16& _XCoord, const int16& _YCoord, const int16& _TileMapIndex, const FPaperTileInfo _TileInfo, const ETileType& _Type);

	UFUNCTION()
	void PlaceRoad(TArray<UTile*> _Tiles, UPaperTileMapComponent* _MainTilemapComponent);

	UFUNCTION()
	void DemolishRoad(TArray<UTile*> _Tiles, UPaperTileMapComponent* _MainTilemapComponent);
	
	UFUNCTION()
	FPaperTileInfo SetTileInfoIndex(int _Index);

	UPROPERTY()
	bool IsConnected;

	UPROPERTY()
	int16 XCoord;

	UPROPERTY()
	int16 YCoord;

	UPROPERTY()
	int16 TileMapIndex;

	UPROPERTY()
	TEnumAsByte<ETileType> Type;
};
