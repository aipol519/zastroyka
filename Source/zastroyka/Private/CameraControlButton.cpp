// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraControlButton.h"

#include "Engine.h"
#include "PlayerPawn.h"

UCameraControlButton::UCameraControlButton()
{
	CameraDirection = 0;

	this->OnHovered.AddDynamic(this, &UCameraControlButton::PlayerMoveButtonHovered);
	this->OnUnhovered.AddDynamic(this, &UCameraControlButton::PlayerMoveButtonUnhovered);

}

void UCameraControlButton::PlayerMoveButtonHovered()
{
	APlayerPawn* PlayerPawnRef = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	PlayerPawnRef->SelectMovementDirection(CameraDirection);

}

void UCameraControlButton::PlayerMoveButtonUnhovered()
{
	APlayerPawn* PlayerPawnRef = Cast<APlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	PlayerPawnRef->StopMovingPlayer();

}
