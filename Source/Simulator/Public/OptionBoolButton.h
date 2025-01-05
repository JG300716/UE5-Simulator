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
	static FSlateBrushOutlineSettings BasicOutlineSettings;
	static UTexture2D* OffTexture;
	static UTexture2D* OnTexture;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OptionButton|Graphic Class|Bool")
	bool BValue;

	UFUNCTION(BlueprintCallable, Category = "OptionButton|Graphic Class|Bool")
	void InitOptionBoolButton(
		const TArray<UButton*> &Buttons,
		const EMenuButtonType MenuType,
		const EOptionButtonType OptionsType,
		const FString &Name,
		const FString ParentName,
		const bool &Value
		);

	virtual void UpdateGraphics() override;
	
};
