/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsLibrary.h"

#include "CRaceGM.h"
#include "IntVectorTypes.h"
#include "OptionVehicleButton.h"
#include "OptionWheelsButton.h"

#include "Kismet/GameplayStatics.h"

TArray<uint8> UOptionsLibrary::Sizes = {0,0,0};
TArray<uint8> UOptionsLibrary::MaxColumns = {5,5,1};
int32 UOptionsLibrary::IndexOfChosenVehicle = -1;
int32 UOptionsLibrary::IndexOfChosenMap = -1;

void UOptionsLibrary::Initialize(UTextBlock* ToolTipTextTmp, UScrollBox* ScrollBoxTmp)
{
    CleanButtons();
    if (IsValid(ToolTipTextTmp)) GetInstance()->OptionsToolTipText = ToolTipTextTmp;
    if (IsValid(ScrollBoxTmp)) GetInstance()->OptionsScrollBox = ScrollBoxTmp;
}

UOptionsLibrary* UOptionsLibrary::GetInstance()
{
    static UOptionsLibrary* Instance = NewObject<UOptionsLibrary>();
    Instance->AddToRoot(); // Keep it alive
    return Instance;
}

int32 UOptionsLibrary::GetSelectedButtonIndex(const FVector &CursorPosition)
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
    const int32 Index = Page + PageOffset + RowOffset + ColumnOffset;
    if (Index >= GetInstance()->Buttons.Num()) return -1; // Invalid index
    return Index;
}

UMenuBaseButton* UOptionsLibrary::GetSelectedButton(const FVector CursorPosition)
{
    const int32 Index = GetSelectedButtonIndex(CursorPosition);
    if (!IsButtonValid(Index)) return nullptr; // Invalid index
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
        case Up:
            if (CursorPosition.Y > 0)
            {
                NewCursorPosition.Y = NewCursorPosition.Y - 1;
                ShouldJumpTheHiddenButtons(FVector(NewCursorPosition), OffsetJump, ShouldJump);
                NewCursorPosition.Y = ShouldJump ? NewCursorPosition.Y - OffsetJump : NewCursorPosition.Y;
                UpdateToolTipText(FVector(NewCursorPosition));
                UpdateScrollBar(FVector(NewCursorPosition), CursorPosition);
            }
            break;
        case Down:
            if (CursorPosition.Y == 0)
            {
                NewCursorPosition.Y = 1; // Move to the first row of the grid
                UpdateToolTipText(FVector(NewCursorPosition));
                UpdateScrollBar(FVector(NewCursorPosition), CursorPosition);
                break;
            }
            if (CursorPosition.Y >= FMath::CeilToInt(PageSize / (float)Columns)) break; // Already at the bottom row, do nothing
            ShouldJumpTheHiddenButtons(CursorPosition, OffsetJump, ShouldJump);
            NewCursorPosition.Y = ShouldJump ? NewCursorPosition.Y + OffsetJump + 1 : NewCursorPosition.Y + 1;
            UpdateToolTipText(FVector(NewCursorPosition));
            UpdateScrollBar(FVector(NewCursorPosition), CursorPosition);
            break;
        case Left:
            if (CursorPosition.Y == 0)
            {
                NewCursorPosition.Z--;  // Move to the previous tab
                break;
            }
            [[fallthrough]];
        case Right:
            UpdateIfThisIsAValueButton(CursorPosition, Direction);
            break;
        
    }
    
    return NewCursorPosition;
}

void UOptionsLibrary::UpdateScrollBar(const FVector& CursorPosition, const FVector& PreviousCursorPosition)
{
    if (!IsValid(GetInstance()->OptionsScrollBox)) return;

    const int32 TotalVisibleButtons = 6;
    const float ScrollOffsetStep = 106.f;

    // Get current button index
    const int32 RawCurrentIndex = GetSelectedButtonIndex(CursorPosition) - 3 - Sizes[0] - Sizes[1];
    if (RawCurrentIndex < 0) return;
    // Initialize accumulator for skipped buttons due to collapse
    int32 TotalSkippedButtons = 0;
    int32 AdjustedCurrentIndex = RawCurrentIndex;

    // Store the original cursor position components
    const float BaseX = CursorPosition.X;
    const float BaseZ = CursorPosition.Z;

    // Check each button's state up to the current index
    for (int32 i = 0; i < RawCurrentIndex; ++i)
    {
        int32 OffsetJump = 0;
        bool ShouldJump = false;
        
        // Calculate the position for the button we're checking
        // We need to offset from the current selected button's position
        FVector ButtonPosition(
            BaseX,
            i,
            BaseZ
        );
        
        // Check if this button is collapsed
        ShouldJumpTheHiddenButtons(ButtonPosition, OffsetJump, ShouldJump);
        
        // If button is collapsed, adjust our counts
        if (ShouldJump)
        {
            i += OffsetJump;
            TotalSkippedButtons += OffsetJump;
            AdjustedCurrentIndex -= OffsetJump;
        }

    }

    const float ScrollOffset = GetInstance()->OptionsScrollBox->GetScrollOffset();
    const float VisibleStartIndex = ScrollOffset / ScrollOffsetStep;
    const float VisibleEndIndex = VisibleStartIndex + TotalVisibleButtons;

    // Check if the adjusted button position is outside the visible range
    if (AdjustedCurrentIndex - 1 < VisibleStartIndex || AdjustedCurrentIndex >= VisibleEndIndex)
    {
        // Calculate new scroll offset considering collapsed buttons
        float NewScrollOffset = (AdjustedCurrentIndex - 2) * ScrollOffsetStep;
        
        // Ensure we don't go negative
        NewScrollOffset = FMath::Max(0.0f, NewScrollOffset);
        
        // Clamp to valid range
        NewScrollOffset = FMath::Min(NewScrollOffset, 
            GetInstance()->OptionsScrollBox->GetScrollOffsetOfEnd());
        
        // Update the scroll box position
        GetInstance()->OptionsScrollBox->SetScrollOffset(NewScrollOffset);
    }
}

void UOptionsLibrary::UpdateToolTipText(const FVector& CursorPosition)
{
    if(CursorPosition.Y == 0)
    {
        GetInstance()->OptionsToolTipText->SetText(FText::FromString(""));
        return;
    }
    int32 Index = GetSelectedButtonIndex(CursorPosition);
    if (!IsButtonValid(Index)) return;
    UOptionBaseButton* Button = static_cast<UOptionBaseButton*>(GetInstance()->Buttons[Index]);
    FString Name = Button->OptionName;
    if(Button->ParentOptionName != "") Name = Button->ParentOptionName;
    UOptionBase* Option = UDefaultPlayerOptions::GetOption(FName(Name));
    if (Option == nullptr) return;
    FString ToolTip = Option->OptionTooltip;
    GetInstance()->OptionsToolTipText->SetText(FText::FromString(ToolTip));
}

int32 UOptionsLibrary::CalculateJumpOffset(const EOptionButtonType& OptionType)
{
    switch(OptionType)
    {
    case Option_WheelsBoolButton:
    case Option_WheelsValueButton:
        return 4;
    case Option_VehicleValueButton:
        return 5;
    case Option_CustomValueButton:
    case Option_ValueButton:
    case Option_BoolButton:
    default:
        return 0;
    }
}

