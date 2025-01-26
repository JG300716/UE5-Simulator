// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "CMyVRPawn.generated.h"

UCLASS()
class SIMULATOR_API ACMyVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACMyVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Camera component to represent the player's viewpoint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="VR")
	UCameraComponent* VRCamera;

	// Enable or disable the camera
	UFUNCTION(BlueprintCallable, Category="VR")
	void SetCameraEnabled(bool bEnable);

	// Get the camera location
	UFUNCTION(BlueprintCallable, Category="VR")
	FVector GetCameraLocation() const;

	// Get the camera rotation
	UFUNCTION(BlueprintCallable, Category="VR")
	FRotator GetCameraRotation() const;

	// Set the camera location
	UFUNCTION(BlueprintCallable, Category="VR")
	void SetCameraLocation(FVector NewLocation);

	// Set the camera rotation
	UFUNCTION(BlueprintCallable, Category="VR")
	void SetCameraRotation(FRotator NewRotation);
};
