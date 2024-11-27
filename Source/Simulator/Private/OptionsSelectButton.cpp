// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsSelectButton.h"

void UOptionsSelectButton::InitializeSelectButton(UButton* Button, EOptionsButtonType Type, FString Name, FString Path)
{
	if (Button == nullptr) return;
	InitializeBaseButton(Button, Type);
	this->OptionButtonName = Name;
	this->OptionButtonPath = Path;
}

FString UOptionsSelectButton::VehicleButtonClicked()
{
	return FPaths::ProjectContentDir() + OptionButtonPath + OptionButtonName + TEXT("_Object.uasset");

}

void UOptionsSelectButton::VehicleButtonClickedWrapper()
{
	AssetObjectPath = VehicleButtonClicked();
	UE_LOG(LogTemp, Warning, TEXT("VehicleButtonClickedWrapper: %s"), *AssetObjectPath);
}

FString UOptionsSelectButton::MapButtonClicked()
{
	return FPaths::ProjectContentDir() + OptionButtonPath + OptionButtonName + TEXT(".uasset");
}

void UOptionsSelectButton::MapButtonClickedWrapper()
{
	AssetObjectPath = MapButtonClicked();
	UE_LOG(LogTemp, Warning, TEXT("MapButtonClickedWrapper: %s"), *AssetObjectPath);
}