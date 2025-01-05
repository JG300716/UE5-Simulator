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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class")
	TEnumAsByte<EOptionButtonType> OptionButtonEype;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class")
	FString OptionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class")
	FString ParentOptionName;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class")
	void InitOptionBaseButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionButtonType &OptionsType,
		const FString &Name,
		const FString ParentName
		);

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class")
	virtual void UpdateGraphics();
};
