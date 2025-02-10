// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"

#include "DefaultPlayerOptions.h"
#include "OptionsLibrary.h"

#include "Kismet/GameplayStatics.h"

#include "Modifiers/AvaDynamicMeshConverterModifier.h"

#include "PhysicsEngine/PhysicsAsset.h"

#include "SimModule/SimulationModuleBase.h"

// Sets default values

AMyCar::AMyCar(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyCar: %p"), this);
	// Create the movement component and attach it
	UE_LOG(LogTemp, Warning, TEXT("1VehicleMovementComp: %p"), GetVehicleMovement());
	TMPMyChaosWheeledVehicleMovementComponent = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());
	UE_LOG(LogTemp, Warning, TEXT("1MyChaosVehicleMovementComp: %p"), TMPMyChaosWheeledVehicleMovementComponent.Get());
	// if (!bPhysicsInitialized)
	// {
	// 	InitializeVehiclePhysics();
	// }
	
}

void AMyCar::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AMyCar::BeginPlay()"));
	//UE_LOG(LogTemp, Warning, TEXT("2VehicleMovementComp: %p"), this->GetVehicleMovementComponent());
	//UE_LOG(LogTemp, Warning, TEXT("2MyChaosVehicleMovementComp: %p"), TMPMyChaosWheeledVehicleMovementComponent.Get());

	// TArray<FName> WheelBones = { FName(TEXT("FL")), FName(TEXT("FR")), FName(TEXT("RL")), FName(TEXT("RR")) };
	// TArray<UClass*> WheelBlueprintClasses;
	//
	// FString VehicleName = UOptionsLibrary::GetChosenVehicleName();
	// if (VehicleName.IsEmpty())
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Invalid vehicle name."));
	// 	return;
	// }
	//
	// FString PathToPhysicalAsset = FString::Printf(TEXT("/Game/Simulator/Cars/FinalModels/%s/PA_%s_Object"), *VehicleName, *VehicleName);
	// if(!GetMesh()) return;
	// // Attempt to load the Physics Asset from the specified path
	// UPhysicsAsset* PhysicsAsset = Cast<UPhysicsAsset>(StaticLoadObject(UPhysicsAsset::StaticClass(), nullptr, *PathToPhysicalAsset));
	//
	// if (PhysicsAsset)
	// {
	// 	// Set the loaded Physics Asset on the skeletal mesh component
	// 	GetMesh()->SetPhysicsAsset(PhysicsAsset);
	// 	UE_LOG(LogTemp, Warning, TEXT("Successfully set physical asset: %s"), *PathToPhysicalAsset);
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Failed to load physical asset at path: %s"), *PathToPhysicalAsset);
	// }

	// for (const FName& BoneName : WheelBones)
	// {
	// 	// Construct the dynamic path to the Blueprint
	// 	FString WheelBlueprintPath = FString::Printf(TEXT("Blueprint'/Game/Simulator/Cars/FinalModels/%s/%s_%s.%s_%s'"),
	// 	    *VehicleName, *VehicleName, *BoneName.ToString(), *VehicleName, *BoneName.ToString());
	//
	// 	UBlueprint* WheelBlueprint = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, *WheelBlueprintPath));
	//
	// 	if (WheelBlueprint && WheelBlueprint->GeneratedClass)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Loaded Wheel Class: %s"), *WheelBlueprint->GeneratedClass->GetName());
	// 		WheelBlueprintClasses.Add(WheelBlueprint->GeneratedClass);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogTemp, Error, TEXT("Failed to load wheel Blueprint class for path: %s"), *WheelBlueprintPath);
	// 	}
	// }
	
	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh(); // Your vehicle's skeletal mesh component
	SkeletalMeshComponent->WakeAllRigidBodies();
	//
	// if (SkeletalMeshComponent && TMPMyChaosWheeledVehicleMovementComponent)
	// {
	// 	for (int32 WheelIndex = 0; WheelIndex < 4; ++WheelIndex)
	// 	{
	// 		if (WheelIndex >= WheelBlueprintClasses.Num()) break;
	//
	// 		if (WheelBlueprintClasses[WheelIndex])
	// 		{
	// 			FChaosWheelSetup WheelSetup;
	// 			WheelSetup.BoneName = WheelBones[WheelIndex];
	// 			WheelSetup.WheelClass = WheelBlueprintClasses[WheelIndex];
	// 			TMPMyChaosWheeledVehicleMovementComponent->WheelSetups.Add(WheelSetup);
	// 			UE_LOG(LogTemp, Warning, TEXT("Wheel %d set with Bone: %s"), WheelIndex, *WheelSetup.BoneName.ToString());
	// 		}
	// 	}
	// }
	//TMPMyChaosWheeledVehicleMovementComponent->SetUpdatedComponent(GetMesh());
	//TMPMyChaosWheeledVehicleMovementComponent->RecreatePhysicsState();
	//TMPMyChaosWheeledVehicleMovementComponent->EnableMechanicalSim(true);
	
}

