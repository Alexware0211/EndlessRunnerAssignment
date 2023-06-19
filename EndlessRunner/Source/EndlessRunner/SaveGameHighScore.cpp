// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGameHighScore.h"

#include "Kismet/GameplayStatics.h"

const FString SaveSlotName = TEXT("MySaveGame");
const uint32 UserIndex = 0;

USaveGameHighScore::USaveGameHighScore()
{
	HighScore = 0;
}

USaveGameHighScore* USaveGameHighScore::Load()
{
	USaveGameHighScore* SaveGame = Cast<USaveGameHighScore>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));

	if(!SaveGame)
	{
		SaveGame = Cast<USaveGameHighScore>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	}
	return SaveGame;
}

void USaveGameHighScore::Save(int32 NewHighScore)
{
	if(NewHighScore > HighScore)
	{
		HighScore = NewHighScore;
		UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
	}
}


