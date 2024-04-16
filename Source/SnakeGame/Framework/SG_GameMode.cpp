// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "SnakeGame/Framework/SG_GameMode.h"
#include "SnakeGame/Core/Types.h"

void ASG_GameMode::StartPlay()
{
	Super::StartPlay();

	Snake::Settings GS{ GridSize.X, GridSize.Y };
	Game = MakeUnique<Snake::Game>(GS);
}
