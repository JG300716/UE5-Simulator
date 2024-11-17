// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCar.h"

#include "AssetTypeCategories.h"

// Sets default values
AMyCar::AMyCar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomChaosWheeledVehicleMovementComponent>(VehicleMovementComponentName))
{
	// Initialize the custom movement component
	CustomChaosWheeledVehicleMovementComponent = Cast<UCustomChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	UE_LOG(LogTemp, Warning, TEXT("AMyCar is %p."), CustomChaosWheeledVehicleMovementComponent.Get());
	GetMesh()->SetCenterOfMass(FVector(0.0f, 0.0f, -50.0f)); // Adjust Z value to lower the center of mass
	UE_LOG(LogTemp, Warning, TEXT("IsGravityEnabled: %s."), GetMesh()->IsGravityEnabled() ? TEXT("true") : TEXT("false"));
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
		CustomChaosWheeledVehicleMovementComponent->SetDriveMode(DrivableMode);
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
}




// Called every frame
void AMyCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//int speed = CustomChaosWheeledVehicleMovementComponent->GetForwardSpeed();
	//UE_LOG(LogTemp, Warning, TEXT("Speed: %d"), speed);
}

// Called to bind functionality to input
void AMyCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCustomChaosWheeledVehicleMovementComponent* AMyCar::GetMyCarVehicleMovementComponent() const
{
	UE_LOG(LogTemp, Warning, TEXT("GetMyCarVehicleMovementComponent is %p."), CustomChaosWheeledVehicleMovementComponent.Get());
	return CustomChaosWheeledVehicleMovementComponent;
}