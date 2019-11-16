 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidgetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UHUDWidgetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void DestroyButtonClicked();
	
	UFUNCTION()
	void BuildButtonClicked();

	UFUNCTION()
	void PauseButtonClicked();

	UFUNCTION()
	void SppedUpButtonClicked();

	UFUNCTION()
	void SpeedDownButtonClicked();

	UFUNCTION()
	void UpdateVisibleStat();

	UFUNCTION()
	void UpdateVisibleIncome();

	UFUNCTION()
	void UpdateVisibleDate();

	UPROPERTY(meta = (BindWidget))
	class UButton* DestroyModeButton;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* BuildModeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BMB_Text;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentMoney;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentPopulation;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentClimate;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentEmployment;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MoneyIncome;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PopulationIncome;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Day;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Month;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Year;

	UPROPERTY(meta = (BindWidget))
	class UButton* PauseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SpeedUpButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* SpeedDownButton;
	
	class ADefaultGameState* DefaultGameStateRef;
	class ADefaultHUD* DefaultHUDRef;
	class UShopWidgetUMG* ShopWidgetRef;
	
};
