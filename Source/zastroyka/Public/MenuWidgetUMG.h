// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidgetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UMenuWidgetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OptionsButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

	UFUNCTION()
	void PlayMenuBorderAnimation(EUMGSequencePlayMode::Type _PlayMode);

	UPROPERTY(meta = (BindWidget))
	class UButton* OptionsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* MenuBorderAnimation;

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY()
	class UTime* CurrentTimeRef;
	
};
