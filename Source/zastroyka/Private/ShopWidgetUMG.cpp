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

	ShopButtons.Add(RoadButton);
	ShopButtons.Add(HutButton);
	ShopButtons.Add(BarrackButton);
	ShopButtons.Add(StandButton);

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
