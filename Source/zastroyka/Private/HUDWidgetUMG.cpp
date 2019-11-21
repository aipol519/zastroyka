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
	DestroyModeButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::DestroyButtonClicked);

	PauseButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::PauseButtonClicked);
	SpeedUpButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SppedUpButtonClicked);
	SpeedDownButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SpeedDownButtonClicked);
	
	DefaultGameStateRef->SetHUDWidgetRef(this);
}

void UHUDWidgetUMG::BuildButtonClicked()
{
	if (!ShopWidgetRef->IsAnimationPlaying(ShopWidgetRef->ShopBorderAnimation) && !(DefaultGameStateRef->IsDestroyModeEnabled))
	{
		DefaultGameStateRef->IsBuildModeEnabled ?
			ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Reverse) :
			ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Forward);

		BMB_Text->SetText(DefaultGameStateRef->IsBuildModeEnabled ? FText::FromString("Enter build mode") : FText::FromString("Exit build mode"));
		DefaultGameStateRef->ToggleMode(true);
		DestroyModeButton->SetVisibility(DefaultGameStateRef->IsBuildModeEnabled ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UHUDWidgetUMG::UpdateVisibleStat()
{
	CurrentMoney->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat->Money)));
	CurrentPopulation->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat->Population)));
	CurrentClimate->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat->Climate) + " %"));
	CurrentEmployment->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat->Employment) + " %"));
}

void UHUDWidgetUMG::UpdateVisibleIncome()
{
	MoneyIncome->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->Income->Money)));
	PopulationIncome->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->Income->Population)));
}

void UHUDWidgetUMG::UpdateVisibleDate()
{
	Day->SetText(FText::FromString("D: " + FString::FromInt(DefaultGameStateRef->CurrentTimeRef->Day)));
	Month->SetText(FText::FromString("M: " + FString::FromInt(DefaultGameStateRef->CurrentTimeRef->Month)));
	Year->SetText(FText::FromString("Y: " + FString::FromInt(DefaultGameStateRef->CurrentTimeRef->Year)));
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

void UHUDWidgetUMG::DestroyButtonClicked()
{
	if (!(DefaultGameStateRef->IsBuildModeEnabled))
	{
		DefaultGameStateRef->ToggleMode(false);
	}
}
