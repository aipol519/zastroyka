// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "HUDSlateWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Engine/GameViewportClient.h"
#include "GamePlayerController.h"

void ADefaultHUD::BeginPlay()
{
	HUDWidget = SNew(HUDSlateWidget).HUDOwnerArg(this).PlayerControllerRef(Cast<AGamePlayerController>(GetWorld()->GetFirstPlayerController()));
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(HUDWidget.ToSharedRef()));
	HUDWidget->SetVisibility(EVisibility::Visible);

}