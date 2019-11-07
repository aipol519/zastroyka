// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class ZASTROYKA_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();
	//ABuilding(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name);

	void Initialize(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name);

	int16 XSize, YSize;
	int32 Cost;

	FString Name;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
