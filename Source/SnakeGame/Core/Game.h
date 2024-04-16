// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace Snake
{
	class Grid;

	class SNAKEGAME_API Game
	{
	public:
		Game(const Settings& settings);
		TSharedPtr<Grid> grid() const { return m_grid; }

	private:
		const Settings c_settings;
		TSharedPtr<Grid> m_grid;
	};
}

