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
#include "EventBase.h"

#include "Sound/AmbientSound.h"
#include "Sound/SoundCue.h"

#include <cstdlib>

#include "HUDWidgetUMG.h"
#include "ShopWidgetUMG.h"

ADefaultGameState::ADefaultGameState()
{
	//Setting up default tileset
	static ConstructorHelpers::FObjectFinder<UPaperTileSet> TilesetObject(TEXT("/Game/sprites/main_tile_set"));
	DefaultTileset = TilesetObject.Object;

	XMapSize = 64;
	YMapSize = 64;

	CurrentStat = FStat(1000, 3, 30, 3);
	Income = FStat(0, 0, 0, 0);
	MaxPopulation = 6;
	ClimateDebuffs = 0;

	IsBuildingMapRestricted = true;
	IsBuildModeEnabled = false;
	IsDestroyModeEnabled = false;

	SelectedBuilding = nullptr;
	AmbientSoundRef = nullptr;
	
	srand(static_cast<unsigned>(FDateTime::Now().GetMillisecond()));
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

	WorldRef = GetWorld();

	AmbientSoundRef = GetWorld()->SpawnActor<AAmbientSound>();
	USoundCue* SoundCueRef = LoadObject<USoundCue>(NULL, *FString("/Game/sound/Soundtrack_Cue"), NULL, LOAD_None, NULL);
	AmbientSoundRef->GetAudioComponent()->SetSound(SoundCueRef);
	AmbientSoundRef->Play();

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

void ADefaultGameState::SetShopWidgetRef(class UShopWidgetUMG* _ShopWidgetRef)
{
	ShopWidgetRef = _ShopWidgetRef;
	//CurrentTimeRef->SetHUDWidgetRef(_HUDWidgetRef);
}

void ADefaultGameState::SetEventWidgetRef(UEventWigdetUMG* _EventWidgetRef)
{
	EventWidgetRef = _EventWidgetRef;

	SetDefaultEvents();
}

void ADefaultGameState::SetPlayerControllerRef(AGamePlayerController* _PlayerControllerRef)
{
	PlayerControllerRef = _PlayerControllerRef;
}

void ADefaultGameState::SetDefaultTiles()
{
	int16 CurrentTileIndex = 0;
	for (int16 i = 0; i < XMapSize; i++)
	{
		for (int16 j = 0; j < YMapSize; j++)
		{
			CurrentTileIndex = ConvertCoordinateToIndex(i, j);
			Tiles.Add(NewObject<UTile>(this));
			Tiles[CurrentTileIndex]->Initialize(i, j, CurrentTileIndex, MainTilemapComponent->GetTile(i, j, 0), GREEN_TILE);
		}
	}

	for (int16 i = 27; i < 36; i++)
	{
		for (int16 j = 28; j < 36; j++)
		{
			CurrentTileIndex = ConvertCoordinateToIndex(i, j);
			if (i < 28 || i > 34 || j < 29 || j > 34)
			{
				Tiles[CurrentTileIndex]->Type = ROAD_TILE;
			}
			else
			{
				Tiles[CurrentTileIndex]->Type = BUILDING_RESTRICTED_TILE;
			}
		}
	}

	for (int16 i = 32; i < 36; i++)
	{
		Tiles[ConvertCoordinateToIndex(31, i)]->Type = ROAD_TILE;
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
	DefaultBuildings.Add("1E", NewObject<ABuilding>(this));
	DefaultBuildings.Add("2", NewObject<ABuilding>(this));

	DefaultBuildings["1"]->Initialize(4, 3, 0, FStat(0, 0, 0, 0), false, "town_hall_lvl1", this);
	DefaultBuildings["1A"]->Initialize(2, 2, 300, FStat(0, 6, 2, 0), false, "hut", this);
	DefaultBuildings["1B"]->Initialize(6, 2, 500, FStat(0, 10, 1, 0), false, "barrack", this);
	DefaultBuildings["1C"]->Initialize(2, 1, 250, FStat(5, 0, 1,2), false, "stand", this);
	DefaultBuildings["1D"]->Initialize(1, 1, 0, FStat(0, 0, 0, 0), true, "road", this);
	DefaultBuildings["1E"]->Initialize(6, 4, 400, FStat(8, 0, 0, 10), false, "farm", this);
	DefaultBuildings["2"]->Initialize(1, 1, 300, FStat(0, 0, 0, 0), false, "town_hall_lvl2", this);

	Buildings.Add(DefaultBuildings["1"]->Place(Tiles, MainTilemapComponent, 30, 30));
	Buildings[0]->ChangeTransparency(false);
}

void ADefaultGameState::SetDefaultEvents()
{
	DefaultEvents.Add("Game Start", NewObject<UEventBase>(this));
	DefaultEvents.Add("test1", NewObject<UEventBase>(this));
	DefaultEvents.Add("test2", NewObject<UEventBase>(this));
	DefaultEvents.Add("test3", NewObject<UEventBase>(this));
	DefaultEvents.Add("test4", NewObject<UEventBase>(this));
	DefaultEvents.Add("test5", NewObject<UEventBase>(this));
	DefaultEvents.Add("test6", NewObject<UEventBase>(this));
	
	DefaultEvents["Game Start"]->Initialize("Welcome to ZASTROYKA",
		"You are the head of this \"city\". The goal of the game is to earn as much money as possible and maybe make people a little happier.\n\nControls:\nLMB - action\nMouse to screen borders - camera movement",
		FStat(0, 0, 0, 0), 0.0, this);
	DefaultEvents["test1"]->Initialize("test1", "Hello TUTOR", FStat(0, 0, 0, 0), 0.01, this);
	DefaultEvents["test2"]->Initialize("test2", "Hello TUTOR", FStat(0, 0, 0, 0), 0.05, this);
	DefaultEvents["test3"]->Initialize("test3", "Hello TUTOR", FStat(0, 0, 0, 0), 0.1, this);
	DefaultEvents["test4"]->Initialize("test4", "Hello TUTOR", FStat(0, 0, 0, 0), 0.15, this);
	DefaultEvents["test5"]->Initialize("test5", "Hello TUTOR", FStat(0, 0, 0, 0), 0.2, this);
	DefaultEvents["test6"]->Initialize("test6", "Exit Event Test", FStat(0, 0, 0, 0), 0.25, this);
	
	DefaultEvents["Game Start"]->Execute();
}

void ADefaultGameState::CheckEvents()
{
	float RandomAppearChance = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	TArray<UEventBase*> SuitableEvents;
	for (auto const& Event : DefaultEvents)
	{
		if (Event.Value->GetAppearChance() > RandomAppearChance)
		{
			SuitableEvents.Add(Event.Value);
		}
	}
	if (SuitableEvents.Num() > 0)
	{
		SuitableEvents[div(rand(), SuitableEvents.Num()).rem]->Execute();
	}
}

FString ADefaultGameState::GetEmploymentLevel()
{
	return FString(
		FString::FromInt(static_cast<int16>((FMath::Clamp<float>(CurrentStat.Employment, .0f, CurrentStat.Population)) / CurrentStat.Population * 100))
		+ "%");
}

FString ADefaultGameState::GetClimateLevel()
{
	return FString(
		FString::FromInt(FMath::Clamp<int16>(CurrentStat.Climate, -100, 100))
		+ ((Income.Climate - ClimateDebuffs > -1) ? ("+") : ("-"))
		+(FString::FromInt(abs(Income.Climate - ClimateDebuffs)))
	);
}

FString ADefaultGameState::GetPopulationLevel()
{
	return FString(
		FString::FromInt(CurrentStat.Population)
		+ "/"
		+ FString::FromInt(MaxPopulation)
	);
}

FString ADefaultGameState::GetMoneyLevel()
{
	return FString(
		FString::FromInt(CurrentStat.Money)
		+ ((Income.Money > -1) ? ("+") : "-")
		+ FString::FromInt(abs(Income.Money 
			* FMath::Clamp<int16>(CurrentStat.Climate, -100, 100) / 100.0f
			* FMath::Clamp<int16>(CurrentStat.Employment, 0, CurrentStat.Population) / CurrentStat.Population))
	);
}

FString ADefaultGameState::GetDay()
{
	return FString("D: " + FString::FromInt(CurrentTimeRef->GetDay()));
}

FString ADefaultGameState::GetMonth()
{
	return FString("M: " + FString::FromInt(CurrentTimeRef->GetMonth()));
}

FString ADefaultGameState::GetYear()
{
	return FString("Y: " + FString::FromInt(CurrentTimeRef->GetYear()));
}

void ADefaultGameState::UpdateStat()
{
	CurrentStat.Money += Income.Money
		* FMath::Clamp<int16>(CurrentStat.Climate, -100, 100) / 100.0f
		* FMath::Clamp<float>(CurrentStat.Employment, .0f, CurrentStat.Population) / CurrentStat.Population;
	
	CurrentStat.Population = FMath::Clamp<int16>(
		CurrentStat.Population + static_cast<int16>(truncf(CurrentStat.Population
			* ((FMath::Clamp<int16>(CurrentStat.Climate, -100, 100) / 100.0f)
				+ ((CurrentStat.Employment >= CurrentStat.Population)
				? FMath::Clamp<float>(CurrentStat.Employment, .0f, CurrentStat.Population) / CurrentStat.Population
				: -FMath::Clamp<float>(CurrentStat.Population, .0f, CurrentStat.Employment * 2) / (CurrentStat.Employment * 2))))),
		0,
		MaxPopulation);

	CurrentStat.Climate += Income.Climate;
	CurrentStat.Climate -= ClimateDebuffs;
}

void ADefaultGameState::CheckEndGameState()
{
	if (CurrentStat.Money < 0)
	{
		//playEndGameEvent
		UKismetSystemLibrary::QuitGame(WorldRef, PlayerControllerRef, EQuitPreference::Quit, true);
	}
}

void ADefaultGameState::SelectBuilding(FString _BuildingID)
{
	ClearBuildingTileMapArea();
	SelectedBuilding = FindBuilding(_BuildingID);
	if (SelectedBuilding->Name == "town_hall_lvl2" || SelectedBuilding->Name == "town_hall_lvl3")
	{
		UpgradeTownHall();
		SelectedBuilding = nullptr;
	}
}

void ADefaultGameState::ClearBuildingTileMapArea()
{
	if (SelectedBuilding != nullptr)
	{
		for (int16 i = GetXCoordFromIndex(SelectedBuilding->AnchorCoordIndex); i < GetXCoordFromIndex(SelectedBuilding->AnchorCoordIndex) + SelectedBuilding->XSize; i++)
		{
			for (int16 j = GetYCoordFromIndex(SelectedBuilding->AnchorCoordIndex); j < GetYCoordFromIndex(SelectedBuilding->AnchorCoordIndex) + SelectedBuilding->YSize; j++)
			{
				(Tiles[ConvertCoordinateToIndex(i, j)]->Type == GREEN_TILE) ? (ExtraTileInfo.PackedTileIndex = 4) : (ExtraTileInfo.PackedTileIndex = 3);
				MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
			}
		}
		SelectedBuilding = nullptr;
	}
}

ABuilding* ADefaultGameState::FindBuilding(FString _BuildingID)
{
	return DefaultBuildings[_BuildingID];
}

ADefaultHUD * ADefaultGameState::GetDefaultHUD()
{
	TArray<AActor*> FoundHUDs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultHUD::StaticClass(), FoundHUDs);

	return Cast<ADefaultHUD>(FoundHUDs[0]);
}

void ADefaultGameState::ToggleBuildMode()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Build Mode Toggled");
	//CurrentTimeRef->Play();
	if (IsBuildModeEnabled)
	{
		ExtraTileInfo.PackedTileIndex = 0;
		SelectedBuilding = nullptr;
		RefreshConnectionMap();
		RefreshIncome();
		//HUDWidgetRef->UpdateVisibleIncome();
		HUDWidgetRef->UpdateVisibleStat();
		GetPlayerRef()->GetController()->SetActorTickEnabled(false);
	}
	else
	{
		ShopWidgetRef->CheckAvailabilityForButtons();
		ExtraTileInfo.PackedTileIndex = 3;
		GetPlayerRef()->GetController()->SetActorTickEnabled(true);
	}
	IsDestroyModeEnabled = false;
	IsBuildModeEnabled = !IsBuildModeEnabled;

	for (UTile* CurrentTile : Tiles)
	{
		CurrentTile->ChangeInBuildMode(MainTilemapComponent, IsBuildModeEnabled);
	}
	for (ABuilding* CurrentBuilding : Buildings)
	{
		CurrentBuilding->ChangeTransparency(IsBuildModeEnabled);
	}
}

