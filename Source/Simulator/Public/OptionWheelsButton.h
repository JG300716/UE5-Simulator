// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"
#include "OptionWheelsButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionWheelsButton : public UOptionBaseButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Wheels")
	FVehicleWheels Wheels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Wheels")
	bool bIsCollapsed = true;
	
	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|Wheels")
	void InitOptionWheelsButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionButtonType &OptionsType,
		const FString &Name,
		const FString ParentName,
		const FVehicleWheels &Value
		);
};
