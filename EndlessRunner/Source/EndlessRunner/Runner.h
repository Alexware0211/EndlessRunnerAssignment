// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runner.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly)
	class AEndlessRunnerGameModeBase* RunnerGameMode;

public:	
	UFUNCTION()
	void AddCoin() const;

	UFUNCTION()
	void DeductHealth(int32 Health);

	UFUNCTION()
	void SetPlayerNumber(int32 NewPlayerNumber);
	
	UPROPERTY(EditAnywhere)
	int32 PlayerNumber;
	
private:

	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	
	int32 MaxHealth = 3;

	int32 CurrentHealth;
	
};
