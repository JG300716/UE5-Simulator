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
    const FString ControllerPath = TEXT("/Game/Simulator/Cars/VehiclePlayerController1.VehiclePlayerController1_C");
    UClass* PlayerControllerClass = StaticLoadClass(APlayerController::StaticClass(), nullptr, *ControllerPath);
    APlayerController* PlayerController = World->SpawnActor<APlayerController>(PlayerControllerClass);
    if (!PlayerController) return;
    PlayerController->Possess(Vehicle);
    //UGameplayStatics::GetPlayerController(World, 0)->SetViewTarget(Vehicle);
    
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
    
}

