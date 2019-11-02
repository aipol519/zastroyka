// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidgetUMG.h"

#include "WidgetAnimation.h"

void UShopWidgetUMG::NativeConstruct()
{


}

void UShopWidgetUMG::PlayShopBorderAnimation(EUMGSequencePlayMode::Type _PlayMode)
{
	PlayAnimation(ShopBorderAnimation, 0.0f, 1, _PlayMode, 1.0f);

}