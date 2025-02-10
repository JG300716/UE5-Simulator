// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputProcessor.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class InputType : uint8
{
	Controller, Car
};

enum class  DeviceStatus
{
	Available, Reserved, Unknown
};

enum class  Result
{
	Success, Error
};

UENUM(BlueprintType)
enum class ControllerState : uint8
{
	Initial, Connecting, Connected, Starting, Started, Stopping, Disconnecting
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMULATOR_API UInputProcessor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInputProcessor();

	float YawAcceleration = 0, ForwardAcceleration = 0, LastYaw = 0, LastSpeed = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SetUp")
	AActor* CarObject;

	InputType CurrentInputType = InputType::Controller;

	FRotator TargetControlRotation = FRotator(0, 0, 0);
	FRotator CurrentControlRotation = FRotator(0, 0, 0);

	//Controller variables
	float Horizontal = 0.f;
	float Vertical = 0.f;
	float Yaw = 0.f;
	float RollScalar = 30.f;
	float PitchScalar = -30.f;

	//Car variables
	float YawTurnSpeed = 100.f;
	float CurrentYaw = 0;
	float HorizontalScalar = 30.f;
	float VerticalScalar = -30.f;
	float ForwardSpeed = 0.f;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ProcessCarInput(float DeltaTime);

	void ProcessControllerInput(float DeltaTime);

	//Mike - set forward velocity from the car
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void SetForwardSpeed(float NewForwardSpeed);

	//Mike - Set control input from a controller
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void SetControlInput(float NewHorizontal, float NewVertical, float NewYaw);

	//Mike - Change between modes
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void ChangeMode(InputType NewMode);

	//Mike - Set the actor that we will derive data from to produce acceleration motions
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void SetCar(AActor* NewCar);

	//Mike - Get the resulting motion data to feed to the motion base
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	FRotator GetControlRotation();
};