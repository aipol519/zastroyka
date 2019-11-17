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

	UFUNCTION()
	void TranslateBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Property")
	FString BuildingID;

};
