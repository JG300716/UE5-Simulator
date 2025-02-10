// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"

/**
 * 
 */

class YawTCPClientDelegate
{
public:
	virtual void DidRecieveTCPMessage(TArray<uint8> data) = 0;
	virtual void DidLostServerConnection() = 0;
};

class SIMULATOR_API YawTCPClient
{
public:
	YawTCPClient() {}

	virtual ~YawTCPClient();

	FSocket* Socket = NULL;

	YawTCPClientDelegate* tcpDelegate = NULL;
	bool connected = false;

	void Initialize(FString ip, int port);

	void CloseConnection();

	void Receive();

	void Send(const TArray<uint8> &data);
};
