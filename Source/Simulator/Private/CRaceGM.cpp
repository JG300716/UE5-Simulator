// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaceGM.h"

ACRaceGM::ACRaceGM()
{
}

void ACRaceGM::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay called"));
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
		URunSimulationLibrary::StartSimulation(World);
		
	}
	UE_LOG(LogTemp, Warning, TEXT("StartSimulation finished"));
}

