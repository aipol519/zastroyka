// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDSlateWidget.h"

#include "SlateOptMacros.h"
#include "DefaultGameState.h"
#include "Engine.h"

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
			
			+ SOverlay::Slot()
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Left)
					.AutoHeight()
					[
						SNew(SButton)
					]

					+ SVerticalBox::Slot()
					[
						SNew(SButton)
					]

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Left)
					.AutoHeight()
					[
						SNew(SButton)
					]
				]

				+ SHorizontalBox::Slot()
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Fill)
					.AutoHeight()
					[
						SNew(SButton)
					]

					+ SVerticalBox::Slot()

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Fill)
					.AutoHeight()
					[
						SNew(SButton)
					]
					
				]

				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SVerticalBox)

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Right)
					.AutoHeight()
					[
						SNew(SButton)
					]

					+ SVerticalBox::Slot()
					[
						SNew(SButton)
					]

					+ SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Right)
					.AutoHeight()
					[
						SNew(SButton)
					]
				]
			]

			//+ SOverlay::Slot()
			//.VAlign(VAlign_Bottom)
			//.HAlign(HAlign_Fill)
			//[
			//	SNew(SButton)
			//]
		];



}

FReply HUDSlateWidget::BuildButtonClicked()
{
	if (DefaultGameStateRef->IsBuildModeEnabled)
	{
		DefaultGameStateRef->DisableBuildMode();
	}
	else
	{
		DefaultGameStateRef->EnableBuildMode();
	}

	return FReply::Handled();
}

void HUDSlateWidget::CameraButtonHovered()
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, "Hovered");

}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION