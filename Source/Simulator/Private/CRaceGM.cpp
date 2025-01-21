// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaceGM.h"

ACRaceGM::ACRaceGM()
{
}

void ACRaceGM::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));
	// Add a delay before calling StartSimulation
	// This ensures everything in the world has been initialized.
	if (!GetWorld()) return;
	UE_LOG(LogTemp, Warning, TEXT("GetWorld()"));
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ACRaceGM::StartSimulation, 0.1f, false);
}

void ACRaceGM::StartSimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("StartSimulation called"));
	UWorld* World = GetWorld();
	if (World)
	{
		DefaultPawnClass = UOptionsLibrary::GetChosenVehicleClass();
		UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass set"));
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No valid world found in StartSimulation"));
	}
	UE_LOG(LogTemp, Warning, TEXT("StartSimulation finished"));
}