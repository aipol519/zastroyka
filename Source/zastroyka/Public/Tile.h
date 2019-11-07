// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileMapActor.h"
#include "PaperTileSet.h"
#include "Tile.generated.h"

UENUM()
enum ETileType { GREEN, ROAD, BUILDING_ALLOWED, BUILDING_RESTRICTED, BUILDING_SELECTABLE };

UCLASS()
class ZASTROYKA_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	//ATile(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected);

	void ChangeInBuildMode(UPaperTileMapComponent* _MainTilemapComponent, bool _BuildFlag);

	FPaperTileInfo TileInfo;
	FPaperTileInfo GetTileInfo();
	void Initialize(int16 _XTileCoord, int16 _YTileCoord, FPaperTileInfo _TileInfo, ETileType _TileType, bool _IsTileConnected);

	bool IsTileConnected;
	int16 XTileCoord, YTileCoord;
	UPROPERTY()
	TEnumAsByte<ETileType> TileType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
