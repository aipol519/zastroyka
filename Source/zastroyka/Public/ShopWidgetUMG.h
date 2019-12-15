// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidgetUMG.generated.h"

UCLASS()
class ZASTROYKA_API UShopWidgetUMG : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	void PlayShopBorderAnimation(EUMGSequencePlayMode::Type _PlayMode);

	UFUNCTION()
	void CheckAvailabilityForButtons();

	UFUNCTION()
	void UpdateShopButtons(FString _TownHallID);

	TArray<class UShopBuldingButton*> ShopButtons;

	UPROPERTY()
	class ADefaultGameState* DefaultGameStateRef;

	UPROPERTY(meta = (BindWidgetAnim))
	class UWidgetAnimation* ShopBorderAnimation;

	//Town hall level 2
	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* TownHallLvl2Button;		//ID: 2//

	//Town hall level 3
	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* TownHallLvl3Button;		//ID: 3//

	//Road
	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* RoadButton;				//ID: 1D//

	//Tier 1 buildings
	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* HutButton;				//ID: 1A//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* BarrackButton;			//ID: 1B//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* StandButton;				//ID: 1C//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* FarmButton;				//ID: 1E//

	//Tier 2 buildings
	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* PanelBuildingButton;		//ID: 2A//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* PlantButton;				//ID: 2B//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* GroceryButton;			//ID: 2C//

	//Tier 3 buildings
	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* ApartmentsButton;			//ID: 3A//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* BusinessCenterButton;		//ID: 3B//

	UPROPERTY(meta = (BindWidget))
	class UShopBuldingButton* SupermarketButton;		//ID: 3C//

};
