// Fill out your copyright notice in the Description page of Project Settings.

#include "UCustomChaosWheeledVehicleMovementComponent.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "WorldPartition/ContentBundle/ContentBundleBase.h"
#include "WorldPartition/ContentBundle/ContentBundleLog.h"

UCustomChaosWheeledVehicleMovementComponent::UCustomChaosWheeledVehicleMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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


