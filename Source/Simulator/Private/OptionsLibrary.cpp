/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsLibrary.h"

#include "IntVectorTypes.h"
#include "OptionWheelsButton.h"

TArray<uint8> UOptionsLibrary::Sizes = {0,0,0};
TArray<uint8> UOptionsLibrary::MaxColumns = {5,5,1};
int32 UOptionsLibrary::IndexOfChosenVehicle = -1;
int32 UOptionsLibrary::IndexOfChosenMap;

UOptionsLibrary* UOptionsLibrary::GetInstance()
{
    static UOptionsLibrary* Instance = NewObject<UOptionsLibrary>();
    Instance->AddToRoot(); // Keep it alive
    return Instance;
}

int32 UOptionsLibrary::GetSelectedButtonIndex(const FVector CursorPosition)
{
    const uint32 Page = CursorPosition.Z;
    uint32 PageOffset = 0;
    if (Page >= static_cast<uint32>(MaxColumns.Num())) return -1; // Invalid page
    const uint32 RowOffset = MaxColumns[Page] * __max((CursorPosition.Y - 1), 0);
    const bool IsTabButton = CursorPosition.Y == 0;
    const uint32 ColumnOffset = CursorPosition.X + (IsTabButton ? 0 : 1);
    if (Page >= static_cast<uint32>(Sizes.Num())) return -1; // Invalid page
    for(uint32 i = 0; i < Page; i++)
    {
        PageOffset += Sizes[i];
    }
    return Page + PageOffset + RowOffset + ColumnOffset;
}


UMenuBaseButton* UOptionsLibrary::GetSelectedButton(const FVector CursorPosition)
{
    const int32 Index = GetSelectedButtonIndex(CursorPosition);
    if (Index < 0 || Index >= GetInstance()->Buttons.Num()) return nullptr; // Invalid index
    return GetInstance()->Buttons[Index];
}

FVector3f UOptionsLibrary::MoveCursorNormal(const EControllersArrowsDirection &Direction, const FVector &CursorPosition)
{
    FVector3f NewCursorPosition = FVector3f(CursorPosition);

    const uint8 Page = CursorPosition.Z;
    const uint8 Columns = MaxColumns[Page]; // Number of columns in the current page
    const uint8 PageSize = Sizes[Page]; // Size of the current page only
    
    switch (Direction)
    {
        case EControllersArrowsDirection::Up:
            if (CursorPosition.Y > 0)
            {
                NewCursorPosition.Y--;
                if (NewCursorPosition.Y == 0)
                    NewCursorPosition.X = 0; // Snap to the current tab button
            }
            return NewCursorPosition;

        case EControllersArrowsDirection::Down:
            if (CursorPosition.Y == 0)
            {
                NewCursorPosition.Y = 1; // Move to the first row of the grid
                NewCursorPosition.X = 0; // Snap to the first column
                return NewCursorPosition;
            }
            if (CursorPosition.Y >= FMath::CeilToInt(PageSize / (float)Columns) - 1)
                return NewCursorPosition; // Already at the bottom row, do nothing

            NewCursorPosition.Y++;
            return NewCursorPosition;

        case EControllersArrowsDirection::Left:
            if (CursorPosition.Y == 0)
            {
                // Moving left among tab buttons
                if (CursorPosition.Z > 0)
                {
                    NewCursorPosition.X = 0; // Reset X to 0 for tabs
                    NewCursorPosition.Z--;  // Move to the previous tab
                }
                return NewCursorPosition;
            }

            if (CursorPosition.X > 0)
            {
                NewCursorPosition.X--;
                return NewCursorPosition; // Move left within the same row
            }

            if (CursorPosition.Y > 1)
            {
                NewCursorPosition.Y--;
                NewCursorPosition.X = Columns - 1; // Wrap to the end of the previous row
            }
            return NewCursorPosition;

        case EControllersArrowsDirection::Right:
            if (CursorPosition.Y == 0)
            {
                // Moving right among tab buttons
                if (CursorPosition.Z < 2)
                {
                    NewCursorPosition.X = 0; // Reset X to 0 for tabs
                    NewCursorPosition.Z++;  // Move to the next tab
                }
                return NewCursorPosition;
            }

            // Check if within bounds of the row
            if (CursorPosition.X + 1 < Columns && 
                (CursorPosition.Y - 1) * Columns + CursorPosition.X + 1 < PageSize)
            {
                NewCursorPosition.X++;
                return NewCursorPosition; // Move right within the same row
            }

            // Check if we can wrap to the next row
            if ((CursorPosition.Y) * Columns < PageSize)
            {
                NewCursorPosition.Y++;
                NewCursorPosition.X = 0; // Wrap to the beginning of the next row
            }
            return NewCursorPosition;

        default:
            return NewCursorPosition; // Handle invalid direction by doing nothing
    }
}

