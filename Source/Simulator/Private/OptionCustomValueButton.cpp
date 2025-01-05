// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionCustomValueButton.h"

TArray<FText> UOptionCustomValueButton::DriveModeTexts =
	{
		FText::FromString(TEXT("All Wheels")),
		FText::FromString(TEXT("Front Wheels")),
		FText::FromString(TEXT("Rear Wheels"))
	};

void UOptionCustomValueButton::InitOptionCustomValueButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionButtonType &OptionsType, const FString &Name, const FString ParentName, const EDriveMode &Value, UTextBlock* ValueText)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->CValue = Value;
	this->CValueText = ValueText;
}


void UOptionCustomValueButton::UpdateGraphics()
{
	if (MenuButton.IsEmpty()) return;
	for(auto &Button : MenuButton)
	{
		if (!IsValid(Button)) continue;
		FButtonStyle Style = Button->GetStyle();
		Style.Normal.OutlineSettings.Color = FLinearColor::Black;
		Button->SetStyle(Style);
	}
	if (!IsValid(CValueText)) return;
	FText ValueText = DriveModeTexts[CValue];
	CValueText->SetText(ValueText);
}
