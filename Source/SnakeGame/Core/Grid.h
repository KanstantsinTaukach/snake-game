// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace SnakeGame
{
	class Grid
	{
	public:
		Grid(const Dim& dim);

		Dim dim() const { return c_dim; }

		void printDebug();
		void update(const TPositionPtr* links, CellType cellType);
		bool hitTest(const Position& position, CellType cellType) const;

	private:
		const Dim c_dim;
		TArray<CellType> m_cells;

		void initWalls();
		FORCEINLINE int32 posToIndex(int32 x, int32 y) const;
		FORCEINLINE int32 posToIndex(const Position& position) const;
		void freeCellsByType(CellType cellType);
	};
}