FVector3f UOptionsLibrary::MoveCursorSpecial(const EControllersArrowsDirection &Direction, const FVector &CursorPosition)
{
    FVector3f NewCursorPosition = FVector3f(CursorPosition);

    const uint8 Page = CursorPosition.Z;
    const uint8 Columns = MaxColumns[Page]; // Number of columns in the current page
    const uint8 PageSize = Sizes[Page]; // Size of the current page only

    bool ShouldJump = false;
    int OffsetJump = 0;
    
    switch (Direction)
    {
        default:
        break;
        case EControllersArrowsDirection::Up:
            if (CursorPosition.Y > 0)
            {
                ShouldJumpTheHiddenButtons(CursorPosition, OffsetJump, ShouldJump);
                NewCursorPosition.Y = ShouldJump ? NewCursorPosition.Y - OffsetJump - 1 : NewCursorPosition.Y - 1;
                if (NewCursorPosition.Y == 0)
                    NewCursorPosition.X = 0; // Snap to the current tab button
            }
            return NewCursorPosition;
        break;
        case EControllersArrowsDirection::Down:
            if (CursorPosition.Y == 0)
            {
                NewCursorPosition.Y = 1; // Move to the first row of the grid
                NewCursorPosition.X = 0; // Snap to the first column
                return NewCursorPosition;
            }
            if (CursorPosition.Y >= FMath::CeilToInt(PageSize / (float)Columns) - 1) return NewCursorPosition; // Already at the bottom row, do nothing
            ShouldJumpTheHiddenButtons(CursorPosition, OffsetJump, ShouldJump);
            NewCursorPosition.Y = ShouldJump ? NewCursorPosition.Y + OffsetJump + 1 : NewCursorPosition.Y + 1;
            return NewCursorPosition;
        break;
        case EControllersArrowsDirection::Left:
        break;
        case EControllersArrowsDirection::Right:
        break;
        
    }
    
    return FVector3f(CursorPosition);
}

void UOptionsLibrary::ShouldJumpTheHiddenButtons(const FVector& CursorPosition, int32& OffsetJump, bool& ShouldJump)
{
    UOptionBaseButton* Button = Cast<UOptionBaseButton>(GetSelectedButton(CursorPosition));
    if (!IsValid(Button)) return; // Invalid button
    
    switch(Button->OptionButtonType)
    {
    case Option_WheelsBoolButton:
    case Option_WheelsValueButton:
        OffsetJump = OffsetJump == 0 ? 4 : OffsetJump;
        [[fallthrough]];
    case Option_VehicleValueButton:
        {
            OffsetJump = OffsetJump == 0 ? 5 : OffsetJump; 
            UOptionWheelsButton* WheelsButton = Cast<UOptionWheelsButton>(Button);
            if (!IsValid(WheelsButton)) return ; // Invalid button
            ShouldJump = WheelsButton->bIsCollapsed;
            break;
        }
    default:
    case Option_CustomValueButton:
    case Option_ValueButton:
    case Option_BoolButton:
        break;
    }
}


FVector3f UOptionsLibrary::MoveCursor(const EControllersArrowsDirection Direction, const FVector CursorPosition)
{
    switch (static_cast<int>(CursorPosition.Z))
    {
    case 0:
    case 1:
    default:
        return MoveCursorNormal(Direction, CursorPosition);
    case 2:
        return MoveCursorSpecial(Direction, CursorPosition);
        
    }
    
    
}


