#pragma once

#include "CoreMinimal.h"
#include "OptionBaseButton.h"
#include "OptionBoolButton.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API UOptionBoolButton : public UOptionBaseButton
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Bool")
	bool BValue;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|Bool")
	void InitOptionBoolButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionsButtonType &OptionsType,
		const FString &Name,
		const FString ParentName,
		const bool &Value
		);
	
};
