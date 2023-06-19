// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHud.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UGameHud : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PointsCount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Lives;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* PauseButton;

	UFUNCTION()
	void PauseGame();

	virtual void NativeConstruct() override;
public:
	UFUNCTION()
	void InitializeHud(class AEndlessRunnerGameModeBase* GameMode);

	UFUNCTION()
	void SetCoinsCount(const int32 CoinsCount);
	
	UFUNCTION()
	void UpdatePoints(const int32 CoinsCount);

	UFUNCTION()
	void SetLivesCount(const int32 LivesCount);
};
