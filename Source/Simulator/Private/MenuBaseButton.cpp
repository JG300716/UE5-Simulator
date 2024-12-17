/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "MenuBaseButton.h"

void UMenuBaseButton::InitializeBaseButton(TArray<UButton*> Buttons, EMenuButtonType Type)
{
 if (Buttons.IsEmpty()) return;
 this->MenuButton = Buttons;
 this->MenuButtonType = Type;
}

void UMenuBaseButton::ChangeButtonOutline(const bool bIsOutline, const FLinearColor Color) const
{
  if (MenuButton.IsEmpty()) return;
  for(auto &Button : MenuButton)
  {
    if (Button == nullptr) continue;
    FButtonStyle Style = Button->GetStyle();
    Style.Normal.OutlineSettings.Color = bIsOutline ? Color : FLinearColor::Black;
    Button->SetStyle(Style);
  }
}
