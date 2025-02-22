// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBaseButton.h"
#include "AssetsLoader.h"
#include "MenuSelectButton.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UCLASS()
class SIMULATOR_API UMenuSelectButton : public UMenuBaseButton
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "OptionButton|MenuSelect")
	void InitMenuSelectButton(const TArray<UButton*> &Buttons, const EMenuButtonType &Type, FString Name, FString Path);

	UFUNCTION()
	FString VehicleButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "OptionButton|MenuSelect")
	void VehicleButtonClickedWrapper();

	UFUNCTION()
	FString MapButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "OptionButton|MenuSelect")
	void MapButtonClickedWrapper();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|MenuSelect")
	FString MenuButtonName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|MenuSelect")
	FString MenuButtonPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|MenuSelect")
	FString AssetObjectPath;
};
