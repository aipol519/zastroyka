// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "HUDSlateWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "DefaultGameState.h"

void ADefaultHUD::BeginPlay()
{
	//Initializing wigdet and adding it to viewport
	HUDWidget = SNew(HUDSlateWidget).HUDOwnerArg(this).DefaultGameStateArg(Cast<ADefaultGameState>(GetWorld()->GetGameState()));
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(HUDWidget.ToSharedRef()));
	HUDWidget->SetVisibility(EVisibility::Visible);

}