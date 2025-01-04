// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"
#include "OptionCustomValueButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionCustomValueButton : public UOptionBaseButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|CustomValue")
	TEnumAsByte<EDriveMode> CValue;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|CustomValue")
	void InitOptionCustomValueButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionsButtonType &OptionsType,
		const FString &Name,
		const FString ParentName,
		const EDriveMode &Value
		);
	
};
