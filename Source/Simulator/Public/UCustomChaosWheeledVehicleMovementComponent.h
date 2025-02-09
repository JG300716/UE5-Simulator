// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Components/ActorComponent.h"
#include "UCustomChaosWheeledVehicleMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMULATOR_API UCustomChaosWheeledVehicleMovementComponent : public UChaosWheeledVehicleMovementComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomChaosWheeledVehicleMovementComponent(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool bToggleAutoTransmission = true;
	int DriveMode = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "MYFunctions|WheeledVehicleMovement")
	int SetDriveMode(int Type);
};
