// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionBaseButton.h"

void UOptionBaseButton::InitOptionBaseButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionButtonType &OptionsType, const FString &Name, const FString ParentName)
{
	InitMenuBaseButton(Buttons, MenuType);
	this->OptionButtonType = OptionsType;
	this->OptionName = Name;
	this->ParentOptionName = ParentName;
}

void UOptionBaseButton::UpdateGraphics()
{
}