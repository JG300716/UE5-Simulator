// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

AMyCar* URunSimulationLibrary::SpawnedVehicle = nullptr;
AController* URunSimulationLibrary::PlayerVehicleController = nullptr;
ACameraActor* URunSimulationLibrary::SimulationCamera = nullptr;
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

    //InitializeVehicleSettings(SpawnedVehicle);
    PossessVehicle(World, SpawnedVehicle);

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

void URunSimulationLibrary::InitializeVehicleSettings(AMyCar* Vehicle)
{
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

    const FString ControllerPath = TEXT("/Game/Simulator/Cars/VehiclePlayerController1.VehiclePlayerController1_C");
    UClass* PlayerControllerClass = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), nullptr, *ControllerPath));

    if (!PlayerControllerClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load player controller class from path: %s"), *ControllerPath);
        return;
    }

    // Create a new player with a specified index
    APlayerController* NewController = Cast<APlayerController>(
        UGameplayStatics::CreatePlayer(World, 0, true) 
    );

    if (!NewController)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create new player controller"));
        return;
    }

    // Verify if the correct controller class is used
    if (!NewController->IsA(PlayerControllerClass))
    {
        UE_LOG(LogTemp, Warning, TEXT("Replacing default controller with custom one"));
        NewController->UnPossess();
        NewController->Destroy();
        
        NewController = World->SpawnActor<APlayerController>(PlayerControllerClass);
        if (!NewController)
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to spawn custom player controller"));
            return;
        }
    }

    NewController->Possess(Vehicle);

    UE_LOG(LogTemp, Warning, TEXT("Successfully possessed vehicle with custom player controller"));
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
    
}

