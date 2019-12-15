// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidgetUMG.h"

#include "Button.h"
#include "DefaultGameState.h"
#include "Time.h"
#include "GamePlayerController.h"
#include "WidgetAnimation.h"

#include "Kismet/GameplayStatics.h"

void UMenuWidgetUMG::NativeConstruct()
{
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	CurrentTimeRef = DefaultGameStateRef->CurrentTimeRef;

	OptionsButton->OnClicked.AddDynamic(this, &UMenuWidgetUMG::OptionsButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMenuWidgetUMG::QuitButtonClicked);

}

void UMenuWidgetUMG::OptionsButtonClicked()
{

	// ... //

}

void UMenuWidgetUMG::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(DefaultGameStateRef->WorldRef, DefaultGameStateRef->PlayerControllerRef, EQuitPreference::Quit, true);
}

void UMenuWidgetUMG::PlayMenuBorderAnimation(EUMGSequencePlayMode::Type _PlayMode)
{
	PlayAnimation(MenuBorderAnimation, 0.0f, 1, _PlayMode, 1.0f);
}
