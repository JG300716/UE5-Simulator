// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunSimulationLibrary.h"
#include "TimerManager.h"
#include "CRaceGM.generated.h"

/**
 * 
 */
UCLASS()
class SIMULATOR_API ACRaceGM : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	ACRaceGM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Function to start simulation
	void StartSimulation();

private:
	// Timer handle for delayed start of simulation (if needed)
	FTimerHandle TimerHandle;
};
