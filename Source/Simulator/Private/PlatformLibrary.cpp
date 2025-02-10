// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformLibrary.h"

FSocket* UPlatformLibrary::Socket;
ISocketSubsystem* UPlatformLibrary::SocketSubsystem;

FString UPlatformLibrary::ReadIPFromFile()
{
	FString FilePath = FPaths::ProjectContentDir() + TEXT("Simulator/IP.txt");
	FString FileContent;

	if (FFileHelper::LoadFileToString(FileContent, *FilePath))
	{
		UE_LOG(LogTemp, Log, TEXT("IP Address: %s"), *FileContent);
		return FileContent.TrimStartAndEnd();  // Remove any extra spaces or newlines
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to read the IP file at path: %s"), *FilePath);
		return TEXT("");
	}
}



bool UPlatformLibrary::ConnectToYawVR(const FString& IPAddress, int32 Port)
{
	// Get the socket subsystem
	SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    
	// Create the internet address as a shared pointer
	TSharedRef<FInternetAddr> Address = SocketSubsystem->CreateInternetAddr();

	bool bIsValid;
	Address->SetIp(*IPAddress, bIsValid);
	Address->SetPort(Port);

	if (!bIsValid)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid IP Address: %s"), *IPAddress);
		return false;
	}

	// Create the socket
	Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("YawVR Socket"), false);

	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create socket."));
		return false;
	}

	// Connect to the address
	bool bConnected = Socket->Connect(*Address);
	if (bConnected)
	{
		Socket->SetNonBlocking(true);
		UE_LOG(LogTemp, Log, TEXT("Connected to YawVR at %s:%d"), *IPAddress, Port);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to YawVR at %s:%d"), *IPAddress, Port);
		Socket->Close();
	}
	return bConnected;
}


void UPlatformLibrary::RotatePlatform(ERotation Rotation, float Value)
{
	FString RotationAxis;
	switch (Rotation)
	{
		case ERotation::RollX:
			RotationAxis = "roll";
			break;
		case ERotation::PitchY:
			RotationAxis = "pitch";
			break;
		case ERotation::YawZ:
			RotationAxis = "yaw";
			break;
		default:
			return;
	}
	FString Command = "{\"command\": \"rotate\", \"axis\": \"" + RotationAxis + "\", \"value\": " + FString::SanitizeFloat(Value) + "}";
	UE_LOG(LogTemp, Log, TEXT("Sending command: %s"), *Command);
	TArray<uint8> Data;
	Data.Append((uint8*)TCHAR_TO_ANSI(*Command), Command.Len());
	bool bSuccess;
	SendData(Data, bSuccess);
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to send command: %s"), *Command);
	}
}


void UPlatformLibrary::SendData(const TArray<uint8>& Data, bool& Success)
{
	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("No valid socket to send data"));
		Success = false;
		return;
	}
	if (Data.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No data to send"));
		Success = false;
		return;
	}
	if (Socket->GetConnectionState() != ESocketConnectionState::SCS_Connected)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket is not connected"));
		Success = false;
		return;
	}

	int32 BytesSent;
	Socket->Send(Data.GetData(), Data.Num(), BytesSent);
}


void UPlatformLibrary::ReceiveData(TArray<uint8>& Data, bool& Success)
{
	
}

void UPlatformLibrary::StopPlatform()
{
	
}
