/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "MenuBaseButton.h"

void UMenuBaseButton::InitMenuBaseButton(const TArray<UButton*> &Buttons, const EMenuButtonType &Type)
{
	if (Buttons.IsEmpty()) return;
	this->MenuButton = Buttons;
	this->MenuButtonType = Type;
}

void UMenuBaseButton::ChangeButtonOutline(const bool bIsOutline, const FLinearColor Color) const
{
	if (MenuButton.IsEmpty()) return;
	const EMenuButtonType Type = MenuButtonType;
	for (auto* Button : MenuButton)
	{
		if (!IsValid(Button)) continue; // Check if the Button is valid
		FButtonStyle Style = Button->GetStyle();
		Style.Normal.OutlineSettings.Color = bIsOutline ? Color : Type == Menu_OptionsButton ? FLinearColor::White : FLinearColor::Black;
		Button->SetStyle(Style);
	}
}
