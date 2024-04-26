// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Snake
{
	struct Dim
	{
		uint32 width;
		uint32 height;
	};

	enum class CellType
	{
		Empty = 0,
		Wall
	};

	struct Settings
	{
		Dim gridSize;
	};
}

