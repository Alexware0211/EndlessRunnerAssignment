// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"
#include "GameHud.h"
#include "Obstacle.h"
#include "Runner.h"
#include "RunningPlatform.h"
#include "SaveGameHighScore.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameModeBase::AEndlessRunnerGameModeBase()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEndlessRunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	StartTime = GetWorld()->GetRealTimeSeconds();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GameHud = Cast<UGameHud>(CreateWidget(GetWorld(), GameHudClass));
	check(GameHud) // Checks if the HUD is there, otherwise crash game.

	GameHud->InitializeHud(this);
	GameHud->AddToViewport();
	
	CreateInitialPlatforms();

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEndlessRunnerGameModeBase::SpawnNewPlatforms, SpawnDelay, true);
	GetWorldTimerManager().SetTimer(SpeedHandle, this, &AEndlessRunnerGameModeBase::UpdateSpeed, SpeedDelay, true);
}

void AEndlessRunnerGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	MoveObjects(ObjectsInScene, DeltaTime, Speed);
	
	TotalPoints += DeltaTime;

	OnCoinsCountChanged.Broadcast(TotalPoints);
}

void AEndlessRunnerGameModeBase::CreateInitialPlatforms()
{
	for (int i = 0; i < AmountOfTiles; ++i)
	{
		SpawnPlatform();
	}
}

void AEndlessRunnerGameModeBase::SpawnPlatform()
{
	UWorld* World = GetWorld();
	
	if(World)
	{
		LastPlatform = World->SpawnActor<ARunningPlatform>(PlatformClass, NewPlatformSpawn);
		ObjectsInScene.Add(LastPlatform);
		
		if(LastPlatform)
		{
			NewPlatformSpawn += NextSpawn;
		}
	}
}

void AEndlessRunnerGameModeBase::AddToPoints()
{
	TotalPoints += 10;

	OnCoinsCountChanged.Broadcast(TotalPoints);
}

void AEndlessRunnerGameModeBase::MoveObjects(TArray<AActor*> &Actors, float DeltaTime, float ObjectSpeed)
{
	TArray<AActor*> ActorsCopy = Actors;

	for (auto Object : ActorsCopy)
	{
		FVector ObjectLocation = Object->GetActorLocation();

		ObjectLocation.X -= ObjectSpeed * DeltaTime;
		
		Object->SetActorLocation(ObjectLocation);
		
		if(ObjectLocation.X <= DestroyLocation)
		{
			if(Object->IsA<AObstacle>())
			{
				bObstaclePassed = true;
			}
			Actors.Remove(Object);
			ObjectsInScene.Remove(Object);
			Object->Destroy();
		}
	}
}

void AEndlessRunnerGameModeBase::SpawnNewPlatforms()
{
	if(GetWorld())
	{
		if(!LastPlatform) return;
		
		LastPlatform->SpawnObject();
		
		FTransform NewTransform = LastPlatform->GetTransform() + NextSpawn;
		LastPlatform = GetWorld()->SpawnActor<ARunningPlatform>(PlatformClass, NewTransform);
		ObjectsInScene.Add(LastPlatform);
	}
}

void AEndlessRunnerGameModeBase::UpdateSpeed()
{
	Speed += 10.f;
	
	if(Speed >= 800.f)
	{
		GetWorldTimerManager().ClearTimer(SpeedHandle);
	}
}

void AEndlessRunnerGameModeBase::GameOver()
{
	if(IsValid(GameOverClass))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		
		UUserWidget* Widget = CreateWidget(GetWorld(), GameOverClass);

		if(Widget)
		{
			Widget->AddToViewport();

			USaveGameHighScore* SaveGame = USaveGameHighScore::Load();
			SaveGame->Save(TotalPoints);
		}
	}
}



