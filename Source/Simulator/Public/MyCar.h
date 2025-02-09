// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UCustomChaosWheeledVehicleMovementComponent.h"
#include "WheeledVehiclePawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "MyCar.generated.h"

/**
 * Was made for engineer degree thesis purposes.
 * Author: Jakub Golder
 */

UCLASS(Blueprintable,BlueprintType)
class SIMULATOR_API AMyCar : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCar(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	FVector StartingLocation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Vehicle", meta=(MultiLine="true"))
	TObjectPtr<UChaosWheeledVehicleMovementComponent> TMPMyChaosWheeledVehicleMovementComponent;
	
	UFUNCTION(BlueprintCallable, Category="Vehicle|Movement")
	void GearUp();

	UFUNCTION(BlueprintCallable, Category="Vehicle|Movement")
	void GearDown();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="MyFunctions|WheeledVehicleMovement")
	UChaosWheeledVehicleMovementComponent* GetMyCarVehicleMovementComponent() const;

	UFUNCTION(BlueprintCallable, Category="MyFunctions|WheeledVehicleMovement")
	void SetUpMyCarVehicleMovementComponent(UChaosWheeledVehicleMovementComponent* Component);
	
	UFUNCTION(BlueprintCallable, Category="MyFunctions|WheeledVehicleMovement")
	void SetUpOptions();
};
