// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControlSlateWidget.h"

#include "SlateOptMacros.h"
#include "DefaultGameState.h"
#include "Engine.h"
#include "PlayerPawn.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void CameraControlSlateWidget::Construct(const FArguments& InArgs)
{
	HUDOwner = InArgs._HUDOwnerArg;
	DefaultGameStateRef = InArgs._DefaultGameStateArg;

	int16 CameraMovementDirection = 0;
	TBaseDelegate<TTypeWrapper<void>>::CreateSP(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, CameraMovementDirection);

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	.Padding(-20.0f)
	[
		SNew(SOverlay)
		//.Clipping(EWidgetClipping::Inherit)

		//Camera scrolling buttons
		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SVerticalBox)

				//Top-left
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(0))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]

				//Left
				+ SVerticalBox::Slot()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(1))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]
	
				//Bottom-left
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(2))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]
			]
	
			+ SHorizontalBox::Slot()
			[
				SNew(SVerticalBox)

				//Top
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Fill)
				.AutoHeight()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(7))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]

				//Empty space
				+ SVerticalBox::Slot()

				//Bottom
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Fill)
				.AutoHeight()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(3))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]
			]

			+ SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SVerticalBox)

				//Top-right
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Top)
				.HAlign(HAlign_Right)
				.AutoHeight()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(6))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]

				//Right
				+ SVerticalBox::Slot()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(5))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]

				//Bottom-right
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.AutoHeight()
				[
					SNew(SButton)
					.OnHovered(this, &CameraControlSlateWidget::PlayerMoveButtonHovered, int16(4))
					.OnUnhovered(this, &CameraControlSlateWidget::PlayerMoveButtonUnhovered)
				]
			]
		]
	];
}

void CameraControlSlateWidget::PlayerMoveButtonHovered(int16 _MovementDirection)
{
	DefaultGameStateRef->GetPlayerRef()->SelectMovementDirection(_MovementDirection);
}

void CameraControlSlateWidget::PlayerMoveButtonUnhovered()
{
	DefaultGameStateRef->GetPlayerRef()->StopMovingPlayer();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION