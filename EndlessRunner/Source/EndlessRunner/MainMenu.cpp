// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "SaveGameHighScore.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UMainMenu::NativeConstruct()
{
	if(StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenu::StartGame);
	}

	if(ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	}
	
	USaveGameHighScore* SaveGameInstance = Cast<USaveGameHighScore>(UGameplayStatics::LoadGameFromSlot("HighScore", 0));
	if (SaveGameInstance)
	{
		HighscoreText->SetText(FText::AsNumber(SaveGameInstance->HighScore));
	}
	else
	{
		HighscoreText->SetText(FText::AsNumber(0));
	}

	USaveGameHighScore* SaveGame = USaveGameHighScore::Load();
	FString HighScore = "HighScore: ";
	HighScore.AppendInt(SaveGame->HighScore);
	HighscoreText->SetText(FText::FromString(HighScore));
}

void UMainMenu::StartGame()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMap"));
	}
}

void UMainMenu::QuitGame()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);
	}
}


