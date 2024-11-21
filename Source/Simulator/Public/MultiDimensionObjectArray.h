// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultiDimensionObjectArray.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 */

UCLASS()
class SIMULATOR_API UMultiDimensionObjectArray : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	
	template <typename T>
	UFUNCTION(BlueprintCallable, Category = "FileSystem")
	static TArray<TArray<T>> ConvertToHigherDimension(const int32& size, TArray<T> array);
	
};
