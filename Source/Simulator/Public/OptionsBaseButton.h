// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBaseButton.h"
#include "OptionsBoolButton.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UENUM(BlueprintType, Blueprintable, Category = "OptionsButton")
enum EOptionsButtonType
{
	BoolButton = 0,
	ValueButton = 1,
	WheelsBoolButton = 2,
	WheelsValueButton = 3,
	VehicleValueButton = 4,
};

UCLASS()
class SIMULATOR_API UOptionsBaseButton : public UMenuBaseButton
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	TEnumAsByte<EOptionsButtonType> OptionsButtonType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	FString OptionName;
	
};
