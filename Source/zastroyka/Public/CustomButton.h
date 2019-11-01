// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CustomButton.generated.h"

UENUM(BlueprintType)
enum class EButtonType : uint8
{
	BT_Direction 	UMETA(DisplayName = "Direction"),
	BT_Shop 		UMETA(DisplayName = "Shop")
};

UCLASS()
class ZASTROYKA_API UCustomButton : public UButton
{
	GENERATED_BODY()
	
public:

	UCustomButton();

	UFUNCTION()
	void PlayerMoveButtonHovered();

	UFUNCTION()
	void PlayerMoveButtonUnhovered();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button type")
	EButtonType ButtonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera direction (if button is a BT_Direction)")
	int CameraDirection;

};
