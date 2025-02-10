// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PlatformLibrary.generated.h"

/**
 * 
 */
UENUM()
enum ERotation : uint8
{
	RollX = 0,
	PitchY = 1,
	YawZ = 2
};

UCLASS()
class SIMULATOR_API UPlatformLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static FSocket* Socket;
	static ISocketSubsystem* SocketSubsystem;

	static void SendData(const TArray<uint8>& Data, bool& Success);
	static void ReceiveData(TArray<uint8>& Data, bool& Success);

public:
	UFUNCTION(BlueprintCallable, Category = "Platform")
	static FString ReadIPFromFile();
	
	UFUNCTION(BlueprintCallable, Category = "Platform")
	static bool ConnectToYawVR(const FString& IPAddress, int32 Port);

	UFUNCTION(BlueprintCallable, Category = "Platform")
	static void RotatePlatform(ERotation Rotation, float Value);

	UFUNCTION(BlueprintCallable, Category = "Platform")
	static void StopPlatform();
};
