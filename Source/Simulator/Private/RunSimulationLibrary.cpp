// Fill out your copyright notice in the Description page of Project Settings.


#include "RunSimulationLibrary.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "NavigationSystemTypes.h"

#include "Blueprint/WidgetBlueprintLibrary.h"

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

    bSimulationInitialized = true;
}

void URunSimulationLibrary::SimulationTick(float DeltaTime)
{
    if (!bSimulationInitialized || !bVRCameraConnected) return;
}

void URunSimulationLibrary::ResetSimulationValues()
{
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
}

void URunSimulationLibrary::GearUpVehicle(UChaosWheeledVehicleMovementComponent* Component)
{
    if (!Component) return;
	if (Component->TransmissionSetup.bUseAutomaticGears) return;
    int Gear = Component->GetCurrentGear();
    Component->SetTargetGear(Gear + 1, true);
}

void URunSimulationLibrary::GearDownVehicle(UChaosWheeledVehicleMovementComponent* Component)
{
    if (!Component) return;
	if (Component->TransmissionSetup.bUseAutomaticGears) return;
    int Gear = Component->GetCurrentGear();
    Component->SetTargetGear(Gear - 1, true);
}

void URunSimulationLibrary::InitPhysics(UChaosWheeledVehicleMovementComponent* Component)
{
    if (!Component) return;
	SetUpOptions(Component);
	if (Component->HasValidPhysicsState()) return;
	Component->CreatePhysicsVehicle();
	Component->PhysicsVehicleOutput();
	CreateWheels(Component);
}

void URunSimulationLibrary::PrintVehicleComponentParams(UChaosWheeledVehicleMovementComponent* Component)
{
	if (!Component->HasValidPhysicsState())
	{
		UE_LOG(LogTemp, Warning, TEXT("Vehicle Statistics:"));
		UE_LOG(LogTemp, Warning, TEXT("HasValidPhysicsState: %d"), Component->HasValidPhysicsState());
		UE_LOG(LogTemp, Warning, TEXT("CanCreateVehicle: %d"), Component->CanCreateVehicle());
		UE_LOG(LogTemp, Warning, TEXT("HasValidPhysicsState: %d"), Component->HasValidPhysicsState());
	}
	for (int i = 0; i < Component->WheelSetups.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wheel[%d]: Class: %s, Bone: %s"),
		    i,
		    *GetNameSafe(Component->WheelSetups[i].WheelClass),
		    *Component->WheelSetups[i].BoneName.ToString()
		);
	}

	UE_LOG(LogTemp, Warning, TEXT("Wheels: %d"), Component->GetNumWheels());
}


