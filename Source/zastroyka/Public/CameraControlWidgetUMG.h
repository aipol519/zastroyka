// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CameraControlWidgetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UCameraControlWidgetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonL;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonR;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonT;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonB;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonLT;
	//
	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonLB;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonRT;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ButtonRB;

	//UPROPERTY(meta = (BindWidget))
	//class UCustomButton* TestHuy;

};
