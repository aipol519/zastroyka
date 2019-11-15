// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"

#include "HUDWidgetUMG.h"
#include "ShopWidgetUMG.h"
#include "CameraControlWidgetUMG.h"
#include "BuildingInfoWidgetUMG.h"
#include "DefaultGameState.h"

#include "GamePlayerController.h"
#include "Kismet/GameplayStatics.h"

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

void ADefaultHUD::AddBuildingInfoWidget()
{
	BuildingInfoWidgetRef = CreateWidget<UBuildingInfoWidgetUMG>(GetWorld(), BuildingInfoWidgetClass);

	float MousePositionX, MousePositionY;

	Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetMousePosition(MousePositionX, MousePositionY);

	BuildingInfoWidgetRef->SetLocation(MousePositionX, MousePositionY);
	BuildingInfoWidgetRef->AddToViewport();
}