void URunSimulationLibrary::SetUpOptions(UChaosWheeledVehicleMovementComponent* Component)
{
	UE_LOG(LogTemp, Warning, TEXT("SetUpOptions()"));
	 auto DOptions = UDefaultPlayerOptions::GetOptionMap();
	if(DOptions.IsEmpty()) return;
	if (!Component)
	{
		UE_LOG(LogTemp, Warning, TEXT("ChaosWheeledVehicleMovementComponent is null"));
		return;
	}
	
	// Handle Drive Mode
	auto DriveMode = static_cast<EDriveMode>(Cast<UOptionDriveMode>(DOptions["Drive Mode"])->ReadDriveModeValue());
	Component->DifferentialSetup.DifferentialType = DriveMode == EDriveMode::AllWheels ? EVehicleDifferential::AllWheelDrive : DriveMode == EDriveMode::FrontWheels ? EVehicleDifferential::FrontWheelDrive : EVehicleDifferential::RearWheelDrive;
	
	Component->bSuspensionEnabled = Cast<UOptionBool>(DOptions["Suspension Enabled"])->ReadBoolValue();
	Component->bWheelFrictionEnabled = Cast<UOptionBool>(DOptions["Wheel Friction Enabled"])->ReadBoolValue();

	// Vehicle Masses data
	auto VehicleMasses = Cast<UOptionVehicle>(DOptions["Vehicle Masses"])->ReadVehicleValue();
	Component->Mass = VehicleMasses.Chassis;	
	float WheelMasses[4] = {
	VehicleMasses.Wheels.FrontLeftWheel,
	VehicleMasses.Wheels.FrontRightWheel,
	VehicleMasses.Wheels.RearLeftWheel,
	VehicleMasses.Wheels.RearRightWheel
	};
	
	// Engine Setup
	auto& EngineSetup = Component->EngineSetup;
	EngineSetup.MaxRPM = Cast<UOptionFloat>(DOptions["Max RPM"])->ReadFloatValue();
	EngineSetup.MaxTorque = Cast<UOptionFloat>(DOptions["Max Torque"])->ReadFloatValue();
	
	// Vehicle Setup
	Component->DragCoefficient = Cast<UOptionFloat>(DOptions["Drag Coefficient"])->ReadFloatValue();
	Component->DownforceCoefficient = Cast<UOptionFloat>(DOptions["Down Force Coefficient"])->ReadFloatValue();
	
	// Transmission Setup
	auto& TransmissionSetup = Component->TransmissionSetup;
	
	TransmissionSetup.bUseAutomaticGears = !Cast<UOptionBool>(DOptions["Manual Gearbox"])->ReadBoolValue();
	TransmissionSetup.bUseAutoReverse = Cast<UOptionBool>(DOptions["Automatic Reverse"])->ReadBoolValue();
	Component->bReverseAsBrake = TransmissionSetup.bUseAutoReverse;
	
	TransmissionSetup.ChangeUpRPM = Cast<UOptionFloat>(DOptions["Automatic Gearbox Up Shift RPM"])->ReadFloatValue();
	TransmissionSetup.ChangeDownRPM = Cast<UOptionFloat>(DOptions["Automatic Gearbox Down Shift RPM"])->ReadFloatValue();
	TransmissionSetup.GearChangeTime = Cast<UOptionFloat>(DOptions["Gearbox Change Time"])->ReadFloatValue();
	TransmissionSetup.TransmissionEfficiency = Cast<UOptionFloat>(DOptions["Gearbox Transmission Efficiency"])->ReadFloatValue();

	UE_LOG(LogTemp, Warning, TEXT("SetUpOptions() Vehicle Mass: %f Diff Type: %d Drag Coeff: %f Downforce Coeff: %f Max RPM: %f Max Torque: %f Auto Gears: %d Auto Reverse: %d Change Up RPM: %f Change Down RPM: %f Gear Change Time: %f Transmission Efficiency: %f"),
		VehicleMasses.Chassis,
		Component->DifferentialSetup.DifferentialType,
		Component->DragCoefficient,
		Component->DownforceCoefficient,
		EngineSetup.MaxRPM,
		EngineSetup.MaxTorque,
		TransmissionSetup.bUseAutomaticGears,
		TransmissionSetup.bUseAutoReverse,
		TransmissionSetup.ChangeUpRPM,
		TransmissionSetup.ChangeDownRPM,
		TransmissionSetup.GearChangeTime,
		TransmissionSetup.TransmissionEfficiency
		);
	
	// Set up gear ratios if they're not already configured
	if (TransmissionSetup.ForwardGearRatios.Num() == 0)
	{
		TransmissionSetup.ForwardGearRatios.Add(2.66f); // 1st
		TransmissionSetup.ForwardGearRatios.Add(1.78f); // 2nd
		TransmissionSetup.ForwardGearRatios.Add(1.30f); // 3rd
		TransmissionSetup.ForwardGearRatios.Add(1.00f); // 4th
	}
	// Set up reverse gear if not configured
	if (TransmissionSetup.ReverseGearRatios.Num() == 0)
	{
		TransmissionSetup.ReverseGearRatios.Add(-2.90f);
	}
	UE_LOG(LogTemp, Warning, TEXT("SetUpOptions() | Transmission Setup:"));
	UE_LOG(LogTemp, Warning, TEXT("  - Automatic Gears: %d"), TransmissionSetup.bUseAutomaticGears);
	UE_LOG(LogTemp, Warning, TEXT("  - Forward Gears: %d"), TransmissionSetup.ForwardGearRatios.Num());
	UE_LOG(LogTemp, Warning, TEXT("  - Current Gear: %d"), Component->GetCurrentGear());
	
	// Set initial gear to neutral
	Component->SetTargetGear(0, true);
	
	// Prepare arrays for wheel data
	float SuspensionData[6] = {
		Cast<UOptionFloat>(DOptions["Suspension Spring Ratio"])->ReadFloatValue(),
		Cast<UOptionFloat>(DOptions["Suspension Dump Ratio"])->ReadFloatValue(),
		Cast<UOptionFloat>(DOptions["Suspension Preload"])->ReadFloatValue(),
		Cast<UOptionFloat>(DOptions["Suspension Max Raise"])->ReadFloatValue(),
		Cast<UOptionFloat>(DOptions["Suspension Max Drop"])->ReadFloatValue(),
		Cast<UOptionFloat>(DOptions["Suspension Smoothness"])->ReadFloatValue()
	};
	
	auto WheelsFriction = Cast<UOptionWheels>(DOptions["Wheels Friction Force Multiplier"])->ReadVehicleWheelsValue();
	float FrictionData[4] = {
		WheelsFriction.FrontLeftWheel,
		WheelsFriction.FrontRightWheel,
		WheelsFriction.RearLeftWheel,
		WheelsFriction.RearRightWheel
	};
	
	auto WheelsBrakeTorque = Cast<UOptionWheels>(DOptions["Wheels Brake Torque"])->ReadVehicleWheelsValue();
	float BrakeTorqueData[4] = {
		WheelsBrakeTorque.FrontLeftWheel,
		WheelsBrakeTorque.FrontRightWheel,
		WheelsBrakeTorque.RearLeftWheel,
		WheelsBrakeTorque.RearRightWheel
	};
	
	auto WheelsHandBrakeTorque = Cast<UOptionWheels>(DOptions["Wheels Hand Brake Torque"])->ReadVehicleWheelsValue();
	float HandBrakeTorqueData[4] = {
		WheelsHandBrakeTorque.FrontLeftWheel,
		WheelsHandBrakeTorque.FrontRightWheel,
		WheelsHandBrakeTorque.RearLeftWheel,
		WheelsHandBrakeTorque.RearRightWheel
	};
	
	// Advanced wheel settings
	auto WheelsAffectedByBrakes = Cast<UOptionWheels>(DOptions["Wheels Affected By Brakes"])->ReadVehicleWheelsValue();
	auto WheelsAffectedByHandBrakes = Cast<UOptionWheels>(DOptions["Wheels Affected By Hand Brakes"])->ReadVehicleWheelsValue();
	auto WheelsAffectedByEngine = Cast<UOptionWheels>(DOptions["Wheels Affected By Engine"])->ReadVehicleWheelsValue();
	auto WheelsAffectedBySteering = Cast<UOptionWheels>(DOptions["Wheels Affected By Steering"])->ReadVehicleWheelsValue();
	
	float WheelsBoolData[5][4] = {
	{WheelsAffectedByBrakes.FrontLeftWheel, WheelsAffectedByBrakes.FrontRightWheel, WheelsAffectedByBrakes.RearLeftWheel, WheelsAffectedByBrakes.RearRightWheel},
	{WheelsAffectedByHandBrakes.FrontLeftWheel, WheelsAffectedByHandBrakes.FrontRightWheel, WheelsAffectedByHandBrakes.RearLeftWheel, WheelsAffectedByHandBrakes.RearRightWheel},
	{WheelsAffectedByEngine.FrontLeftWheel, WheelsAffectedByEngine.FrontRightWheel, WheelsAffectedByEngine.RearLeftWheel, WheelsAffectedByEngine.RearRightWheel},
	{WheelsAffectedBySteering.FrontLeftWheel, WheelsAffectedBySteering.FrontRightWheel, WheelsAffectedBySteering.RearLeftWheel, WheelsAffectedBySteering.RearRightWheel},
	};
	
	bool WheelsTractionControlEnabled = Cast<UOptionBool>(DOptions["Traction Control Enabled"])->ReadBoolValue();
	bool WheelsAbsEnabled = Cast<UOptionBool>(DOptions["ABS Enabled"])->ReadBoolValue();
	float WheelsMaxSteeringAngle = Cast<UOptionFloat>(DOptions["Max Wheels Steering Angle"])->ReadFloatValue();
	
	// Apply all wheel settings in a single loop
	auto& Wheels = Component->Wheels;
	int32 WheelIndex = 0;
	for (auto& Wheel : Wheels)
	{
		if (!Wheel) continue;
		// Set wheel mass
		Wheel->WheelMass = WheelMasses[WheelIndex];
	
		// Set suspension parameters
		Wheel->SpringRate = SuspensionData[0];
		Wheel->SuspensionDampingRatio = SuspensionData[1];
		Wheel->SpringPreload = SuspensionData[2];
		Wheel->SuspensionMaxRaise = SuspensionData[3];
		Wheel->SuspensionMaxDrop = SuspensionData[4];
		Wheel->SuspensionSmoothing = SuspensionData[5];
		
		// Set friction, brake, and handbrake
		Wheel->FrictionForceMultiplier = FrictionData[WheelIndex];
		Wheel->MaxBrakeTorque = BrakeTorqueData[WheelIndex];
		Wheel->MaxHandBrakeTorque = HandBrakeTorqueData[WheelIndex];
	
		// Set boolean parameters
		Wheel->bAffectedByBrake = WheelsBoolData[0][WheelIndex] > 0.5f;
		Wheel->bAffectedByHandbrake = WheelsBoolData[1][WheelIndex] > 0.5f;
		Wheel->bAffectedByEngine = WheelsBoolData[2][WheelIndex] > 0.5f;
		Wheel->bAffectedBySteering = WheelsBoolData[3][WheelIndex] > 0.5f;
		Wheel->MaxSteerAngle = WheelsMaxSteeringAngle;
		Wheel->bABSEnabled = WheelsAbsEnabled;
		Wheel->bTractionControlEnabled = WheelsTractionControlEnabled;
		WheelIndex++;
	
		UE_LOG(LogTemp, Warning, TEXT("Wheel[%d]: Mass: %f, Spring Rate: %f, Damping Ratio: %f, Preload: %f, Max Raise: %f, Max Drop: %f, Smoothing: %d, Friction: %f, Brake Torque: %f, Handbrake Torque: %f, Affected By Brake: %d, Affected By Handbrake: %d, Affected By Engine: %d, Affected By Steering: %d, Max Steering Angle: %f, ABS Enabled: %d, Traction Control Enabled: %d"),
		    WheelIndex - 1,
		    Wheel->WheelMass,
		    Wheel->SpringRate,
		    Wheel->SuspensionDampingRatio,
		    Wheel->SpringPreload,
		    Wheel->SuspensionMaxRaise,
		    Wheel->SuspensionMaxDrop,
		    Wheel->SuspensionSmoothing,
		    Wheel->FrictionForceMultiplier,
		    Wheel->MaxBrakeTorque,
		    Wheel->MaxHandBrakeTorque,
		    Wheel->bAffectedByBrake,
		    Wheel->bAffectedByHandbrake,
		    Wheel->bAffectedByEngine,
		    Wheel->bAffectedBySteering,
		    Wheel->MaxSteerAngle,
		    Wheel->bABSEnabled,
		    Wheel->bTractionControlEnabled
		);
		
	}
	UE_LOG(LogTemp, Warning, TEXT("Wheels: %d"), Wheels.Num());
	Component->TransmissionSetup = TransmissionSetup;
	Component->EngineSetup = EngineSetup;
}

