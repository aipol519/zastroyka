// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileSet.h"

class ZASTROYKA_API FTile
{
public:
	FTile();
	FTile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo);

	void ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, bool _BuildFlag);

	FPaperTileInfo GetTileInfo();

	int16 XTileCoord, YTileCoord;
	bool IsBuildingAllowed;

	FPaperTileInfo TileInfo;

};
