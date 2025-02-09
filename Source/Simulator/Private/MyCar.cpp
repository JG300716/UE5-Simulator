// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"

#include "AssetTypeCategories.h"
#include "DefaultPlayerOptions.h"
#include "OptionsLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Modifiers/AvaDynamicMeshConverterModifier.h"

#include "SimModule/SimulationModuleBase.h"

// Sets default values

AMyCar::AMyCar(const FObjectInitializer& ObjectInitializer)
{
	// Create the movement component and attach it
	UE_LOG(LogTemp, Warning, TEXT("1VehicleMovementComp: %p"), this->GetVehicleMovementComponent());
	TMPMyChaosWheeledVehicleMovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(this->GetVehicleMovementComponent());
	UE_LOG(LogTemp, Warning, TEXT("1MyChaosVehicleMovementComp: %p"), TMPMyChaosWheeledVehicleMovementComponent.Get());


	// USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	// if (!SkeletalMeshComponent) return;
	// SkeletalMeshComponent->SetSimulatePhysics(true);
	// SkeletalMeshComponent->SetEnableGravity(true);
	// SkeletalMeshComponent->WakeAllRigidBodies();
	
}

void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	//SetUpOptions();
	UE_LOG(LogTemp, Warning, TEXT("AMyCar::BeginPlay()"));
	UE_LOG(LogTemp, Warning, TEXT("2VehicleMovementComp: %p"), this->GetVehicleMovementComponent());
	UE_LOG(LogTemp, Warning, TEXT("2MyChaosVehicleMovementComp: %p"), TMPMyChaosWheeledVehicleMovementComponent.Get());

	   if (!TMPMyChaosWheeledVehicleMovementComponent) return;
	
	TArray<FName> WheelBones = { FName(TEXT("FL")), FName(TEXT("FR")), FName(TEXT("RL")), FName(TEXT("RR")) };
	TArray<UClass*> WheelBlueprintClasses;

	FString VehicleName = UOptionsLibrary::GetChosenVehicleName();
	if (VehicleName.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid vehicle name."));
		return;
	}
	
	for (const FName& BoneName : WheelBones)
	{
		// Construct the dynamic path to the Blueprint
		FString WheelBlueprintPath = FString::Printf(TEXT("Blueprint'/Game/Simulator/Cars/FinalModels/%s/%s_%s.%s_%s'"),
		    *VehicleName, *VehicleName, *BoneName.ToString(), *VehicleName, *BoneName.ToString());

		UBlueprint* WheelBlueprint = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *WheelBlueprintPath));

		if (WheelBlueprint && WheelBlueprint->GeneratedClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded Wheel Class: %s"), *WheelBlueprint->GeneratedClass->GetName());
			WheelBlueprintClasses.Add(WheelBlueprint->GeneratedClass);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load wheel Blueprint class for path: %s"), *WheelBlueprintPath);
		}
	}
	
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh(); // Your vehicle's skeletal mesh component
	
	if (SkeletalMeshComponent && TMPMyChaosWheeledVehicleMovementComponent)
	{
		for (int32 WheelIndex = 0; WheelIndex < 4; ++WheelIndex)
		{
			if (WheelIndex >= WheelBlueprintClasses.Num()) break;
			if (WheelBlueprintClasses[WheelIndex])
			{
				UChaosVehicleWheel* NewWheel = NewObject<UChaosVehicleWheel>(this, WheelBlueprintClasses[WheelIndex]);
				TMPMyChaosWheeledVehicleMovementComponent->Wheels.Add(NewWheel);
				FChaosWheelSetup WheelSetup;
				WheelSetup.BoneName = WheelBones[WheelIndex];
				WheelSetup.WheelClass = UChaosVehicleWheel::StaticClass(); 
				WheelSetup.AdditionalOffset = SkeletalMeshComponent->GetSocketLocation(WheelBones[WheelIndex]); 
				TMPMyChaosWheeledVehicleMovementComponent->WheelSetups[WheelIndex] = WheelSetup;
				UE_LOG(LogTemp, Warning, TEXT("Wheel %d: %s at Location: %s"), WheelIndex, *NewWheel->GetName(), *WheelSetup.AdditionalOffset.ToString());
			}
		}
	}
	
}

 //    if (!ChaosWheeledVehicleMovementComponent) return;
 //
 //    	TArray<FName> WheelBones = { FName(TEXT("FL")), FName(TEXT("FR")), FName(TEXT("RL")), FName(TEXT("RR")) };
 //
	// // Array to store the Blueprint classes for each wheel
	// TArray<UClass*> WheelBlueprintClasses = {
	// 	LoadObject<UClass>(nullptr, TEXT("Blueprint'/Game/Simulator/Cars/Front_Left_Wheel_BP.Front_Left_Wheel_BP_C'")),
	// 	LoadObject<UClass>(nullptr, TEXT("Blueprint'/Game/Simulator/Cars/Front_Right_Wheel_BP.Front_Right_Wheel_BP_C'")),
	// 	LoadObject<UClass>(nullptr, TEXT("Blueprint'/Game/Simulator/Cars/Rear_Left_Wheel_BP.Rear_Left_Wheel_BP_C'")),
	// 	LoadObject<UClass>(nullptr, TEXT("Blueprint'/Game/Simulator/Cars/Rear_Right_Wheel_BP.Rear_Right_Wheel_BP_C'"))
	//   };
 //
	// USkeletalMeshComponent* SkeletalMeshComponent = GetMesh(); // Your vehicle's skeletal mesh component
 //
	// if (SkeletalMeshComponent && ChaosWheeledVehicleMovementComponent)
	// {
	// 	for (int32 WheelIndex = 0; WheelIndex < 4; ++WheelIndex)
	// 	{
	// 		if (WheelBlueprintClasses[WheelIndex])
	// 		{
	// 			UChaosVehicleWheel* NewWheel = NewObject<UChaosVehicleWheel>(this, WheelBlueprintClasses[WheelIndex]);
	// 			ChaosWheeledVehicleMovementComponent->Wheels.Add(NewWheel);
	// 			FChaosWheelSetup WheelSetup;
	// 			WheelSetup.BoneName = WheelBones[WheelIndex];
	// 			WheelSetup.WheelClass = UChaosVehicleWheel::StaticClass(); 
	// 			WheelSetup.AdditionalOffset = SkeletalMeshComponent->GetSocketLocation(WheelBones[WheelIndex]); 
	// 			ChaosWheeledVehicleMovementComponent->WheelSetups[WheelIndex] = WheelSetup;
	// 			UE_LOG(LogTemp, Warning, TEXT("Wheel %d: %s at Location: %s"), WheelIndex, *NewWheel->GetName(), *WheelSetup.AdditionalOffset.ToString());
	// 		}
	// 	}
	// }
 //
	// // Basic Setup
	// ChaosWheeledVehicleMovementComponent->SetUpdatedComponent(GetMesh());
	// ChaosWheeledVehicleMovementComponent->Activate(true);
 //    
	// // Physics setup
	// ChaosWheeledVehicleMovementComponent->RecreatePhysicsState();
 //
	// if (USkeletalMeshComponent* VehicleMesh = GetMesh())
	// {
	// 	VehicleMesh->SetSimulatePhysics(true);
	// 	VehicleMesh->SetEnableGravity(true);
	// 	VehicleMesh->WakeAllRigidBodies();
	// 	VehicleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// }



// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto& Wheels = TMPMyChaosWheeledVehicleMovementComponent->Wheels;
	UE_LOG(LogTemp, Warning, TEXT("Wheels: %d"), Wheels.Num());
	for(auto &Wheel : Wheels)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wheel name: %s"), *Wheel->GetName());
	}
	//ChaosWheeledVehicleMovementComponent->TickComponent(DeltaTime, ELevelTick::LEVELTICK_All, nullptr);
	//int speed = ChaosWheeledVehicleMovementComponent->GetForwardSpeed();
}

// Called to bind functionality to input
void AMyCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UChaosWheeledVehicleMovementComponent* AMyCar::GetMyCarVehicleMovementComponent() const
{
	return TMPMyChaosWheeledVehicleMovementComponent;
}

void AMyCar::SetUpMyCarVehicleMovementComponent(UChaosWheeledVehicleMovementComponent* Component)
{
	TMPMyChaosWheeledVehicleMovementComponent = Component;
}

void AMyCar::GearUp()
{
	UE_LOG(LogTemp, Warning, TEXT("ChaosWheeledVehicleMovementComponent %p"), TMPMyChaosWheeledVehicleMovementComponent.Get());

	if (!TMPMyChaosWheeledVehicleMovementComponent) return;

	auto& TransmissionSetup = TMPMyChaosWheeledVehicleMovementComponent->TransmissionSetup;
	int32 CurrentGear = TMPMyChaosWheeledVehicleMovementComponent->GetCurrentGear();
	int32 MaxGear = TransmissionSetup.ForwardGearRatios.Num();
	// Normal gear up logic for non-neutral gears
	if (CurrentGear < MaxGear)
	{
		int32 NewGear = CurrentGear + 1;
		TMPMyChaosWheeledVehicleMovementComponent->SetTargetGear(NewGear, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("GearUp() | Current Gear: %d"), TMPMyChaosWheeledVehicleMovementComponent->GetCurrentGear());
}

void AMyCar::GearDown()
{
	if (!TMPMyChaosWheeledVehicleMovementComponent) return;
	int32 CurrentGear = TMPMyChaosWheeledVehicleMovementComponent->GetCurrentGear();
	if (CurrentGear > -1)  // -1 is reverse
	{
		int32 NewGear = CurrentGear - 1;
		TMPMyChaosWheeledVehicleMovementComponent->SetTargetGear(NewGear, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("GearDown() | Current Gear: %d"), TMPMyChaosWheeledVehicleMovementComponent->GetCurrentGear());
}

void AMyCar::SetUpOptions()
{
	auto DOptions = UDefaultPlayerOptions::GetOptionMap();
	
	if (!TMPMyChaosWheeledVehicleMovementComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("ChaosWheeledVehicleMovementComponent is null"));
		return;
	}

	// Handle Drive Mode
	auto DriveMode = static_cast<EDriveMode>(Cast<UOptionDriveMode>(DOptions["Drive Mode"])->ReadDriveModeValue());
	TMPMyChaosWheeledVehicleMovementComponent->DifferentialSetup.DifferentialType = DriveMode == EDriveMode::AllWheels ? EVehicleDifferential::AllWheelDrive : DriveMode == EDriveMode::FrontWheels ? EVehicleDifferential::FrontWheelDrive : EVehicleDifferential::RearWheelDrive;

	TMPMyChaosWheeledVehicleMovementComponent->bSuspensionEnabled = Cast<UOptionBool>(DOptions["Suspension Enabled"])->ReadBoolValue();
	TMPMyChaosWheeledVehicleMovementComponent->bWheelFrictionEnabled = Cast<UOptionBool>(DOptions["Wheel Friction Enabled"])->ReadBoolValue();

	// Vehicle Masses data
	auto VehicleMasses = Cast<UOptionVehicle>(DOptions["Vehicle Masses"])->ReadVehicleValue();
	TMPMyChaosWheeledVehicleMovementComponent->Mass = VehicleMasses.Chassis;

	float WheelMasses[4] = {
	VehicleMasses.Wheels.FrontLeftWheel,
	VehicleMasses.Wheels.FrontRightWheel,
	VehicleMasses.Wheels.RearLeftWheel,
	VehicleMasses.Wheels.RearRightWheel
	};

	// Engine Setup
	auto& EngineSetup = TMPMyChaosWheeledVehicleMovementComponent->EngineSetup;
	EngineSetup.MaxRPM = Cast<UOptionFloat>(DOptions["Max RPM"])->ReadFloatValue();
	EngineSetup.MaxTorque = Cast<UOptionFloat>(DOptions["Max Torque"])->ReadFloatValue();

	// if (IsValid(MyChaosWheeledVehicleMovementComponent))
	// {
	// 	if (EngineSetup.TorqueCurve.GetRichCurve())
	// 	{
	// 		float MaxTorque = EngineSetup.MaxTorque;
	// 		if (MaxTorque > 0)
	// 		{
	// 			EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	// 			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, MaxTorque * 0.8f);
	// 			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1500.0f, MaxTorque);
	// 			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(3500.0f, MaxTorque * 0.8f);
	// 			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(6000.0f, MaxTorque * 0.4f);
	// 			// Explicitly apply settings
	// 			UE_LOG(LogTemp, Warning, TEXT("SetUpOptions() | Engine Setup:"));
	// 		}
	// 		else
	// 		{
	// 			UE_LOG(LogTemp, Error, TEXT("Invalid Max Torque value."));
	// 		}
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Error, TEXT("TorqueCurve is not valid."));
	// 	}
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Invalid Vehicle Movement Component."));
	// }
	//
	//
	// if (MyChaosWheeledVehicleMovementComponent->EngineSetup.TorqueCurve.GetRichCurve()->GetNumKeys() > 0)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Torque Curve defined with %d keys."),
	// 		 MyChaosWheeledVehicleMovementComponent->EngineSetup.TorqueCurve.GetRichCurve()->GetNumKeys());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Torque Curve has no keys defined."));
	// }

	
	// Vehicle Setup
	TMPMyChaosWheeledVehicleMovementComponent->DragCoefficient = Cast<UOptionFloat>(DOptions["Drag Coefficient"])->ReadFloatValue();
	TMPMyChaosWheeledVehicleMovementComponent->DownforceCoefficient = Cast<UOptionFloat>(DOptions["Down Force Coefficient"])->ReadFloatValue();

	// Transmission Setup
	auto& TransmissionSetup = TMPMyChaosWheeledVehicleMovementComponent->TransmissionSetup;

	TransmissionSetup.bUseAutomaticGears = !Cast<UOptionBool>(DOptions["Manual Gearbox"])->ReadBoolValue();
	TransmissionSetup.bUseAutoReverse = Cast<UOptionBool>(DOptions["Automatic Reverse"])->ReadBoolValue();

	TransmissionSetup.ChangeUpRPM = Cast<UOptionFloat>(DOptions["Automatic Gearbox Up Shift RPM"])->ReadFloatValue();
	TransmissionSetup.ChangeDownRPM = Cast<UOptionFloat>(DOptions["Automatic Gearbox Down Shift RPM"])->ReadFloatValue();
	TransmissionSetup.GearChangeTime = Cast<UOptionFloat>(DOptions["Gearbox Change Time"])->ReadFloatValue();
	TransmissionSetup.TransmissionEfficiency = Cast<UOptionFloat>(DOptions["Gearbox Transmission Efficiency"])->ReadFloatValue();

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
	UE_LOG(LogTemp, Warning, TEXT("  - Current Gear: %d"), TMPMyChaosWheeledVehicleMovementComponent->GetCurrentGear());

	// Set initial gear to neutral
	TMPMyChaosWheeledVehicleMovementComponent->SetTargetGear(0, true);

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
	auto& Wheels = TMPMyChaosWheeledVehicleMovementComponent->Wheels;
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
	}
	UE_LOG(LogTemp, Warning, TEXT("Wheels: %d"), Wheels.Num());
	TMPMyChaosWheeledVehicleMovementComponent->TransmissionSetup = TransmissionSetup;
	TMPMyChaosWheeledVehicleMovementComponent->EngineSetup = EngineSetup;
	TMPMyChaosWheeledVehicleMovementComponent->RecreatePhysicsState();
}

