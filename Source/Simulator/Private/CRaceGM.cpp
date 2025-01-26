// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaceGM.h"

ACRaceGM::ACRaceGM()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("/Game/Simulator/Cars/VehiclePlayerController1.VehiclePlayerController1_C"));
	if (PlayerControllerBP.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBP.Class;
	}

	DefaultPawnClass = nullptr;
	PrimaryActorTick.bCanEverTick = true;
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
	bSimulatorInitialized = true;
}

void ACRaceGM::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bSimulatorInitialized) return;
	URunSimulationLibrary::SimulationTick(DeltaSeconds);
}
