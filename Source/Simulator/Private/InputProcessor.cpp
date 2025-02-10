// Fill out your copyright notice in the Description page of Project Settings.


#include "InputProcessor.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UInputProcessor::UInputProcessor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInputProcessor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UInputProcessor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (CurrentInputType)
	{
	case InputType::Car:
		ProcessCarInput(DeltaTime);
		break;
	case InputType::Controller:
		ProcessControllerInput(DeltaTime);
		break;
	default:
		break;
	}

	CurrentControlRotation = FMath::RInterpTo(CurrentControlRotation, TargetControlRotation, DeltaTime, 3.0f);
}

void UInputProcessor::ProcessCarInput(float DeltaTime)
{
	if (!CarObject)
		return;

	YawAcceleration = (LastYaw - CarObject->GetActorRotation().Yaw) / DeltaTime;
	LastYaw = CarObject->GetActorRotation().Yaw;

	ForwardAcceleration = FMath::Clamp(((LastSpeed - ForwardSpeed) / 15), -1.0f, 1.0f);
	LastSpeed = ForwardSpeed;

	TargetControlRotation.Roll = RollScalar * (YawAcceleration / 70.f);
	TargetControlRotation.Pitch = PitchScalar * ForwardAcceleration;
	TargetControlRotation.Yaw = CurrentControlRotation.Yaw + (( YawAcceleration / 70 )* -7.5f);
}


void UInputProcessor::ProcessControllerInput(float DeltaTime)
{
	CurrentYaw += (Yaw * DeltaTime * YawTurnSpeed);

	TargetControlRotation.Roll = Horizontal * HorizontalScalar;
	TargetControlRotation.Pitch = Vertical * VerticalScalar;
	TargetControlRotation.Yaw = CurrentYaw;
}

void UInputProcessor::SetForwardSpeed(float NewForwardSpeed)
{
	ForwardSpeed = NewForwardSpeed;
}

void UInputProcessor::SetControlInput(float NewHorizontal, float NewVertical, float NewYaw)
{
	Horizontal = NewHorizontal;
	Vertical = NewVertical;
	Yaw = NewYaw;
}

void UInputProcessor::SetCar(AActor* NewCar)
{
	CarObject = NewCar;
}

void UInputProcessor::ChangeMode(InputType NewMode)
{
	CurrentInputType = NewMode;
}

FRotator UInputProcessor::GetControlRotation()
{
	return CurrentControlRotation;
}