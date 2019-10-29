// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameState.h"

#include "Engine.h"
#include "PlayerPawn.h"

ADefaultGameState::ADefaultGameState()
{
	//Setting up default tileset
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TilesetObject(TEXT("/Game/sprites/main_tile_set"));
	DefaultTileset = TilesetObject.Object;

	XMapSize = 64;
	YMapSize = 64;

	BuildingMap.Init(true, 81);
	IsBuildingMapRestricted = false;

	IsBuildModeEnabled = false;

}

void ADefaultGameState::BeginPlay()
{
	Super::BeginPlay();

	//Getting instance of tilemap rendering component
	TArray<AActor*> FoundTilemaps;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APaperTileMapActor::StaticClass(), FoundTilemaps);
	MainTilemapComponent = Cast<APaperTileMapActor>(FoundTilemaps[0])->GetRenderComponent();

	//Let tilemap can changing at runtime
	MainTilemapComponent->MakeTileMapEditable();

	SetDefaultTiles();

}

void ADefaultGameState::SetDefaultTiles()
{
	for (int16 i = 0; i < XMapSize; i++)
	{
		for (int16 j = 0; j < YMapSize; j++)
		{
			Tiles.Add(new FTile(i, j, MainTilemapComponent->GetTile(i, j, 0), GREEN));
		}
	}

	for (int16 i = 27; i < 37; i++)
	{
		for (int16 j = 29; j < 35; j++)
		{
			if ((i == 27 || i == 36) && ((j == 29) || (j == 34)))
			{
				Tiles[ConvertCoordinateToIndex(i, j)]->TileType = ROAD;
			}
			else
			{
				Tiles[ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED;
			}
		}
	}

	TileInfo = Tiles[0]->TileInfo;
}

void ADefaultGameState::ToggleBuildMode(bool _IsBuildModeEnabled)
{
	IsBuildModeEnabled = _IsBuildModeEnabled;
	(IsBuildModeEnabled) ? (GetPlayerRef()->GetController()->SetActorTickEnabled(true)) : (GetPlayerRef()->GetController()->SetActorTickEnabled(false));
	
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Build mode toggled");
	
	for (FTile* CurrentTile : Tiles)
	{
		CurrentTile->ChangeInBuildMode(MainTilemapComponent, _IsBuildModeEnabled);
	}
}

void ADefaultGameState::UpdateTileMap(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord)
{
	if ((_PrevXTileCoord != _XTileCoord) || (_PrevYTileCoord != _YTileCoord))
	{
		for (int i = _PrevXTileCoord + 4; i > _PrevXTileCoord - 5 && i >= 0 && i < XMapSize; i--)
		{
			for (int j = _PrevYTileCoord + 4; j > _PrevYTileCoord - 5 && j >= 0 && j < YMapSize; j--)
			{
				if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType == GREEN)
				{
					TileInfo.PackedTileIndex = 4;
				}
				else
				{
					TileInfo.PackedTileIndex = 3;
				}
				MainTilemapComponent->SetTile(i, j, 0, TileInfo);
			}
		}

		_PrevXTileCoord = _XTileCoord;
		_PrevYTileCoord = _YTileCoord;

		TileInfo.PackedTileIndex = 2;
		if (_XTileCoord - 4 < 0 || _XTileCoord + 5 > XMapSize || _YTileCoord - 4 < 0 || _YTileCoord + 5 > YMapSize)
		{
			IsBuildingMapRestricted = true;
		}
		if (!IsBuildingMapRestricted)
		{
			for (int i = _XTileCoord + 4; i > _XTileCoord - 5; i--)
			{
				for (int j = _YTileCoord + 4; j > _YTileCoord - 5; j--)
				{
					if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType != GREEN)
					{
						IsBuildingMapRestricted = true;
						break;
					}
				}
				if (IsBuildingMapRestricted)
				{
					break;
				}
			}
		}
		if (IsBuildingMapRestricted)
		{
			TileInfo.PackedTileIndex = 3;
		}	

		for (int i = 0; i < 9 && _XTileCoord + 4 - i >= 0 && _XTileCoord + 4 - i < XMapSize; i++)
		{
			for (int j = 0; j < 9 && _YTileCoord + 4 - j >= 0 && _YTileCoord + 4 - j < YMapSize; j++)
			{
				if (BuildingMap[i * 9 + j])
				{
					MainTilemapComponent->SetTile(_XTileCoord + 4 - i, _YTileCoord + 4 - j, 0, TileInfo);
					if (_XTileCoord + 4 - i >= 0 && _XTileCoord + 4 - i < XMapSize && _YTileCoord + 4 - j >= 0 && _YTileCoord + 4 - j < YMapSize)
					{

					}
				}
			}
		}

		IsBuildingMapRestricted = false;
	}
}

int16 ADefaultGameState::ConvertCoordinateToIndex(int16 _i, int16 _j)
{
	return (XMapSize * _i + _j);
}

//Function to get player instance
APlayerPawn* ADefaultGameState::GetPlayerRef()
{
	return Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}