// void AMyCar::DelayedPhysicsInit()
// {
// 	UE_LOG(LogTemp, Warning, TEXT("Attempting delayed physics initialization..."));
// 	InitializeVehiclePhysics();
// }

// void AMyCar::InitializeVehiclePhysics()
// {
// 	if (!GetMesh() || !TMPMyChaosWheeledVehicleMovementComponent)
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("InitializeVehiclePhysics: Invalid components!"));
// 		return;
// 	}
// 	
// 	//SetupMeshPhysics();
// 	
// 	// Only proceed with movement setup if physics is valid
// 	if (GetMesh()->GetPhysicsAsset())
// 	{
// 		TMPMyChaosWheeledVehicleMovementComponent->SetUpdatedComponent(GetMesh());
// 		TMPMyChaosWheeledVehicleMovementComponent->Mass = ChassisTargetMass;
// 		TMPMyChaosWheeledVehicleMovementComponent->RecreatePhysicsState();
// 		TMPMyChaosWheeledVehicleMovementComponent->EnableMechanicalSim(true);
// 	
// 		if (ValidatePhysicsSetup())
// 		{
// 			bPhysicsInitialized = true;
// 			PhysicsInitRetryCount = 0;
// 			UE_LOG(LogTemp, Warning, TEXT("Physics initialization successful"));
// 		}
// 		else
// 		{
// 			PhysicsInitRetryCount++;
// 			UE_LOG(LogTemp, Warning, TEXT("Physics initialization attempt %d failed"), PhysicsInitRetryCount);
// 		}
// 	}
// }

