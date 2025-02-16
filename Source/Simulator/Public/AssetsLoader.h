// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/LevelStreamingDynamic.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetsLoader.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 * https://github.com/JG300716
 */
UCLASS()
class SIMULATOR_API UAssetsLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FileSystem")
	static TArray<FString> GetFoldersInDirectory(const FString& DirectoryPath);
	
	UFUNCTION(BlueprintCallable, Category = "FileSystem")
	static void LoadVehicleAsset(const FString& AssetPath, bool &Success);

	UFUNCTION(BlueprintCallable, Category = "FileSystem")
	static void LoadMapAsset(const FString& AssetPath, bool &Success);
};
