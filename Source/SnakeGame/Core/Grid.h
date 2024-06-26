// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Utils.h"

namespace SnakeGame
{
	class Grid
	{
	public:
		Grid(const Dim& dim, const IPositionRandomizerPtr& randomizer = MakeShared<PositionRandomizer>());

		Dim dim() const { return c_dim; }

		void printDebug();
		void update(const TPositionPtr* links, CellType cellType);
		void update(const  Position& position, CellType cellType);
		bool hitTest(const Position& position, CellType cellType) const;

		UE_NODISCARD bool randomEmptyPosition(Position& position) const;

		static Position center(int32 width, int32 height)
		{
			return Position(width / 2 + 1, height / 2 + 1);
		}

	private:
		const Dim c_dim;
		TArray<CellType> m_cells;
		TMap<CellType, TArray<uint32>> m_indByType =
		{
			{CellType::Snake, {}},
			{CellType::Wall, {}},
			{CellType::Food, {}},
		};

		TSharedPtr<IPositionRandomizer> m_positionRandomizer;

		void initWalls();
		void updateInternal(const  Position& position, CellType cellType);
		void freeCellsByType(CellType cellType);

		FORCEINLINE int32 posToIndex(int32 x, int32 y) const;
		FORCEINLINE int32 posToIndex(const Position& position) const;
	};
}

