// Snake Game. Copyright Taukach K. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/List.h"

namespace SnakeGame
{
	struct Dim
	{
		int32 width;
		int32 height;
	};

	struct Position
	{
		Position(int32 inX, int32 inY) : x(inX), y(inY) {}
		int32 x;
		int32 y;

		FORCEINLINE Position& operator+=(const Position& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		static Position Zero;
	};

	struct Input
	{
		int8 x;
		int8 y;

		FORCEINLINE bool opposite(const Input& rhs) const
		{
			return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0);
		}

		static Input Default;
	};

	enum class CellType
	{
		Empty = 0,
		Wall,
		Snake
	};

	struct Settings
	{
		Dim gridDims{ 50, 25 };
		struct Snake
		{
			int32 defaultSize{ 4 };
			Position startPosition{ Position::Zero };
		} snake;
		float gameSpeed{ 1.0f };
	};

	using TPositionPtr = TDoubleLinkedList<Position>::TDoubleLinkedListNode;

	class TSnakeList : public TDoubleLinkedList<Position>
	{
	public:
		void MoveTail(TPositionPtr* Tail, TPositionPtr* Head, const Position& Pos)
		{
			RemoveNode(Tail);
			InsertNode(Pos, Head->GetNextNode());
		}
	};
	
}

