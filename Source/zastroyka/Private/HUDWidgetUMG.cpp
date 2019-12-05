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
	SpeedUpButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SpeedUpButtonClicked);
	SpeedDownButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SpeedDownButtonClicked);

	PlayButtonStyle = PauseButton->WidgetStyle;
	SpeedUpButtonStyle = SpeedUpButton->WidgetStyle;
	SpeedDownButtonStyle = SpeedDownButton->WidgetStyle;
	
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
		DefaultGameStateRef->ToggleBuildMode();
		PauseButtonClicked();
		DestroyModeButton->SetVisibility(DefaultGameStateRef->IsBuildModeEnabled ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UHUDWidgetUMG::UpdateVisibleStat()
{
	//CurrentMoney->SetText(FText::FromString(FString::SanitizeFloat(DefaultGameStateRef->CurrentStat.Money)));
	//CurrentPopulation->SetText(FText::FromString(FString::SanitizeFloat(DefaultGameStateRef->CurrentStat.Population)));
	//CurrentClimate->SetText(FText::FromString(FString::SanitizeFloat(DefaultGameStateRef->CurrentStat.Climate * 100) + " %"));
	//CurrentEmployment->SetText(FText::FromString(FString::SanitizeFloat(DefaultGameStateRef->CurrentStat.Employment * 100) + " %"));
	CurrentMoney->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat.Money)));
	CurrentPopulation->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat.Population)));
	CurrentClimate->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat.Climate) + "%"));
	CurrentEmployment->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->CurrentStat.Employment) + "%"));
}

void UHUDWidgetUMG::UpdateVisibleIncome()
{
	//MoneyIncome->SetText(FText::FromString((DefaultGameStateRef->Income.Money >= 0) ? "+" + FString::SanitizeFloat(DefaultGameStateRef->Income.Money) : (FString::SanitizeFloat(DefaultGameStateRef->Income.Money))));
	//PopulationIncome->SetText(FText::FromString("/" + FString::SanitizeFloat(DefaultGameStateRef->MaxPopulation)));
	MoneyIncome->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->Income.Money)));
	PopulationIncome->SetText(FText::FromString(FString::FromInt(DefaultGameStateRef->Income.Population)));
}

void UHUDWidgetUMG::UpdateVisibleDate()
{
	Day->SetText(FText::FromString("D: " + FString::FromInt(DefaultGameStateRef->CurrentTimeRef->GetDay())));
	Month->SetText(FText::FromString("M: " + FString::FromInt(DefaultGameStateRef->CurrentTimeRef->GetMonth())));
	Year->SetText(FText::FromString("Y: " + FString::FromInt(DefaultGameStateRef->CurrentTimeRef->GetYear())));
}

void UHUDWidgetUMG::PauseButtonClicked()
{
	switch (DefaultGameStateRef->CurrentTimeRef->GetCurrentTimeMode())
	{
	case NORMAL:
	case FAST:
	case SLOW:
		PauseButton->SetStyle(PlayButtonStyle);
		SpeedUpButton->SetStyle(SpeedUpButtonStyle);
		SpeedDownButton->SetStyle(SpeedDownButtonStyle);
		break;
	case PAUSE:
		PauseButton->SetStyle(ActivePauseButtonStyle);
		break;
	default:
		break;
	}

	DefaultGameStateRef->CurrentTimeRef->Play();

}

void UHUDWidgetUMG::SpeedUpButtonClicked()
{
	switch (DefaultGameStateRef->CurrentTimeRef->GetCurrentTimeMode())
	{
	case NORMAL:
		PauseButton->SetStyle(PauseButtonStyle);
		SpeedUpButton->SetStyle(ActiveSpeedUpButtonStyle);
		break;
	case SLOW:
		PauseButton->SetStyle(ActivePauseButtonStyle);
		SpeedDownButton->SetStyle(SpeedDownButtonStyle);
		break;
	case PAUSE:
	case FAST:
	default:
		break;
	}

	DefaultGameStateRef->CurrentTimeRef->Faster();

}

void UHUDWidgetUMG::SpeedDownButtonClicked()
{
	switch (DefaultGameStateRef->CurrentTimeRef->GetCurrentTimeMode())
	{
	case NORMAL:
		SpeedDownButton->SetStyle(ActiveSpeedDownButtonStyle);
		PauseButton->SetStyle(PauseButtonStyle);
		break;
	case FAST:
		SpeedUpButton->SetStyle(SpeedUpButtonStyle);
		PauseButton->SetStyle(ActivePauseButtonStyle);
		break;
	case SLOW:
	case PAUSE:
	default:
		break;
	}

	DefaultGameStateRef->CurrentTimeRef->Slower();

}

void UHUDWidgetUMG::DestroyButtonClicked()
{
	DefaultGameStateRef->ToggleDestroyMode();
	DefaultGameStateRef->IsDestroyModeEnabled ?
		ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Reverse) :
		ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Forward);

}
