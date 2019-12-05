// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopBuldingButton.h"

#include "DefaultGameState.h"
#include "Engine.h"
#include "Building.h"

UShopBuldingButton::UShopBuldingButton()
{
	OnClicked.AddDynamic(this, &UShopBuldingButton::TranslateBuilding);

}

void UShopBuldingButton::Initialize()
{
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());
	AvailableButtonStyle = WidgetStyle;

}

void UShopBuldingButton::CheckAvailability()
{
	if (DefaultGameStateRef->CurrentStat.Money - DefaultGameStateRef->FindBuilding(BuildingID)->Cost < 0)
	{
		SetStyle(UnavailableButtonStyle);
		SetIsEnabled(false);
	}
	else
	{
		SetStyle(AvailableButtonStyle);
		SetIsEnabled(true);
	}

}

void UShopBuldingButton::TranslateBuilding()
{
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	DefaultGameStateRef->SelectBuilding(BuildingID);

}
