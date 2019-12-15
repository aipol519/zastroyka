// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidgetUMG.h"

#include "Button.h"
#include "TextBlock.h"
#include "Engine.h"
#include "DefaultHUD.h"
#include "DefaultGameState.h"
#include "Time.h"

#include "ShopWidgetUMG.h"
#include "MenuWidgetUMG.h"

void UHUDWidgetUMG::NativeConstruct()
{
	Super::NativeConstruct();

	//Getting game state object reference
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	//Binding event to buttons
	BuildModeButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::BuildButtonClicked);
	DestroyModeButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::DestroyButtonClicked);
	MainMenuButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::MainMenuButtonClicked);

	PauseButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::PauseButtonClicked);
	SpeedUpButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SpeedUpButtonClicked);
	SpeedDownButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::SpeedDownButtonClicked);

	DestroyModeButtonStyle = DestroyModeButton->WidgetStyle;
	PlayButtonStyle = PauseButton->WidgetStyle;
	SpeedUpButtonStyle = SpeedUpButton->WidgetStyle;
	SpeedDownButtonStyle = SpeedDownButton->WidgetStyle;
	
	DefaultGameStateRef->SetHUDWidgetRef(this);
	CurrentTimeRef = DefaultGameStateRef->CurrentTimeRef;

	IsMenuEnabled = false;

}

void UHUDWidgetUMG::BuildButtonClicked()
{
	if (!ShopWidgetRef->IsAnimationPlaying(ShopWidgetRef->ShopBorderAnimation))
	{
		if (!DefaultGameStateRef->IsDestroyModeEnabled)
		{
			DefaultGameStateRef->IsBuildModeEnabled ?
				ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Reverse) :
				ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Forward);
		}
		//BMB_Text->SetText(DefaultGameStateRef->IsBuildModeEnabled ? FText::FromString("Enter build mode") : FText::FromString("Exit build mode"));
		DefaultGameStateRef->ToggleBuildMode();
		CurrentTimeRef->Play();
		if (DefaultGameStateRef->IsBuildModeEnabled)
		{
			BMB_Text->SetText(FText::FromString("Exit build mode"));
			DestroyModeButton->SetStyle(DestroyModeButtonStyle);
			DestroyModeButton->SetVisibility(ESlateVisibility::Visible);
			SpeedDownButton->SetVisibility(ESlateVisibility::HitTestInvisible);
			PauseButton->SetVisibility(ESlateVisibility::HitTestInvisible);
			SpeedUpButton->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else
		{
			BMB_Text->SetText(FText::FromString("Enter build mode"));
			DestroyModeButton->SetStyle(ActiveDestroyModeButtonStyle);
			DestroyModeButton->SetVisibility(ESlateVisibility::Collapsed);
			SpeedDownButton->SetVisibility(ESlateVisibility::Visible);
			PauseButton->SetVisibility(ESlateVisibility::Visible);
			SpeedUpButton->SetVisibility(ESlateVisibility::Visible);
		}
		//DestroyModeButton->SetVisibility(DefaultGameStateRef->IsBuildModeEnabled ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}

void UHUDWidgetUMG::UpdateVisibleStat()
{
	CurrentMoney->SetText(FText::FromString(DefaultGameStateRef->GetMoneyLevel()));
	CurrentPopulation->SetText(FText::FromString(DefaultGameStateRef->GetPopulationLevel()));
	CurrentClimate->SetText(FText::FromString(DefaultGameStateRef->GetClimateLevel()));
	CurrentEmployment->SetText(FText::FromString(DefaultGameStateRef->GetEmploymentLevel()));
}

void UHUDWidgetUMG::UpdateVisibleDate()
{
	Day->SetText(FText::FromString(DefaultGameStateRef->GetDay()));
	Month->SetText(FText::FromString(DefaultGameStateRef->GetMonth()));
	Year->SetText(FText::FromString(DefaultGameStateRef->GetYear()));
}

void UHUDWidgetUMG::PauseButtonClicked()
{
	CurrentTimeRef->Play();
}

void UHUDWidgetUMG::SpeedUpButtonClicked()
{
	CurrentTimeRef->Faster();
}

void UHUDWidgetUMG::SpeedDownButtonClicked()
{
	CurrentTimeRef->Slower();
}

void UHUDWidgetUMG::SetTimeButtonsStyle()
{
	switch (CurrentTimeRef->GetCurrentTimeMode())
	{
	case NORMAL:
		SpeedDownButton->SetStyle(SpeedDownButtonStyle);
		PauseButton->SetStyle(ActivePauseButtonStyle);
		SpeedUpButton->SetStyle(SpeedUpButtonStyle);
		break;
	case FAST:
		SpeedDownButton->SetStyle(SpeedDownButtonStyle);
		PauseButton->SetStyle(PauseButtonStyle);
		SpeedUpButton->SetStyle(ActiveSpeedUpButtonStyle);
		break;
	case SLOW:
		SpeedDownButton->SetStyle(ActiveSpeedDownButtonStyle);
		PauseButton->SetStyle(PauseButtonStyle);
		SpeedUpButton->SetStyle(SpeedUpButtonStyle);
		break;
	case PAUSE:
		SpeedDownButton->SetStyle(SpeedDownButtonStyle);
		PauseButton->SetStyle(PlayButtonStyle);
		SpeedUpButton->SetStyle(SpeedUpButtonStyle);
		break;
	default:
		break;
	}
}

void UHUDWidgetUMG::DestroyButtonClicked()
{
	DefaultGameStateRef->ToggleDestroyMode();
	if (DefaultGameStateRef->IsDestroyModeEnabled)
	{
		DestroyModeButton->SetStyle(ActiveDestroyModeButtonStyle);
		ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Reverse);
	}
	else
	{
		DestroyModeButton->SetStyle(DestroyModeButtonStyle);
		ShopWidgetRef->PlayShopBorderAnimation(EUMGSequencePlayMode::Forward);
	}
}

void UHUDWidgetUMG::MainMenuButtonClicked()
{
	if (MenuWidgetRef->IsAnimationPlaying(MenuWidgetRef->MenuBorderAnimation))
	{
		return;
	}

	IsMenuEnabled ?
		MenuWidgetRef->PlayMenuBorderAnimation(EUMGSequencePlayMode::Reverse) :
		MenuWidgetRef->PlayMenuBorderAnimation(EUMGSequencePlayMode::Forward);
	
	MenuWidgetRef->SetVisibility(ESlateVisibility::Visible);

	IsMenuEnabled = !IsMenuEnabled;

}
