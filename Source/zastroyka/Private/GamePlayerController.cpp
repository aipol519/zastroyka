// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"

#include "Engine.h"
#include "PaperTileMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "DefaultGameState.h"
#include "PlayerPawn.h"

AGamePlayerController::AGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	MouseWorldPosition = FVector(0.0f, 0.0f, 0.0f);

	MouseStartScreenPosition = FVector2D(0.0f, 0.0f);
	MouseCurrentScreenPosition = FVector2D(0.0f, 0.0f);

	XTileCoord = 0;
	YTileCoord = 0;
	PrevXTileCoord = 0;
	PrevYTileCoord = 0;

}

void AGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Converting mouse world position to tile coordinates
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	XTileCoord = FMath::FloorToInt(HitResult.Location.X / 32.0f);
	YTileCoord = FMath::FloorToInt(HitResult.Location.Y / 32.0f);

	DefaultGameStateRef->UpdateTileMap(PrevXTileCoord, PrevYTileCoord, XTileCoord, YTileCoord);
	
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, 
		"X: " + 
		FString::FromInt(XTileCoord) + 
		" Y: " + 
		FString::FromInt(YTileCoord) + 
		" " + 
		FString::FromInt(DefaultGameStateRef->XMapSize * YTileCoord + XTileCoord));
}

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Getting instance of GameState
	DefaultGameStateRef = Cast<ADefaultGameState>(GetWorld()->GetGameState());

}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	FInputModeGameAndUI InputMode;

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);

	InputComponent->BindAction("RightMouseButtonSingle", EInputEvent::IE_Pressed, this, &AGamePlayerController::RightMouseButtonDownOnce);
	InputComponent->BindAction("RightMouseButtonSingle", EInputEvent::IE_Released, this, &AGamePlayerController::RightMouseButtonUp);

}

bool AGamePlayerController::IsMouseMoving()
{
	float MouseDeltaX, MouseDeltaY;

	GetInputMouseDelta(MouseDeltaX, MouseDeltaY);

	return (MouseDeltaX != 0.0f) || (MouseDeltaY != 0.0f);
}

void AGamePlayerController::RightMouseButtonDownOnce()
{
	InputComponent->BindAxis("RightMouseButtonContinious", this, &AGamePlayerController::RightMouseButtonDownContinious);

	GetMousePosition(MouseStartScreenPosition.X, MouseStartScreenPosition.Y);

}

void AGamePlayerController::RightMouseButtonUp()
{
	InputComponent->AxisBindings.RemoveAt(InputComponent->AxisBindings.Num() - 1);
}

void AGamePlayerController::RightMouseButtonDownContinious(float _Value)
{
	GetMousePosition(MouseCurrentScreenPosition.X, MouseCurrentScreenPosition.Y);

	FVector ResultVector = FVector(MouseCurrentScreenPosition.X - MouseStartScreenPosition.X, MouseCurrentScreenPosition.Y - MouseStartScreenPosition.Y, 0.0f);

	if (IsMouseMoving())
	{
		ResultVector = FVector(MouseCurrentScreenPosition.X - MouseStartScreenPosition.X, MouseCurrentScreenPosition.Y - MouseStartScreenPosition.Y, 0.0f);
	}
	else
	{
		ResultVector = ResultVector;
		GetMousePosition(MouseStartScreenPosition.X, MouseStartScreenPosition.Y);
	}

	ResultVector /= 64.0f;

	ResultVector = ResultVector.RotateAngleAxis(-45.0f, FVector(0.0f, 0.0f, 1.0f));

	//ResultVector.Normalize();

	if (IsMouseMoving()) 
	{
		DefaultGameStateRef->GetPlayerRef()->MoveByMouse(ResultVector);
	}

	//GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, 
	//	/*FString::SanitizeFloat(DefaultGameStateRef->GetPlayerRef()->GetActorLocation().X) +
	//	" " +
	//	FString::SanitizeFloat(DefaultGameStateRef->GetPlayerRef()->GetActorLocation().Y) +
	//	" " +*/
	//	FString::SanitizeFloat(MouseCurrentScreenPosition.X - MouseStartScreenPosition.X) +
	//	" " + 
	//	FString::SanitizeFloat(MouseCurrentScreenPosition.Y - MouseStartScreenPosition.Y));

}
