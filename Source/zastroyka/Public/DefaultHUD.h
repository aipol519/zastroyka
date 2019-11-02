// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

class CameraControlSlateWidget;
class HUDSlateWidget;

UCLASS()
class ZASTROYKA_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

public:

	TSharedPtr<CameraControlSlateWidget> CameraControlWidget;
	TSharedPtr<HUDSlateWidget> HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UHUDWidgetUMG> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UCameraControlWidgetUMG> CameraControlWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UShopWidgetUMG> ShopWidgetClass;

	UHUDWidgetUMG* HUDWidgetRef;
	UCameraControlWidgetUMG* CameraControlWidgetRef;
	UShopWidgetUMG* ShopWidgetRef;

	void BeginPlay();

};
