// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
	class IPositionRandomizer
	{
	public:
		virtual bool generatePosition(const Dim& dim, const TArray<CellType>& cells, Position& position) const = 0;
		virtual ~IPositionRandomizer() = default;
	};

	class PositionRandomizer : public IPositionRandomizer
	{
		virtual bool generatePosition(const Dim& dim, const TArray<CellType>& cells, Position& position) const override
		{
			const int32 gridSize = dim.width * dim.height;
			const int32 index = FMath::RandRange(0, gridSize - 1);
			for (int32 i = index; i < gridSize; ++i)
			{
				if (cells[i] == CellType::Empty)
				{
					position = indexToPos(i, dim);
					if (position != Position::Zero)
					{
						return true;
					}
				}
			}

			for (int32 i = index; i > 0; --i)
			{
				if (cells[i] == CellType::Empty)
				{
					position = indexToPos(i, dim);
					if (position != Position::Zero)
					{
						return true;
					}
				}
			}
			return false;
		}

	private:
		FORCEINLINE Position indexToPos(int32 index, const Dim& dim) const
		{
			return Position(index % dim.width, index / dim.width);
		}
	};

	using IPositionRandomizerPtr = TSharedPtr<IPositionRandomizer>;
}