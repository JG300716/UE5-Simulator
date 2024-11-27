// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsBaseButton.h"
#include "AssetsLoader.h"
#include "OptionsSelectButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionsSelectButton : public UOptionsBaseButton
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void InitializeSelectButton(UButton* Button, EOptionsButtonType Type, FString Name, FString Path);

	UFUNCTION()
	FString VehicleButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void VehicleButtonClickedWrapper();

	UFUNCTION()
	FString MapButtonClicked();

	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void MapButtonClickedWrapper();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	FString OptionButtonName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	FString OptionButtonPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	FString AssetObjectPath;
};
