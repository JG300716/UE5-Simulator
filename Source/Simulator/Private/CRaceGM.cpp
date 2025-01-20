// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaceGM.h"

ACRaceGM::ACRaceGM()
{
	// Set the default GameMode properties (optional)
	// For example, set the default pawn class, HUD class, etc.
}

void ACRaceGM::BeginPlay()
{
	Super::BeginPlay();
    
	// Add a delay before calling StartSimulation
	// This ensures everything in the world has been initialized.
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACRaceGM::StartSimulation, 0.1f, false);
}

void ACRaceGM::StartSimulation()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// If the world is valid, call StartSimulation from your RunSimulationLibrary
		URunSimulationLibrary::StartSimulation(World);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No valid world found in StartSimulation"));
	}
}