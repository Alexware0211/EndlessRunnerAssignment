// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameHighScore.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API USaveGameHighScore : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 HighScore;

	USaveGameHighScore();

	static USaveGameHighScore* Load();

	void Save(int32 NewHighScore);
};
