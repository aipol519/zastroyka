// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidgetUMG.h"

#include "Button.h"
#include "TextBlock.h"
#include "Engine.h"
#include "DefaultHUD.h"
#include "ShopWidgetUMG.h"
#include "DefaultGameState.h"
#include "Time.h"

void UHUDWidgetUMG::NativeConstruct()
{
	Super::NativeConstruct();

	//Getting game state object reference
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	//Binding event to build button clicked
	BuildModeButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::BuildButtonClicked);

	PauseButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::PauseButtonClicked);
	SpeedUpButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SppedUpButtonClicked);
	SpeedDownButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SpeedDownButtonClicked);
	
	DefaultGameStateRef->SetHUDWidgetRef(this);
}

void UHUDWidgetUMG::BuildButtonClicked()
{
	if (!ShopWidgetRef->IsAnimationPlaying(ShopWidgetRef->ShopBorderAnimation))
	{
		DefaultGameStateRef->IsBuildModeEnabled ?
			ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Reverse) :
			ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Forward);

		BMB_Text->SetText(DefaultGameStateRef->IsBuildModeEnabled ? FText::FromString("Enter build mode") : FText::FromString("Exit build mode"));
		DefaultGameStateRef->ToggleBuildMode(!(DefaultGameStateRef->IsBuildModeEnabled));
	}
}

void UHUDWidgetUMG::UpdateVisibleStat()
{
	CurrentMoney->SetText(FText::AsNumber(DefaultGameStateRef->CurrentStat->Money));
	CurrentPopulation->SetText(FText::AsNumber(DefaultGameStateRef->CurrentStat->Population));
	CurrentClimate->SetText(FText::AsNumber(DefaultGameStateRef->CurrentStat->Climate));
}

void UHUDWidgetUMG::UpdateVisibleIncome()
{
	MoneyIncome->SetText(FText::AsNumber(DefaultGameStateRef->Income->Money));
	PopulationIncome->SetText(FText::AsNumber(DefaultGameStateRef->Income->Population));
	ClimateIncome->SetText(FText::AsNumber(DefaultGameStateRef->Income->Climate));
}

void UHUDWidgetUMG::PauseButtonClicked()
{
	DefaultGameStateRef->CurrentTimeRef->Play();
}

void UHUDWidgetUMG::SppedUpButtonClicked()
{
	DefaultGameStateRef->CurrentTimeRef->Faster();
}

void UHUDWidgetUMG::SpeedDownButtonClicked()
{
	DefaultGameStateRef->CurrentTimeRef->Slower();
}