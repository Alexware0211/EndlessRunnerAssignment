// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runner.h"
#include "GameFramework/Pawn.h"
#include "InputManager.generated.h"

UCLASS()
class ENDLESSRUNNER_API AInputManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInputManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARunner> RunnerClass;
	
	UPROPERTY();
	TArray<AActor*> Runners;
	
	UPROPERTY();
	ARunner* Player1;
	
	UPROPERTY()
	ARunner* Player2;

private:
	
	UFUNCTION()
	void MoveRightP1(float Value);

	UFUNCTION()
	void MoveRightP2(float Value);

	UFUNCTION()
	void JumpP1();

	UFUNCTION()
	void JumpP2();
};