void UOptionsLibrary::UpdateBoolButton(UOptionBoolButton* BoolButton)
{
    if (!IsValid(BoolButton)) return; // Invalid button
    FString Name = BoolButton->OptionName;
    if(BoolButton->ParentOptionName != "") Name = BoolButton->ParentOptionName;
    UOptionBase* BaseOption = UDefaultPlayerOptions::GetOption(FName(Name));
    if (!IsValid(BaseOption)) return; // Invalid option
    
    switch (BaseOption->BaseOptionButtonType)
    {
        default:
        case Option_ValueButton:
        case Option_CustomValueButton:
        case Option_VehicleValueButton:
        case Option_WheelsValueButton:
        return;
        case Option_BoolButton:
        {
            UOptionBool* Option = Cast<UOptionBool>(BaseOption);
            if (!IsValid(Option)) return; // Invalid option
            Option->BValue = !Option->BValue;
        break;
        }
        case Option_WheelsBoolButton:
        {
            UOptionWheels* WheelsOption = Cast<UOptionWheels>(BaseOption);
            if (!IsValid(WheelsOption)) return; // Invalid option
            if(BoolButton->OptionName == "Front Left Wheel")
            {
                WheelsOption->FVehicleWheelsValue.FrontLeftWheel = !WheelsOption->FVehicleWheelsValue.FrontLeftWheel;
            }
            if (BoolButton->OptionName == "Front Right Wheel")
            {
                WheelsOption->FVehicleWheelsValue.FrontRightWheel = !WheelsOption->FVehicleWheelsValue.FrontRightWheel;
            }
            if (BoolButton->OptionName == "Rear Left Wheel")
            {
                WheelsOption->FVehicleWheelsValue.RearLeftWheel = !WheelsOption->FVehicleWheelsValue.RearLeftWheel;
            }
            if (BoolButton->OptionName == "Rear Right Wheel")
            {
                WheelsOption->FVehicleWheelsValue.RearRightWheel = !WheelsOption->FVehicleWheelsValue.RearRightWheel;
            }
        break;
        }
    }

    BoolButton->BValue = !BoolButton->BValue;
    BoolButton->UpdateGraphics();
}

void UOptionsLibrary::UpdateIfThisIsAValueButton(const FVector& CursorPosition, const EControllersArrowsDirection &Direction)
{
    UMenuBaseButton* Button = GetSelectedButton(CursorPosition);
    if (!IsValid(Button)) return; // Invalid button
    if (Button->MenuButtonType != Menu_OptionsButton) return; // Only check for options buttons
    UOptionBaseButton* OptionButton = Cast<UOptionBaseButton>(Button);
    if (!IsValid(OptionButton)) return; // Invalid button
    if (OptionButton->OptionButtonEype == Option_ValueButton) UpdateValueButton(Cast<UOptionValueButton>(OptionButton), Direction);
    if (OptionButton->OptionButtonEype == Option_CustomValueButton) UpdateCustomValueButton(Cast<UOptionCustomValueButton>(OptionButton), Direction);
}

