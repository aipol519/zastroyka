// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "Engine.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "DefaultGameState.h"

AGamePlayerController::AGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	MouseWorldPosition = FVector(0.0f, 0.0f, 0.0f);
	XTileCoord = 0;
	YTileCoord = 0;
    
}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Converting mouse position to tile coordinates
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	XTileCoord = FMath::FloorToInt(HitResult.Location.X / 32.0f);
	YTileCoord = FMath::FloorToInt(HitResult.Location.Y / 32.0f);

	TestOutput = FString::Printf(*("X: " + FString::FromInt(XTileCoord) + " Y: " + FString::FromInt(YTileCoord) + " " + FString::FromInt(DefaultGameStateRef->XMapSize * YTileCoord + XTileCoord)));
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TestOutput);

}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Getting instance of GameState
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

}