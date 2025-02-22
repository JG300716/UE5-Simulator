// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionWheelsButton.h"
#include "OptionVehicleButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionVehicleButton  : public UOptionWheelsButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Vehicle")
	FVehicle FVehicleValue;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|Vehicle")
	void InitOptionVehicleButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionButtonType &OptionsType,
		const FString &Name,
		const FString ParentName,
		const FVehicle &Value
		);
	
};
