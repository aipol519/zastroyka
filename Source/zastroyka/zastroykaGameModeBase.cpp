// Fill out your copyright notice in the Description page of Project Settings.

#include "zastroykaGameModeBase.h"
#include "PlayerPawn.h"
#include "GamePlayerController.h"
#include "DefaultHUD.h"
#include "DefaultGameState.h"
#include "UObject/ConstructorHelpers.h" 
#include "Engine.h"

AzastroykaGameModeBase::AzastroykaGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AGamePlayerController::StaticClass();
	GameStateClass = ADefaultGameState::StaticClass();

	static ConstructorHelpers::FClassFinder<ADefaultHUD> HUDClassFinder(TEXT("/Game/blueprints/DefaultHUDBlueprint"));
	HUDClass = HUDClassFinder.Class;
}

void AzastroykaGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());
	DefaultGameStateRef->GameModeBaseRef = this;
	//DefaultGameStateRef->InitializeTime();
}

void AzastroykaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}