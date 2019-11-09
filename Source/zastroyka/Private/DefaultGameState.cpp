// Fill out your copyright notice in the Description page of Project Settings.

#include "DefaultGameState.h"
#include "Engine.h"
#include "Tile.h"
#include "Time.h"
#include "Building.h"
#include "PlayerPawn.h"
#include "GamePlayerController.h"
#include "DefaultHUD.h"
#include "Kismet/GameplayStatics.h"
#include "zastroykaGameModeBase.h"
#include "HUDWidgetUMG.h"

ADefaultGameState::ADefaultGameState()
{
	//Setting up default tileset
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TilesetObject(TEXT("/Game/sprites/main_tile_set"));
	DefaultTileset = TilesetObject.Object;

	XMapSize = 64;
	YMapSize = 64;

	IsBuildingMapRestricted = false;

	CurrentStat = new FStat(1000, 0, 5);
	Income = new FStat(-10, 1, 0);

	IsBuildModeEnabled = false;

	temp = 0;
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
	SetDefaultBuildings();
	InitializeTime();
}

void ADefaultGameState::InitializeTime()
{
	CurrentTimeRef = NewObject<UTime>(this);
	CurrentTimeRef->Initialize();
}

void ADefaultGameState::SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef)
{
	HUDWidgetRef = _HUDWidgetRef;
	CurrentTimeRef->SetHUDWidgetRef(_HUDWidgetRef);
}

void ADefaultGameState::SetDefaultTiles()
{
	for (int16 i = 0; i < XMapSize; i++)
	{
		for (int16 j = 0; j < YMapSize; j++)
		{
			//Tiles.Add(new ATile(i, j, MainTilemapComponent->GetTile(i, j, 0), GREEN, false));
			Tiles.Add(NewObject<UTile>(this));
			Tiles[ConvertCoordinateToIndex(i, j)]->Initialize(i, j, MainTilemapComponent->GetTile(i, j, 0), GREEN, false);
		}
	}

	for (int16 i = 27; i < 37; i++)
	{
		for (int16 j = 28; j < 36; j++)
		{
			if ((i == 27 || i == 36) && ((j == 28) || (j == 35)))
			{
				Tiles[ConvertCoordinateToIndex(i, j)]->TileType = ROAD;
			}
			else
			{
				Tiles[ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED;
			}
		}
	}

	ExtraTileInfo = Tiles[0]->TileInfo;
}

void ADefaultGameState::SetDefaultBuildings()
{
	//Buildings.Add("1A", new ABuilding(4, 4, 250, FString("Izba")));
	//Buildings.Add("1B", new ABuilding(6, 4, 500, FString("Barak")));
	//Buildings.Add("1C", new ABuilding(2, 2, 300, FString("Larek")));

	Buildings.Add("1A", NewObject<ABuilding>(this));
	Buildings.Add("1B", NewObject<ABuilding>(this));
	Buildings.Add("1C", NewObject<ABuilding>(this));
	Buildings["1A"]->Initialize(4, 4, 250, FString("Izba"));
	Buildings["1B"]->Initialize(6, 4, 500, FString("Barak"));
	Buildings["1C"]->Initialize(2, 2, 300, FString("Larek"));
}

void ADefaultGameState::UpdateStat()
{
	CurrentStat->Money += Income->Money;
	CurrentStat->Population += Income->Population;
	CurrentStat->Climate += Income->Climate;
}

void ADefaultGameState::SelectBuilding(FString _BuildingID)
{
	SelectedBuilding = Buildings[_BuildingID];

	GetPlayerRef()->GetController()->SetActorTickEnabled(true);

}

void ADefaultGameState::ToggleBuildMode(bool _IsBuildModeEnabled)
{
	CurrentTimeRef->Play();
	
	if (IsBuildModeEnabled) { GetPlayerRef()->GetController()->SetActorTickEnabled(false); }

	IsBuildModeEnabled = _IsBuildModeEnabled;
	
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Build mode toggled");
	
	for (UTile* CurrentTile : Tiles)
	{
		CurrentTile->ChangeInBuildMode(MainTilemapComponent, _IsBuildModeEnabled);
	}
}

void ADefaultGameState::MoveSelectionZone(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord)
{
	if ((_PrevXTileCoord != _XTileCoord) || (_PrevYTileCoord != _YTileCoord))
	{
		if (!(((_XTileCoord - div(SelectedBuilding->XSize, 2).quot) < 0) || ((_XTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem - 1) >= XMapSize) ||
			((_YTileCoord - div(SelectedBuilding->YSize, 2).quot) < 0) || ((_YTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem - 1) >= YMapSize)))
		{
			IsBuildingMapRestricted = false;
			for (int i = _PrevXTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem - 1; i >= _PrevXTileCoord - div(SelectedBuilding->XSize, 2).quot; i--)
			{
				for (int j = _PrevYTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem - 1; j >= _PrevYTileCoord - div(SelectedBuilding->YSize, 2).quot; j--)
				{
					if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
					{
						if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType == GREEN)
						{
							ExtraTileInfo.PackedTileIndex = 4;
						}
						else
						{
							ExtraTileInfo.PackedTileIndex = 3;
						}
						MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
					}
				}
			}

			_PrevXTileCoord = _XTileCoord;
			_PrevYTileCoord = _YTileCoord;

			ExtraTileInfo.PackedTileIndex = 2;

			if (!IsBuildingMapRestricted)
			{
				for (int i = _XTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem - 1; i >= _XTileCoord - div(SelectedBuilding->XSize, 2).quot; i--)
				{
					for (int j = _YTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem - 1; j >= _YTileCoord - div(SelectedBuilding->YSize, 2).quot; j--)
					{
						if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType != GREEN)
						{
							IsBuildingMapRestricted = true;
							break;
						}
						else if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
						{
							MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
						}
					}
					if (IsBuildingMapRestricted)
					{

						ExtraTileInfo.PackedTileIndex = 3;
						for (int i = _XTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem - 1; i >= _XTileCoord - div(SelectedBuilding->XSize, 2).quot; i--)
						{
							for (int j = _YTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem - 1; j >= _YTileCoord - div(SelectedBuilding->YSize, 2).quot; j--)
							{
								if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
								{
									MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
								}
							}
						}
						break;
					}
				}
			}
			//IsBuildingMapRestricted = true;
			//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Building Restricted");
		}
	
	}
}