bool UOptionsLibrary::UpdateSelectedButton(
    const FVector CurrentCursorPosition,
    const FVector PreviousCursorPosition)
{
  
    // Ensure valid positions
    if (CurrentCursorPosition.Z < 0 || PreviousCursorPosition.Z < 0)
        return false; // Invalid position

    if (MaxColumns.IsEmpty()) return false;

    if (Sizes.IsEmpty()) return false;
    
    // Compute indices for current and previous buttons
    const int32 CurrentIndex = GetSelectedButtonIndex(CurrentCursorPosition);
    const int32 PreviousIndex = GetSelectedButtonIndex(PreviousCursorPosition);
    TArray<UMenuBaseButton*> AllButtons = GetInstance()->Buttons;
    if (AllButtons.IsEmpty()) return false;

    if (CurrentIndex < 0 || CurrentIndex >= AllButtons.Num()) return false;
    // Update buttons if indices are valid

    if (AllButtons.IsValidIndex(PreviousIndex) && PreviousIndex != CurrentIndex && PreviousIndex != IndexOfChosenVehicle)
    {
        AllButtons[PreviousIndex]->ChangeButtonOutline(false, OptionsHoveredButtonColor); // Remove highlight from the previously selected button
    }
    if (AllButtons.IsValidIndex(CurrentIndex) && CurrentIndex != IndexOfChosenVehicle)
    {
        AllButtons[CurrentIndex]->ChangeButtonOutline(true, OptionsHoveredButtonColor); // Highlight the currently selected button
    }

    if (abs((CurrentCursorPosition - PreviousCursorPosition).Z) != 1) return false; // Only update if the page has changed
    return true;
    
}

TArray<UMenuBaseButton*> UOptionsLibrary::AddTabButtons(TArray<UButton*> TabButtons)
{
    uint32 Offset = 0;
    for(int i = 0; i < TabButtons.Num(); i++)
    {
        TArray<UButton*> TmpButtons;
        TmpButtons.Add(TabButtons[i]);
        UMenuBaseButton* Button = NewObject<UMenuBaseButton>(UMenuBaseButton::StaticClass());
        Button->InitMenuBaseButton(TmpButtons, Menu_TabButton);
        GetInstance()->Buttons.Insert(Button, Offset);
        Offset += Sizes[i] + 1;
    }
    return GetInstance()->Buttons;
}

