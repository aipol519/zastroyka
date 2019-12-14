// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHUD.generated.h"

UCLASS()
class ZASTROYKA_API ADefaultHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	//UFUNCTION()
	//void AddBuildingInfoWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UHUDWidgetUMG> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UCameraControlWidgetUMG> CameraControlWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UShopWidgetUMG> ShopWidgetClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<class UBuildingInfoWidgetUMG> BuildingInfoWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UEventWigdetUMG> EventWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UMenuWidgetUMG> MenuWidgetClass;

	UFUNCTION()
	UEventWigdetUMG* GetEventWidget();

	UFUNCTION()
	UMenuWidgetUMG* GetMenuWidget();

	UPROPERTY()
	UHUDWidgetUMG* HUDWidgetRef;

	UPROPERTY()
	UCameraControlWidgetUMG* CameraControlWidgetRef;

	UPROPERTY()
	UShopWidgetUMG* ShopWidgetRef;

	//UBuildingInfoWidgetUMG* BuildingInfoWidgetRef;

	UPROPERTY()
	UEventWigdetUMG* EventWidgetRef;

	UPROPERTY()
	UMenuWidgetUMG* MenuWidgetRef;

	UFUNCTION()
	void BeginPlay();

};