// void AMyCar::SetupMeshPhysics()
// {
//     USkeletalMeshComponent* VehicleMesh = GetMesh();
//     if (!VehicleMesh)
//     {
//         UE_LOG(LogTemp, Error, TEXT("SetupMeshPhysics: Invalid Mesh!"));
//         return;
//     }
//
//     // Wait for physics asset to be fully loaded
//     UPhysicsAsset* PhysAsset = VehicleMesh->GetPhysicsAsset();
//     if (!PhysAsset)
//     {
//         UE_LOG(LogTemp, Warning, TEXT("SetupMeshPhysics: Waiting for Physics Asset to load..."));
//         if (UWorld* World = GetWorld())
//         {
//             World->GetTimerManager().SetTimer(
//                 PhysicsInitTimerHandle,
//                 this,
//                 &AMyCar::DelayedPhysicsInit,
//                 0.1f,
//                 false
//             );
//         }
//         return;
//     }
//
//     UE_LOG(LogTemp, Warning, TEXT("Setting up physics for mesh with asset: %s"), *PhysAsset->GetName());
//
//     // Force clean up existing physics state
//     VehicleMesh->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
//     VehicleMesh->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
//
//     // Update physics asset
//     PhysAsset->UpdateBoundsBodiesArray();
//     PhysAsset->UpdateBodySetupIndexMap();
//
//     // Set up body instances
//     TArray<FName> BoneNames;
//     VehicleMesh->GetBoneNames(BoneNames);
//
//     for (const FName& BoneName : BoneNames)
//     {
//         FBodyInstance* BodyInstance = VehicleMesh->GetBodyInstance(BoneName);
//         if (BodyInstance)
//         {
//             BodyInstance->SetEnableGravity(true);
//             BodyInstance->SetMassScale(1.0f);
// 		UE_LOG(LogTemp, Warning, TEXT("Is Instance Awake?  %s"), BodyInstance->IsInstanceAwake() ? TEXT("true") : TEXT("false"));
//         	UE_LOG(LogTemp, Warning, TEXT("Is Simulating Physics?  %s"), BodyInstance->bSimulatePhysics ? TEXT("true") : TEXT("false"));
//
//         	// Only set mass override for the root bone
//             if (BoneName == FName("root") || BoneName == FName("Root"))
//             {
//                 BodyInstance->SetMassOverride(ChassisTargetMass);
//             }
//             
//             BodyInstance->UpdateMassProperties();
//         }
//         else
//         {
//         	UE_LOG(LogTemp, Warning, TEXT("Body Instance is null of Bone Name:  %s"), *BoneName.ToString());
//         }
//     }
//
//     // Set mesh physics properties
//     VehicleMesh->SetSimulatePhysics(true);
//     VehicleMesh->SetEnableGravity(true);
//     VehicleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
//     VehicleMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
//     VehicleMesh->bEnablePhysicsOnDedicatedServer = true;
//
//     // Log current state
//     UE_LOG(LogTemp, Warning, TEXT("Mesh Physics Setup:"));
//     UE_LOG(LogTemp, Warning, TEXT("  - Physics Asset: %s"), *PhysAsset->GetName());
//     UE_LOG(LogTemp, Warning, TEXT("  - Bone Count: %d"), BoneNames.Num());
//     UE_LOG(LogTemp, Warning, TEXT("  - Target Mass: %f"), ChassisTargetMass);
//     
//     // Force physics state recreation
//     VehicleMesh->RecreatePhysicsState();
//     VehicleMesh->WakeAllRigidBodies();
// }

// bool AMyCar::ValidatePhysicsSetup() const
// {
// 	USkeletalMeshComponent* VehicleMesh = GetMesh();
// 	if (!VehicleMesh || !TMPMyChaosWheeledVehicleMovementComponent)
// 	{
// 		return false;
// 	}
//
// 	float TotalMass = 0.0f;
// 	TArray<FName> BoneNames;
// 	VehicleMesh->GetBoneNames(BoneNames);
//     
// 	for (const FName& BoneName : BoneNames)
// 	{
// 		const FBodyInstance* BodyInstance = VehicleMesh->GetBodyInstance(BoneName);
// 		if (BodyInstance)
// 		{
// 			TotalMass += BodyInstance->GetBodyMass();
// 		}
// 	}
//
// 	const bool bPhysicsEnabled = VehicleMesh->IsSimulatingPhysics();
// 	const bool bGravityEnabled = VehicleMesh->IsGravityEnabled();
//
// 	UE_LOG(LogTemp, Warning, TEXT("Physics Validation:"));
// 	UE_LOG(LogTemp, Warning, TEXT("  - Total Mass: %f"), TotalMass);
// 	UE_LOG(LogTemp, Warning, TEXT("  - Physics Enabled: %s"), bPhysicsEnabled ? TEXT("True") : TEXT("False"));
// 	UE_LOG(LogTemp, Warning, TEXT("  - Gravity Enabled: %s"), bGravityEnabled ? TEXT("True") : TEXT("False"));
//
// 	return TotalMass > 0.0f && bPhysicsEnabled && bGravityEnabled;
// }

