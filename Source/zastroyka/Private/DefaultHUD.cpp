// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "HUDWidgetUMG.h"
#include "ShopWidgetUMG.h"
#include "CameraControlWidgetUMG.h"
#include "DefaultGameState.h"

void ADefaultHUD::BeginPlay()
{
	Super::BeginPlay();

	HUDWidgetRef = CreateWidget<UHUDWidgetUMG>(GetWorld(), HUDWidgetClass);
	HUDWidgetRef->AddToViewport();

	ShopWidgetRef = CreateWidget<UShopWidgetUMG>(GetWorld(), ShopWidgetClass);
	HUDWidgetRef->ShopWidgetRef = ShopWidgetRef;
	ShopWidgetRef->AddToViewport();

	CameraControlWidgetRef = CreateWidget<UCameraControlWidgetUMG>(GetWorld(), CameraControlWidgetClass);
	CameraControlWidgetRef->AddToViewport();
}