// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidgetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UShopWidgetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	void PlayShopBorderAnimation(EUMGSequencePlayMode::Type _PlayMode);

	void CheckAvailabilityForButtons();

	TArray<class UShopBuldingButton*> ShopButtons;

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* ShopBorderAnimation;

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* RoadButton;

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* HutButton;

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* BarrackButton;

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* StandButton;

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* FarmButton;

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* TownHallLvl2Button;

};
