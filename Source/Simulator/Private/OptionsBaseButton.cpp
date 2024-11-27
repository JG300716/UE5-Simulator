/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsBaseButton.h"

void UOptionsBaseButton::InitializeBaseButton(UButton* Button, EOptionsButtonType Type)
{
 if (Button == nullptr) return;
 this->OptionButton = Button;
 this->OptionButtonType = Type;
}

void UOptionsBaseButton::ChangeButtonOutline(const bool bIsOutline, const FLinearColor Color) const
{
 if (OptionButton == nullptr) return;
 FButtonStyle Style = OptionButton->GetStyle();
 Style.Normal.OutlineSettings.Color = bIsOutline ? Color : FLinearColor::Black;
 OptionButton->SetStyle(Style);
}
