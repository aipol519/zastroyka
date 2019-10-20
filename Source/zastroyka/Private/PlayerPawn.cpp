// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UCameraComponent *PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	PlayerCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	PlayerCamera->SetOrthoWidth(1024.0f);

	USpringArmComponent *SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AddRelativeRotation(FRotator(-30.0f, -45.0f, 0.0f));
	SpringArm->TargetArmLength = 2500.0f;
	
	PlayerCamera->AttachTo(SpringArm);

	XAddition = 0;
	YAddition = 0;
	VariableCoordinateX = 0;
	VariableCoordinateY = 0;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	VariableCoordinateX += XAddition;
	VariableCoordinateY += YAddition;
	SetActorLocation(FVector(VariableCoordinateX, VariableCoordinateY, GetActorLocation().Z));

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::SelectMovementDirection(int16 _MovementDirection)
{
	VariableCoordinateX = GetActorLocation().X;
	VariableCoordinateY = GetActorLocation().Y;

	switch (_MovementDirection)
	{
	case 0:
		XAddition = 0;
		YAddition = -2;
		break;
	case 1:
		XAddition = -2;
		YAddition = -2;
		break;
	case 2:
		XAddition = -2;
		YAddition = 0;
		break;
	case 3:
		XAddition = -2;
		YAddition = 2;
		break;
	case 4:
		XAddition = 0;
		YAddition = 2;
		break;
	case 5:
		XAddition = 2;
		YAddition = 2;
		break;
	case 6:
		XAddition = 2;
		YAddition = 0;
		break;
	case 7:
		XAddition = 2;
		YAddition = -2;
		break;
	default:
		break;
	}

	SetActorTickEnabled(true);
}

void APlayerPawn::StopMovingPlayer()
{
	SetActorTickEnabled(false);
}

void APlayerPawn::MoveByMouse(FVector _DirectionVector)
{
	SetActorLocation(GetActorLocation() + _DirectionVector);

}
