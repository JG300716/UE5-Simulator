// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h" // For UUniformGridPanel
#include "Styling/SlateTypes.h"      // For FButtonStyle
#include "OptionsBaseButton.h"       // For EControllersArrowsDirection
#include "OptionsSelectButton.h"

#include "Chaos/UniformGrid.h"

#include "OptionsLibrary.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UENUM(BlueprintType, Blueprintable, Category = "OptionsButton")
enum EControllersArrowsDirection : uint8
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3
};

UENUM(BlueprintType, Blueprintable, Category = "OptionsButton")
enum EControllersButtonsDirection : uint8
{
	TriangleOrY = 0, // Triangle or Y - UP
	CircleOrB = 1, // Circle or B - DOWN
	CrossOrA = 2, // Cross or A - LEFT
	SquareOrX = 3 // Square or X - RIGHT
};

UCLASS()
class SIMULATOR_API UOptionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	static TArray<uint8> Sizes;
	static TArray<uint8> MaxColumns;
	static TArray<UOptionsBaseButton*> Buttons;
	static int32 IndexOfChosenVehicle;
	static constexpr FLinearColor OptionsHoveredButtonColor = FLinearColor(255, 165, 0, 1);
	static constexpr FLinearColor OptionsChosenButtonColor = FLinearColor(0, 255, 0, 1);
	static constexpr FLinearColor OptionsFailedButtonColor = FLinearColor(255, 0, 0, 1);
public:
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void Initialize(TArray<uint8> TmpSizes, TArray<uint8> TmpMaxColumns, TArray<UOptionsBaseButton*> TmpButtons);

	UFUNCTION()
	static int32 GetSelectedButtonIndex(const FVector CursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static UOptionsBaseButton* GetSelectedButton( const FVector CursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static FVector3f MoveCursor(const EControllersArrowsDirection Direction, const FVector CursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static bool UpdateSelectedButton(const FVector CurrentCursorPosition, const FVector PreviousCursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void ChangePanelVisibility(TArray<UUniformGridPanel*> Panels, const FVector CursorPosition, const FVector PreviousCursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static TArray<UOptionsBaseButton*> AddTabButtons(TArray<UButton*> TabButtons);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void SuccessedToLoadAsset(const FVector CursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void FailedToLoadAsset(const FVector CursorPosition);
};
