// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopBuldingButton.h"

#include "DefaultGameState.h"
#include "Engine.h"

UShopBuldingButton::UShopBuldingButton()
{
	BuildingID = "NONE";

	this->OnClicked.AddDynamic(this, &UShopBuldingButton::TranslateBuilding);

}

void UShopBuldingButton::TranslateBuilding()
{
	ADefaultGameState* DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	DefaultGameStateRef->SelectBuilding(BuildingID);

}
