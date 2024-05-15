// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "SnakeGame/Core/Grid.h"

DEFINE_LOG_CATEGORY_STATIC(LogGrid, All, All);

using namespace SnakeGame;

Grid::Grid(const Dim& dim) : c_dim(Dim{dim.width + 2, dim.height + 2})
{
	/*
	
	* * * * * *
	* 0 0 0 0 *
	* 0 0 0 0 *
	* 0 0 0 0 *
	* * * * * *
	
	*/

	m_cells.Init(CellType::Empty, c_dim.width * c_dim.height);
	initWalls();
	printDebug();
}

void Grid::initWalls()
{
	for (int32 y = 0; y < c_dim.height; ++y)
	{
		for (int32 x = 0; x < c_dim.width; ++x)
		{
			if ((x == 0) || (x == c_dim.width - 1) || (y == 0) || (y == c_dim.height - 1)) 
			{
				const auto index = posToIndex(x, y);
				m_cells[index] = CellType::Wall;
				m_indByType[CellType::Wall].Add(index);
			}
		}
	}
}

void Grid::printDebug()
{
#if !UE_BUILD_SHIPPING
	for (int32 y = 0; y < c_dim.height; ++y)
	{
		FString line;
		for (int32 x = 0; x < c_dim.width; ++x)
		{
			TCHAR symbol{};
			switch (m_cells[posToIndex(x, y)])
			{
			case CellType::Empty: symbol = '0'; break;
			case CellType::Wall: symbol = '*'; break;
			case CellType::Snake: symbol = '_'; break;
			case CellType::Food: symbol = '.'; break;
			}
			line.AppendChar(symbol).AppendChar(' ');
		}
		UE_LOG(LogGrid, Display, TEXT("%s"), *line);
	}
#endif
}

void Grid::update(const TPositionPtr* links, CellType cellType)
{
	freeCellsByType(cellType);
	auto* link = links;
	while (link)
	{
		updateInternal(link->GetValue(), cellType);
		link = link->GetNextNode();
	}
}

void Grid::update(const Position& position, CellType cellType)
{
	freeCellsByType(cellType);
	updateInternal(position, cellType);
}

void Grid::updateInternal(const Position& position, CellType cellType)
{
	const auto index = posToIndex(position);
	m_cells[index] = cellType;
	m_indByType[cellType].Add(index);
}

void Grid::freeCellsByType(CellType cellType)
{
	for (int32 i = 0; i < m_indByType[cellType].Num(); ++i)
	{
		const int32 ind = m_indByType[cellType][i];
		m_cells[ind] = CellType::Empty;
	}
	m_indByType[cellType].Empty();
}

bool Grid::hitTest(const Position& position, CellType cellType) const
{
	return m_cells[posToIndex(position)] == cellType;
}

Position Grid::randomEmptyPosition() const
{
	const int32 gridSize = c_dim.width * c_dim.height;
	const int32 index = FMath::RandRange(0, gridSize - 1);
	for (int32 i = index; i < gridSize; ++i)
	{
		if (m_cells[i] == CellType::Empty) {
			return indexToPos(i);
		}
	}

	for (int32 i = index; i > 0; --i)
	{
		if (m_cells[i] == CellType::Empty) {
			return indexToPos(i);
		}
	}

	UE_LOG(LogGrid, Error, TEXT("Empty cell doesn't exist"));
	checkNoEntry();
	return Position::Zero;
}

int32 Grid::posToIndex(int32 x, int32 y) const
{
	return x + y * c_dim.width;
}

int32 Grid::posToIndex(const Position& position) const
{
	return posToIndex(position.x, position.y);
}

Position Grid::indexToPos(int32 index) const
{
	return Position(index % c_dim.width, index / c_dim.width);
}