// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"
#include "OptionsValueButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionValueButton : public UOptionBaseButton
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Value")
	float Value;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Value")
	void InitOptionValueButton(const TArray<UButton*>& Buttons, const EMenuButtonType& MenuType, const EOptionsButtonType& OptionsType, const FString& Name, const float &Value);
	
};
