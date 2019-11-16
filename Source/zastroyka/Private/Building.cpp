// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Tile.h"

#include "DefaultGameState.h"
#include "DefaultHUD.h"

#include "Components/StaticMeshComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	MeshComponent->OnClicked.AddDynamic(this, &ABuilding::OnBuildingClicked);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetNotifyRigidBodyCollision(true);
	MeshComponent->SetCollisionProfileName("BlockAll");
	
}

void ABuilding::Initialize(int16 _XSize, int16 _YSize, int32 _Cost, EBuldingType _BuildingType, FStat _Income)
{
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());
	
	XSize = _XSize;
	YSize = _YSize;
	Cost = _Cost;

	AnchorCoord = 0;
	
	BuildingType = _BuildingType;

	isBuildingConnected = false;
	
	Income.Climate = _Income.Climate;
	Income.Money = _Income.Money;
	Income.Population = _Income.Population;
	Income.Employment = _Income.Employment;
	
}

void ABuilding::OnBuildingClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (DefaultGameStateRef->IsDestroyModeEnabled)
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "DESTROY HOUSE");
		DefaultGameStateRef->DeleteBuildingInfo(this);
		this->Destroy();
		//удаление клеток, удаление здания из списка референсов
	}
	else
	{
		TArray<AActor*> FoundHUDs;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultHUD::StaticClass(), FoundHUDs);
		Cast<ADefaultHUD>(FoundHUDs[0])->AddBuildingInfoWidget();
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

ABuilding* ABuilding::Place(TArray<UTile*> _Tiles, UPaperTileMapComponent* _MainTilemapComponent, int16 _XTileCoord, int16 _YTileCoord)
{
	
	FPaperTileInfo ExtraTileInfo = _Tiles[0]->TileInfo;
	ExtraTileInfo.PackedTileIndex = 3;

	AnchorCoord = DefaultGameStateRef->ConvertCoordinateToIndex(_XTileCoord - div(XSize, 2).quot, _YTileCoord - div(YSize, 2).quot);

	for (int i = _XTileCoord + div(XSize, 2).quot + div(XSize, 2).rem - 1; i >= _XTileCoord - div(XSize, 2).quot; i--)
	{
		for (int j = _YTileCoord + div(YSize, 2).quot + div(YSize, 2).rem - 1; j >= _YTileCoord - div(YSize, 2).quot; j--)
		{
			_Tiles[DefaultGameStateRef->ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED_TILE;
			_Tiles[DefaultGameStateRef->ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 0;
			_MainTilemapComponent->SetTile(i, j, 0, ExtraTileInfo);

		}
	}

	ABuilding* NewBuilding = GetWorld()->SpawnActor<ABuilding>(
		FVector(_Tiles[AnchorCoord]->XTileCoord * 32.0f + 16.0f, _Tiles[AnchorCoord]->YTileCoord * 32.0f + 16.0f, 0.0f),
		FRotator(0.0f, 0.0f, 0.0f), FActorSpawnParameters());

	NewBuilding->Initialize(XSize, YSize, Cost, BuildingType, Income);
	NewBuilding->AnchorCoord = AnchorCoord;

	switch (BuildingType)
	{
	case STAND_BUILDING:
		NewBuilding->MeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Game/geometry/stand/stand"), NULL, LOAD_None, NULL));
		break;
	case HUT_BUILDING:
		NewBuilding->MeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Game/geometry/hut/hut"), NULL, LOAD_None, NULL));
		break;
	default:
		NewBuilding->MeshComponent->SetStaticMesh(nullptr);
		break;
	}

	return NewBuilding;
	
}