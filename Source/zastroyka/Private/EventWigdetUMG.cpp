// Fill out your copyright notice in the Description page of Project Settings.


#include "EventWigdetUMG.h"

#include "TextBlock.h"
#include "Button.h"
#include "EventBase.h"
#include "DefaultGameState.h"

void UEventWigdetUMG::NativeConstruct()
{
	AcceptButton->OnClicked.AddDynamic(this, &UEventWigdetUMG::AcceptButtonClicked);

	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());
	DefaultGameStateRef->SetEventWidgetRef(this);
}

void UEventWigdetUMG::AcceptButtonClicked()
{
	CurrentEventRef->ReadingEventDone();
	SetVisibility(ESlateVisibility::Hidden);
}

void UEventWigdetUMG::ShowUp(UEventBase* _CurrentEventRef)
{
	CurrentEventRef = _CurrentEventRef;
	HeaderText->SetText(FText::FromString(CurrentEventRef->GetName()));
	DescriptionText->SetText(FText::FromString(CurrentEventRef->GetDescription()));

	SetVisibility(ESlateVisibility::Visible);

}
