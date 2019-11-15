// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Tile.h"

#include "DefaultGameState.h"
#include "DefaultHUD.h"

#include "Engine/StaticMesh.h"
#include "Components/StaticMeshComponent.h"

#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	MeshComponent->OnClicked.AddDynamic(this, &ABuilding::OnBuildingClicked);
	MeshComponent->SetupAttachment(RootComponent);

	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingMeshAsset(TEXT("StaticMesh'/Game/geometry/town_hall_lvl1.town_hall_lvl1'"));
	//Mesh->SetStaticMesh(BuildingMeshAsset.Object);
}

//ABuilding::ABuilding(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name)
//{
//	XSize = _XSize;
//	YSize = _YSize;
//	Cost = _Cost;
//
//	Name = _Name;
//}

void ABuilding::Initialize(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name, FStat _Income)
{
	XSize = _XSize;
	YSize = _YSize;
	Cost = _Cost;

	Name = _Name;
	
	//if (Name == "Road")
	//{
	//	Mesh->SetStaticMesh(nullptr);
	//}
	//if (Name == "Larek")
	//{
	//	static ConstructorHelpers::FObjectFinder<UStaticMesh> BuildingMeshAsset(TEXT("StaticMesh'/Game/geometry/stand/stand.stand'"));
	//	Mesh->SetStaticMesh(BuildingMeshAsset.Object);
	//}
	//else
	//{
		//Mesh->SetStaticMesh(test);
	//}
	
	Income.Climate = _Income.Climate;
	Income.Money = _Income.Money;
	Income.Population = _Income.Population;
	Income.Employment = _Income.Employment;
}

void ABuilding::OnBuildingClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	TArray<AActor*> FoundHUDs;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultHUD::StaticClass(), FoundHUDs);
	Cast<ADefaultHUD>(FoundHUDs[0])->AddBuildingInfoWidget();
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

	int16 FirstTileIndex;
	FirstTileIndex = _TempGameStateRef->ConvertCoordinateToIndex(_XTileCoord - div(XSize, 2).quot, _YTileCoord - div(YSize, 2).quot);

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
		//ABuilding* Test = GetWorld()->SpawnActor<ThisClass>(FVector((_XTileCoord - div(XSize, 2).quot) * 32.0f, (_YTileCoord  - div(YSize, 2).quot) * 32.0f, 0.0f), FRotator(0.0f,0.0f,0.0f), FActorSpawnParameters());

		ABuilding* Test = GetWorld()->SpawnActor<ThisClass>(FVector(_Tiles[FirstTileIndex]->XTileCoord * 32.0f + 16.0f, _Tiles[FirstTileIndex]->YTileCoord * 32.0f + 16.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());
		Test->MeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Game/geometry/stand/stand"), NULL, LOAD_None, NULL));
		Test->MeshComponent->SetNotifyRigidBodyCollision(true);
		Test->MeshComponent->SetCollisionProfileName("BlockAll");

	}
	else
	{
		_Tiles[_TempGameStateRef->ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileType = ROAD;
		_Tiles[_TempGameStateRef->ConvertCoordinateToIndex(_XTileCoord, _YTileCoord)]->TileInfo.PackedTileIndex = 1;
		_MainTilemapComponent->SetTile(_XTileCoord, _YTileCoord, 0, ExtraTileInfo);
	}

	//_TempGameStateRef->RefreshConnectionMap();
	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Building Placed");
}