void ADefaultGameState::ToggleDestroyMode()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Destroy Mode Toggled");
	if (!IsDestroyModeEnabled)
	{
		ClearBuildingTileMapArea();
		ExtraTileInfo.PackedTileIndex = 4;
	}
	else
	{
		HUDWidgetRef->UpdateVisibleStat();
	}
	for (ABuilding* CurrentBuilding : Buildings)
	{
		CurrentBuilding->ChangeTransparency(IsDestroyModeEnabled);
	}
	IsDestroyModeEnabled = !IsDestroyModeEnabled;
}

bool ADefaultGameState::IsCoordinatesValid(float _X, float _Y)
{
	int16 XTileCoord = FMath::FloorToInt(_X / 32.0f);
	int16 YTileCoord = FMath::FloorToInt(_Y / 32.0f);
	return (XTileCoord >= 0 && XTileCoord < XMapSize && YTileCoord >= 0 && YTileCoord < YMapSize);
}

void ADefaultGameState::MoveSelectionZone(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord)
{
	if ((_PrevXTileCoord != _XTileCoord) || (_PrevYTileCoord != _YTileCoord))
	{
		IsBuildingMapRestricted = true;
		
		int16 PrevAnchorCoordIndex = 
			ConvertCoordinateToIndex(_PrevXTileCoord - div(SelectedBuilding->XSize, 2).quot, _PrevYTileCoord - div(SelectedBuilding->YSize, 2).quot);

		if (GetXCoordFromIndex(PrevAnchorCoordIndex) >= 0 && GetXCoordFromIndex(PrevAnchorCoordIndex) + SelectedBuilding->XSize < XMapSize
			&& GetYCoordFromIndex(PrevAnchorCoordIndex) >= 0 && GetYCoordFromIndex(PrevAnchorCoordIndex) + SelectedBuilding->YSize < YMapSize)
		{
			for (int16 i = GetXCoordFromIndex(PrevAnchorCoordIndex); i < GetXCoordFromIndex(PrevAnchorCoordIndex) + SelectedBuilding->XSize; i++)
			{
				for (int16 j = GetYCoordFromIndex(PrevAnchorCoordIndex); j < GetYCoordFromIndex(PrevAnchorCoordIndex) + SelectedBuilding->YSize; j++)
				{
					if (Tiles[ConvertCoordinateToIndex(i, j)]->Type == GREEN_TILE)
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
		
		int16 TempAnchorCoordIndex = 
			ConvertCoordinateToIndex(_XTileCoord - div(SelectedBuilding->XSize, 2).quot, _YTileCoord - div(SelectedBuilding->YSize, 2).quot);

		if (GetXCoordFromIndex(TempAnchorCoordIndex) >= 0 && GetXCoordFromIndex(TempAnchorCoordIndex) + SelectedBuilding->XSize < XMapSize
			&& GetYCoordFromIndex(TempAnchorCoordIndex) >= 0 && GetYCoordFromIndex(TempAnchorCoordIndex) + SelectedBuilding->YSize < YMapSize)
		{
			SelectedBuilding->AnchorCoordIndex = TempAnchorCoordIndex;
			
			IsBuildingMapRestricted = false;

			for (int16 i = GetXCoordFromIndex(SelectedBuilding->AnchorCoordIndex); i < GetXCoordFromIndex(SelectedBuilding->AnchorCoordIndex) + SelectedBuilding->XSize; i++)
			{
				for (int16 j = GetYCoordFromIndex(SelectedBuilding->AnchorCoordIndex); j < GetYCoordFromIndex(SelectedBuilding->AnchorCoordIndex) + SelectedBuilding->YSize; j++)
				{
					if (Tiles[ConvertCoordinateToIndex(i, j)]->Type == GREEN_TILE)
					{
						MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
					}
					else
					{
						IsBuildingMapRestricted = true;
						break;
					}
				}
				if (IsBuildingMapRestricted)
				{
					ExtraTileInfo.PackedTileIndex = 3;
					for (int16 k = GetXCoordFromIndex(SelectedBuilding->AnchorCoordIndex); k < GetXCoordFromIndex(SelectedBuilding->AnchorCoordIndex) + SelectedBuilding->XSize; k++)
					{
						for (int16 l = GetYCoordFromIndex(SelectedBuilding->AnchorCoordIndex); l < GetYCoordFromIndex(SelectedBuilding->AnchorCoordIndex) + SelectedBuilding->YSize; l++)
						{
							MainTilemapComponent->SetTile(k, l, 0, ExtraTileInfo);
						}
					}
					break;
				}
			}
		}
	}
}

void ADefaultGameState::Action(int16 _XTileCoord, int16 _YTileCoord)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Action Triggered");
	if (IsDestroyModeEnabled)
	{
		Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->
			DemolishRoad(Tiles, MainTilemapComponent);
	}
	else if (IsBuildModeEnabled)
	{
		if (!IsBuildingMapRestricted)
		{
			if (SelectedBuilding->IsRoadBuilding)
			{
				Tiles[ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->
					PlaceRoad(Tiles, MainTilemapComponent);
			}
			else
			{
				Buildings.Add(SelectedBuilding->Place(Tiles, MainTilemapComponent, _XTileCoord, _YTileCoord));

				CurrentStat.Money -= SelectedBuilding->Cost;
				if (SelectedBuilding->Cost > CurrentStat.Money)
				{
					ClearBuildingTileMapArea();
					SelectedBuilding = nullptr;
					IsBuildingMapRestricted = true;
				}
				HUDWidgetRef->UpdateVisibleStat();
				ShopWidgetRef->CheckAvailabilityForButtons();
			}
		}
	}
}

void ADefaultGameState::UpgradeTownHall()
{
	Buildings[0]->Demolish();
	ExtraTileInfo.PackedTileIndex = BUILDING_RESTRICTED_TILE;
	Buildings.Insert(SelectedBuilding->Place(Tiles, MainTilemapComponent, 30, 30), 0);
	// shop update
}

void ADefaultGameState::RefreshConnectionMap()
{
	for (UTile* CurrentTile : Tiles)
	{
		CurrentTile->IsConnected = false;
	}
	for (ABuilding* CurrentBuilding: Buildings)
	{
		CurrentBuilding->IsConnected = false;
	}
	CheckConnection(XMapSize / 2, YMapSize / 2);
}

void ADefaultGameState::CheckConnection(int16 _XTileCoord, int16 _YTileCoord)
{
	if (Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->IsConnected == false &&
		(Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->Type == ROAD_TILE || Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->Type == BUILDING_RESTRICTED_TILE))
	{
		Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->IsConnected = true;
		if (Tiles[(ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))]->Type == BUILDING_RESTRICTED_TILE)
		{
			for (ABuilding* CurrentBuilding: Buildings)
			{
				if (CurrentBuilding->IsConnected == false)
				{
					if (CurrentBuilding->AnchorCoordIndex == ConvertCoordinateToIndex(_XTileCoord, _YTileCoord))
					{
						CurrentBuilding->IsConnected = true;
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
	FStat TempStat(0, 0, 0, 0);
	for (ABuilding* CurrentBuilding: Buildings)
	{
		if (CurrentBuilding->IsConnected)
		{
			TempStat += CurrentBuilding->Income;
		}
	}
	CurrentStat.Employment = 3 + TempStat.Employment;
	Income.Climate = TempStat.Climate;
	MaxPopulation = 6 + TempStat.Population;
	CurrentStat.Population = FMath::Clamp<int16>(CurrentStat.Population, 0, MaxPopulation);
	Income.Money = TempStat.Money;
}

void ADefaultGameState::DeleteBuildingInfo(ABuilding* _DeletingBuilding)
{
	for (ABuilding* CurrentBuilding: Buildings)
	{
		if (CurrentBuilding->AnchorCoordIndex == _DeletingBuilding->AnchorCoordIndex)
		{
			ExtraTileInfo.PackedTileIndex = 4;
			for (int16 i = GetXCoordFromIndex(CurrentBuilding->AnchorCoordIndex); i < GetXCoordFromIndex(CurrentBuilding->AnchorCoordIndex) + CurrentBuilding->XSize; i++)
			{
				for (int16 j = GetYCoordFromIndex(CurrentBuilding->AnchorCoordIndex); j < GetYCoordFromIndex(CurrentBuilding->AnchorCoordIndex) + CurrentBuilding->YSize; j++)
				{
					Tiles[ConvertCoordinateToIndex(i, j)]->Type = GREEN_TILE;
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