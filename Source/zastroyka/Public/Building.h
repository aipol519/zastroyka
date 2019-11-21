// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefaultGameState.h"
#include "Building.generated.h"

UCLASS()
class ZASTROYKA_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	void Initialize(int16 _XSize, int16 _YSize, int32 _Cost, FStat _Income, bool _IsRoadBuilding, FString _BuildingName);

	UFUNCTION()
	void OnBuildingClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	ABuilding* Place(TArray<class UTile*> _Tiles, class UPaperTileMapComponent* _MainTilemapComponent, int16 _XTileCoord, int16 _YTileCoord);

	int16 AnchorCoord;
	int16 XSize, YSize;
	int32 Cost;

	bool IsBuildingConnected;
	
	bool IsRoadBuilding;

	struct FStat Income;

	FString BuildingName;

	ADefaultGameState* DefaultGameStateRef;
	UStaticMeshComponent* MeshComponent;
 	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
