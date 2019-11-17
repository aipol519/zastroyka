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

	IsBuildingMapRestricted = true;

	CurrentStat = new FStat(1000, 3, 50, 100);
	Income = new FStat(-10, 0, 0, 0);

	IsBuildModeEnabled = false;
	IsDestroyModeEnabled = false;

	SelectedBuilding = nullptr;
	
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
			Tiles.Add(NewObject<UTile>(this));
			Tiles[ConvertCoordinateToIndex(i, j)]->Initialize(i, j, MainTilemapComponent->GetTile(i, j, 0), GREEN_TILE, false);
		}
	}

	for (int16 i = 27; i < 36; i++)
	{
		for (int16 j = 28; j < 36; j++)
		{
			if (i < 28 || i > 34 || j < 29 || j > 34)
			{
				Tiles[ConvertCoordinateToIndex(i, j)]->TileType = ROAD_TILE;
			}
			else
			{
				Tiles[ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED_TILE;
			}
		}
	}

	for (int16 i = 32; i < 36; i++)
	{
		Tiles[ConvertCoordinateToIndex(31, i)]->TileType = ROAD_TILE;
	}
	 
	ExtraTileInfo = Tiles[ConvertCoordinateToIndex(XMapSize / 2, YMapSize / 2)]->TileInfo;
}

void ADefaultGameState::SetDefaultBuildings()
{
	DefaultBuildings.Add("1", NewObject<ABuilding>(this));
	DefaultBuildings.Add("1A", NewObject<ABuilding>(this));
	DefaultBuildings.Add("1B", NewObject<ABuilding>(this));
	DefaultBuildings.Add("1C", NewObject<ABuilding>(this));
	DefaultBuildings.Add("1D", NewObject<ABuilding>(this));

	DefaultBuildings["1"]->Initialize(4, 3, 0, TOWNHALLONE_BUILDING, FStat(0, 0, 0, 0));
	DefaultBuildings["1A"]->Initialize(2, 2, 250, HUT_BUILDING, FStat(5, 15, 1, 1));
	DefaultBuildings["1B"]->Initialize(6, 4, 500, BARRACK_BUILDING, FStat(5, 15, 1, 1));
	DefaultBuildings["1C"]->Initialize(2, 1, 300, STAND_BUILDING, FStat(5, 15, 1,1));
	DefaultBuildings["1D"]->Initialize(1, 1, 300, ROAD_BUILDING, FStat(5, 15, 1, 1));

	DefaultBuildings["1"]->Place(Tiles, MainTilemapComponent, 30, 30);
}

void ADefaultGameState::UpdateStat()
{
	*CurrentStat += *Income;
}

void ADefaultGameState::SelectBuilding(FString _BuildingID)
{
	SelectedBuilding = DefaultBuildings[_BuildingID];
}

void ADefaultGameState::ToggleMode(bool _IsBuildMode)
{
	CurrentTimeRef->Play();
	GetPlayerRef()->GetController()->SetActorTickEnabled(!GetPlayerRef()->GetController()->IsActorTickEnabled());
	if (IsBuildModeEnabled || IsDestroyModeEnabled)
	{
		GetPlayerRef()->GetController()->SetActorTickEnabled(false);
		ExtraTileInfo.PackedTileIndex = 0;
		SelectedBuilding = nullptr;
		RefreshConnectionMap();
		RefreshIncome();
		HUDWidgetRef->UpdateVisibleIncome();
	}
	if (_IsBuildMode)
	{
		IsBuildModeEnabled = !IsBuildModeEnabled;
		if (IsDestroyModeEnabled)
		{
			ExtraTileInfo.PackedTileIndex = 3;
		}
	}
	else
	{
		IsDestroyModeEnabled = !IsDestroyModeEnabled;
		if (IsDestroyModeEnabled)
		{
			ExtraTileInfo.PackedTileIndex = 4;
		}
	}
	for (UTile* CurrentTile : Tiles)
	{
		CurrentTile->ChangeInBuildDestroyMode(MainTilemapComponent, IsBuildModeEnabled || IsDestroyModeEnabled);
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
						if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType == GREEN_TILE)
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
						if (Tiles[ConvertCoordinateToIndex(i, j)]->TileType != GREEN_TILE)
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
			if (SelectedBuilding->BuildingType == ROAD_BUILDING)
			{
				Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileType = ROAD_TILE;
				Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileInfo.PackedTileIndex = 1;
				MainTilemapComponent->SetTile(_XTileCoord, _YTileCoord, 0, ExtraTileInfo);
			}
			else
			{
				Buildings.Add(SelectedBuilding->Place(Tiles, MainTilemapComponent, _XTileCoord, _YTileCoord));
			}
		}
	}
	else if (IsDestroyModeEnabled)
	{
		if (_XTileCoord < 27 || _XTileCoord > 35 || _YTileCoord < 28 || _YTileCoord > 35)
		{
			if (Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileType == ROAD_TILE)
			{
				Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileType = GREEN_TILE;
				Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileInfo.PackedTileIndex = 0;
				MainTilemapComponent->SetTile(_XTileCoord, _YTileCoord, 0, ExtraTileInfo);
			}
		}
	}
}

