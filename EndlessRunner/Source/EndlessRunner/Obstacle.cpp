// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Runner.h"
#include "Components/BoxComponent.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Mesh");
	ObstacleMesh->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(Root);
	BoxCollision->SetGenerateOverlapEvents(true);
}


void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnOverlapBegin);
}

void AObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != nullptr)
	{
		ARunner* Runner = Cast<ARunner>(OtherActor);
		if(Runner)
		{
			Runner->DeductHealth(1);
			
			this->ObstacleMesh->SetVisibility(false);
			this->ObstacleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			this->BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

