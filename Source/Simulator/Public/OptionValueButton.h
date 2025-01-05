
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"

#include "Components/TextBlock.h"

#include "OptionValueButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionValueButton : public UOptionBaseButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Value")
	float FValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Value")
	FString FUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Value")
	UTextBlock* FValueText;
	
	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|Value")
	void InitOptionValueButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionButtonType OptionsType,
		const FString &Name,
		const FString ParentName,
		const float &Value,
		const FString &Unit,
		UTextBlock* ValueText
		 );

	virtual void UpdateGraphics() override;
	
};
