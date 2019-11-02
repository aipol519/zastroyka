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

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* ShopBorderAnimation;

};
