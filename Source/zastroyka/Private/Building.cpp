// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Tile.h"
#include "DefaultGameState.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	Placeholder = CreateDefaultSubobject<UStaticMeshComponent>(FName("Placeholder"));
	Placeholder->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Game/geometry/town_hall_lvl1.town_hall_lvl1'"));
	Placeholder->SetStaticMesh(SphereMeshAsset.Object);
}

//ABuilding::ABuilding(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name)
//{
//	XSize = _XSize;
//	YSize = _YSize;
//	Cost = _Cost;
//
//	Name = _Name;
//}

void ABuilding::Initialize(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name)
{
	XSize = _XSize;
	YSize = _YSize;
	Cost = _Cost;

	Name = _Name;

	if (Name == "Road")
	{
		Placeholder->SetStaticMesh(nullptr);
	}
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::Place(ADefaultGameState* _TempGameStateRef, TArray<UTile*>& _Tiles, UPaperTileMapComponent* _MainTilemapComponent, int16 _XTileCoord, int16 _YTileCoord)
{
	FPaperTileInfo ExtraTileInfo = _Tiles[0]->TileInfo;
	ExtraTileInfo.PackedTileIndex = 3;
	FVector test, test2;
	GetActorBounds(false, test, test2);
	if (Name != "Road")
	{
		for (int i = _XTileCoord + div(XSize, 2).quot + div(XSize, 2).rem - 1; i >= _XTileCoord - div(XSize, 2).quot; i--)
		{
			for (int j = _YTileCoord + div(YSize, 2).quot + div(YSize, 2).rem - 1; j >= _YTileCoord - div(YSize, 2).quot; j--)
			{
				_Tiles[_TempGameStateRef->ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED;
				_Tiles[_TempGameStateRef->ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 0;
				_MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);
			}
		}
		GetWorld()->SpawnActor<ThisClass>(FVector(_XTileCoord * 32.0f - test2.X, _YTileCoord * 32.0f - test2.Y, 0.0f), FRotator(), FActorSpawnParameters());
	}
	else
	{
		_Tiles[_TempGameStateRef->ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileType = ROAD;
		_Tiles[_TempGameStateRef->ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileInfo.PackedTileIndex = 1;
		_MainTilemapComponent->SetTile(_XTileCoord, _YTileCoord, 0, ExtraTileInfo);
	}

	_TempGameStateRef->RefreshConnectionMap();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Building Placed");
}