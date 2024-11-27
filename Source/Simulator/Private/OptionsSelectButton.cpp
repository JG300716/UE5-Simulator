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
	// Example path:
	// "/Game/Simulator/Cars/FinalModels/Schevrolet/Schevrolet_Object.Schevrolet_Object_C"
	
	FString Result = OptionButtonPath;
	Result = Result.RightChop(OptionButtonPath.Find(TEXT("/Content/")));
	Result.ReplaceInline(TEXT("Content"), TEXT("Game"));
	const FString AssetName = OptionButtonName + TEXT("_Object");
	Result = Result / AssetName + TEXT(".") + AssetName + TEXT("_C");
	UE_LOG(LogTemp, Warning, TEXT("VehicleButtonClicked: %s"), *Result);
	return  Result;
}

void UOptionsSelectButton::VehicleButtonClickedWrapper()
{
	AssetObjectPath = VehicleButtonClicked();
}

FString UOptionsSelectButton::MapButtonClicked()
{
	return OptionButtonPath + OptionButtonName + TEXT(".uasset");
}

void UOptionsSelectButton::MapButtonClickedWrapper()
{
	AssetObjectPath = MapButtonClicked();
	UE_LOG(LogTemp, Warning, TEXT("MapButtonClickedWrapper: %s"), *AssetObjectPath);
}