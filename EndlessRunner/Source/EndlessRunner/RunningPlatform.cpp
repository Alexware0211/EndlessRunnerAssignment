// Fill out your copyright notice in the Description page of Project Settings.


#include "RunningPlatform.h"
#include "Coins.h"
#include "EndlessRunnerGameModeBase.h"
#include "Obstacle.h"
#include "Runner.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

class ACoins;
// Sets default values
ARunningPlatform::ARunningPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	PlatformComponent = CreateDefaultSubobject<UStaticMeshComponent>("Platform Component");
	PlatformComponent->SetupAttachment(Root);

	MiddleLane = CreateDefaultSubobject<UArrowComponent>("Middle Lane");
	MiddleLane->SetupAttachment(Root);

	RightLane = CreateDefaultSubobject<UArrowComponent>("Right Lane");
	RightLane->SetupAttachment(Root);

	LeftLane = CreateDefaultSubobject<UArrowComponent>("Left Lane");
	LeftLane->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ARunningPlatform::BeginPlay()
{
	Super::BeginPlay();

	RunnerGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	
	check(RunnerGameMode);
}

void ARunningPlatform::SpawnObject()
{
	if(ObstacleClass)
	{
		SpawnLaneObstacles(MiddleLane);
		SpawnLaneObstacles(RightLane);
		SpawnLaneObstacles(LeftLane);
	}
}

void ARunningPlatform::SpawnLaneObstacles(const UArrowComponent* Lane) const
{
	const float RandomValue = FMath::FRand();

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	const FTransform& SpawnLocation = Lane->GetComponentTransform();

	//If the bool is true, spawn a coin to reward the player with a 10-25% chance rate.
	if(RunnerGameMode->bObstaclePassed && UKismetMathLibrary::InRange_FloatFloat(RandomValue,
	0.1,
	0.25,
	true,
	true))
	{
		ACoins* Coins = GetWorld()->SpawnActor<ACoins>(CoinsClass, SpawnLocation, SpawnParameters);
		RunnerGameMode->ObjectsInScene.Add(Coins);

		RunnerGameMode->bObstaclePassed = false;
	}
	else if(UKismetMathLibrary::InRange_FloatFloat(RandomValue,
	0.5,
	1,
	true,
	true))
	{
		AObstacle* Obstacle = GetWorld()->SpawnActor<AObstacle>(ObstacleClass, SpawnLocation, SpawnParameters);
		RunnerGameMode->ObjectsInScene.Add(Obstacle);
	}
	else
	{
		ACoins* Coins = GetWorld()->SpawnActor<ACoins>(CoinsClass, SpawnLocation, SpawnParameters);
		RunnerGameMode->ObjectsInScene.Add(Coins);
	}
}


