/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "OptionsLibrary.h"

FVector3f UOptionsLibrary::MoveCursor(const ECursorDirection Direction, const FVector3d CursorPosition, const TArray<uint8> Sizes)
{
    FVector3f NewCursorPosition = FVector3f(CursorPosition);

    const uint8 Page = CursorPosition.Z;
    const uint8 MaxColumns = (Page == 2) ? 1 : 5; // Options panel has 1 column, others have 5
    uint8 PageSize = 0;

    for(int i = 0; i < Page; i++)
    {
        PageSize += Sizes[i];
    }

    switch (Direction)
    {
        case ECursorDirection::Up:
            if (CursorPosition.Y > 0)
            {
                NewCursorPosition.Y--;
                if (NewCursorPosition.Y == 0)
                    NewCursorPosition.X = 0; // Snap to the current tab button
            }
            return NewCursorPosition;

        case ECursorDirection::Down:
            if (CursorPosition.Y == 0)
            {
                NewCursorPosition.Y = 1; // Move to the first row of the grid
                NewCursorPosition.X = 0; // Snap to the first column
                return NewCursorPosition;
            }

            if (CursorPosition.Y >= FMath::CeilToInt(PageSize / (float)MaxColumns) - 1)
                return NewCursorPosition; // Already at the bottom row, do nothing

            NewCursorPosition.Y++;
            if (NewCursorPosition.Y == FMath::CeilToInt(PageSize / (float)MaxColumns) - 1)
                NewCursorPosition.X = FMath::Min(CursorPosition.X, PageSize % MaxColumns - 1); // Clamp to last slot
            return NewCursorPosition;

        case ECursorDirection::Left:
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

            if (Page == 2)
                return NewCursorPosition; // Do nothing for Options panel

            if (CursorPosition.X > 0)
            {
                NewCursorPosition.X--;
                return NewCursorPosition; // Move left within the same row
            }

            if (CursorPosition.Y > 1)
            {
                NewCursorPosition.Y--;
                NewCursorPosition.X = MaxColumns - 1; // Wrap to the end of the previous row
            }
            return NewCursorPosition;

        case ECursorDirection::Right:
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

            if (Page == 2)
                return NewCursorPosition; // Do nothing for Options panel

            if (CursorPosition.X < MaxColumns - 1 && (CursorPosition.Y * MaxColumns + CursorPosition.X + 1) < PageSize)
            {
                NewCursorPosition.X++;
                return NewCursorPosition; // Move right within the same row
            }

            if ((CursorPosition.Y + 1) * MaxColumns < PageSize)
            {
                NewCursorPosition.Y++;
                NewCursorPosition.X = 0; // Wrap to the beginning of the next row
            }
            return NewCursorPosition;

        default:
            return NewCursorPosition; // Handle invalid direction by doing nothing
    }
}

void UOptionsLibrary::UpdateSelectedButton(
    TArray<UOptionsButtonType*> Buttons,
    const FVector CurrentCursorPosition,
    const FVector PreviousCursorPosition,
    const TArray<uint8> Sizes,
    const TArray<uint8> MaxColumns)
{
    auto CalculateIndex = [Sizes, MaxColumns](const FVector& CursorPosition) -> int32
    {
        const uint32 Page = CursorPosition.Z;
        uint32 PageOffset = 0;
        const uint32 RowOffset = MaxColumns[Page] * __max((CursorPosition.Y - 1), 0);
        const bool IsTabButton = CursorPosition.Y == 0;
        const uint32 ColumnOffset = IsTabButton ? 0 : 1;
        for(uint32 i = 0; i < Page; i++)
        {
            PageOffset += Sizes[i];
        }
        return Page + PageOffset + RowOffset + ColumnOffset;
    };


    // Ensure valid positions
    if (CurrentCursorPosition.Z < 0 || PreviousCursorPosition.Z < 0)
        return; // Invalid position

    // Compute indices for current and previous buttons
    const int32 CurrentIndex = CalculateIndex(CurrentCursorPosition);
    const int32 PreviousIndex = CalculateIndex(PreviousCursorPosition);

    UE_LOG(LogTemp, Warning, TEXT("CurrentIndex: %d, PreviousIndex: %d"), CurrentIndex, PreviousIndex);
    
    // Update buttons if indices are valid
    if (Buttons.IsValidIndex(CurrentIndex))
    {
        Buttons[CurrentIndex]->ChangeButtonOutline(true); // Highlight the currently selected button
    }

    if (Buttons.IsValidIndex(PreviousIndex) && PreviousIndex != CurrentIndex)
    {
        Buttons[PreviousIndex]->ChangeButtonOutline(false); // Remove highlight from the previously selected button
    }
}

