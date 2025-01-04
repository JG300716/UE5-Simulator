// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionBoolButton.h"


void UOptionBoolButton::InitOptionBoolButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionsButtonType &OptionsType, const FString &Name, const FString ParentName, const bool &Value)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->BValue = Value;	
}
