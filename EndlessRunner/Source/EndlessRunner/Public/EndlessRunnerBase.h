// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerBase.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerBase : public AGameModeBase
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditDefaultsOnly)
			TSubclassOf<AActor> floor;
		UPROPERTY(EditDefaultsOnly)
			TSubclassOf<AActor> walls;

		void BeginPlay() override;

		void Tick(float DeltaTime) override;

		AEndlessRunnerBase();

		
};
