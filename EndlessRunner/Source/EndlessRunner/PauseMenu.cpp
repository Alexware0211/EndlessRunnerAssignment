// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenu::NativeConstruct()
{
	if(ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::ResumeGame);
	}

	if(RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UPauseMenu::RestartGame);
	}

	if(MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UPauseMenu::BackToMainMenu);
	}
}

void UPauseMenu::ResumeGame()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	RemoveFromParent();
}

void UPauseMenu::RestartGame()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMap"));
	}
}

void UPauseMenu::BackToMainMenu()
{
	UWorld* World = GetWorld();

	if(World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
	}
}


