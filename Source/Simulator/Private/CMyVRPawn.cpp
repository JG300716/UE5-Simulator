#include "CMyVRPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACMyVRPawn::ACMyVRPawn()
{
	// Enable ticking
	PrimaryActorTick.bCanEverTick = true;

	// Create the camera component and attach it to the root component
	VRCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("VRCamera"));
	VRCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACMyVRPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACMyVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACMyVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Enable or disable the camera
void ACMyVRPawn::SetCameraEnabled(bool bEnable)
{
	if (VRCamera)
	{
		VRCamera->SetActive(bEnable);
		VRCamera->SetVisibility(bEnable);
	}
}

// Get the camera location
FVector ACMyVRPawn::GetCameraLocation() const
{
	if (VRCamera)
	{
		return VRCamera->GetComponentLocation();
	}
	return FVector::ZeroVector;
}

// Get the camera rotation
FRotator ACMyVRPawn::GetCameraRotation() const
{
	if (VRCamera)
	{
		return VRCamera->GetComponentRotation();
	}
	return FRotator::ZeroRotator;
}

// Set the camera location
void ACMyVRPawn::SetCameraLocation(FVector NewLocation)
{
	if (VRCamera)
	{
		VRCamera->SetWorldLocation(NewLocation);
	}
}

// Set the camera rotation
void ACMyVRPawn::SetCameraRotation(FRotator NewRotation)
{
	if (VRCamera)
	{
		VRCamera->SetWorldRotation(NewRotation);
	}
}
