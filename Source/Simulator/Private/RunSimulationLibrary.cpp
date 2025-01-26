// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

#include "DetailLayoutBuilder.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

AMyCar* URunSimulationLibrary::SpawnedVehicle = nullptr;
AController* URunSimulationLibrary::PlayerVehicleController = nullptr;
bool URunSimulationLibrary::bSimulationInitialized = false;
bool URunSimulationLibrary::bVRCameraConnected = false;
USceneComponent* URunSimulationLibrary::VRCameraRoot = nullptr;
UCameraComponent* URunSimulationLibrary::VRCamera = nullptr;
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

    SpawnVehicle(World);
    ConnectVrCamera();
    UE_LOG(LogTemp, Warning, TEXT("Vehicle spawned"));
    PossessVehicle(World, SpawnedVehicle);
    InitializeVehicleSettings(SpawnedVehicle);
    UE_LOG(LogTemp, Warning, TEXT("StartSimulation | AMyCar %p: AMyCar->VRCameraRoot %p, AMyCar->VRCamera %p"), SpawnedVehicle, SpawnedVehicle->GetVRCameraRoot(), SpawnedVehicle->GetVRCamera());
    bSimulationInitialized = true;
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

UCameraComponent* URunSimulationLibrary::SpawnVRCamera(UWorld* World)
{
    UE_LOG(LogTemp, Warning, TEXT("SpawnVRCamera"));
    if (!World) return nullptr;
    UCameraComponent* Camera = NewObject<UCameraComponent>(UCameraComponent::StaticClass());
    if (!Camera) return nullptr;
    UE_LOG(LogTemp, Warning, TEXT("SpawnVRCamera | Camera: %p"), Camera);
    Camera->RegisterComponent();
    Camera->SetRelativeTransform(FTransform(FRotator(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f)));
    Camera->SetFieldOfView(90.0f);
    Camera->SetAutoActivate(true);
    return Camera;
}

void URunSimulationLibrary::AssignVRCameraPawn(USceneComponent* CameraRoot)
{
    if (!CameraRoot) return;
    UCameraComponent* Camera = SpawnVRCamera(CameraRoot->GetWorld());
    if (!CameraRoot || !Camera) return;
    VRCameraRoot = CameraRoot;
    VRCamera = Camera;
    UE_LOG(LogTemp, Warning, TEXT("AssignVRCameraPawn | CameraRoot: %p, Camera: %p"), CameraRoot, Camera);
}

void URunSimulationLibrary::ConnectVrCamera()
{
    if (!SpawnedVehicle || !VRCameraRoot || !VRCamera) return;
    SpawnedVehicle->SetupVRReferences(VRCameraRoot, VRCamera);
    bVRCameraConnected = true;
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
    VRCameraRoot = nullptr;
    VRCamera = nullptr;
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