// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Button.h"       // For UButton
#include "Styling/SlateTypes.h"      // For FButtonStyle
#include "Brushes/SlateBrush.h"      // For FSlateBrush if needed
#include "ChangeButtonOutline.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UChangeButtonOutline : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "ButtonOutline")
	static void ChangeButtonOutline(UButton* Button, bool bIsOutline);
	
};
