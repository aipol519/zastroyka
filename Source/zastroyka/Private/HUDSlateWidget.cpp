// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDSlateWidget.h"

#include "SlateOptMacros.h"
#include "DefaultGameState.h"
#include "Engine.h"
#include "PlayerPawn.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void HUDSlateWidget::Construct(const FArguments& InArgs)
{
	HUDOwner = InArgs._HUDOwnerArg;
	DefaultGameStateRef = InArgs._DefaultGameStateArg;

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
		
		//Build mode button
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.DesiredSizeScale(FVector2D(2.0f, 2.0f))
			.OnClicked(this, &HUDSlateWidget::BuildButtonClicked)
			[
				SNew(STextBlock)
				.Text(FText::FromString("Building mode"))
				.ColorAndOpacity(FLinearColor::Black)
				.Font(FSlateFontInfo(FPaths::GameContentDir() / TEXT("fonts/UpheavalPro.ttf"), 24, EFontHinting::None))
			]
		]
	];
}

FReply HUDSlateWidget::BuildButtonClicked()
{
	DefaultGameStateRef->ToggleBuildMode(!(DefaultGameStateRef->IsBuildModeEnabled));

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION