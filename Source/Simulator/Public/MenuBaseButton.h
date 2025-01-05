// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MenuBaseButton.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UENUM(BlueprintType)
enum EMenuButtonType : uint8
{
	Menu_TabButton = 0,
	Menu_VehicleButton = 1,
	Menu_MapButton = 2,
	Menu_OptionsButton = 3,
};

static constexpr FLinearColor OptionsHoveredButtonColor = FLinearColor(255, 165, 0, 1);
static constexpr FLinearColor OptionsChosenButtonColor = FLinearColor(0, 255, 0, 1);
static constexpr FLinearColor OptionsFailedButtonColor = FLinearColor(255, 0, 0, 1);

UCLASS(BlueprintType, Blueprintable)
class SIMULATOR_API UMenuBaseButton : public UButton
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "OptionButton|MenuBase")
	void ChangeButtonOutline(const bool bIsOutline, const FLinearColor Color) const;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|MenuBase")
	void InitMenuBaseButton(const TArray<UButton*> &Buttons, const EMenuButtonType &Type);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|MenuBase")
	TArray<UButton*> MenuButton;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|MenuBase")
	TEnumAsByte<EMenuButtonType> MenuButtonType;
	
};
