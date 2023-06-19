// Fill out your copyright notice in the Description page of Project Settings.


#include "Coins.h"
#include "Runner.h"
#include "Components/SphereComponent.h"

// Sets default values
ACoins::ACoins()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>("Coin Mesh");
	CoinMesh->SetupAttachment(Root);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereCollision->SetupAttachment(Root);
	SphereCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ACoins::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ACoins::OnOverlapBegin);
}

void ACoins::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != nullptr)
	{
		ARunner* Runner = Cast<ARunner>(OtherActor);
		if(Runner)
		{
			Runner->AddCoin();
			
			this->CoinMesh->SetVisibility(false);
			this->CoinMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			this->SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
		}
	}
}


