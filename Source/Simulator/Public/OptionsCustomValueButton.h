// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsBaseButton.h"
#include "OptionsCustomValueButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionsCustomValueButton : public UOptionsBaseButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton | CustomValue")
	TEnumAsByte<EDriveMode> Value;
	
};
