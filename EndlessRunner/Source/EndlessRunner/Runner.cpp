// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "EndlessRunnerGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunner::ARunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();

	RunnerGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	check(RunnerGameMode);

	CurrentHealth = MaxHealth;
}

void ARunner::AddCoin() const
{
	RunnerGameMode->AddToPoints();
}

void ARunner::DeductHealth(int32 Health)
{
	CurrentHealth -= Health;

	RunnerGameMode->OnLivesCountChanged.Broadcast(CurrentHealth);
	
	if(CurrentHealth <= 0)
	{
		RunnerGameMode->GameOver();
		Destroy();
	}
}

void ARunner::SetPlayerNumber(int32 NewPlayerNumber)
{
	PlayerNumber = NewPlayerNumber;
}



