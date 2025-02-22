// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSelectButton.h"

void UMenuSelectButton::InitMenuSelectButton(const TArray<UButton*> &Buttons, const EMenuButtonType &Type, FString Name, FString Path)
{
	if (Buttons.IsEmpty()) return;
	InitMenuBaseButton(Buttons, Type);
	this->MenuButtonName = Name;
	this->MenuButtonPath = Path;

	switch(Type)
	{
		case Menu_VehicleButton:
			AssetObjectPath = VehicleButtonClicked();
            break;
		case Menu_MapButton:
            AssetObjectPath = MapButtonClicked();
            break;
		default:
			break;
	}
	
}

FString UMenuSelectButton::VehicleButtonClicked()
{
	// Example path:
	// "/Game/Simulator/Cars/FinalModels/Chevrolet/Chevrolet_Object.Chevrolet_Object_C"
	
	FString Result = MenuButtonPath;
	Result = Result.RightChop(MenuButtonPath.Find(TEXT("/Content/")));
	Result.ReplaceInline(TEXT("Content"), TEXT("Game"));
	const FString AssetName = MenuButtonName + TEXT("_Object");
	Result = Result / AssetName + TEXT(".") + AssetName + TEXT("_C");
	return  Result;
}

void UMenuSelectButton::VehicleButtonClickedWrapper()
{
	AssetObjectPath = VehicleButtonClicked();
	UE_LOG(LogTemp, Warning, TEXT("VehicleButtonClickedWrapper: %s"), *AssetObjectPath);
}

FString UMenuSelectButton::MapButtonClicked()
{
	// Example path:
	// "/Game/Simulator/Maps/Racetrack/Racetrack_Map"
	
	FString Result = MenuButtonPath;
	Result = Result.RightChop(MenuButtonPath.Find(TEXT("/Content/")));
	Result.ReplaceInline(TEXT("Content"), TEXT("Game"));
	const FString AssetName = MenuButtonName + TEXT("_Map");
	Result = Result / AssetName + TEXT(".") + AssetName + TEXT("_C");
	return  Result;
}

void UMenuSelectButton::MapButtonClickedWrapper()
{
	AssetObjectPath = MapButtonClicked();
	UE_LOG(LogTemp, Warning, TEXT("MapButtonClickedWrapper: %s"), *AssetObjectPath);
}