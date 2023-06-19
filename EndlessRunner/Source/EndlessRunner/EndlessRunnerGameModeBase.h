// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

/**
 * 
 */
class UUserWidget;
class ARunningPlatform;
class ARunner;
class APlayerStart;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged, int32, PointsCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLivesCountChanged, int32, Lives);
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	AEndlessRunnerGameModeBase();

	FTimerHandle SpawnTimer;

	FTimerHandle SpeedHandle;
	
public:
	UFUNCTION()
	void SpawnNewPlatforms();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<AActor*> ObjectsInScene;
	
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	class UGameHud* GameHud;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegates")
	FOnLivesCountChanged OnLivesCountChanged;

	UFUNCTION()
	void AddToPoints();

	UFUNCTION()
	void GameOver();

	UPROPERTY()
	float TotalPoints = 0;

	bool bObstaclePassed = false;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UUserWidget> GameHudClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<ARunningPlatform> PlatformClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<UUserWidget> GameOverClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	int32 AmountOfTiles = 11;

	UPROPERTY(EditDefaultsOnly, Category = "Platform")
	FTransform NextSpawn;

	UPROPERTY()
	FTransform NewPlatformSpawn;

	UPROPERTY()
	ARunningPlatform* LastPlatform;
	
	UFUNCTION()
	void CreateInitialPlatforms();

	UFUNCTION()
	void SpawnPlatform();

	UFUNCTION()
	void UpdateSpeed();

	UFUNCTION()
	void MoveObjects(TArray<AActor*>& Actors, float DeltaTime, float ObjectSpeed);
	
	float DestroyLocation = -1000.f;
	
	float Speed = 600.f;
	
	float SpawnDelay = 0.7f;

	float SpeedDelay = 2.f;

	float StartTime;

	int32 PlayerAmount;
};
