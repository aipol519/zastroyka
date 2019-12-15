// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Engine/Engine.h"

UTile::UTile()
{
}

void UTile::Initialize(const int16& _XCoord, const int16& _YCoord, const int16& _TileMapIndex, const FPaperTileInfo _TileInfo, const ETileType& _Type)
{
	XCoord = _XCoord;
	YCoord = _YCoord;
	TileMapIndex = _TileMapIndex;
	TileInfo = _TileInfo;
	Type = _Type;
	IsConnected = false;
}

FPaperTileInfo UTile::GetTileInfo()
{
	return TileInfo;
}

void UTile::ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, const bool& _BuildFlag)
{
	FPaperTileInfo TempTileInfo = TileInfo;
	if (_BuildFlag)
	{
		switch (Type)
		{
		case GREEN_TILE:
			TempTileInfo.PackedTileIndex = BUILDING_ALLOWED_TILE;
			break;
		default:
			TempTileInfo.PackedTileIndex = BUILDING_RESTRICTED_TILE;
			break;
		}
	}
	else
	{
		switch (Type)
		{
		case GREEN_TILE:
		case BUILDING_RESTRICTED_TILE:
			TempTileInfo.PackedTileIndex = GREEN_TILE;
			break;
		case ROAD_TILE:
			TempTileInfo.PackedTileIndex = ROAD_TILE;
			break;
		default:
			break;
		}
	}
	_MainTilemapComponent->SetTile(XCoord, YCoord, 0, TempTileInfo);
}

FPaperTileInfo UTile::SetTileInfoIndex(int _Index)
{
	return GetTileInfo();
}

void UTile::PlaceRoad(TArray<UTile*> _Tiles, UPaperTileMapComponent* _MainTilemapComponent)
{
	FPaperTileInfo TempTileInfo = TileInfo;
	TempTileInfo.PackedTileIndex = BUILDING_RESTRICTED_TILE;
	_Tiles[TileMapIndex]->Type = ROAD_TILE;
	_Tiles[TileMapIndex]->TileInfo.PackedTileIndex = ROAD_TILE;
	_MainTilemapComponent->SetTile(XCoord, YCoord, 0, TempTileInfo);
}

void UTile::DemolishRoad(TArray<UTile*> _Tiles, UPaperTileMapComponent* _MainTilemapComponent)
{
	if (XCoord < 27 || XCoord > 35 || YCoord < 28 || YCoord > 35)
	{
		if (_Tiles[TileMapIndex]->Type == ROAD_TILE)
		{
			FPaperTileInfo TempTileInfo = TileInfo;
			TempTileInfo.PackedTileIndex = BUILDING_ALLOWED_TILE;
			_Tiles[TileMapIndex]->Type = GREEN_TILE;
			_Tiles[TileMapIndex]->TileInfo.PackedTileIndex = GREEN_TILE;
			_MainTilemapComponent->SetTile(XCoord, YCoord, 0, TempTileInfo);
		}
	}
}