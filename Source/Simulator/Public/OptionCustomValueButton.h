// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"
#include "OptionsCustomValueButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionCustomValueButton : public UOptionBaseButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton | CustomValue")
	TEnumAsByte<EDriveMode> Value;
	
};
