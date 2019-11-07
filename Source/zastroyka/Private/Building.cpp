// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