void ADefaultGameState::RefreshConnectionMap()
{
	temp = 0;
	temp2 = 0;

	for (UTile* CurrentTile : Tiles)
	{
		CurrentTile->IsTileConnected = false;
	}
	for (ABuilding* CurrentBuilding: Buildings)
	{
		CurrentBuilding->IsBuildingConnected = false;
	}
	CheckConnection(XMapSize / 2, YMapSize / 2);
}

void ADefaultGameState::CheckConnection(int16 _XTileCoord, int16 _YTileCoord)
{
	if (Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->IsTileConnected == false &&
		(Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->TileType == ROAD_TILE || Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->TileType == BUILDING_RESTRICTED_TILE))
	{
		Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->IsTileConnected = true;
		if (Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->TileType == BUILDING_RESTRICTED_TILE)
		{
			for (ABuilding* CurrentBuilding: Buildings)
			{
				if (CurrentBuilding->IsBuildingConnected == false)
				{
					if (CurrentBuilding->AnchorCoord == ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))
					{
						CurrentBuilding->IsBuildingConnected = true;
						++temp2;
						break;
					}
				}
			}
		}
		if (_XTileCoord >= 0 && _YTileCoord >= 0 && _XTileCoord < XMapSize && _YTileCoord < YMapSize)
		{
			CheckConnection(_XTileCoord + 1, _YTileCoord);
			CheckConnection(_XTileCoord, _YTileCoord + 1);
			CheckConnection(_XTileCoord - 1, _YTileCoord);
			CheckConnection(_XTileCoord, _YTileCoord - 1);
		}
	}
}

void ADefaultGameState::RefreshIncome()
{
	FStat TempIncome(0, 0, 0, 0);
	for (ABuilding* CurrentBuilding: Buildings)
	{
		if (CurrentBuilding->IsBuildingConnected)
		{
			TempIncome += CurrentBuilding->Income;
		}
	}
	*Income = TempIncome;
}

void ADefaultGameState::DeleteBuildingInfo(ABuilding* _DeletingBuilding)
{
	for (ABuilding* CurrentBuilding: Buildings)
	{
		if (CurrentBuilding->AnchorCoord == _DeletingBuilding->AnchorCoord)
		{
			ExtraTileInfo.PackedTileIndex = 4;
			for (int16 i = GetXCoordFromIndex(CurrentBuilding->AnchorCoord); i < GetXCoordFromIndex(CurrentBuilding->AnchorCoord) + CurrentBuilding->XSize; i++)
			{
				for (int16 j = GetYCoordFromIndex(CurrentBuilding->AnchorCoord); j < GetYCoordFromIndex(CurrentBuilding->AnchorCoord) + CurrentBuilding->YSize; j++)
				{
					Tiles[ConvertCoordinateToIndex(i, j)]->TileType = GREEN_TILE;
					MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
				}
			}
			Buildings.RemoveSingle(CurrentBuilding);
			break;
		}
	}
}

int16 ADefaultGameState::GetXCoordFromIndex(int16 _Index)
{
	return div(_Index, XMapSize).quot;
}

int16 ADefaultGameState::GetYCoordFromIndex(int16 _Index)
{
	return div(_Index, XMapSize).rem;
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