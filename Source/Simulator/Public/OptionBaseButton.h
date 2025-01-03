// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBaseButton.h"
#include "DefaultPlayerOptions.h"
#include "OptionsBaseButton.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UCLASS()
class SIMULATOR_API UOptionBaseButton : public UMenuBaseButton
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton")
	TEnumAsByte<EOptionsButtonType> OptionButtonType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton")
	FString OptionName;

	UFUNCTION(BlueprintCallable, Category = "OptionButton")
	void InitOptionBaseButton(const TArray<UButton*> &Buttons, const EMenuButtonType &MenuType, const EOptionsButtonType &OptionsType, const FString &Name);
	
};
