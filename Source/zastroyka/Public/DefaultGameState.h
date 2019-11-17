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

	FStat& operator+=(const FStat& _AddStat)
	{
		Money += _AddStat.Money;
		Population += _AddStat.Population;
		Climate += _AddStat.Climate;
		Employment += _AddStat.Employment;
		return * this;
	}
	
	FStat& operator=(const FStat& _AssignedStat)
	{
		Money = _AssignedStat.Money;
		Population = _AssignedStat.Population;
		Climate = _AssignedStat.Climate;
		Employment = _AssignedStat.Employment;
		return * this;
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
	void ToggleMode(bool _IsBuildMode);

	void SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef);
	void InitializeTime();

	int16 ConvertCoordinateToIndex(int16 _i, int16 _j);
	int16 GetXCoordFromIndex(int16 _Index);
	int16 GetYCoordFromIndex(int16 _Index);
	
	class APlayerPawn* GetPlayerRef();

	TArray<class UTile*> Tiles;
	
	TMap<FString, class ABuilding*> DefaultBuildings;
	TArray<class ABuilding*> Buildings;
	void DeleteBuildingInfo(class ABuilding* _DeletingBuilding);
	
	FStat* CurrentStat;
	FStat* Income;
	void UpdateStat();
	void RefreshIncome();

	class ABuilding* SelectedBuilding;

	int16 XMapSize, YMapSize;
	bool IsBuildModeEnabled, IsDestroyModeEnabled;

	FPaperTileInfo ExtraTileInfo;
	void MoveSelectionZone(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord);
	bool IsBuildingMapRestricted;

	void RefreshConnectionMap();
	void CheckConnection(int16 _XTileCoord, int16 _YTileCoord);
	int16 temp, temp2;

	void Action(int16 _XTileCoord, int16 _YTileCoord);

	UPaperTileMapComponent* MainTilemapComponent;
	UPaperTileSet* DefaultTileset;

	class AzastroykaGameModeBase* GameModeBaseRef;
	class UTime* CurrentTimeRef;
	class UHUDWidgetUMG* HUDWidgetRef;

};
