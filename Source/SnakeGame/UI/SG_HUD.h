// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SG_HUD.generated.h"

class USG_GameplayWidget; 
class USG_GameOverWidget;

UENUM()
enum class EUIGameState : int8
{
	GameInProgress = 0,
	GameOver,
	GameCompleted
};

namespace SnakeGame
{
	class Game;
}

UCLASS()
class SNAKEGAME_API ASG_HUD : public AHUD
{
	GENERATED_BODY()


public:
	ASG_HUD();

	void SetModel(const TSharedPtr<SnakeGame::Game>& InGame);
	void SetInputKeyNames(const FString& ResetGameKeyName);

	virtual void Tick(float DeltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_GameplayWidget> GameplayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<USG_GameOverWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	USG_GameplayWidget* GameplayWidget;

	UPROPERTY()
	USG_GameOverWidget* GameOverWidget;

	UPROPERTY()
	TMap<EUIGameState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	TWeakPtr<SnakeGame::Game> Game;
	EUIGameState GameState;

	void SetEUGameState(EUIGameState GameState);
};
