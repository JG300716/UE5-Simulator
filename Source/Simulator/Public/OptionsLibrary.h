// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h" // For UUniformGridPanel
#include "Styling/SlateTypes.h"      // For FButtonStyle
#include "OptionBaseButton.h"       // For EControllersArrowsDirection
#include "MenuSelectButton.h"
#include "OptionBoolButton.h"
#include "OptionValueButton.h"
#include "OptionCustomValueButton.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/World.h"

#include "Chaos/UniformGrid.h"

#include "Components/ScrollBox.h"

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
	Right = 3,
	None = 4
};

UENUM(BlueprintType, Blueprintable, Category = "OptionsButton")
enum EControllersButtonsDirection : uint8
{
	TriangleOrY = 0, // Triangle or Y - UP
	CircleOrB = 1, // Circle or B - LEFT
	CrossOrA = 2, // Cross or A - DOWN
	SquareOrX = 3 // Square or X - RIGHT
};

UCLASS()
class SIMULATOR_API UOptionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	static TArray<uint8> Sizes;
	static TArray<uint8> MaxColumns;
	static int32 IndexOfChosenVehicle;
	static int32 IndexOfChosenMap;
	static bool OptionsInitialized;
	
	static void LoadAssetWith(const FVector &CursorPosition, int32 &IndexOfChosenAsset, const FLinearColor Color);
	static bool IsButtonValid(const int32 Index);
	static FVector3f MoveCursorNormal(const EControllersArrowsDirection &Direction, const FVector &CursorPosition);
	static FVector3f MoveCursorSpecial(const EControllersArrowsDirection &Direction, const FVector &CursorPosition);
	static void UpdateOptionButtonGraphics(UOptionBaseButton* OptionButton);
	static int32 CalculateJumpOffset(const EOptionButtonType &OptionType);
	static UOptionBaseButton* GetButtonByName(const FString &Name);
	static void UpdateScrollBar(const FVector &CursorPosition, const FVector &PreviousCursorPosition);
	static void UpdateToolTipText(const FVector &CursorPosition);
	static void ShouldJumpTheHiddenButtons(const FVector &CursorPosition, int32 &OffsetJump, bool &ShouldJump);
	static void UpdateBoolButton(UOptionBoolButton* BoolButton);
	static void UpdateIfThisIsAValueButton(const FVector &CursorPosition, const EControllersArrowsDirection &Direction);
	static void UpdateValueButton(UOptionValueButton* ValueButton, const EControllersArrowsDirection &Direction);
	static void UpdateCustomValueButton(UOptionCustomValueButton* CustomValueButton, const EControllersArrowsDirection &Direction);
public:
	UPROPERTY()
	TArray<UMenuBaseButton*> Buttons;

	UPROPERTY()
	UTextBlock* OptionsToolTipText;

	UPROPERTY()
	UScrollBox* OptionsScrollBox;

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void Initialize(UTextBlock* ToolTipTextTmp, UScrollBox* ScrollBoxTmp);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static bool AreOptionsInitialized();
	
	static UOptionsLibrary* GetInstance();
	
	UFUNCTION()
	static int32 GetSelectedButtonIndex(const FVector &CursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static UMenuBaseButton* GetSelectedButton( const FVector CursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static FVector3f MoveCursor(const EControllersArrowsDirection Direction, const FVector CursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static bool UpdateSelectedButton(const FVector CurrentCursorPosition, const FVector PreviousCursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void ChangePanelVisibility(TArray<UWidget*> Panels, const FVector CursorPosition, const FVector PreviousCursorPosition);
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static TArray<UMenuBaseButton*> AddTabButtons(TArray<UButton*> TabButtons);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void SucceededToLoadVehicleAsset(const FVector CursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void FailedToLoadVehicleAsset(const FVector CursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void SucceededToLoadMapAsset(const FVector CursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void FailedToLoadMapAsset(const FVector CursorPosition);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void AddToButtons(UMenuBaseButton* Button);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static TArray<UMenuBaseButton*> GetButtons();

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void CleanButtons();
	
	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void CalculateButtonsDimensions();

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void OptionButtonPressed(UOptionBaseButton* Button, const EControllersButtonsDirection ControllerButton);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static void TryToStartGame(UUserWidget* WidgetContext);

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static UClass* GetChosenVehicleClass();

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static FString GetChosenVehicleName();

	UFUNCTION(BlueprintCallable, Category = "OptionsLibrary")
	static EControllersArrowsDirection GetDirectionFromButton(const int64 Value);
};
