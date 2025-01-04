// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWheelsButton.h"

void UOptionWheelsButton::InitOptionWheelsButton(const TArray<UButton*>& Buttons, const EMenuButtonType MenuType, const EOptionsButtonType& OptionsType, const FString& Name, const FString ParentName, const FVehicleWheels &Value)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->Wheels = Value;
}