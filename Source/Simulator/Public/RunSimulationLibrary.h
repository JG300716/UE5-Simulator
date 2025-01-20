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

	static void StartSimulationInternal();

public:
	// Main function to start the simulation
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void StartSimulation(UWorld* World);

	// Function to spawn the vehicle at player start
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void SpawnVehicle();

	// Function to initialize vehicle settings
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void InitializeVehicleSettings(APawn* Vehicle);

	// Function to possess the spawned vehicle
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void PossessVehicle(APawn* Vehicle);

	// Tick function for simulation updates
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void SimulationTick(float DeltaTime);

private:
	// Static properties to store references
	static APawn* SpawnedVehicle;
	static ACameraActor* SimulationCamera;
	static bool bSimulationInitialized;
};
