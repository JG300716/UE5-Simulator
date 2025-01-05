// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"

#include "Components/TextBlock.h"

#include "OptionCustomValueButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionCustomValueButton : public UOptionBaseButton
{
	GENERATED_BODY()

	static TArray<FText> DriveModeTexts;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|CustomValue")
	TEnumAsByte<EDriveMode> CValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|CustomValue")
	UTextBlock* CValueText;
	
	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|CustomValue")
	void InitOptionCustomValueButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionButtonType &OptionsType,
		const FString &Name,
		const FString ParentName,
		const EDriveMode &Value,
		UTextBlock* ValueText
		);

	virtual void UpdateGraphics() override;
	
};
