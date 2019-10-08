// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDSlateWidget.h"

#include "SlateOptMacros.h"
#include "GamePlayerController.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void HUDSlateWidget::Construct(const FArguments& InArgs)
{
	HUDOwner = InArgs._HUDOwnerArg;
	//PlayerControllerRef = Cast<AGamePlayerController>();

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Center)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			.DesiredSizeScale(FVector2D(2.0f, 2.0f))
			[
				SNew(STextBlock)
				.Text(FText::FromString("Enter build mode"))
				.ColorAndOpacity(FLinearColor::Black)
				.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 24))
			]
		]
	];

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION