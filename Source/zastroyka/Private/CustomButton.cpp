// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomButton.h"

#include "Engine.h"
#include "PlayerPawn.h"

UCustomButton::UCustomButton()
{
	ButtonType = EButtonType::BT_Direction;
	CameraDirection = 0;

	switch (ButtonType)
	{
	case EButtonType::BT_Direction:
		this->OnHovered.AddDynamic(this, &UCustomButton::PlayerMoveButtonHovered);
		this->OnUnhovered.AddDynamic(this, &UCustomButton::PlayerMoveButtonUnhovered);
		break;
	case EButtonType::BT_Shop:
		break;
	default:
		break;
	}

}

void UCustomButton::PlayerMoveButtonHovered()
{
	APlayerPawn* PlayerPawnRef = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	PlayerPawnRef->SelectMovementDirection(CameraDirection);

}

void UCustomButton::PlayerMoveButtonUnhovered()
{
	APlayerPawn* PlayerPawnRef = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	PlayerPawnRef->StopMovingPlayer();

}
