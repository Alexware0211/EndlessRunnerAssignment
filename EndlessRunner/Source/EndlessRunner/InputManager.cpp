// Fill out your copyright notice in the Description page of Project Settings.


#include "InputManager.h"

#include "Kismet/GameplayStatics.h"
#include "Runner.h"
// Sets default values
AInputManager::AInputManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInputManager::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), RunnerClass, Runners);

	Player1 = Cast<ARunner>(Runners[0]);
	Player2 = Cast<ARunner>(Runners[1]);

	check(Player1 && Player2)

	
}

// Called to bind functionality to input
void AInputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Right", this, &AInputManager::MoveRightP1);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AInputManager::JumpP1);

	PlayerInputComponent->BindAxis("Move Right Player 2", this, &AInputManager::MoveRightP2);
	PlayerInputComponent->BindAction("Jump Player 2", EInputEvent::IE_Pressed, this, &AInputManager::JumpP2);
	
}

void AInputManager::MoveRightP1(float Value)
{
	Player1->AddMovementInput(GetActorRightVector() * Value);
}

void AInputManager::MoveRightP2(float Value)
{
	Player2->AddMovementInput(GetActorRightVector() * Value);
}

void AInputManager::JumpP1()
{
	Player1->Jump();
}

void AInputManager::JumpP2()
{
	Player2->Jump();
}
