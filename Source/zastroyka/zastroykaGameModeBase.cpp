// Fill out your copyright notice in the Description page of Project Settings.


#include "zastroykaGameModeBase.h"
#include "PlayerPawn.h"
#include "GamePlayerController.h"
#include "DefaultHUD.h"
#include "DefaultGameState.h"

AzastroykaGameModeBase::AzastroykaGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AGamePlayerController::StaticClass();
	HUDClass = ADefaultHUD::StaticClass();
	GameStateClass = ADefaultGameState::StaticClass();

}
