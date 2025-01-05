// Fill out your copyright notice in the Description page of Project Settings.

#include "OptionValueButton.h"

#include <string>


void UOptionValueButton::InitOptionValueButton(const TArray<UButton*> &Buttons, const EMenuButtonType MenuType, const EOptionButtonType OptionsType, const FString &Name, const FString ParentName, const float &Value, const FString &Unit, UTextBlock* ValueText)
{
	InitOptionBaseButton(Buttons, MenuType, OptionsType, Name, ParentName);
	this->FValue = Value;
	this->FUnit = Unit;
	this->FValueText = ValueText;
}


void UOptionValueButton::UpdateGraphics()
{
	if (MenuButton.IsEmpty()) return;
	for(auto &Button : MenuButton)
	{
		if (!IsValid(Button)) continue;
		FButtonStyle Style = Button->GetStyle();
		Style.Normal.OutlineSettings.Color = FLinearColor::Black;
		Button->SetStyle(Style);
	}
	if (!IsValid(FValueText)) return;
	FString Text = FString::Printf(FValue > 10 ? L"%.0f" : L"%.1f", FValue) + (FUnit != "" ? " " + FUnit : "");
	FText ValueText = FText::FromString(Text);
	FValueText->SetText(ValueText);

}
