// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "OptionsBaseButton.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UENUM(BlueprintType, Blueprintable, Category = "OptionsButton")
enum EMenuButtonType : uint8
{
	TabButton = 0,
	VehicleButton = 1,
	MapButton = 2,
	OptionsButton = 3,
};

UCLASS(BlueprintType, Blueprintable)
class SIMULATOR_API UMenuBaseButton : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void ChangeButtonOutline(const bool bIsOutline, const FLinearColor Color) const;

	UFUNCTION(BlueprintCallable, Category = "OptionsButton")
	void InitializeBaseButton(UButton* Button, EMenuButtonType Type);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	UButton* MenuButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton")
	TEnumAsByte<EMenuButtonType> MenuButtonType;
	
};
