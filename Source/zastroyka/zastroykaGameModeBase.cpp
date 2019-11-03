// Fill out your copyright notice in the Description page of Project Settings.


#include "zastroykaGameModeBase.h"

#include "PlayerPawn.h"
#include "GamePlayerController.h"
#include "DefaultHUD.h"
#include "DefaultGameState.h"

#include "UObject/ConstructorHelpers.h" 

#include "Components/TimelineComponent.h"
#include "Engine.h"
#include "HUDWidgetUMG.h"
#include "TextBlock.h"

AzastroykaGameModeBase::AzastroykaGameModeBase()
{
	DefaultPawnClass = APlayerPawn::StaticClass();
	PlayerControllerClass = AGamePlayerController::StaticClass();
	GameStateClass = ADefaultGameState::StaticClass();

	static ConstructorHelpers::FClassFinder<ADefaultHUD> HUDClassFinder(TEXT("/Game/blueprints/DefaultHUDBlueprint"));
	HUDClass = HUDClassFinder.Class;

	MainTimeline = NewObject<UTimelineComponent>(this, FName("MainTimeline"));
	MainTimeline->CreationMethod = EComponentCreationMethod::Native;

	MainTimeline->SetLooping(true);
	MainTimeline->SetTimelineLength(1.0f);
	MainTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);

	FOnTimelineEvent TimelineEvent;
	TimelineEvent.BindUFunction(this, FName("TimelineTick"));

	MainTimeline->AddEvent(0.0f, TimelineEvent);

	MainTimeline->SetPlaybackPosition(0.0f, false);
	MainTimeline->SetPlayRate(1.0f);

}

void AzastroykaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

	PlayTimeline();

}

void AzastroykaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AzastroykaGameModeBase::PlayTimeline()
{
	if (MainTimeline != NULL)
	{
		MainTimeline->PlayFromStart();
	}
}

void AzastroykaGameModeBase::TimelineTick()
{
	CalculateIncome();
}


void AzastroykaGameModeBase::CalculateIncome()
{
	DefaultGameStateRef->CurrentStat->Money += DefaultGameStateRef->Income->Money;
	DefaultGameStateRef->CurrentStat->Population += DefaultGameStateRef->Income->Population;
	DefaultGameStateRef->CurrentStat->Climate += DefaultGameStateRef->Income->Climate;

	UpdateShopWidget();
}

void AzastroykaGameModeBase::UpdateShopWidget()
{
	HUDWidgetRef->CurrentMoney->SetText(FText::AsNumber(DefaultGameStateRef->CurrentStat->Money));
	HUDWidgetRef->CurrentPopulation->SetText(FText::AsNumber(DefaultGameStateRef->CurrentStat->Population));
	HUDWidgetRef->CurrentClimate->SetText(FText::AsNumber(DefaultGameStateRef->CurrentStat->Climate));

	HUDWidgetRef->MoneyIncome->SetText(FText::AsNumber(DefaultGameStateRef->Income->Money));
	HUDWidgetRef->PopulationIncome->SetText(FText::AsNumber(DefaultGameStateRef->Income->Population));
	HUDWidgetRef->ClimateIncome->SetText(FText::AsNumber(DefaultGameStateRef->Income->Climate));

}