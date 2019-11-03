// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class ZASTROYKA_API FBuilding
{
public:

	FBuilding();
	FBuilding(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name);

	int16 XSize, YSize;
	int32 Cost;

	FString Name;

};
