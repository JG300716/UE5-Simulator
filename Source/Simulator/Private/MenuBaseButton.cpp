/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "MenuBaseButton.h"

void UMenuBaseButton::InitializeBaseButton(UButton* Button, EMenuButtonType Type)
{
 if (Button == nullptr) return;
 this->MenuButton = Button;
 this->MenuButtonType = Type;
}

void UMenuBaseButton::ChangeButtonOutline(const bool bIsOutline, const FLinearColor Color) const
{
 if (MenuButton == nullptr) return;
 FButtonStyle Style = MenuButton->GetStyle();
 Style.Normal.OutlineSettings.Color = bIsOutline ? Color : FLinearColor::Black;
 MenuButton->SetStyle(Style);
}
