// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* RestartButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitButton;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void BackToMainMenu();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void QuitGame();
};
