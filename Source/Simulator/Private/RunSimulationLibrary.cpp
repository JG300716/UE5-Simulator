// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

AMyCar* URunSimulationLibrary::SpawnedVehicle = nullptr;
AController* URunSimulationLibrary::PlayerVehicleController = nullptr;
bool URunSimulationLibrary::bSimulationInitialized = false;

void URunSimulationLibrary::StartSimulation(UWorld* World)
{
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("No valid World in StartSimulation"));
        return;
    }

    SpawnVehicle(World);
    UE_LOG(LogTemp, Warning, TEXT("Vehicle spawned"));

    PossessVehicle(World, SpawnedVehicle);
    InitializeVehicleSettings(SpawnedVehicle);
    
}

void URunSimulationLibrary::SpawnVehicle(UWorld* World)
{
    if (!World) return;
    UClass* VehicleClass = UOptionsLibrary::GetChosenVehicleClass();
    if (!VehicleClass) return;
    AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass());
    if (!PlayerStart) return;
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    SpawnParams.Owner = PlayerStart;
    FTransform SpawnTransform = PlayerStart->GetTransform();
    SpawnedVehicle = World->SpawnActor<AMyCar>(VehicleClass, SpawnTransform, SpawnParams);
}

void URunSimulationLibrary::ConnectVRCameraPawn(USceneComponent* CameraRoot, UCameraComponent* Camera)
{
    if (!SpawnedVehicle) return;
        SpawnedVehicle->SetupVRReferences(CameraRoot, Camera);   
}


void URunSimulationLibrary::InitializeVehicleSettings(AMyCar* Vehicle)
{
    if (!SpawnedVehicle) return;
    SpawnedVehicle->SetUpOptions();
    
	// Set the vehicle's initial settings
	UE_LOG(LogTemp, Warning, TEXT("InitializeVehicleSettings"));
}

void URunSimulationLibrary::PossessVehicle(UWorld* World, AMyCar* Vehicle)
{
    if (!World || !Vehicle)
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid World or Vehicle passed to PossessVehicle"));
        return;
    }

    // Get the existing player controller instead of creating a new one
    APlayerController* ExistingController = UGameplayStatics::GetPlayerController(World, 0);
    
    if (!ExistingController)
    {
        UE_LOG(LogTemp, Error, TEXT("No existing player controller found"));
        return;
    }

    // Unpossess current pawn if any
    ExistingController->UnPossess();

    // Possess the new vehicle
    ExistingController->Possess(Vehicle);

    UE_LOG(LogTemp, Warning, TEXT("Successfully possessed vehicle with existing player controller"));
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
    
}

