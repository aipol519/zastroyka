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
	void AcceptButtonClicked();

	UFUNCTION()
	void InitializeEventWidget(FString _HeaderText, FString _DescriptionText);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HeaderText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	class UButton* AcceptButton;
	
};
