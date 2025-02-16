#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"

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
	
	// Tick function for simulation updates
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void SimulationTick(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void PrintMovementPointer(UChaosWheeledVehicleMovementComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void GearUpVehicle(UChaosWheeledVehicleMovementComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void GearDownVehicle(UChaosWheeledVehicleMovementComponent* Component);
	
	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void InitPhysics(UChaosWheeledVehicleMovementComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "Simulation")
	static void PrintVehicleComponentParams(UChaosWheeledVehicleMovementComponent* Component);
	
private:
	static bool IsVREnabled;
	static bool IsMenuOpen;
	static bool IsOptionOpen;
	// Static properties to store references
	static bool bSimulationInitialized;
	static bool bVRCameraConnected;

	static void ResetSimulationValues();

	static void SetUpOptions(UChaosWheeledVehicleMovementComponent* Component);
	static void CreateWheels(UChaosWheeledVehicleMovementComponent* Component);
};
