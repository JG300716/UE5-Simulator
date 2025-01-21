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
	// Main function to start the simulation
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void StartSimulation(UWorld* World);

	// Function to spawn the vehicle at player start
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void SpawnVehicle(UWorld* World);

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
	// Static properties to store references
	static AMyCar* SpawnedVehicle;
	static ACameraActor* SimulationCamera;
	static bool bSimulationInitialized;
};
