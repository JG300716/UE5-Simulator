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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USceneComponent* VRCameraRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* VRCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle|Options")
	bool bIsAutomaticTransmission;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Vehicle")
	FVector StartingLocation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Domyślne", meta=(MultiLine="true"))
	TObjectPtr<UCustomChaosWheeledVehicleMovementComponent> CustomChaosWheeledVehicleMovementComponent;

	UFUNCTION(BlueprintCallable, Category="MyFunctions|WheeledVehicleMovement")
	UCustomChaosWheeledVehicleMovementComponent* GetMyCarVehicleMovementComponent() const;

	UFUNCTION(BlueprintCallable, Category="MyFunctions|WheeledVehicleMovement")
	void SetUpMyCarVehicleMovementComponent(UCustomChaosWheeledVehicleMovementComponent* Component);

	UFUNCTION(BlueprintCallable, Category = "VR")
	void SetupVRReferences(USceneComponent* CameraRoot, UCameraComponent* Camera);

	UFUNCTION(BlueprintCallable, Category="Vehicle")
	UCameraComponent* GetVRCamera() const { return VRCamera; }

	UFUNCTION(BlueprintCallable, Category="Vehicle")
	USceneComponent* GetVRCameraRoot() const { return VRCameraRoot; }
	
	UFUNCTION(BlueprintCallable, Category="MyFunctions|WheeledVehicleMovement")
	void SetUpOptions();
};
