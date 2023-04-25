// Fill out your copyright notice in the Description page of Project Settings.


#include "EndlessRunnerBase.h"

AEndlessRunnerBase::AEndlessRunnerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEndlessRunnerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEndlessRunnerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Green,TEXT("Test"));


}
