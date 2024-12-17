// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSelectButton.h"

void UMenuSelectButton::InitializeSelectButton(TArray<UButton*> Buttons, EMenuButtonType Type, FString Name, FString Path)
{
	if (Buttons.IsEmpty()) return;
	InitializeBaseButton(Buttons, Type);
	this->MenuButtonName = Name;
	this->MenuButtonPath = Path;
}

FString UMenuSelectButton::VehicleButtonClicked()
{
	// Example path:
	// "/Game/Simulator/Cars/FinalModels/Schevrolet/Schevrolet_Object.Schevrolet_Object_C"
	
	FString Result = MenuButtonPath;
	Result = Result.RightChop(MenuButtonPath.Find(TEXT("/Content/")));
	Result.ReplaceInline(TEXT("Content"), TEXT("Game"));
	const FString AssetName = MenuButtonName + TEXT("_Object");
	Result = Result / AssetName + TEXT(".") + AssetName + TEXT("_C");
	UE_LOG(LogTemp, Warning, TEXT("VehicleButtonClicked: %s"), *Result);
	return  Result;
}

void UMenuSelectButton::VehicleButtonClickedWrapper()
{
	AssetObjectPath = VehicleButtonClicked();
}

FString UMenuSelectButton::MapButtonClicked()
{
	// Example path:
	// "/Game/Simulator/Maps/Racetrack/Racetrack_Object"
	
	FString Result = MenuButtonPath;
	Result = Result.RightChop(MenuButtonPath.Find(TEXT("/Content/")));
	Result.ReplaceInline(TEXT("Content"), TEXT("Game"));
	const FString AssetName = MenuButtonName + TEXT("_Object");
	Result = Result / AssetName + TEXT(".") + AssetName + TEXT("_C");
	UE_LOG(LogTemp, Warning, TEXT("MapButtonClicked: %s"), *Result);
	return  Result;
}

void UMenuSelectButton::MapButtonClickedWrapper()
{
	AssetObjectPath = MapButtonClicked();
	UE_LOG(LogTemp, Warning, TEXT("MapButtonClickedWrapper: %s"), *AssetObjectPath);
}