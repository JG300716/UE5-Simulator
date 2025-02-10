// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"

#include "Common/UdpSocketReceiver.h"

/**
 * 
 */
class YawUDPClientDelegate
{
public:
	virtual void DidRecieveUDPMessage(FString message, const FIPv4Endpoint& remoteEndPoint) = 0;
};

class SIMULATOR_API YawUDPClient
{
public:
	int listeningPort;

	FSocket* Socket = NULL;
	FUdpSocketReceiver* udpClient = NULL;

	TSharedPtr<FInternetAddr> remoteEndPointRE;
	YawUDPClientDelegate* udpDelegate = NULL;

	YawUDPClient(int listeningPort);

	virtual ~YawUDPClient();

	void SetRemoteEndPoint(FString ipAddress, int port);

	void StartListening();
	void StopListening();

	void Receive(const FArrayReaderPtr& Data, const FIPv4Endpoint& FromAddress);

	void SendBroadcast(int port, const TArray<uint8> &data);


	void Send(const TArray<uint8> &data);
};
