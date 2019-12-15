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
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int16 Money;

	UPROPERTY()
	int16 Population;

	UPROPERTY()
	int16 Climate;

	UPROPERTY()
	int16 Employment;

	FStat() {}

	FStat(int16 _Money, int16 _Population, int16 _Climate, int16 _Employment)
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

	//Setters
	UFUNCTION()
	void SetHUDWidgetRef(class UHUDWidgetUMG* _HUDWidgetRef);

	UFUNCTION()
	void SetShopWidgetRef(class UShopWidgetUMG* _ShopWidgetRef);

	UFUNCTION()
	void SetEventWidgetRef(class UEventWigdetUMG* _EventWidgetRef);

	UFUNCTION()
	void SetPlayerControllerRef(class AGamePlayerController* _PlayerControllerRef);

	UFUNCTION()
	void SetDefaultTiles();

	UFUNCTION()
	void SetDefaultBuildings();

	UFUNCTION()
	void SetDefaultEvents();

	//Getters
	UFUNCTION()
	class ADefaultHUD* GetDefaultHUD();

	UFUNCTION()
	int16 GetXCoordFromIndex(int16 _Index);

	UFUNCTION()
	int16 GetYCoordFromIndex(int16 _Index);

	UFUNCTION()
	class APlayerPawn* GetPlayerRef();

	UFUNCTION()
	FString GetEmploymentLevel();

	UFUNCTION()
	FString GetClimateLevel();

	UFUNCTION()
	FString GetPopulationLevel();

	UFUNCTION()
	FString GetMoneyLevel();

	UFUNCTION()
	FString GetDay();

	UFUNCTION()
	FString GetMonth();

	UFUNCTION()
	FString GetYear();

	//Flags
	UPROPERTY()
	bool IsBuildModeEnabled;

	UPROPERTY()
	bool IsDestroyModeEnabled;

	UPROPERTY()
	bool IsBuildingMapRestricted;

	UFUNCTION()
	bool IsCoordinatesValid(float _X, float _Y);

	//References
	UPROPERTY()
	class UWorld* WorldRef;

	UPROPERTY()
	class AzastroykaGameModeBase* GameModeBaseRef;

	UPROPERTY()
	class UTime* CurrentTimeRef;

	UPROPERTY()
	class UHUDWidgetUMG* HUDWidgetRef;

	UPROPERTY()
	class UShopWidgetUMG* ShopWidgetRef;

	UPROPERTY()
	class UEventWigdetUMG* EventWidgetRef;

	UPROPERTY()
	AGamePlayerController* PlayerControllerRef;

	UPROPERTY()
	UPaperTileMapComponent* MainTilemapComponent;

	UPROPERTY()
	UPaperTileSet* DefaultTileset;

	UPROPERTY()
	class AAmbientSound* AmbientSoundRef;
	
	//Other
	UFUNCTION()
	void UpgradeTownHall(FString _TownHallID);
	
	UFUNCTION()
	void CheckEvents();
	
	UFUNCTION()
	void SelectBuilding(FString _BuildingID);

	UFUNCTION()
	class ABuilding* FindBuilding(FString _BuildingID);

	UFUNCTION()
	void ToggleBuildMode();

	UFUNCTION()
	void ToggleDestroyMode();

	UFUNCTION()
	void ClearBuildingTileMapArea();

	UFUNCTION()
	void InitializeTime();

	UFUNCTION()
	int16 ConvertCoordinateToIndex(int16 _i, int16 _j);

	UPROPERTY()
	TArray<class UTile*> Tiles;

	UPROPERTY()
	TMap<FString, class UEventBase*> DefaultEvents;

	UPROPERTY()
	TMap<FString, class ABuilding*> DefaultBuildings;

	UPROPERTY()
	TArray<class ABuilding*> Buildings;

	UFUNCTION()
	void DeleteBuildingInfo(class ABuilding* _DeletingBuilding);

	UPROPERTY()
	FStat CurrentStat;

	UPROPERTY()
	FStat Income;

	UFUNCTION()
	void UpdateStat();

	UFUNCTION()
	void RefreshIncome();
	
	UPROPERTY()
	int16 ClimateDebuffs;
	
	UPROPERTY()
	int16 MaxPopulation;

	UFUNCTION()
	void CheckEndGameState();
	
	UPROPERTY()
	class ABuilding* SelectedBuilding;

	UPROPERTY()
	int16 XMapSize;

	UPROPERTY()
	int16 YMapSize;

	UPROPERTY()
	FPaperTileInfo ExtraTileInfo;

	UFUNCTION()
	void MoveSelectionZone(int16& _PrevXTileCoord, int16& _PrevYTileCoord, int16 _XTileCoord, int16 _YTileCoord);

	UFUNCTION()
	void RefreshConnectionMap();

	UFUNCTION()
	void CheckConnection(int16 _XTileCoord, int16 _YTileCoord);

	UFUNCTION()
	void Action(int16 _XTileCoord, int16 _YTileCoord);
};
