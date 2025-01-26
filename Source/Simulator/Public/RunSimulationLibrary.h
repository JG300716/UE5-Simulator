#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerStart.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "OptionsLibrary.h"
#include "RunSimulationLibrary.generated.h"

UCLASS()
class SIMULATOR_API URunSimulationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Simulation|GUI")
	static void SetVREnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Simulation|GUI")
	static bool GetVREnabled();

	UFUNCTION(BlueprintCallable, Category = "Simulation|GUI")
	static void SetMenuOpen(bool bOpen);

	UFUNCTION(BlueprintCallable, Category = "Simulation|GUI")
	static bool GetMenuOpen();

	UFUNCTION(BlueprintCallable, Category = "Simulation|GUI")
	static void SetOptionOpen(bool bOpen);

	UFUNCTION(BlueprintCallable, Category = "Simulation|GUI")
	static bool GetOptionOpen();
	
	// Main function to start the simulation
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void StartSimulation(UWorld* World);

	// Function to spawn the vehicle at player start
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void SpawnVehicle(UWorld* World);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void AssignVRCameraPawn(USceneComponent* CameraRoot, UCameraComponent* Camera);
	
	// Function to initialize vehicle settings
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void InitializeVehicleSettings(AMyCar* Vehicle);

	// Function to possess the spawned vehicle
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void PossessVehicle(UWorld* World, AMyCar* Vehicle);

	// Tick function for simulation updates
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void SimulationTick(float DeltaTime);

private:
	static bool IsVREnabled;
	static bool IsMenuOpen;
	static bool IsOptionOpen;
	// Static properties to store references
	static AMyCar* SpawnedVehicle;
	static AController* PlayerVehicleController;
	static USceneComponent* VRCameraRoot;
	static UCameraComponent* VRCamera;
	static bool bSimulationInitialized;
	static bool bVRCameraConnected;

	static void ResetSimulationValues();
	static void ConnectVrCamera();
	
};
