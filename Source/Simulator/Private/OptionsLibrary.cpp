/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsLibrary.h"

#include "IntVectorTypes.h"

TArray<uint8> UOptionsLibrary::Sizes;
TArray<uint8> UOptionsLibrary::MaxColumns;
TArray<UMenuBaseButton*> UOptionsLibrary::Buttons;
int32 UOptionsLibrary::IndexOfChosenVehicle;
int32 UOptionsLibrary::IndexOfChosenMap;

void UOptionsLibrary::Initialize(TArray<uint8> TmpSizes, TArray<uint8> TmpMaxColumns, TArray<UMenuBaseButton*> TmpButtons)
{
    Sizes = TmpSizes;
    MaxColumns = TmpMaxColumns;
    Buttons = TmpButtons;
    IndexOfChosenVehicle = -1;
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
    if (Index < 0 || Index >= Buttons.Num()) return nullptr; // Invalid index
    return Buttons[Index];
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
    return FVector3f(CursorPosition);
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

    if (Buttons.IsEmpty()) return false;

    if (CurrentIndex < 0 || CurrentIndex >= Buttons.Num()) return false;
    // Update buttons if indices are valid

    if (Buttons.IsValidIndex(PreviousIndex) && PreviousIndex != CurrentIndex && PreviousIndex != IndexOfChosenVehicle)
    {
        Buttons[PreviousIndex]->ChangeButtonOutline(false, OptionsHoveredButtonColor); // Remove highlight from the previously selected button
    }
    if (Buttons.IsValidIndex(CurrentIndex) && CurrentIndex != IndexOfChosenVehicle)
    {
        Buttons[CurrentIndex]->ChangeButtonOutline(true, OptionsHoveredButtonColor); // Highlight the currently selected button
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
        Button->InitMenuBaseButton(TmpButtons, EMenuButtonType::TabButton);
        Buttons.Insert(Button, Offset);
        Offset += Sizes[i] + 1;
    }
    return Buttons;
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
    if (IsButtonValid(IndexOfChosenAsset)) Buttons[IndexOfChosenAsset]->ChangeButtonOutline(false, Color);
    IndexOfChosenAsset = GetSelectedButtonIndex(CursorPosition);
    if (IsButtonValid(IndexOfChosenAsset)) Buttons[IndexOfChosenAsset]->ChangeButtonOutline(true, Color);
}

bool UOptionsLibrary::IsButtonValid(const int32 Index)
{
    return Index >= 0 && Index < Buttons.Num() && Buttons[Index] != nullptr;
}