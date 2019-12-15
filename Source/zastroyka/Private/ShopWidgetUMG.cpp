// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidgetUMG.h"

#include "DefaultGameState.h"

#include "WidgetAnimation.h"
#include "ShopBuldingButton.h"

void UShopWidgetUMG::NativeConstruct()
{
	//Getting game state object reference
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	DefaultGameStateRef->SetShopWidgetRef(this);

	ShopButtons.Add(TownHallLvl2Button);
	ShopButtons.Add(TownHallLvl3Button);

	ShopButtons.Add(RoadButton);

	ShopButtons.Add(HutButton);
	ShopButtons.Add(BarrackButton);
	ShopButtons.Add(StandButton);
	ShopButtons.Add(FarmButton);

	ShopButtons.Add(PanelBuildingButton);
	ShopButtons.Add(PlantButton);
	ShopButtons.Add(GroceryButton);

	ShopButtons.Add(ApartmentsButton);
	ShopButtons.Add(BusinessCenterButton);
	ShopButtons.Add(SupermarketButton);
	
	for (auto& Button : ShopButtons)
	{
		Button->Initialize();
	}

}

void UShopWidgetUMG::PlayShopBorderAnimation(EUMGSequencePlayMode::Type _PlayMode)
{
	PlayAnimation(ShopBorderAnimation, 0.0f, 1, _PlayMode, 1.0f);

}

void UShopWidgetUMG::CheckAvailabilityForButtons()
{
	for (auto& Button : ShopButtons)
	{
		Button->CheckAvailability();
	}

}

void UShopWidgetUMG::UpdateShopButtons(FString _TownHallID)
{
	switch (FCString::Atoi(*_TownHallID))
	{
	case 2:

		PanelBuildingButton->SetVisibility(ESlateVisibility::Visible);
		PlantButton->SetVisibility(ESlateVisibility::Visible);
		GroceryButton->SetVisibility(ESlateVisibility::Visible);

		TownHallLvl2Button->SetVisibility(ESlateVisibility::Collapsed);

		TownHallLvl3Button->SetVisibility(ESlateVisibility::Visible);

		break;
	case 3:

		ApartmentsButton->SetVisibility(ESlateVisibility::Visible);
		BusinessCenterButton->SetVisibility(ESlateVisibility::Visible);
		SupermarketButton->SetVisibility(ESlateVisibility::Visible);

		TownHallLvl3Button->SetVisibility(ESlateVisibility::Collapsed);

		break;
	default:
		break;
	}
}
