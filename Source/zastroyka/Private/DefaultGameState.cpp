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

	BuildingLength = 5;
	BuildingWidth = 5;
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
		IsBuildingMapRestricted = false;
		for (int i = _PrevXTileCoord + div(BuildingWidth, 2).quot + div(BuildingWidth, 2).rem - 1; i >= _PrevXTileCoord - div(BuildingWidth, 2).quot; i--)
		{
			for (int j = _PrevYTileCoord + div(BuildingLength, 2).quot + div(BuildingLength, 2).rem - 1; j >= _PrevYTileCoord - div(BuildingLength, 2).quot; j--)
			{
				if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
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
		}

		_PrevXTileCoord = _XTileCoord;
		_PrevYTileCoord = _YTileCoord;

		TileInfo.PackedTileIndex = 2;
		if (((_XTileCoord - div(BuildingWidth, 2).quot) < 0) || ((_XTileCoord + div(BuildingWidth, 2).quot + div(BuildingWidth, 2).rem - 1) >= XMapSize) ||
			((_YTileCoord - div(BuildingLength, 2).quot) < 0) || ((_YTileCoord + div(BuildingLength, 2).quot + div(BuildingLength, 2).rem - 1) >= YMapSize))
		{
			IsBuildingMapRestricted = true;
			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Building Restricted");
		}
		if (!IsBuildingMapRestricted)
		{
			for (int i = _XTileCoord + div(BuildingWidth, 2).quot + div(BuildingWidth, 2).rem - 1; i >= _XTileCoord - div(BuildingWidth, 2).quot; i--)
			{
				for (int j = _YTileCoord + div(BuildingLength, 2).quot + div(BuildingLength, 2).rem - 1; j >= _YTileCoord - div(BuildingLength, 2).quot; j--)
				{
					if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType != GREEN)
					{
						IsBuildingMapRestricted = true;
						break;
					}
					else if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
					{
						MainTilemapComponent->SetTile(i, j, 0, TileInfo);
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
			for (int i = _XTileCoord + div(BuildingWidth, 2).quot + div(BuildingWidth, 2).rem - 1; i >= _XTileCoord - div(BuildingWidth, 2).quot; i--)
			{
				for (int j = _YTileCoord + div(BuildingLength, 2).quot + div(BuildingLength, 2).rem - 1; j >= _YTileCoord - div(BuildingLength, 2).quot; j--)
				{
					if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
					{
						MainTilemapComponent->SetTile(i, j, 0, TileInfo);
					}
				}
			}
		}	
	}
}

void ADefaultGameState::Action(int16 _XTileCoord, int16 YTileCoord)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Action Triggered");
	if (IsBuildModeEnabled)
	{
		if (!IsBuildingMapRestricted)
		{
			PlaceBuilding(_XTileCoord, YTileCoord);
		}
	}
}

void ADefaultGameState::PlaceBuilding(int16 _XTileCoord, int16 _YTileCoord)
{
	for (int i = _XTileCoord + div(BuildingWidth, 2).quot + div(BuildingWidth, 2).rem - 1; i >= _XTileCoord - div(BuildingWidth, 2).quot; i--)
	{
		for (int j = _YTileCoord + div(BuildingLength, 2).quot + div(BuildingLength, 2).rem - 1; j >= _YTileCoord - div(BuildingLength, 2).quot; j--)
		{
			Tiles[ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED;
			Tiles[ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 0;
		}
	}
	for (int i = _XTileCoord + div(BuildingWidth, 2).quot + div(BuildingWidth, 2).rem - 2; i >= _XTileCoord - div(BuildingWidth, 2).quot + 1; i += BuildingWidth + 1)
	{
		for (int j = _YTileCoord + div(BuildingLength, 2).quot + div(BuildingLength, 2).rem - 2; j >= _YTileCoord - div(BuildingLength, 2).quot + 1; j += BuildingLength + 1)
		{
			if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
			{
				if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType == GREEN)
				{
					Tiles[ConvertCoordinateToIndex(i, j)]->TileType = ROAD;
					Tiles[ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 1;
				}
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Building Placed");
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
