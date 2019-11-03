// Fill out your copyright notice in the Description page of Project Settings.


#include "FBuilding.h"

FBuilding::FBuilding()
{

}

FBuilding::FBuilding(int16 _XSize, int16 _YSize, int32 _Cost, FString _Name)
{
	XSize = _XSize;
	YSize = _YSize;
	Cost = _Cost;
	
	Name = _Name;
}
