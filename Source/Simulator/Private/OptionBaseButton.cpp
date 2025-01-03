// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionBaseButton.h"

void UOptionBaseButton::InitOptionBaseButton(const TArray<UButton*>& Buttons, const EMenuButtonType& MenuType, const EOptionsButtonType& OptionsType, const FString& Name)
{

	InitMenuBaseButton(Buttons, MenuType);
	this->OptionButtonType = OptionsType;
	this->OptionName = Name;
	
}

