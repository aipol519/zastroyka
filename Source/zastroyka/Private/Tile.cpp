// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//ATile::ATile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected)
//{
//	XTileCoord = _XTileCoord;
//	YTileCoord = _YTileCoord;
//	TileInfo = _TileInfo;
//	TileType = _TileType;
//	IsTileConnected = _IsTileConnected;
//}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::Initialize(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected)
{
	XTileCoord = _XTileCoord;
	YTileCoord = _YTileCoord;
	TileInfo = _TileInfo;
	TileType = _TileType;
	IsTileConnected = _IsTileConnected;
}

FPaperTileInfo ATile::GetTileInfo()
{
	return TileInfo;
}

void ATile::ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, bool _BuildFlag)
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