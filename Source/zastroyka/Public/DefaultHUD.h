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
	TSubclassOf<class UHUDWidgetUMG> MainMenuWidgetClass;

	UHUDWidgetUMG* MainMenuWidgetRef;

	void BeginPlay();

};
