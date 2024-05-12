// Snake Game. Copyright Taukach K. All Rights Reserved.


#include "Core/Snake.h"

using namespace SnakeGame;

Snake::Snake(const Settings::Snake& settings)
{
	checkf(settings.defaultSize >= 4, TEXT("Snake length is too small: %i"), settings.defaultSize);
	// Add snake links horizontally to the left [ ----* ]
	const auto startPos = settings.startPosition;
	for (int32 i = 0; i < settings.defaultSize; ++i)
	{
		m_links.AddTail(Position{ startPos.x - i, startPos.y });
	}
}

void SnakeGame::Snake::move(const Input& input)
{
	// Can't move opposite direction
	if (!m_lastInput.opposite(input))
	{
		m_lastInput = input;
	}
	m_links.RemoveNode(m_links.GetTail());
	m_links.InsertNode(m_links.GetHead()->GetValue(), m_links.GetHead()->GetNextNode());
	m_links.GetHead()->GetValue() += Position(m_lastInput.x, m_lastInput.y);
}