// void AMyCar::ForcePhysicsInit()
// {
//     bPhysicsInitialized = false;
//     PhysicsInitRetryCount = 0;
//     InitializeVehiclePhysics();
// }

// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// // Attempt to reinitialize physics if it's not working
	// if (!bPhysicsInitialized && PhysicsInitRetryCount < MaxPhysicsInitRetries)
	// {
	// 	InitializeVehiclePhysics();
	// }
	// else if (bPhysicsInitialized && !GetMesh()->IsSimulatingPhysics())
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Physics disabled unexpectedly, attempting to re-enable"));
	// 	SetupMeshPhysics();
	// }
}

void AMyCar::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//InitializeVehiclePhysics();
	// if(TMPMyChaosWheeledVehicleMovementComponent)
	// {
	// 	if(!IsValid(GetMesh())) return;
	// 	if(!IsValid(GetMesh()->GetPhysicsAsset())) return;
	// 	UE_LOG(LogTemp, Warning, TEXT("Physics Asset: %s"), *GetMesh()->GetPhysicsAsset()->GetName());
	// 	UE_LOG(LogTemp, Warning, TEXT("Chassis Mass: %f"), TMPMyChaosWheeledVehicleMovementComponent->Mass);
	// 	UE_LOG(LogTemp, Warning, TEXT("1Mesh Mass: %f"), GetMesh()->CalculateMass(FName("Root")));
	// 	UE_LOG(LogTemp, Warning, TEXT("2Mesh Mass: %f"), GetMesh()->GetMass());
	// 	UE_LOG(LogTemp, Warning, TEXT("Init Tick"));
	// 	UE_LOG(LogTemp, Warning, TEXT("Is Gravity Enabled: %s"), GetMesh()->IsGravityEnabled() ? TEXT("true") : TEXT("false"));
	// 	UE_LOG(LogTemp, Warning, TEXT("Is Simulating Physics: %s"), GetMesh()->IsSimulatingPhysics(FName("Root")) ? TEXT("true") : TEXT("false"));
	// 	UE_LOG(LogTemp, Warning, TEXT("Animation class: %s"), *GetMesh()->AnimClass->GetName());
	// }
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
}

void AMyCar::SetUpOptions()
{
	UE_LOG(LogTemp, Warning, TEXT("SetUpOptions()"));
	 auto DOptions = UDefaultPlayerOptions::GetOptionMap();
	if(DOptions.IsEmpty()) return;
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
	ChassisTargetMass = VehicleMasses.Chassis;
	
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

	if (IsValid(TMPMyChaosWheeledVehicleMovementComponent))
	{
		if (EngineSetup.TorqueCurve.GetRichCurve())
		{
			float MaxTorque = EngineSetup.MaxTorque;
			if (MaxTorque > 0)
			{
				EngineSetup.TorqueCurve.GetRichCurve()->Reset();
				EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, MaxTorque * 0.8f);
				EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1500.0f, MaxTorque);
				EngineSetup.TorqueCurve.GetRichCurve()->AddKey(3500.0f, MaxTorque * 0.8f);
				EngineSetup.TorqueCurve.GetRichCurve()->AddKey(6000.0f, MaxTorque * 0.4f);
				// Explicitly apply settings
				UE_LOG(LogTemp, Warning, TEXT("SetUpOptions() | Engine Setup:"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Invalid Max Torque value."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TorqueCurve is not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Vehicle Movement Component."));
	}
	
	
	if (TMPMyChaosWheeledVehicleMovementComponent->EngineSetup.TorqueCurve.GetRichCurve()->GetNumKeys() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Torque Curve defined with %d keys."),
			 TMPMyChaosWheeledVehicleMovementComponent->EngineSetup.TorqueCurve.GetRichCurve()->GetNumKeys());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Torque Curve has no keys defined."));
	}

	
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

