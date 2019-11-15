// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingInfoWidgetUMG.h"

#include "Button.h"
#include "CanvasPanel.h"
#include "CanvasPanelSlot.h"

void UBuildingInfoWidgetUMG::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton->OnClicked.AddDynamic(this, &UBuildingInfoWidgetUMG::CloseWindow);

}

void UBuildingInfoWidgetUMG::SetLocation(float _X, float _Y)
{
	Cast<UCanvasPanelSlot>(Root->GetSlots()[0])->SetPosition(FVector2D(_X, _Y));
}

void UBuildingInfoWidgetUMG::CloseWindow()
{
	this->RemoveFromParent();

}
