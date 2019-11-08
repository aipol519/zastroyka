// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

UTile::UTile()
{
}

void UTile::Initialize(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected)
{
	XTileCoord = _XTileCoord;
	YTileCoord = _YTileCoord;
	TileInfo = _TileInfo;
	TileType = _TileType;
	IsTileConnected = _IsTileConnected;
}

FPaperTileInfo UTile::GetTileInfo()
{
	return TileInfo;
}

void UTile::ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, bool _BuildFlag)
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
		default:
			TempTileInfo.PackedTileIndex = 3;
			break;
		}
	}
	else
	{
		TempTileInfo = TileInfo;
	}
	_MainTilemapComponent->SetTile(XTileCoord, YTileCoord, 0, TempTileInfo);
}

FPaperTileInfo UTile::SetTileInfoIndex(int _Index)
{
	return GetTileInfo();
}