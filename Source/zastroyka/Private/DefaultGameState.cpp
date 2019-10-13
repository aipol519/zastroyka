// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameState.h"

#include "Engine.h"

ADefaultGameState::ADefaultGameState()
{
	//Setting up default tileset
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TilesetObject(TEXT("/Game/sprites/main_tile_set"));
	DefaultTileset = TilesetObject.Object;

	XMapSize = 64;
	YMapSize = 64;

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
	for (int16 i = 0; i < YMapSize; i++)
	{
		for (int16 j = 0; j < XMapSize; j++)
		{
			Tiles.Add(new FTile(j, i, MainTilemapComponent->GetTile(j, i, 0)));
		}
	}

	for (int16 i = 29; i < 35; i++)
	{
		for (int16 j = 27; j < 37; j++)
		{
			Tiles[ConvertCoordinateToIndex(i, j)]->IsBuildingAllowed = false;
		}

	}

}

void ADefaultGameState::EnableBuildMode()
{
	IsBuildModeEnabled = true;
	
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Build mode enabled");
	
	for (FTile* CurrentTile : Tiles)
	{
		CurrentTile->ChangeInBuildMode(MainTilemapComponent, true);
	}

}

void ADefaultGameState::DisableBuildMode()
{
	IsBuildModeEnabled = false;

	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Build mode disabled");

	for (FTile* CurrentTile : Tiles)
	{
		CurrentTile->ChangeInBuildMode(MainTilemapComponent, false);
	}

}

int16 ADefaultGameState::ConvertCoordinateToIndex(int16 _i, int16 _j)
{
	return (XMapSize * _i + _j);
}
