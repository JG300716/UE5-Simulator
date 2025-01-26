// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"

#include "AssetTypeCategories.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCar::AMyCar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomChaosWheeledVehicleMovementComponent>(VehicleMovementComponentName))
{
	// Initialize the custom movement component
	CustomChaosWheeledVehicleMovementComponent = Cast<UCustomChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	UE_LOG(LogTemp, Warning, TEXT("AMyCar() | AMyCar is %p."), this);
	UE_LOG(LogTemp, Warning, TEXT("AMyCar() | CustomChaosWheeledVehicleMovementComponent is %p."), CustomChaosWheeledVehicleMovementComponent.Get());
	GetMesh()->SetCenterOfMass(FVector(0.0f, 0.0f, -50.0f)); // Adjust Z value to lower the center of mass
	if (CustomChaosWheeledVehicleMovementComponent != nullptr)
	{
		// Access and set up the Engine Setup
		FVehicleEngineConfig& EngineSetup = CustomChaosWheeledVehicleMovementComponent->EngineSetup;

		if (EngineSetup.TorqueCurve.GetRichCurve() != nullptr)
		{
			EngineSetup.TorqueCurve.GetRichCurve()->Reset();
			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f, 400.0f);
			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1500.0f, 500.0f);
			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(3500.0f, 400.0f);
			EngineSetup.TorqueCurve.GetRichCurve()->AddKey(6000.0f, 200.0f);

			EngineSetup.MaxRPM = 6000.0f;
			EngineSetup.MaxTorque = 600.0f;

			UE_LOG(LogTemp, Log, TEXT("Torque curve setup successfully in constructor."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TorqueCurve RichCurve is null in constructor."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CustomChaosWheeledVehicleMovementComponent is null in constructor."));
	}
}
void AMyCar::BeginPlay()
{
	Super::BeginPlay();

	if (CustomChaosWheeledVehicleMovementComponent != nullptr)
	{
		// Log torque curve setup
		UE_LOG(LogTemp, Log, TEXT("Torque curve setup during BeginPlay."));

		// Access the Engine Setup
		FVehicleEngineConfig& EngineSetup = CustomChaosWheeledVehicleMovementComponent->EngineSetup;

		if (EngineSetup.TorqueCurve.GetRichCurve() != nullptr && !EngineSetup.TorqueCurve.GetRichCurve()->IsEmpty())
		{
			UE_LOG(LogTemp, Log, TEXT("Torque curve is correctly set up."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Torque curve is empty during BeginPlay."));
		}
	}
	StartingLocation = GetActorLocation();

	// Comprehensive camera component investigation
	UE_LOG(LogTemp, Warning, TEXT("Car BeginPlay Camera Investigation"));
}

// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//int speed = CustomChaosWheeledVehicleMovementComponent->GetForwardSpeed();
	//UE_LOG(LogTemp, Warning, TEXT("Speed: %d"), speed);

	// Log every 60 frames (approximately every second)
	static int TickCounter = 0;
	TickCounter++;

	if (TickCounter % 60 == 0 && VRCameraRoot && VRCamera)
	{
		// Camera Relative Transform Debug
		FVector CameraLocation = VRCamera->GetComponentLocation();
		FRotator CameraRotation = VRCamera->GetComponentRotation();
        
		// VR Camera Root Relative Transform Debug
		FVector RootLocation = VRCameraRoot->GetComponentLocation();
		FRotator RootRotation = VRCameraRoot->GetComponentRotation();

		// Vehicle Relative Transform Debug
		FVector VehicleLocation = GetActorLocation();
		FRotator VehicleRotation = GetActorRotation();

		UE_LOG(LogTemp, Warning, TEXT("Camera Debug Relative - Location: %s, Rotation: %s"), 
		    *CameraLocation.ToString(), *CameraRotation.ToString());
        
		UE_LOG(LogTemp, Warning, TEXT("Camera Root Debug Relative - Location: %s, Rotation: %s"), 
		    *RootLocation.ToString(), *RootRotation.ToString());

		UE_LOG(LogTemp, Warning, TEXT("Vehicle Debug Relative - Location: %s, Rotation: %s"),
			*VehicleLocation.ToString(), *VehicleRotation.ToString());

		// Optional: Check if camera is actually enabled
		bool bIsCameraEnabled = VRCamera->IsActive();
		UE_LOG(LogTemp, Warning, TEXT("Camera Enabled: %s"), 
		    bIsCameraEnabled ? TEXT("TRUE") : TEXT("FALSE"));
	}
	
}

// Called to bind functionality to input
void AMyCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCustomChaosWheeledVehicleMovementComponent* AMyCar::GetMyCarVehicleMovementComponent() const
{
	return CustomChaosWheeledVehicleMovementComponent;
}

void AMyCar::SetUpMyCarVehicleMovementComponent(UCustomChaosWheeledVehicleMovementComponent* Component)
{
	CustomChaosWheeledVehicleMovementComponent = Component;
}

void AMyCar::SetupVRReferences(USceneComponent* CameraRoot, UCameraComponent* Camera)
{
	if (!CameraRoot || !Camera) return;

	this->VRCameraRoot = CameraRoot;
	this->VRCamera = Camera;

	UE_LOG(LogTemp, Warning, TEXT("SetupVRReferences | CameraRoot: %p, Camera: %p"), CameraRoot, Camera);
	
	// Set relative location to zero explicitly
	VRCamera->AttachToComponent(VRCameraRoot, FAttachmentTransformRules::KeepRelativeTransform);
	VRCamera->Activate();
}

void AMyCar::ResetCameraTransform()
{
	if (VRCameraRoot && VRCamera)
	{
		FTransform VehicleTrans = GetActorTransform();
		VRCameraRoot->SetWorldTransform(VehicleTrans);
		VRCamera->SetWorldRotation(VehicleTrans.GetRotation());
	}
}

void AMyCar::SetUpOptions()
{
	bIsAutomaticTransmission = false;
}

