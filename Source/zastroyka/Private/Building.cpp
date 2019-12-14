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
	//MeshComponent->SetCollisionProfileName("BlockAll");

	RootComponent = MeshComponent;
	
}

void ABuilding::Initialize(int16 _XSize, int16 _YSize, int32 _Cost, FStat _Income, bool _IsRoadBuilding, FString _BuildingName, AActor* _Owner)
{
	SetOwner(_Owner);
	DefaultGameStateRef = Cast<ADefaultGameState>(GetOwner());
	
	XSize = _XSize;
	YSize = _YSize;
	Cost = _Cost;

	AnchorCoordIndex = 0;
	
	IsRoadBuilding = _IsRoadBuilding;

	BuildingName = _BuildingName;

	IsBuildingConnected = false;
	
	Income.Climate = _Income.Climate;
	Income.Money = _Income.Money;
	Income.Population = _Income.Population;
	Income.Employment = _Income.Employment;
	
}

void ABuilding::OnBuildingClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (DefaultGameStateRef->IsDestroyModeEnabled)
	{
		if (BuildingName != "town_hall_lvl1" && BuildingName != "town_hall_lvl2" && BuildingName != "town_hall_lvl3")
		{
			GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "DESTROY HOUSE");
			DefaultGameStateRef->DeleteBuildingInfo(this);
			Destroy();
			ConditionalBeginDestroy();
		}
	}
	else if (!DefaultGameStateRef->IsBuildModeEnabled)
	{
		TArray<AActor*> FoundHUDs;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADefaultHUD::StaticClass(), FoundHUDs);
		//Cast<ADefaultHUD>(FoundHUDs[0])->AddBuildingInfoWidget();
	}
}

void ABuilding::ChangeTransparency(bool _IsTransparent)
{
	if (_IsTransparent)
	{
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(NULL, *FString("/Game/geometry/" + BuildingName + "/" + BuildingName + "_texture_material_transparent"), NULL, LOAD_None, NULL));
		MeshComponent->SetCollisionProfileName("UnclickableBuilding");
	}
	else
	{
		MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(NULL, *FString("/Game/geometry/" + BuildingName + "/" + BuildingName + "_texture_material"), NULL, LOAD_None, NULL));
		
		MeshComponent->SetCollisionProfileName("ClickableBuilding");
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

	AnchorCoordIndex = DefaultGameStateRef->ConvertCoordinateToIndex(_XTileCoord - div(XSize, 2).quot, _YTileCoord - div(YSize, 2).quot);

	for (int i = _XTileCoord + div(XSize, 2).quot + div(XSize, 2).rem - 1; i >= _XTileCoord - div(XSize, 2).quot; i--)
	{
		for (int j = _YTileCoord + div(YSize, 2).quot + div(YSize, 2).rem - 1; j >= _YTileCoord - div(YSize, 2).quot; j--)
		{
			DefaultGameStateRef->Tiles[DefaultGameStateRef->ConvertCoordinateToIndex(i, j)]->TileType = BUILDING_RESTRICTED_TILE;
			DefaultGameStateRef->Tiles[DefaultGameStateRef->ConvertCoordinateToIndex(i, j)]->TileInfo.PackedTileIndex = 0;
			DefaultGameStateRef->MainTilemapComponent->SetTile(i, j, 0, DefaultGameStateRef->ExtraTileInfo);
		}
	}

	ABuilding* NewBuilding = DefaultGameStateRef->WorldRef->SpawnActor<ABuilding>(
		FVector(DefaultGameStateRef->Tiles[AnchorCoordIndex]->XTileCoord * 32.0f + 16.0f, DefaultGameStateRef->Tiles[AnchorCoordIndex]->YTileCoord * 32.0f + 16.0f, 0.0f),
		FRotator(0.0f, 0.0f, 0.0f), 
		FActorSpawnParameters());
	
	NewBuilding->Initialize(XSize, YSize, Cost, Income, IsRoadBuilding, BuildingName, GetOwner());
	NewBuilding->AnchorCoordIndex = AnchorCoordIndex;
	
	NewBuilding->MeshComponent->SetStaticMesh(LoadObject<UStaticMesh>(NULL, *FString("/Game/geometry/" + BuildingName + "/" + BuildingName), NULL, LOAD_None, NULL));
	NewBuilding->MeshComponent->SetMaterial(0, LoadObject<UMaterialInterface>(NULL, *FString("/Game/geometry/" + BuildingName + "/" + BuildingName + "_texture_material_transparent"), NULL, LOAD_None, NULL));
	NewBuilding->MeshComponent->SetCollisionProfileName("UnclickableBuilding");
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, NewBuilding->MeshComponent->GetFullName());

	return NewBuilding;
	
}