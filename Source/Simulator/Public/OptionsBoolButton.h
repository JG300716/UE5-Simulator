// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OptionsBaseButton.h"
#include "OptionsBoolButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionsBoolButton : public UOptionsBaseButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionsButton/Bool")
	bool Value;
	
};
