// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "OptionsButtonType.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UENUM(BlueprintType, Blueprintable, Category = "OptionsButton")
enum EOptionsButtonType : uint8
{
	TabButton = 0,
	VehicleButton = 1,
	MapButton = 2,
	OptionsButton = 3
};

UCLASS(BlueprintType, Blueprintable)
class SIMULATOR_API UOptionsButtonType : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void ChangeButtonOutline(const bool bIsOutline) const;

	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void InitializeButton(UButton* Button, EOptionsButtonType Type, FString Name, FString Path);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	UButton* OptionButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	TEnumAsByte<EOptionsButtonType> OptionButtonType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	FString OptionButtonName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	FString OptionButtonPath;
};
