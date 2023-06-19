// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunningPlatform.generated.h"


UCLASS()
class ENDLESSRUNNER_API ARunningPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARunningPlatform();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameModeBase* RunnerGameMode;
	
public:	

	UFUNCTION()
	void SpawnObject();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AObstacle> ObstacleClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ACoins> CoinsClass;

protected:
	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* PlatformComponent;

	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* MiddleLane;
	
	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* LeftLane;
	
	UPROPERTY(EditDefaultsOnly)
	class UArrowComponent* RightLane;

	FVector CurrentLocation;

	UFUNCTION()
	void SpawnLaneObstacles(const UArrowComponent* Lane) const;
};
