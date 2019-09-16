// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "Engine.h"

AGamePlayerController::AGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	MouseWorldPosition = FVector(0.0f, 0.0f, 0.0f);

}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	MouseWorldPosition = HitResult.Location;
	TestOutput = FString::Printf(*MouseWorldPosition.ToString());
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TestOutput);

}