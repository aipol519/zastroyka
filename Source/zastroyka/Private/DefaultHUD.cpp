// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "CameraControlSlateWidget.h"
#include "HUDSlateWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "DefaultGameState.h"

#include "HUDWidgetUMG.h"
#include "CameraControlWidgetUMG.h"

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	////Joining widgets to variables
	//SAssignNew(CameraControlWidget, CameraControlSlateWidget).HUDOwnerArg(this).DefaultGameStateArg(Cast<ADefaultGameState>(GetWorld()->GetGameState()));
	//SAssignNew(HUDWidget, HUDSlateWidget).HUDOwnerArg(this).DefaultGameStateArg(Cast<ADefaultGameState>(GetWorld()->GetGameState()));

	////Adding widgets to screen
	//GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(CameraControlWidget.ToSharedRef()), 0);
	//GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(HUDWidget.ToSharedRef()), 1);

	//HUDWidget->SetVisibility(EVisibility::SelfHitTestInvisible);

	CameraControlWidgetRef = CreateWidget<UCameraControlWidgetUMG>(GetWorld(), CameraControlWidgetClass);
	CameraControlWidgetRef->AddToViewport();

	MainMenuWidgetRef = CreateWidget<UHUDWidgetUMG>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidgetRef->AddToViewport();

}