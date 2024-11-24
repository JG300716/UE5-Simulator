// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Button.h"
#include "Styling/SlateTypes.h"      // For FButtonStyle
#include "OptionsButtonType.h"       // For ECursorDirection
#include "OptionsLibrary.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UCLASS()
class SIMULATOR_API UOptionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static FVector3f MoveCursor(const ECursorDirection Direction, const FVector CursorPosition, const TArray<uint8> Sizes );

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void UpdateSelectedButton(TArray<UOptionsButtonType*> Buttons, const FVector CurrentCursorPosition, const FVector PreviousCursorPosition, const TArray<uint8> Sizes, const TArray<uint8> MaxColumns);
	
};
