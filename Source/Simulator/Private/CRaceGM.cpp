// Fill out your copyright notice in the Description page of Project Settings.


#include "CRaceGM.h"

ACRaceGM::ACRaceGM()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBP(TEXT("/Game/Simulator/Cars/VehiclePlayerController1.VehiclePlayerController1_C"));
	if (PlayerControllerBP.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBP.Class;
	}
	if (UOptionsLibrary::AreOptionsInitialized())
	{
		DefaultPawnClass = UOptionsLibrary::GetChosenVehicleClass();
	}
	else DefaultPawnClass = nullptr;
	if (DefaultPawnClass != nullptr) UE_LOG(LogTemp, Warning, TEXT("DefaultPawnClass: %s"), *DefaultPawnClass->GetName());
	bStartPlayersAsSpectators = false;
	PrimaryActorTick.bCanEverTick = true;
	bAllowTickBeforeBeginPlay = true;
	bAllowReceiveTickEventOnDedicatedServer = true;
	SetTickGroup(ETickingGroup::TG_PrePhysics);
}

void ACRaceGM::BeginPlay()
{
	Super::BeginPlay();

	// Log player controller details
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller: %p"), PC);
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Class: %s"), 
		    *PC->GetClass()->GetName());
	}
	
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
