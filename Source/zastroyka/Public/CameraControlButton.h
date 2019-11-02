// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CameraControlButton.generated.h"

UCLASS()
class ZASTROYKA_API UCameraControlButton : public UButton
{
	GENERATED_BODY()

public:

	UCameraControlButton();

	UFUNCTION()
	void PlayerMoveButtonHovered();

	UFUNCTION()
	void PlayerMoveButtonUnhovered();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera direction")
	int CameraDirection;
	
};
