// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <SocketSubsystem.h>
#include "Interfaces/IPv4/IPv4Address.h"
#include <IPAddress.h>
#include "InputProcessor.h"

/**
 * 
 */
class SIMULATOR_API YawDevice
{
public:
	FIPv4Address* ipAddress;

	int tcpPort;

	int udpPort;
	FString id;
	FString name;

	DeviceStatus status;

	FVector ActualPosition = FVector();

	YawDevice(FIPv4Address* ipAddress, int tcpPort, int udpPort, FString id, FString name, DeviceStatus status);

	void SetStatus(DeviceStatus statusDS);
};
