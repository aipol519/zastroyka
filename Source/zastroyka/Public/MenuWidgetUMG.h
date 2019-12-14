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
	void ResumeButtonClicked();

	UFUNCTION()
	void QuitButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY()
	class UTime* CurrentTimeRef;
	
};
