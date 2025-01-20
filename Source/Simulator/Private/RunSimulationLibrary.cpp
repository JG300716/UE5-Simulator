// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

APawn* URunSimulationLibrary::SpawnedVehicle = nullptr;
ACameraActor* URunSimulationLibrary::SimulationCamera = nullptr;
bool URunSimulationLibrary::bSimulationInitialized = false;

void URunSimulationLibrary::StartSimulation()
{
    UE_LOG(LogTemp, Warning, TEXT("StartSimulation"));

    bSimulationInitialized = false;
}

void URunSimulationLibrary::StartSimulationInternal()
{
    // This will be called after a short delay
    UE_LOG(LogTemp, Warning, TEXT("StartSimulation Internal"));

    UWorld* World = GEngine->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("No valid World in StartSimulation"));
        return;
    }

    AGameModeBase* GameMode = World->GetAuthGameMode();
    if (!GameMode)
    {
        UE_LOG(LogTemp, Error, TEXT("No valid GameMode"));
        return;
    }

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

    // Get world context through game mode
    AGameModeBase* GameMode = Cast<AGameModeBase>(GEngine->GetWorld()->GetAuthGameMode());
    if (!GameMode)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid GameMode"));
        return;
    }
    
    UWorld* World = GameMode->GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid World Context"));
        return;
    }

    // Log the vehicle class name for debugging
    UE_LOG(LogTemp, Warning, TEXT("Attempting to spawn vehicle class: %s"), *VehicleClass->GetName());

    // Find player start location
    AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass());
    if (!PlayerStart)
    {
        UE_LOG(LogTemp, Error, TEXT("No PlayerStart found in level"));
        return;
    }

    // Log player start location
    UE_LOG(LogTemp, Warning, TEXT("Found PlayerStart at location: %s"), *PlayerStart->GetActorLocation().ToString());

    // Set spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    SpawnParams.Owner = GameMode;
    
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
    if (!bSimulationInitialized)
    {
        UWorld* World = GEngine->GetWorld();
        if (!World)
        {
            UE_LOG(LogTemp, Error, TEXT("No valid World in StartSimulation"));
            return;
        }
        StartSimulationInternal();
    }
    
}

