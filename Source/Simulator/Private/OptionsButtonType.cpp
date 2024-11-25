/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsButtonType.h"

void UOptionsButtonType::InitializeButton(UButton* Button, EOptionsButtonType Type, FString Name, FString Path)
{
 if (Button == nullptr) return;
 this->OptionButton = Button;
 this->OptionButtonType = Type;
 this->OptionButtonName = Name;
 this->OptionButtonPath = Path;
}

void UOptionsButtonType::ChangeButtonOutline(const bool bIsOutline) const
{
 if (OptionButton == nullptr) return;
 FButtonStyle Style = OptionButton->GetStyle();
 UE_LOG(LogTemp, Warning, TEXT("ChangeButtonOutline: %d"), bIsOutline);
 Style.Normal.OutlineSettings.Color = bIsOutline ? FLinearColor(255, 165, 0, 1) : FLinearColor::Black;
 OptionButton->SetStyle(Style);
}