void URunSimulationLibrary::CreateWheels(UChaosWheeledVehicleMovementComponent* Component)
{
	if (!Component) return;
	if (Component->Wheels.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wheels already created."));
		return;
	}
	FString VehicleName = UOptionsLibrary::GetChosenVehicleName();
	FString WheelsBones[4] = {
		"FL",
		"FR",
		"RL",
		"RR"
	};
	FString WheelsBasePath = "/Game/Simulator/Cars/FinalModels/";
	if (VehicleName.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Vehicle name is empty."));
		return;
	}
	for(int i = 0; i < 4; i++)
	{
		FString WheelName = VehicleName + "_" + WheelsBones[i];
		FString WheelPath = WheelsBasePath + VehicleName + "/" + WheelName + "." + WheelName + "_C";
		UE_LOG(LogTemp, Warning, TEXT("Wheel Path: %s"), *WheelPath);
		UClass* WheelClass = StaticLoadClass(UChaosVehicleWheel::StaticClass(), nullptr, *WheelPath);
		if (!WheelClass)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load wheel class at path: %s"), *WheelPath);
			continue;
		}
		UChaosVehicleWheel* Wheel = NewObject<UChaosVehicleWheel>(Component, WheelClass);
		if (!Wheel) continue;
		Component->Wheels.Add(Wheel);
	}
	Component->RecreatePhysicsState();

}