void ADefaultGameState::Action(int16 _XTileCoord, int16 _YTileCoord)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Action Triggered");
	if (IsBuildModeEnabled)
	{
		if (!IsBuildingMapRestricted)
		{
			PlaceBuilding(_XTileCoord, _YTileCoord);
		}
	}
}

void ADefaultGameState::PlaceBuilding(int16 _XTileCoord, int16 _YTileCoord)
{
	ExtraTileInfo.PackedTileIndex = 3;
	for (int i = _XTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem - 1; i >= _XTileCoord - div(SelectedBuilding->XSize, 2).quot; i--)
	{
		for (int j = _YTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem - 1; j >= _YTileCoord - div(SelectedBuilding->YSize, 2).quot; j--)
		{
			Tiles[ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED;
			Tiles[ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 0;
			MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
		}
	}
	for (int i = _XTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem; i >= _XTileCoord - div(SelectedBuilding->XSize, 2).quot - 1; i -= (SelectedBuilding->XSize + 1))
	{
		for (int j = _YTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem; j >= _YTileCoord - div(SelectedBuilding->YSize, 2).quot - 1; j--)
		{
			if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
			{
				if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType == GREEN)
				{
					Tiles[ConvertCoordinateToIndex(i, j)]->TileType = ROAD;
					Tiles[ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 1;
					MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
				}
			}
		}
	}
	for (int j = _YTileCoord + div(SelectedBuilding->YSize, 2).quot + div(SelectedBuilding->YSize, 2).rem; j >= _YTileCoord - div(SelectedBuilding->YSize, 2).quot - 1; j -= (SelectedBuilding->YSize + 1))
	{
		for (int i = _XTileCoord + div(SelectedBuilding->XSize, 2).quot + div(SelectedBuilding->XSize, 2).rem; i >= _XTileCoord - div(SelectedBuilding->XSize, 2).quot - 1; i--)
		{
			if (i >= 0 && j >= 0 && i < XMapSize && j < YMapSize)
			{
				if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType == GREEN)
				{
					Tiles[ConvertCoordinateToIndex(i, j)]->TileType = ROAD;
					Tiles[ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 1;
					MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
				}
			}
		}
	}

	RefreshConnectionMap();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Building Placed");
}

void ADefaultGameState::RefreshConnectionMap()
{
	temp = 0;

	for (UTile* CurrentTile : Tiles)
	{
		CurrentTile->IsTileConnected = false;
	}
	CheckTileConnection(XMapSize / 2, YMapSize / 2);
}

void ADefaultGameState::CheckTileConnection(int16 _XTileCoord, int16 _YTileCoord)
{
	if (Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->IsTileConnected == false &&
		(Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->TileType == ROAD || Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->TileType == BUILDING_RESTRICTED))
	{
		Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->IsTileConnected = true;
		++temp;
		if (_XTileCoord >= 0 && _YTileCoord >= 0 && _XTileCoord < XMapSize && _YTileCoord < YMapSize)
		{
			CheckTileConnection(_XTileCoord + 1, _YTileCoord);
			CheckTileConnection(_XTileCoord, _YTileCoord + 1);
			CheckTileConnection(_XTileCoord - 1, _YTileCoord);
			CheckTileConnection(_XTileCoord, _YTileCoord - 1);
		}
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, FString::FromInt(temp));
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
