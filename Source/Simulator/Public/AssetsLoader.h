// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetsLoader.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 */
UCLASS()
class SIMULATOR_API UAssetsLoader : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FileSystem")	static TArray<FString> GetFoldersInDirectory(const FString& DirectoryPath);
};
