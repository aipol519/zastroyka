// Fill out your copyright notice in the Description page of Project Settings.

#include "FTile.h"

FTile::FTile()
{

}

FTile::FTile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected)
{
	XTileCoord = _XTileCoord;
	YTileCoord = _YTileCoord;
	TileInfo = _TileInfo;
	TileType = _TileType;
	IsTileConnected = _IsTileConnected;
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
		switch (TileType)
		{
		case GREEN:
			TempTileInfo.PackedTileIndex = 4;
			break;
		case ROAD:
			TempTileInfo.PackedTileIndex = 3;
			break;
		case BUILDING_RESTRICTED:
			TempTileInfo.PackedTileIndex = 3;
		default:
			break;
		}
	}
	else
	{
		TempTileInfo = TileInfo;
	}
	_MainTilemapComponent->SetTile(XTileCoord, YTileCoord, 0, TempTileInfo);
}