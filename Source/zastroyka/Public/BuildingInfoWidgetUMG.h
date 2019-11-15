// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingInfoWidgetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UBuildingInfoWidgetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void SetLocation(float _X, float _Y);

	UFUNCTION()
	void CloseWindow();

	UPROPERTY(meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Root;
	
};
