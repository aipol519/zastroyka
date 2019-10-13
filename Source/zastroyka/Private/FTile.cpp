// Fill out your copyright notice in the Description page of Project Settings.

#include "FTile.h"

FTile::FTile()
{


}

FTile::FTile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo)
{
	XTileCoord = _XTileCoord;
	YTileCoord = _YTileCoord;
	TileInfo = _TileInfo;

	IsBuildingAllowed = true;

}

FPaperTileInfo FTile::GetTileInfo()
{
	return TileInfo;

}

void FTile::ChangeInBuildMode(UPaperTileMapComponent * _MainTilemapComponent, bool _BuildFlag)
{
	FPaperTileInfo TempTileInfo;
	TempTileInfo.TileSet = TileInfo.TileSet;

	if (_BuildFlag)
	{
		if (IsBuildingAllowed)
		{
			TempTileInfo.PackedTileIndex = 2;
		}
		else
		{
			TempTileInfo.PackedTileIndex = 3;
		}
		_MainTilemapComponent->SetTile(XTileCoord, YTileCoord, 0, TempTileInfo);
	}
	else
	{
		TempTileInfo = TileInfo;
		_MainTilemapComponent->SetTile(XTileCoord, YTileCoord, 0, TempTileInfo);
	}

}