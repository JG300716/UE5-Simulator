// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

#include "DetailLayoutBuilder.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

AMyCar* URunSimulationLibrary::SpawnedVehicle = nullptr;
AController* URunSimulationLibrary::PlayerVehicleController = nullptr;
bool URunSimulationLibrary::bSimulationInitialized = false;
bool URunSimulationLibrary::bVRCameraConnected = false;
bool URunSimulationLibrary::IsVREnabled = false;
bool URunSimulationLibrary::IsMenuOpen = false;
bool URunSimulationLibrary::IsOptionOpen = false;

void URunSimulationLibrary::StartSimulation(UWorld* World)
{
    ResetSimulationValues();
    
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("No valid World in StartSimulation"));
        return;
    }

    //SpawnVehicle(World);
    GetSpawnedVehicle(World);
    UE_LOG(LogTemp, Warning, TEXT("Vehicle spawned"));
    PossessVehicle(World, SpawnedVehicle);
    //InitializeVehicleSettings(SpawnedVehicle);
    UE_LOG(LogTemp, Warning, TEXT("StartSimulation | AMyCar %p"), SpawnedVehicle);
    bSimulationInitialized = true;
}

void URunSimulationLibrary::SpawnVehicle(UWorld* World)
{
    if (!World) return;

    // Load the Blueprint class
    UClass* VehicleClass = World->GetAuthGameMode()->DefaultPawnClass;
    if (!VehicleClass)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load vehicle BP class!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Vehicle Class: %s"), *VehicleClass->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Vehicle Path: %s"), *VehicleClass->GetPathName());
    // Find Player Start
    AActor* PlayerStart = UGameplayStatics::GetActorOfClass(World, APlayerStart::StaticClass());
    if (!PlayerStart)
    {
        UE_LOG(LogTemp, Error, TEXT("No PlayerStart found."));
        return;
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    // Use AActor instead of specific class
    FTransform SpawnTransform = PlayerStart->GetTransform();
    AActor* SpawnedActor = World->SpawnActor<AActor>(VehicleClass, SpawnTransform, SpawnParams);
    if (!SpawnedActor) return;
    SpawnedVehicle = Cast<AMyCar>(SpawnedActor);
}

void URunSimulationLibrary::GetSpawnedVehicle(UWorld* World)
{
    if (!World) return;
    SpawnedVehicle = Cast<AMyCar>(UGameplayStatics::GetPlayerPawn(World, 0));
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

    //ExistingController->AutoManageActiveCameraTarget(Vehicle);
   

    UE_LOG(LogTemp, Warning, TEXT("Successfully possessed vehicle with existing player controller"));
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
    if (!bSimulationInitialized || !bVRCameraConnected) return;
}

void URunSimulationLibrary::ResetSimulationValues()
{
    SpawnedVehicle = nullptr;
    PlayerVehicleController = nullptr;
    bSimulationInitialized = false;
    bVRCameraConnected = false;
}

void URunSimulationLibrary::SetVREnabled(bool bEnabled)
{
    IsVREnabled = bEnabled;
}

bool URunSimulationLibrary::GetVREnabled()
{
    return IsVREnabled;
}

void URunSimulationLibrary::SetMenuOpen(bool bOpen)
{
    IsMenuOpen = bOpen;
}

bool URunSimulationLibrary::GetMenuOpen()
{
    return IsMenuOpen;
}

void URunSimulationLibrary::SetOptionOpen(bool bOpen)
{
    IsOptionOpen = bOpen;
}

bool URunSimulationLibrary::GetOptionOpen()
{
    return IsOptionOpen;
}

void URunSimulationLibrary::PrintMovementPointer(UChaosWheeledVehicleMovementComponent* Component)
{
    if (!Component) return;
    UE_LOG(LogTemp, Warning, TEXT("Movement Pointer: %p"), Component);
    if (!SpawnedVehicle) return;
    UE_LOG(LogTemp, Warning, TEXT("My Vehicle Movement Pointer: %p"), SpawnedVehicle->GetMyCarVehicleMovementComponent());
}

