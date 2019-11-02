// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidgetUMG.h"

#include "Button.h"
#include "TextBlock.h"

#include "Engine.h"
#include "DefaultGameState.h"
#include "DefaultHUD.h"
#include "ShopWidgetUMG.h"

void UHUDWidgetUMG::NativeConstruct()
{
	Super::NativeConstruct();

	//Getting game state object reference
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	//Binding event to build button clicked
	BuildModeButton->OnClicked.AddDynamic(this, &UHUDWidgetUMG::BuildButtonClicked);

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