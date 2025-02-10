// Fill out your copyright notice in the Description page of Project Settings.


#include "YawUDPClient.h"

#include "Common/UdpSocketBuilder.h"

YawUDPClient::YawUDPClient(int listeningPort) {
	this->listeningPort = listeningPort;

	int32 BufferSize = 2 * 1024 * 1024;
	Socket = FUdpSocketBuilder(TEXT("UDP Socket"))
		.AsReusable()
		.AsNonBlocking()
		.WithBroadcast()
		.WithSendBufferSize(BufferSize)
		.WithReceiveBufferSize(BufferSize)
		.BoundToAddress(FIPv4Address::Any)
		.BoundToEndpoint(FIPv4Endpoint::Any)
		.BoundToPort(listeningPort)
		.Build();

	udpClient = new FUdpSocketReceiver(Socket, FTimespan(0, 0, 0, 0, 200), TEXT("UDP Socket"));
}

YawUDPClient::~YawUDPClient() {
	//TODO: This causes a Access violation
	//investigate wether not explicitly cleaning the socket leads to a memory leak
	//EDIT: first tests show memory footprint to be at most a few KB and atleast the socket does get released
	//StopListening();
}

void YawUDPClient::SetRemoteEndPoint(FString ipAddress, int port) {
	remoteEndPointRE = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	remoteEndPointRE->SetIp(*ipAddress, bIsValid); // Destination IP
	remoteEndPointRE->SetPort(port); // Destination port
}

void YawUDPClient::StartListening()
{
	udpClient->OnDataReceived().BindRaw(this, &YawUDPClient::Receive);
	udpClient->Start();
}
void YawUDPClient::StopListening()
{
	if (udpClient != NULL) {
		udpClient->Exit();
		udpClient->Stop();
		udpClient = NULL;
	}
	if (Socket != NULL) {
		Socket->Close();
		Socket = NULL;
	}
}

void YawUDPClient::Receive(const FArrayReaderPtr& Data, const FIPv4Endpoint& FromAddress)
{
	//UE_LOG(LogTemp, Log, TEXT("UDP: Data Received: %i Bytes"), Data->Num());

	FString message = FString(UTF8_TO_TCHAR(Data->GetData()));
	//UE_LOG(LogTemp, Log, TEXT("%s"), *message);

	udpDelegate->DidRecieveUDPMessage(message, FromAddress);
}

void YawUDPClient::SendBroadcast(int port, const TArray<uint8> &data)
{
	UE_LOG(LogTemp, Error, TEXT("MA: Send Broadcast"));

	TSharedPtr<FInternetAddr> remoteEndPointRE2 = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	remoteEndPointRE2->SetIp(TEXT("255.255.255.255"), bIsValid);
	//remoteEndPointRE2->SetIp(TEXT("192.168.1.54"), bIsValid);
	//remoteEndPointRE2->SetIp(TEXT("169.254.240.142"), bIsValid);
	//remoteEndPointRE2->SetIp(TEXT("192.168.1.1"), bIsValid);
	remoteEndPointRE2->SetBroadcastAddress();
	remoteEndPointRE2->SetPort(port);

	/*
	FString Message;
	data = (uint8*)TCHAR_TO_UTF8(Message.GetCharArray().GetData());
	*/

	int32 BytesSent;

	Socket->SendTo(data.GetData(), data.Num(), BytesSent, *remoteEndPointRE2);

	if (data.Num() != BytesSent) {
		ESocketErrors ErrorCode = ISocketSubsystem::Get()->GetLastErrorCode();
		UE_LOG(LogTemp, Error, TEXT("MA: (%i) Failed to send %i bytes of data.  Sent %i bytes."), int32(ErrorCode), data.Num(), BytesSent);
	}
}


void YawUDPClient::Send(const TArray<uint8> &data)
{
	/*
	FString Message;
	data = (uint8*)TCHAR_TO_UTF8(Message.GetCharArray().GetData());
	*/

	int32 BytesSent;

	Socket->SendTo(data.GetData(), data.Num(), BytesSent, *remoteEndPointRE);

	if (data.Num() != BytesSent) {
		ESocketErrors ErrorCode = ISocketSubsystem::Get()->GetLastErrorCode();
		UE_LOG(LogTemp, Error, TEXT("UDP: (%i) Failed to send %i bytes of data.  Sent %i bytes."), int32(ErrorCode), data.Num(), BytesSent);
	}
}