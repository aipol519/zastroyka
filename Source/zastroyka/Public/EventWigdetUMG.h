// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventWigdetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UEventWigdetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ShowUp(class UEventBase* _CurrentEventRef);

private:
	
	UFUNCTION()
	void AcceptButtonClicked();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HeaderText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	class UButton* AcceptButton;

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY()
	UEventBase* CurrentEventRef;
};
