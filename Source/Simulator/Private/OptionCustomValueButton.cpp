// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionCustomValueButton.h"


void UOptionCustomValueButton::InitOptionCustomValueButton(const TArray<UButton*>& Buttons, const EMenuButtonType MenuType, const EOptionsButtonType& OptionsType, const FString& Name, const EDriveMode &Value)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name);
	this->CValue = Value;
}
