/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsLibrary.h"

TArray<uint8> UOptionsLibrary::Sizes;
TArray<uint8> UOptionsLibrary::MaxColumns;

void UOptionsLibrary::Initialize(TArray<uint8> TmpSizes, TArray<uint8> TmpMaxColumns)
{
    Sizes = TmpSizes;
    MaxColumns = TmpMaxColumns;
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


UOptionsBaseButton* UOptionsLibrary::GetSelectedButton(TArray<UOptionsBaseButton*> Buttons, const FVector CursorPosition)
{
    const int32 Index = GetSelectedButtonIndex(CursorPosition);
    if (Index < 0 || Index >= Buttons.Num()) return nullptr; // Invalid index
    return Buttons[Index];
}

FVector3f UOptionsLibrary::MoveCursor(const EControllersArrowsDirection Direction, const FVector3d CursorPosition)
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


bool UOptionsLibrary::UpdateSelectedButton(
    TArray<UOptionsBaseButton*> Buttons,
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
    // Update buttons if indices are vali

    if (Buttons.IsValidIndex(PreviousIndex) && PreviousIndex != CurrentIndex)
    {
        Buttons[PreviousIndex]->ChangeButtonOutline(false); // Remove highlight from the previously selected button
    }
    if (Buttons.IsValidIndex(CurrentIndex))
    {
        Buttons[CurrentIndex]->ChangeButtonOutline(true); // Highlight the currently selected button
    }

    if (abs((CurrentCursorPosition - PreviousCursorPosition).Z) != 1) return false; // Only update if the page has changed
    return true;
    
}

TArray<UOptionsBaseButton*> UOptionsLibrary::AddTabButtons(TArray<UButton*> TabButtons, TArray<UOptionsBaseButton*> Buttons)
{
    uint32 Offset = 0;
    for(int i = 0; i < TabButtons.Num(); i++)
    {
        UOptionsBaseButton* Button = NewObject<UOptionsBaseButton>(UOptionsBaseButton::StaticClass());
        Button->InitializeBaseButton(TabButtons[i], EOptionsButtonType::TabButton);
        Buttons.Insert(Button, Offset);
        Offset += Sizes[i] + 1;
    }
    return Buttons;
}

void UOptionsLibrary::ChangePanelVisibility(TArray<UUniformGridPanel*> Panels, const FVector CursorPosition, const FVector PreviousCursorPosition)
{
    if (CursorPosition.Z == PreviousCursorPosition.Z) return; // Only change visibility if the page has changed
    if (Panels.IsValidIndex(CursorPosition.Z))
    {
        Panels[CursorPosition.Z]->SetVisibility(ESlateVisibility::Visible);
    }
    if (Panels.IsValidIndex(PreviousCursorPosition.Z))
    {
        Panels[PreviousCursorPosition.Z]->SetVisibility(ESlateVisibility::Hidden);
    }
}

