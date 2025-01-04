// Fill out your copyright notice in the Description page of Project Settings.

#include "OptionValueButton.h"


void UOptionValueButton::InitOptionValueButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionsButtonType &OptionsType, const FString &Name, const FString ParentName, const float &Value, const FString &Unit)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->FValue = Value;
	this->FUnit = Unit;
}