void UOptionsLibrary::ChangePanelVisibility(TArray<UWidget*> Panels, const FVector CursorPosition, const FVector PreviousCursorPosition)
{
    if (CursorPosition.Z == PreviousCursorPosition.Z) return; // Only change visibility if the page has changed
    const int Page = CursorPosition.Z * 2;
    const int PreviousPage = PreviousCursorPosition.Z * 2;
    if (Panels.IsValidIndex(Page))
    {
        Panels[Page]->SetVisibility(ESlateVisibility::Visible);
    }
    if (Panels.IsValidIndex(PreviousPage))
    {
        Panels[PreviousPage]->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UOptionsLibrary::SucceededToLoadVehicleAsset(const FVector CursorPosition)
{
    LoadAssetWith(CursorPosition, IndexOfChosenVehicle, OptionsChosenButtonColor);
}

void UOptionsLibrary::FailedToLoadVehicleAsset(const FVector CursorPosition)
{
    LoadAssetWith(CursorPosition, IndexOfChosenVehicle, OptionsFailedButtonColor);
}

void UOptionsLibrary::SucceededToLoadMapAsset(const FVector CursorPosition)
{
    LoadAssetWith(CursorPosition, IndexOfChosenMap, OptionsChosenButtonColor);
}

void UOptionsLibrary::FailedToLoadMapAsset(const FVector CursorPosition)
{
    LoadAssetWith(CursorPosition, IndexOfChosenMap, OptionsFailedButtonColor);
}

void UOptionsLibrary::LoadAssetWith(const FVector &CursorPosition, int32 &IndexOfChosenAsset, const FLinearColor Color)
{
    if (IsButtonValid(IndexOfChosenAsset)) GetInstance()->Buttons[IndexOfChosenAsset]->ChangeButtonOutline(false, Color);
    IndexOfChosenAsset = GetSelectedButtonIndex(CursorPosition);
    if (IsButtonValid(IndexOfChosenAsset)) GetInstance()->Buttons[IndexOfChosenAsset]->ChangeButtonOutline(true, Color);
}

bool UOptionsLibrary::IsButtonValid(const int32 Index)
{
    return Index >= 0 && Index < GetInstance()->Buttons.Num() && GetInstance()->Buttons[Index] != nullptr;
}

void UOptionsLibrary::AddToButtons(UMenuBaseButton* Button)
{
    GetInstance()->Buttons.Add(Button);
}

TArray<UMenuBaseButton*> UOptionsLibrary::GetButtons()
{
    return GetInstance()->Buttons;
}

void UOptionsLibrary::CalculateButtonsDimensions()
{
   for(auto &Button : GetInstance()->Buttons)
   {
       if (!IsValid(Button)) continue;
       switch (Button->MenuButtonType)
       {
       case Menu_VehicleButton:
           Sizes[0]++;
           break;
       case Menu_MapButton:
           Sizes[1]++;
           break;
       case Menu_OptionsButton:
           Sizes[2]++;
           UpdateOptionButtonGraphics(Cast<UOptionBaseButton>(Button));
           break;
       default:
           break;
       }
   }
}

void UOptionsLibrary::OptionButtonPressed(UOptionBaseButton* Button, const EControllersButtonsDirection ControllerButton)
{
    if (!IsValid(Button)) return;

    const EOptionButtonType Type = Button->OptionButtonType;

    FString OptionName = Button->OptionName;
    FString ParentName = Button->ParentOptionName;

    auto Options = UDefaultPlayerOptions::GetOptionMap();
    UOptionBase* Option = Options.Contains(FName(OptionName)) ? Options[FName(OptionName)] : Options.Contains(FName(ParentName)) ? Options[FName(ParentName)] : nullptr;
    if (!IsValid(Option)) return;
    
    switch (ControllerButton)
    {
            default:
        case TriangleOrY:
        case CircleOrB:
            return;
        case CrossOrA:
            // Toggle the value of the option
            switch (Type)
            {
                default:
                case Option_ValueButton:
                case Option_CustomValueButton:
                    return;
                case Option_WheelsBoolButton:
                case Option_WheelsValueButton:
                case Option_VehicleValueButton:
                    {
                        UOptionWheelsButton* WheelsButton = Cast<UOptionWheelsButton>(Button);
                        if (!IsValid(WheelsButton)) return;
                        WheelsButton->bIsCollapsed = !WheelsButton->bIsCollapsed;
                    }
                [[fallthrough]];
                case Option_BoolButton:
                    {
                        TArray<UButton*> buttons = Button->MenuButton;
                        if (buttons.IsEmpty()) return;
                        UButton* button = buttons[0];
                        if (!IsValid(button)) return;
                        button->OnClicked.Broadcast();
                        if(Type != Option_BoolButton) break;
                        UOptionBool* BOption = Cast<UOptionBool>(Option);
                        if (!IsValid(BOption)) return;
                        BOption->BValue = !BOption->BValue;
                    }
                break;
            }
            break;
        case SquareOrX:
            // Reset to default value
            switch (Type)
            {
                default:
                case Option_WheelsBoolButton:
                case Option_WheelsValueButton:
                case Option_VehicleValueButton:
                    return;
                case Option_ValueButton:
                    {
                        UOptionFloat* FOption = Cast<UOptionFloat>(Option);
                        if (!IsValid(FOption)) return;
                        FOption->FValue = FOption->FDefaultValue;
                    }
                break;   
                case Option_CustomValueButton:
                    {
                        UOptionDriveMode* DOption = Cast<UOptionDriveMode>(Option);
                        if (!IsValid(DOption)) return;
                        DOption->DriveModeValue = DOption->DriveModeDefaultValue;
                    }
                break;   
                case Option_BoolButton:
                    {
                        UOptionBool* BOption = Cast<UOptionBool>(Button);
                        if (!IsValid(BOption)) return;
                        BOption->BValue = BOption->BDefaultValue;
                    }
                break;
            }
        break;
    }
    
}

void UOptionsLibrary::UpdateOptionButtonGraphics(UOptionBaseButton* OptionButton)
{
    if (!IsValid(OptionButton)) return;

    const EOptionButtonType Type = OptionButton->OptionButtonType;

    switch (Type)
    {
        default:
        case Option_VehicleValueButton:
        case Option_WheelsBoolButton:
        case Option_WheelsValueButton:
            return;
        case Option_BoolButton:
            {
                UOptionBoolButton* BButton = Cast<UOptionBoolButton>(OptionButton);
                if (!IsValid(BButton)) return;
                BButton->UpdateGraphics();
            }
        case Option_ValueButton:
            {
                UOptionValueButton* VButton = Cast<UOptionValueButton>(OptionButton);
                if (!IsValid(VButton)) return;
                VButton->UpdateGraphics();
            }
        case Option_CustomValueButton:
            {
                UOptionCustomValueButton* CButton = Cast<UOptionCustomValueButton>(OptionButton);
                if (!IsValid(CButton)) return;
                CButton->UpdateGraphics();
            }
    }
    
}
