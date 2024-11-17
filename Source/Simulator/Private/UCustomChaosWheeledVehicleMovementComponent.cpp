// Fill out your copyright notice in the Description page of Project Settings.

#include "UCustomChaosWheeledVehicleMovementComponent.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "WorldPartition/ContentBundle/ContentBundleBase.h"
#include "WorldPartition/ContentBundle/ContentBundleLog.h"

UCustomChaosWheeledVehicleMovementComponent::UCustomChaosWheeledVehicleMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Ensure the torque curve is initialized
	EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, 400.0f);    // (RPM, Torque) at 0 RPM
	EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1500.0f, 500.0f); // Torque at 1500 RPM
	EngineSetup.TorqueCurve.GetRichCurve()->AddKey(3500.0f, 400.0f); // Torque at 3500 RPM
	EngineSetup.TorqueCurve.GetRichCurve()->AddKey(6000.0f, 200.0f); // Torque at 6000 RPM

	EngineSetup.MaxRPM = 6000.0f;
	EngineSetup.MaxTorque = 600.0f;
	
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCustomChaosWheeledVehicleMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UCustomChaosWheeledVehicleMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateState(DeltaTime);
}

int UCustomChaosWheeledVehicleMovementComponent::SetDriveMode(int Type)
{
	//UE_LOG(LogContentBundle, Warning, TEXT("Drive Mode: %d"), Type);
	switch (Type)
	{
	case 0:
		DifferentialSetup.DifferentialType = EVehicleDifferential::AllWheelDrive;
		DriveMode = 1;
		break;
	case 1:
		DifferentialSetup.DifferentialType = EVehicleDifferential::FrontWheelDrive;
		DriveMode = 2;
		break;
	case 2:
		DifferentialSetup.DifferentialType = EVehicleDifferential::RearWheelDrive;
		DriveMode = 0;
		break;
	default:
		DifferentialSetup.DifferentialType = EVehicleDifferential::AllWheelDrive;
		DriveMode = 1;
	break;
	}
	return DriveMode;
}

bool UCustomChaosWheeledVehicleMovementComponent::ToggleAutoTransmission()
{
	bToggleAutoTransmission = !bToggleAutoTransmission;
	if (bToggleAutoTransmission)
	{
		TransmissionType = Chaos::ETransmissionType::Automatic;
		bReverseAsBrake = true;
	}
	else
	{
		TransmissionType = Chaos::ETransmissionType::Manual;
		bReverseAsBrake = false;
	}
	return bToggleAutoTransmission;
}

