#pragma once

#include "CoreMinimal.h"
#include "DefaultPlayerOptions.h"
#include "MenuBaseButton.h"
#include "OptionBaseButton.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */

UCLASS()
class SIMULATOR_API UOptionBaseButton : public UMenuBaseButton
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton")
	TEnumAsByte<EOptionsButtonType> OptionButtonType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton")
	FString OptionName;

	UFUNCTION(BlueprintCallable, Category = "OptionButton")
	void InitOptionBaseButton(const TArray<UButton*> &Buttons, const EMenuButtonType &MenuType, const EOptionsButtonType &OptionsType, const FString &Name);
	
};
