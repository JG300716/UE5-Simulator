// Fill out your copyright notice in the Description page of Project Settings.


#include "YawTCPClient.h"

#include "Common/TcpSocketBuilder.h"

YawTCPClient::~YawTCPClient() {
	CloseConnection();
}

void YawTCPClient::Initialize(FString ip, int port)
{
	UE_LOG(LogTemp, Log, TEXT("TCP client started connecting"));
	CloseConnection();

    connected = false;


	/*
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString ipL = "10.0.75.1";
	bool bIsValidL = false;

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(*ipL, bIsValidL);
	addr->SetPort(50020);

	bool result = Socket->Connect(*addr);

	ESocketErrors ErrorCode = ISocketSubsystem::Get()->GetLastErrorCode();
	UE_LOG(LogTemp, Log, TEXT("TCP: (%i) result: %i"), int32(ErrorCode), ErrorCode);
	*/


	int32 BufferSize = 2 * 1024 * 1024;
	Socket = FTcpSocketBuilder(TEXT("TCP Socket"))
		.AsReusable()
		.AsNonBlocking()
		.WithSendBufferSize(BufferSize)
		.WithReceiveBufferSize(BufferSize)
		//.BoundToAddress(FIPv4Address::Any)
		//.BoundToEndpoint(FIPv4Endpoint::Any)
		//.Listening(4)
		.Build();

	TSharedPtr<FInternetAddr> remoteEndPoint = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid = false;
	remoteEndPoint->SetIp(*ip, bIsValid);
	remoteEndPoint->SetPort(port);
	bool result = Socket->Connect(*(remoteEndPoint.Get()));

	//UE_LOG(LogTemp, Log, TEXT("TCP: connection to [%s:%i]"), *ip, port);

	//7 = case WSAEWOULDBLOCK: return SE_EWOULDBLOCK;
	//ESocketErrors ErrorCode = ISocketSubsystem::Get()->GetLastErrorCode();
	//UE_LOG(LogTemp, Log, TEXT("TCP: (%i) result: %i"), int32(ErrorCode), ErrorCode);
}

void YawTCPClient::CloseConnection()
{
	connected = false;
	if (Socket != NULL) {
		Socket->Close();
		Socket = NULL;
	}
}

void YawTCPClient::Receive()
{
	if (Socket != NULL && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected) {
		TArray<uint8> data;
		uint32 Size;
		while (Socket->HasPendingData(Size)) {
			data.Init(FMath::Min(Size, 65507u), Size);

			int32 Read = 0;
			Socket->Recv(data.GetData(), data.Num(), Read);
		}

		if (data.Num() > 0) {
			UE_LOG(LogTemp, Log, TEXT("TCP: Data Received: %i Bytes"), data.Num());

			tcpDelegate->DidRecieveTCPMessage(data);
		}
	}
}

void YawTCPClient::Send(const TArray<uint8> &data)
{
	int32 BytesSent;

	Socket->Send(data.GetData(), data.Num(), BytesSent);

	if (data.Num() != BytesSent) {
		//29 = case WSAENOTCONN: return SE_ENOTCONN;
		ESocketErrors ErrorCode = ISocketSubsystem::Get()->GetLastErrorCode();
		UE_LOG(LogTemp, Error, TEXT("TCP: (%i) Failed to send %i bytes of data.  Sent %i bytes."), int32(ErrorCode), data.Num(), BytesSent);
	}
}