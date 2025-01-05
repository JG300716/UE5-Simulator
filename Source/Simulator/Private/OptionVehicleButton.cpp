// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionVehicleButton.h"

void UOptionVehicleButton::InitOptionVehicleButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionButtonType &OptionsType, const FString &Name, const FString ParentName, const FVehicle &Value)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->FVehicleValue = Value;
}