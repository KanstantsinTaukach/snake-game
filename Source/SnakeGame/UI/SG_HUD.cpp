// Snake Game. Copyright Taukach K. All Rights Reserved.

#include "UI/SG_HUD.h"
#include "UI/SG_GameplayWidget.h"
#include "UI/SG_GameOverWidget.h"
#include "Core/Game.h"

void ASG_HUD::BeginPlay()
{
	Super::BeginPlay();

	GameplayWidget = CreateWidget<USG_GameplayWidget>(GetWorld(), GameplayWidgetClass);
	check(GameplayWidget);
	GameWidgets.Add(EUIGameState::GameInProgress, GameplayWidget);

	GameOverWidget = CreateWidget<USG_GameOverWidget>(GetWorld(), GameOverWidgetClass);
	check(GameOverWidget);
	GameWidgets.Add(EUIGameState::GameOver, GameOverWidget);

	/*for (auto& [UIState, GameWidget] : GameWidgets)
	{
		if (GameWidget)
		{
			GameWidget->AddToViewport();
			GameWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}*/
	for (auto it = GameWidgets.begin(); it != GameWidgets.end(); ++it)
	{
		if (it->Value)
		{
			it->Value->AddToViewport();
			it->Value->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void ASG_HUD::SetModel(const TSharedPtr<SnakeGame::Game>& InGame)
{
	if (!InGame)
	{
		return;
	}

	using namespace SnakeGame;

	Game = InGame;

	SetEUGameState(EUIGameState::GameInProgress);
	GameplayWidget->SetScore(InGame->score());
	GameOverWidget->SetScore(InGame->score());
		
	InGame->subscribeOnGameplayEvent(
		[&](GameplayEvent Event)
		{
			switch (Event)
			{
			case GameplayEvent::FoodTaken:
				GameplayWidget->SetScore(InGame->score());
				break;

			case GameplayEvent::GameCompleted: [[fallthrough]];
			case GameplayEvent::GameOver:
				GameOverWidget->SetScore(InGame->score());
				SetEUGameState(EUIGameState::GameOver);
				break;
			}
		});
}

void ASG_HUD::SetInputKeyNames(const FString& ResetGameKeyName)
{
	GameplayWidget->SetResetGameKeyName(ResetGameKeyName);
	GameOverWidget->SetResetGameKeyName(ResetGameKeyName);
}

void ASG_HUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (Game.IsValid() && GameState == EUIGameState::GameInProgress)
	{
		GameplayWidget->SetGameTime(Game.Pin()->gameTime());
	}
}

void ASG_HUD::SetEUGameState(EUIGameState InGameState)
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GameWidgets.Contains(InGameState))
	{
		CurrentWidget = GameWidgets[InGameState];
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}

	GameState = InGameState;
}