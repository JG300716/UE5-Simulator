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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Bool")
	bool BValue;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Bool")
	void InitOptionBoolButton(const TArray<UButton*>& Buttons, const EMenuButtonType MenuType, const EOptionsButtonType& OptionsType, const FString& Name, const bool &Value);
	
};
