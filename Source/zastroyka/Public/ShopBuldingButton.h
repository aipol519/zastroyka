// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Building.h"
#include "ShopBuldingButton.generated.h"

UCLASS()
class ZASTROYKA_API UShopBuldingButton : public UButton
{
	GENERATED_BODY()
	
public:

	UShopBuldingButton();

	void CheckAvailability();
	void Initialize();

	UFUNCTION()
	void TranslateBuilding();

	UPROPERTY()
	ADefaultGameState* DefaultGameStateRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	FString BuildingID;

	struct FButtonStyle AvailableButtonStyle;

	UPROPERTY(EditAnywhere, Category = "Property")
	struct FButtonStyle UnavailableButtonStyle;

};
