// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHud.h"
#include "EndlessRunnerGameModeBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"


void UGameHud::NativeConstruct()
{
	if(PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UGameHud::PauseGame);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

void UGameHud::InitializeHud(AEndlessRunnerGameModeBase* GameMode)
{
	if(GameMode)
	{
		PointsCount->SetText(FText::FromString("Score: 0"));
		Lives->SetText(FText::FromString("Lives: 3"));

		GameMode->OnCoinsCountChanged.AddDynamic(this, &UGameHud::SetCoinsCount);
		GameMode->OnLivesCountChanged.AddDynamic(this, &UGameHud::SetLivesCount);
	}
}

void UGameHud::SetCoinsCount(const int32 CoinsCount)
{
	FString Score = "Score: ";
	Score.AppendInt(CoinsCount);
	
	PointsCount->SetText(FText::FromString(Score));
}

void UGameHud::UpdatePoints(const int32 CoinsCount)
{
	FString Score = "Score: ";
	Score.AppendInt(CoinsCount);
	
	PointsCount->SetText(FText::FromString(Score));
}

void UGameHud::SetLivesCount(int32 LivesCount)
{
	FString Life = "Lives: ";
	Life.AppendInt(LivesCount);
	
	Lives->SetText(FText::FromString(Life));
}

void UGameHud::PauseGame()
{
	if(IsValid(PauseMenuWidgetClass))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		
		UUserWidget* Widget = CreateWidget(GetWorld(), PauseMenuWidgetClass);

		if(Widget)
		{
			Widget->AddToViewport();
		}
	}
}
