// Fill out your copyright notice in the Description page of Project Settings.


#include "EventWigdetUMG.h"

#include "TextBlock.h"
#include "Button.h"

void UEventWigdetUMG::NativeConstruct()
{
	AcceptButton->OnClicked.AddDynamic(this, &UEventWigdetUMG::AcceptButtonClicked);

}

void UEventWigdetUMG::AcceptButtonClicked()
{
	this->RemoveFromViewport();
	
}

void UEventWigdetUMG::InitializeEventWidget(FString _HeaderText, FString _DescriptionText)
{
	HeaderText->SetText(FText::FromString(_HeaderText));
	DescriptionText->SetText(FText::FromString(_DescriptionText));

	this->AddToViewport();

}
