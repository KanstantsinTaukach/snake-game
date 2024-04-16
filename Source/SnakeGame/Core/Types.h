// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace Snake
{
	struct Dim
	{
		int32 width;
		int32 height;
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
class SNAKEGAME_API Types
{
public:
	Types();
	~Types();
};
