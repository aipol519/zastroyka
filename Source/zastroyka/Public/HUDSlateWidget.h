// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DefaultHUD.h"

#include "SlateBasics.h"

class ZASTROYKA_API HUDSlateWidget : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(HUDSlateWidget) : _HUDOwnerArg(){}

	//Arguments to pass to a widget
	SLATE_ARGUMENT(TWeakObjectPtr<class ADefaultHUD>, HUDOwnerArg)
	SLATE_ARGUMENT(class ADefaultGameState*, DefaultGameStateArg)

	SLATE_END_ARGS()

public:
	void Construct(const FArguments& InArgs);
	FReply BuildButtonClicked();

	class ADefaultGameState* DefaultGameStateRef;

private:
	TWeakObjectPtr<class ADefaultHUD> HUDOwner;

};
