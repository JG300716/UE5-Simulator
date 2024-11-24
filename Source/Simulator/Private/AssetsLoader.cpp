/**
* Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
#include "AssetsLoader.h"
TArray<FString> UAssetsLoader::GetFoldersInDirectory(const FString& DirectoryPath)
{
    TArray<FString> FolderPaths;
    IFileManager& FileManager = IFileManager::Get();

    // Construct the full path based on the provided DirectoryPath
    FString FolderPath = FPaths::ProjectContentDir() + DirectoryPath;
    if (FPaths::DirectoryExists(FolderPath)) {
        // Find folders directly in the specified directory (non-recursive)
        TArray<FString> FoundItems;
        FileManager.FindFiles(FoundItems, *(FolderPath / TEXT("*")), false, true);

        // Append the directory path to each found folder name
        for (const FString& Item : FoundItems) {
            FolderPaths.Add(FolderPath / Item);
        }

        UE_LOG(LogTemp, Warning, TEXT("Found %d folders in %s."), FolderPaths.Num(), *FolderPath);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Directory was not found in %s."), *FolderPath);
    }

    return FolderPaths;
}