void UOptionsLibrary::UpdateValueButton(UOptionValueButton* ValueButton, const EControllersArrowsDirection& Direction)
{
    int8 Sign = 0;
    switch (Direction)
    {
        default:
        return;
        case Left:
            Sign = -1;
        break;
        case Right:
            Sign = 1;
        break;
    }
    if (!IsValid(ValueButton)) return; // Invalid button
    FString Name = ValueButton->OptionName;
    if(ValueButton->ParentOptionName != "") Name = ValueButton->ParentOptionName;
    UOptionBase* BaseOption = UDefaultPlayerOptions::GetOption(FName(Name));
    if (!IsValid(BaseOption)) return; // Invalid option
    float NewValue;
    switch (BaseOption->BaseOptionButtonType)
    {
        default:
        return;
        case Option_ValueButton:
        {
            UOptionFloat* Option = Cast<UOptionFloat>(BaseOption);
            if (!IsValid(Option)) return; // Invalid option
            NewValue = Option->FValue + Sign * Option->Step;
            if (NewValue < Option->FMinValue || NewValue > Option->FMaxValue) return; // Out of bounds
            Option->FValue = NewValue;
        }
        break;
        case Option_VehicleValueButton:
            {
                UOptionVehicle* VehicleOption = Cast<UOptionVehicle>(BaseOption);
                if (!IsValid(VehicleOption)) return; // Invalid option
                if(ValueButton->OptionName == "Chassis")
                {
                    NewValue = VehicleOption->FVehicleValue.Chassis + Sign * VehicleOption->Step;
                    if (NewValue < VehicleOption->FVehicleMinValue.Chassis || NewValue > VehicleOption->FVehicleMaxValue.Chassis) return; // Out of bounds
                    VehicleOption->FVehicleValue.Chassis = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Front Left Wheel")
                {
                    NewValue = VehicleOption->FVehicleValue.Wheels.FrontLeftWheel + Sign * VehicleOption->Step;
                    if (NewValue < VehicleOption->FVehicleMinValue.Wheels.FrontLeftWheel || NewValue > VehicleOption->FVehicleMaxValue.Wheels.FrontLeftWheel) return; // Out of bounds
                    VehicleOption->FVehicleValue.Wheels.FrontLeftWheel = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Front Right Wheel")
                {
                    NewValue = VehicleOption->FVehicleValue.Wheels.FrontRightWheel + Sign * VehicleOption->Step;
                    if (NewValue < VehicleOption->FVehicleMinValue.Wheels.FrontRightWheel || NewValue > VehicleOption->FVehicleMaxValue.Wheels.FrontRightWheel) return; // Out of bounds
                    VehicleOption->FVehicleValue.Wheels.FrontRightWheel = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Rear Left Wheel")
                {
                    NewValue = VehicleOption->FVehicleValue.Wheels.RearLeftWheel + Sign * VehicleOption->Step;
                    if (NewValue < VehicleOption->FVehicleMinValue.Wheels.RearLeftWheel || NewValue > VehicleOption->FVehicleMaxValue.Wheels.RearLeftWheel) return; // Out of bounds
                    VehicleOption->FVehicleValue.Wheels.RearLeftWheel = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Rear Right Wheel")
                {
                    NewValue = VehicleOption->FVehicleValue.Wheels.RearRightWheel + Sign * VehicleOption->Step;
                    if (NewValue < VehicleOption->FVehicleMinValue.Wheels.RearRightWheel || NewValue > VehicleOption->FVehicleMaxValue.Wheels.RearRightWheel) return; // Out of bounds
                    VehicleOption->FVehicleValue.Wheels.RearRightWheel = NewValue;
                    break;
                }
            }
        case Option_WheelsBoolButton:
        case Option_WheelsValueButton:
            {
                UOptionWheels* WheelsOption = Cast<UOptionWheels>(BaseOption);
                if (!IsValid(WheelsOption)) return; // Invalid option
                if(ValueButton->OptionName == "Front Left Wheel")
                {
                    NewValue = WheelsOption->FVehicleWheelsValue.FrontLeftWheel + Sign * WheelsOption->Step;
                    if (NewValue < WheelsOption->FVehicleWheelsMinValue.FrontLeftWheel || NewValue > WheelsOption->FVehicleWheelsMaxValue.FrontLeftWheel) return; // Out of bounds
                    WheelsOption->FVehicleWheelsValue.FrontLeftWheel = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Front Right Wheel")
                {
                    NewValue = WheelsOption->FVehicleWheelsValue.FrontRightWheel + Sign * WheelsOption->Step;
                    if (NewValue < WheelsOption->FVehicleWheelsMinValue.FrontRightWheel || NewValue > WheelsOption->FVehicleWheelsMaxValue.FrontRightWheel) return; // Out of bounds
                    WheelsOption->FVehicleWheelsValue.FrontRightWheel = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Rear Left Wheel")
                {
                    NewValue = WheelsOption->FVehicleWheelsValue.RearLeftWheel + Sign * WheelsOption->Step;
                    if (NewValue < WheelsOption->FVehicleWheelsMinValue.RearLeftWheel || NewValue > WheelsOption->FVehicleWheelsMaxValue.RearLeftWheel) return; // Out of bounds
                    WheelsOption->FVehicleWheelsValue.RearLeftWheel = NewValue;
                    break;
                }
                if (ValueButton->OptionName == "Rear Right Wheel")
                {
                    NewValue = WheelsOption->FVehicleWheelsValue.RearRightWheel + Sign * WheelsOption->Step;
                    if (NewValue < WheelsOption->FVehicleWheelsMinValue.RearRightWheel || NewValue > WheelsOption->FVehicleWheelsMaxValue.RearRightWheel) return; // Out of bounds
                    WheelsOption->FVehicleWheelsValue.RearRightWheel = NewValue;
                    break;
                }
                return;
            }
        break;
    }

    ValueButton->FValue = NewValue;
    UpdateOptionButtonGraphics(ValueButton);
    
}

void UOptionsLibrary::UpdateCustomValueButton(UOptionCustomValueButton* CustomValueButton, const EControllersArrowsDirection& Direction)
{
    int8 Sign = 0;
    switch (Direction)
    {
    default:
        return;
    case Left:
        Sign = -1;
        break;
    case Right:
        Sign = 1;
        break;
    }
    if (!IsValid(CustomValueButton)) return; // Invalid button
    FString Name = CustomValueButton->OptionName;
    UOptionDriveMode* Option = Cast<UOptionDriveMode>(UDefaultPlayerOptions::GetOption(FName(Name)));
    if (!IsValid(Option)) return; // Invalid option
    float NewValue = Option->DriveModeValue + Sign * Option->Step;
    if (NewValue < Option->DriveModeMinValue || NewValue > Option->DriveModeMaxValue) return; // Out of bounds
    Option->DriveModeValue = static_cast<EDriveMode>(NewValue);
    CustomValueButton->CValue = Option->DriveModeValue;
    UpdateOptionButtonGraphics(CustomValueButton);
}

UOptionBaseButton* UOptionsLibrary::GetButtonByName(const FString& Name)
{
    if (Name.IsEmpty()) return nullptr; // Invalid name
    for(auto &Button : GetInstance()->Buttons)
    {
        if (!IsValid(Button)) continue;
        if (Button->MenuButtonType != Menu_OptionsButton) continue; // Only check for options buttons
        UOptionBaseButton* OptionButton = Cast<UOptionBaseButton>(Button);
        if (!IsValid(OptionButton)) continue; // Invalid button
        if (OptionButton->OptionName == Name) return OptionButton;
    }
    return nullptr; // No button found
}

void UOptionsLibrary::ShouldJumpTheHiddenButtons(const FVector& CursorPosition, int32& OffsetJump, bool& ShouldJump)
{
    UMenuBaseButton* Button = Cast<UMenuBaseButton>(GetSelectedButton(CursorPosition));
    if (!IsValid(Button)) return; // Invalid button

    const EMenuButtonType MenuType = Button->MenuButtonType;
    if (MenuType != Menu_OptionsButton) return; // Only check for options buttons

    UOptionBaseButton* OptionButton = Cast<UOptionBaseButton>(Button);
    if (!IsValid(OptionButton)) return; // Invalid button
    
    switch(OptionButton->OptionButtonEype)
    {
    case Option_WheelsBoolButton:
    case Option_WheelsValueButton:
    case Option_VehicleValueButton:
    break;
    default:
    case Option_CustomValueButton:
    return;
    case Option_ValueButton:
    case Option_BoolButton:
        {
            const FString ParentName = OptionButton->ParentOptionName;
            if (ParentName.IsEmpty()) return; // No parent to check
            OptionButton = GetButtonByName(ParentName);
        }
        break;
    }
    if (!IsValid(OptionButton)) return; // Invalid button
    OffsetJump = CalculateJumpOffset(OptionButton->OptionButtonEype);
    UOptionWheelsButton* WheelsButton = Cast<UOptionWheelsButton>(OptionButton);
    if (!IsValid(WheelsButton)) return ; // Invalid button
    ShouldJump = WheelsButton->bIsCollapsed;
}

FVector3f UOptionsLibrary::MoveCursor(const EControllersArrowsDirection Direction, const FVector CursorPosition)
{
    FVector3f NewCursorPosition = FVector3f(CursorPosition);
    switch (static_cast<int>(CursorPosition.Z))
    {
    case 0:
    case 1:
    default:
        return MoveCursorNormal(Direction, CursorPosition);
    case 2:
       NewCursorPosition = MoveCursorSpecial(Direction, CursorPosition);
    }
    return NewCursorPosition;
    
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

    if (!IsButtonValid(CurrentIndex)) return false;
    if (!IsButtonValid(PreviousIndex)) return false;
    // Update buttons if indices are valid

    if (AllButtons.IsValidIndex(PreviousIndex) && PreviousIndex != CurrentIndex && PreviousIndex != IndexOfChosenVehicle)
    {
        if (!IsValid(AllButtons[PreviousIndex])) return false;
        AllButtons[PreviousIndex]->ChangeButtonOutline(false, OptionsHoveredButtonColor); // Remove highlight from the previously selected button
    }
    if (AllButtons.IsValidIndex(CurrentIndex) && CurrentIndex != IndexOfChosenVehicle)
    {
        if (!IsValid(AllButtons[CurrentIndex])) return false;
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

    if (IsButtonValid(IndexOfChosenVehicle)) GetInstance()->Buttons[IndexOfChosenVehicle]->ChangeButtonOutline(true, OptionsChosenButtonColor);
    if (IsButtonValid(IndexOfChosenMap)) GetInstance()->Buttons[IndexOfChosenMap]->ChangeButtonOutline(true, OptionsChosenButtonColor);
    
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
    if (!IsValid(Button)) return;
    GetInstance()->Buttons.Add(Button);
}

TArray<UMenuBaseButton*> UOptionsLibrary::GetButtons()
{
    return GetInstance()->Buttons;
}

void UOptionsLibrary::CleanButtons()
{
    GetInstance()->Buttons.Empty();
    Sizes = {0,0,0};
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
           {
                UOptionBaseButton* OptionButton = Cast<UOptionBaseButton>(Button);
                if (!IsValid(OptionButton)) return;
           }
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
            switch (Button->OptionButtonEype)
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
                        TArray<UButton*> buttons = Button->MenuButton;
                        if (buttons.IsEmpty()) return;
                        UButton* button = buttons[0];
                        if (!IsValid(button)) return;
                        button->OnClicked.Broadcast();
                break;
                    }
                case Option_BoolButton:
                    UpdateBoolButton(Cast<UOptionBoolButton>(Button));
                break;
            }
            break;
        case SquareOrX:
            // Reset to default value
            switch (Option->BaseOptionButtonType)
            {
                default:
                return;
                case Option_VehicleValueButton:
                {
                    UOptionVehicle* VehicleOption = Cast<UOptionVehicle>(Option);
                    if (!IsValid(VehicleOption)) return; // Invalid option
                    UOptionValueButton* VButton = Cast<UOptionValueButton>(Button);
                    if (!IsValid(VButton)) return;
                    if (Button->OptionName == "Chassis")
                    {
                        VehicleOption->FVehicleValue.Chassis = VehicleOption->FVehicleDefaultValue.Chassis;
                        VButton->FValue = VehicleOption->FVehicleDefaultValue.Chassis;
                    }
                    if (Button->OptionName == "Front Left Wheel")
                    {
                        VehicleOption->FVehicleValue.Wheels.FrontLeftWheel = VehicleOption->FVehicleDefaultValue.Wheels.FrontLeftWheel;
                        VButton->FValue = VehicleOption->FVehicleDefaultValue.Wheels.FrontLeftWheel;
                    }
                    if (Button->OptionName == "Front Right Wheel")
                    {
                        VehicleOption->FVehicleValue.Wheels.FrontRightWheel = VehicleOption->FVehicleDefaultValue.Wheels.FrontRightWheel;
                        VButton->FValue = VehicleOption->FVehicleDefaultValue.Wheels.FrontRightWheel;
                    }
                    if (Button->OptionName == "Rear Left Wheel")
                    {
                        VehicleOption->FVehicleValue.Wheels.RearLeftWheel = VehicleOption->FVehicleDefaultValue.Wheels.RearLeftWheel;
                        VButton->FValue = VehicleOption->FVehicleDefaultValue.Wheels.RearLeftWheel;
                    }
                    if (Button->OptionName == "Rear Right Wheel")
                    {
                        VehicleOption->FVehicleValue.Wheels.RearRightWheel = VehicleOption->FVehicleDefaultValue.Wheels.RearRightWheel;
                        VButton->FValue = VehicleOption->FVehicleDefaultValue.Wheels.RearRightWheel;
                    }
                break;
                }
                case Option_WheelsBoolButton:
                {
                    UOptionWheels* WheelsOption = Cast<UOptionWheels>(Option);
                    if (!IsValid(WheelsOption)) return; // Invalid option
                    UOptionBoolButton* VButton = Cast<UOptionBoolButton>(Button);
                    if (!IsValid(VButton)) return;
                    if (Button->OptionName == "Front Left Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.FrontLeftWheel = WheelsOption->FVehicleWheelsDefaultValue.FrontLeftWheel;
                        VButton->BValue = WheelsOption->FVehicleWheelsDefaultValue.FrontLeftWheel > 0;
                    }
                    if (Button->OptionName == "Front Right Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.FrontRightWheel = WheelsOption->FVehicleWheelsDefaultValue.FrontRightWheel;
                        VButton->BValue = WheelsOption->FVehicleWheelsDefaultValue.FrontRightWheel > 0;
                    }
                    if (Button->OptionName == "Rear Left Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.RearLeftWheel = WheelsOption->FVehicleWheelsDefaultValue.RearLeftWheel;
                        VButton->BValue = WheelsOption->FVehicleWheelsDefaultValue.RearLeftWheel > 0;
                    }
                    if (Button->OptionName == "Rear Right Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.RearRightWheel = WheelsOption->FVehicleWheelsDefaultValue.RearRightWheel;
                        VButton->BValue = WheelsOption->FVehicleWheelsDefaultValue.RearRightWheel > 0;
                    }
                    break;
                }
                case Option_WheelsValueButton:
               {
                    UOptionWheels* WheelsOption = Cast<UOptionWheels>(Option);
                    if (!IsValid(WheelsOption)) return; // Invalid option
                    UOptionValueButton* VButton = Cast<UOptionValueButton>(Button);
                    if (!IsValid(VButton)) return;
                    if (Button->OptionName == "Front Left Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.FrontLeftWheel = WheelsOption->FVehicleWheelsDefaultValue.FrontLeftWheel;
                        VButton->FValue = WheelsOption->FVehicleWheelsDefaultValue.FrontLeftWheel;
                    }
                    if (Button->OptionName == "Front Right Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.FrontRightWheel = WheelsOption->FVehicleWheelsDefaultValue.FrontRightWheel;
                        VButton->FValue = WheelsOption->FVehicleWheelsDefaultValue.FrontRightWheel;
                    }
                    if (Button->OptionName == "Rear Left Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.RearLeftWheel = WheelsOption->FVehicleWheelsDefaultValue.RearLeftWheel;
                        VButton->FValue = WheelsOption->FVehicleWheelsDefaultValue.RearLeftWheel;
                    }
                    if (Button->OptionName == "Rear Right Wheel")
                    {
                        WheelsOption->FVehicleWheelsValue.RearRightWheel = WheelsOption->FVehicleWheelsDefaultValue.RearRightWheel;
                        VButton->FValue = WheelsOption->FVehicleWheelsDefaultValue.RearRightWheel;
                    }
                break;
                }
                case Option_CustomValueButton:
                {
                    UOptionDriveMode* DOption = Cast<UOptionDriveMode>(Option);
                    if (!IsValid(DOption)) return;
                    DOption->DriveModeValue = DOption->DriveModeDefaultValue;
                    UOptionCustomValueButton* CButton = Cast<UOptionCustomValueButton>(Button);
                    if (!IsValid(CButton)) return;
                    CButton->CValue = DOption->DriveModeDefaultValue;
                break;   
                }
                case Option_ValueButton:
                {
                    UOptionFloat* FOption = Cast<UOptionFloat>(Option);
                    if (!IsValid(FOption)) return;
                    FOption->FValue = FOption->FDefaultValue;
                    UOptionValueButton* VButton = Cast<UOptionValueButton>(Button);
                    if (!IsValid(VButton)) return;
                    VButton->FValue = FOption->FDefaultValue;
                break;   
                }
                case Option_BoolButton:
                {
                    UOptionBool* BOption = Cast<UOptionBool>(Option);
                    if (!IsValid(BOption)) return;
                    BOption->BValue = BOption->BDefaultValue;
                    UOptionBoolButton* BButton = Cast<UOptionBoolButton>(Button);
                    if (!IsValid(BButton)) return;
                    BButton->BValue = BOption->BDefaultValue;
                break;
                }
            }
        break;
    }
    UpdateOptionButtonGraphics(Button);
}

void UOptionsLibrary::UpdateOptionButtonGraphics(UOptionBaseButton* OptionButton)
{
    if (!IsValid(OptionButton)) return;
    
    switch (OptionButton->OptionButtonEype)
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

void UOptionsLibrary::TryToStartGame(UUserWidget* WidgetContext)
{
    UE_LOG(LogTemp, Warning, TEXT("TryToStartGame"));
    UE_LOG(LogTemp, Warning, TEXT("IndexOfChosenVehicle: %d"), IndexOfChosenVehicle);
    UE_LOG(LogTemp, Warning, TEXT("IndexOfChosenMap: %d"), IndexOfChosenMap);

    if (IndexOfChosenVehicle < 0 || IndexOfChosenMap < 0) return;

    if (!WidgetContext)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid widget context"));
        return;
    }

    UWorld* World = WidgetContext->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid world context from widget"));
        return;
    }

    UMenuSelectButton* VehicleButton = Cast<UMenuSelectButton>(GetInstance()->Buttons[IndexOfChosenVehicle]);
    if (!IsValid(VehicleButton)) return;

    const FString VehiclePath = VehicleButton->AssetObjectPath;
    UE_LOG(LogTemp, Warning, TEXT("Vehicle Path: %s"), *VehiclePath);
    UClass* VehicleClass = StaticLoadClass(APawn::StaticClass(), nullptr, *VehiclePath);

    if (!VehicleClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load Vehicle class from path: %s"), *VehiclePath);
        return;
    }

    // Load the game mode class
    const FString GameModePath = TEXT("/Script/Simulator.CRaceGM");
    UClass* GameModeClass = StaticLoadClass(AGameModeBase::StaticClass(), nullptr, *GameModePath);

    if (!GameModeClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load GameMode class from path: %s"), *GameModePath);
        return;
    }

    // Cast to the specific GameMode class
    ACRaceGM* GameModeInstance = Cast<ACRaceGM>(GameModeClass->GetDefaultObject());
    if (!GameModeInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to cast GameMode to ACRaceGM"));
        return;
    }

    GameModeInstance->DefaultPawnClass = VehicleClass;
    
    FString Options;
    Options.Appendf(TEXT("?Game=%s?DefaultPawnClass=%s"), *GameModeClass->GetPathName(), *VehicleClass->GetPathName());

    UMenuSelectButton* MapButton = Cast<UMenuSelectButton>(GetInstance()->Buttons[IndexOfChosenMap]);
    if (!IsValid(MapButton)) return;

    const FString& MapPath = MapButton->AssetObjectPath;
    UGameplayStatics::OpenLevel(World, *MapPath, true, Options);
}

UClass* UOptionsLibrary::GetChosenVehicleClass()
{
    if (IndexOfChosenVehicle < 0) return nullptr;
    UMenuSelectButton* VehicleButton = Cast<UMenuSelectButton>(GetInstance()->Buttons[IndexOfChosenVehicle]);
    if (!IsValid(VehicleButton)) return nullptr;
    const FString VehiclePath = VehicleButton->AssetObjectPath;
    UClass* VehicleClass = StaticLoadClass(APawn::StaticClass(), nullptr, *VehiclePath);
    return VehicleClass;
}

FString UOptionsLibrary::GetChosenVehicleName()
{
    if (IndexOfChosenVehicle < 0) return FString();
    UMenuSelectButton* VehicleButton = Cast<UMenuSelectButton>(GetInstance()->Buttons[IndexOfChosenVehicle]);
    if (!IsValid(VehicleButton)) return FString();
    return VehicleButton->MenuButtonName;
}
