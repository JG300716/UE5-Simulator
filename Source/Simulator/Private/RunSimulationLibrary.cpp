// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

APawn* URunSimulationLibrary::SpawnedVehicle = nullptr;
ACameraActor* URunSimulationLibrary::SimulationCamera = nullptr;

void URunSimulationLibrary::StartSimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("StartSimulation"));
	SpawnVehicle();
	UE_LOG(LogTemp, Warning, TEXT("Vehicle spawned"));
	if (!SpawnedVehicle)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn vehicle"));
		return;
	}
	InitializeVehicleSettings(SpawnedVehicle);
	PossessVehicle(SpawnedVehicle);
	
}

void URunSimulationLibrary::SpawnVehicle()
{
	// Get the vehicle class from OptionsLibrary
	UClass* VehicleClass = UOptionsLibrary::GetChosenVehicleClass();
	if (!VehicleClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get vehicle class from OptionsLibrary"));
		return;
	}

	// Get the world context
	UWorld* World = GEngine->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid World Context"));
		return;
	}

	// Find player start location
	AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass());
	if (!PlayerStart)
	{
		UE_LOG(LogTemp, Error, TEXT("No PlayerStart found in level"));
		return;
	}

	// Set spawn parameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    
	// Get transform from player start
	FTransform SpawnTransform = PlayerStart->GetTransform();

	// Spawn the vehicle
	SpawnedVehicle = World->SpawnActor<APawn>(VehicleClass, SpawnTransform, SpawnParams);
    
	if (!SpawnedVehicle)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to spawn vehicle"));
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Successfully spawned vehicle at player start"));
}

void URunSimulationLibrary::InitializeVehicleSettings(APawn* Vehicle)
{
	// Set the vehicle's initial settings
	UE_LOG(LogTemp, Warning, TEXT("InitializeVehicleSettings"));
}

void URunSimulationLibrary::PossessVehicle(APawn* Vehicle)
{
	
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
	
}

