// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultHUD.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "DefaultGameState.h"

#include "HUDWidgetUMG.h"
#include "ShopWidgetUMG.h"
#include "CameraControlWidgetUMG.h"
//#include "BuildingInfoWidgetUMG.h"
#include "EventWigdetUMG.h"
#include "MenuWidgetUMG.h"

//#include "GamePlayerController.h"
//#include "Kismet/GameplayStatics.h"

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

	MenuWidgetRef = CreateWidget<UMenuWidgetUMG>(GetWorld(), MenuWidgetClass);
	MenuWidgetRef->SetVisibility(ESlateVisibility::Hidden);
	MenuWidgetRef->AddToViewport();

	EventWidgetRef = CreateWidget<UEventWigdetUMG>(GetWorld(), EventWidgetClass);
	EventWidgetRef->SetVisibility(ESlateVisibility::Hidden);
	EventWidgetRef->AddToViewport();
}

//Will be added in future releases

//void ADefaultHUD::AddBuildingInfoWidget()
//{
//	BuildingInfoWidgetRef = CreateWidget<UBuildingInfoWidgetUMG>(GetWorld(), BuildingInfoWidgetClass);
//
//	float MousePositionX, MousePositionY;
//
//	Cast<AGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->GetMousePosition(MousePositionX, MousePositionY);
//
//	BuildingInfoWidgetRef->SetLocation(MousePositionX, MousePositionY);
//	BuildingInfoWidgetRef->AddToViewport();
//}

UEventWigdetUMG* ADefaultHUD::GetEventWidget()
{
	return EventWidgetRef;
}

UMenuWidgetUMG* ADefaultHUD::GetMenuWidget()
{
	return MenuWidgetRef;
}