// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerBase.h"
#include "Engine/World.h"


AEndlessRunnerBase::AEndlessRunnerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEndlessRunnerBase::BeginPlay() // Start
{
	Super::BeginPlay();
}

void AEndlessRunnerBase::Tick(float DeltaTime) // Update(Per Tick)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Green,TEXT("Test"));

	
}

void AEndlessRunnerBase::SpawnMyActor(UWorld* World, FVector SpawnLocation, FRotator SpawnRotation)
{
	TSubclassOf<AActor> FloorActor = AEndlessRunnerBase::StaticClass();
	AActor* NewActor = World->SpawnActor<AActor>(FloorActor,SpawnLocation, SpawnRotation);

}