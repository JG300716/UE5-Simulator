// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiDimensionObjectArray.h"

template <typename T>
TArray<TArray<T>> UMultiDimensionObjectArray::ConvertToHigherDimension(const int32& size, TArray<T> array)
{
	TArray<TArray<T>> result;
	for(int i = 0; i< array.Max(); i+=size)
	{
		TArray<T> temp;
		for(int j = 0; j < size; j++)
		{
			temp.Add(array[i+j]);
		}
		result.Add(temp);
	}
	return result;
}