// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidgetUMG.h"

#include "Button.h"
#include "DefaultGameState.h"
#include "Time.h"
#include "GamePlayerController.h"

#include "Kismet/GameplayStatics.h"

void UMenuWidgetUMG::NativeConstruct()
{
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	CurrentTimeRef = DefaultGameStateRef->CurrentTimeRef;

	ResumeButton->OnClicked.AddDynamic(this, &UMenuWidgetUMG::ResumeButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMenuWidgetUMG::QuitButtonClicked);

}

void UMenuWidgetUMG::ResumeButtonClicked()
{
	CurrentTimeRef->Play();

	SetVisibility(ESlateVisibility::Collapsed);

}

void UMenuWidgetUMG::QuitButtonClicked()
{
	UKismetSystemLibrary::QuitGame(DefaultGameStateRef->WorldRef, DefaultGameStateRef->PlayerControllerRef, EQuitPreference::Quit, true);
}
