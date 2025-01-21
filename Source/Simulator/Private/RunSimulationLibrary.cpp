// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

AMyCar* URunSimulationLibrary::SpawnedVehicle = nullptr;
ACameraActor* URunSimulationLibrary::SimulationCamera = nullptr;
bool URunSimulationLibrary::bSimulationInitialized = false;

void URunSimulationLibrary::StartSimulation(UWorld* World)
{
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

    UE_LOG(LogTemp, Warning, TEXT("Vehicle spawned"));

    //InitializeVehicleSettings(SpawnedVehicle);
    //PossessVehicle(SpawnedVehicle);

}

void URunSimulationLibrary::SpawnVehicle(UWorld* World)
{
    // Get the vehicle class from OptionsLibrary
    UClass* VehicleClass = UOptionsLibrary::GetChosenVehicleClass();
    if (!VehicleClass) return;

    if (!World) return;
    
    // Get world context through game mode
    AGameModeBase* GameMode = Cast<AGameModeBase>(World->GetAuthGameMode());
    if (!GameMode) return;

    // Log the vehicle class name for debugging
    UE_LOG(LogTemp, Warning, TEXT("Attempting to spawn vehicle class: %s"), *VehicleClass->GetName());

    // Find player start location
    AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass());
    if (!PlayerStart) return;

    // Log player start location
    UE_LOG(LogTemp, Warning, TEXT("Found PlayerStart at location: %s"), *PlayerStart->GetActorLocation().ToString());

    // Set spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    SpawnParams.Owner = GameMode;
    
    // Get transform from player start
    FTransform SpawnTransform = PlayerStart->GetTransform();

    // Spawn the vehicle
    SpawnedVehicle = World->SpawnActor<AMyCar>(VehicleClass, SpawnTransform, SpawnParams);
    
    if (!SpawnedVehicle) return;

    SpawnedVehicle->SetUpMyCarVehicleMovementComponent(SpawnedVehicle->GetMyCarVehicleMovementComponent());
    
    UE_LOG(LogTemp, Log, TEXT("Successfully spawned vehicle at player start"));
}

void URunSimulationLibrary::InitializeVehicleSettings(AMyCar* Vehicle)
{
	// Set the vehicle's initial settings
	UE_LOG(LogTemp, Warning, TEXT("InitializeVehicleSettings"));
}

void URunSimulationLibrary::PossessVehicle(AMyCar* Vehicle)
{
	if (!Vehicle) return;

    const FString PlayerControllerPath = TEXT("/Game/Simulator/Cars/VehiclePlayerController1.VehiclePlayerController1_C");
	
    // Load the PlayerController Blueprint class dynamically
    UClass* NewPlayerControllerClass = StaticLoadClass(APlayerController::StaticClass(), nullptr, *PlayerControllerPath);
    
    if (!NewPlayerControllerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load PlayerController class from path: %s"), *PlayerControllerPath);
        return;
    }
    
    // Get the player controller
    APlayerController* PlayerController = NewPlayerControllerClass->GetDefaultObject<APlayerController>();
    if (!PlayerController) return;
    PlayerController->Possess(Vehicle);
    UE_LOG(LogTemp, Log, TEXT("Possessed vehicle"));
    
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
    
}

