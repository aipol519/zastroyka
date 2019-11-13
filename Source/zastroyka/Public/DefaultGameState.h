// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileSet.h"
#include "GameFramework/GameStateBase.h"
#include "DefaultGameState.generated.h"

USTRUCT()
struct FStat
{
	GENERATED_BODY()

	UPROPERTY()
	int32 Money;

	UPROPERTY()
	int32 Population;

	UPROPERTY()
	int32 Climate;

	UPROPERTY()
	int32 Employment;
	
	FStat() {}

	FStat(int32 _Money, int32 _Population, int32 _Climate, int32 _Employment)
	{
		Money = _Money;
		Population = _Population;
		Climate = _Climate;
		Employment = _Employment;
	}
};

UCLASS()
class ZASTROYKA_API ADefaultGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:
	ADefaultGameState();

	void SetDefaultTiles();
	void SetDefaultBuildings();
	void SelectBuilding(FString _BuildingID);
	void ToggleBuildMode(bool _IsBuildModeEnabled);

	void SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef);
	void InitializeTime();

	int16 ConvertCoordinateToIndex(int16 _i, int16 _j);

	class APlayerPawn* GetPlayerRef();

	TArray<class UTile*> Tiles;
	
	TMap<FString, class ABuilding*> DefaultBuildings;
	TArray<class ABuilding*> CurrentBuildings;

	FStat* CurrentStat;
	FStat* Income;
	void UpdateStat();
	void SetIncome(FStat _NewBuildingIncome);

	class ABuilding* SelectedBuilding;

	int16 XMapSize, YMapSize;
	bool IsBuildModeEnabled;

	FPaperTileInfo ExtraTileInfo;
	void MoveSelectionZone(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord);
	bool IsBuildingMapRestricted;

	void RefreshConnectionMap();
	void CheckTileConnection(int16 _XTileCoord, int16 _YTileCoord);
	int16 temp;

	void Action(int16 _XTileCoord, int16 _YTileCoord);

	UPaperTileMapComponent* MainTilemapComponent;
	UPaperTileSet* DefaultTileset;

	class AzastroykaGameModeBase* GameModeBaseRef;
	class UTime* CurrentTimeRef;
	class UHUDWidgetUMG* HUDWidgetRef;

};
