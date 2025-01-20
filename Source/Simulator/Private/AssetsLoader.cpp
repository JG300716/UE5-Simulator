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


void ListFilesInDirectory(const FString& DirectoryPath)
{
    // Directory you want to scan (change this path to match your directory)

    // Get the Asset Registry Module
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

    // Get all assets in the directory (this returns all asset metadata)
    TArray<FAssetData> AssetDataArray;
    AssetRegistry.GetAssetsByPath(FName(*DirectoryPath), AssetDataArray);

    // Log each file in the directory
    for (const FAssetData& AssetData : AssetDataArray)
    {
        FString AssetName = AssetData.AssetName.ToString();
        FString AssetPath = AssetData.ObjectPath.ToString();

        // You can process the asset here as needed
        UE_LOG(LogTemp, Log, TEXT("Asset found: %s at Path: %s"), *AssetName, *AssetPath);
    }

    // Optionally, handle if no assets were found
    if (AssetDataArray.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No assets found in the directory: %s"), *DirectoryPath);
    }
}

TSoftClassPtr<AMyCar> UAssetsLoader::LoadVehicleAsset(const FString& AssetPath, bool &Success)
{
   // Example path:
   // "/Game/Simulator/Cars/FinalModels/Chevrolet/Chevrolet_Object.Chevrolet_Object_C"
    TSoftClassPtr<AMyCar> Asset = TSoftClassPtr<AMyCar>(FSoftObjectPath(AssetPath));
    Success = Asset.IsValid();
    if (Success) {
        UE_LOG(LogTemp, Warning, TEXT("Asset loaded successfully from %s."), *AssetPath);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Asset could not be loaded from %s."), *AssetPath);
    }
    //ListFilesInDirectory("/Game/Simulator/Cars/FinalModels/Chevrolet/");

    return Asset;
}

FString UAssetsLoader::LoadMapAsset(const FString& AssetPath, bool &Success)
{
    // Example path:
    // "/Game/Simulator/Maps/Racetrack/Racetrack_Map"

    const FSoftObjectPath AssetObjectPath = FSoftObjectPath(AssetPath);
    Success = AssetObjectPath.IsValid();
    if (Success)
    {
        UE_LOG(LogTemp, Log, TEXT("Level '%s' is preloaded."), *AssetPath);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to preload level '%s'."), *AssetPath);
    }
    return AssetPath;
}