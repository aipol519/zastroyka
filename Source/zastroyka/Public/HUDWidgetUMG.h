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
	void BuildButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UButton* BuildModeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BMB_Text;

	class ADefaultGameState* DefaultGameStateRef;
	
};
