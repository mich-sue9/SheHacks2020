#pragma once
#include "GameEngine/EntitySystem/Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>


namespace Game
{
	//Used for storing and controling all game related entities
	class PlayerEntity;

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		//Temp - for nice architecture this should be within some sort of IUpdatable interface that GameEngine handles (so that not only entities can be updated)
		void Update();

		void UpdateMole();


		bool IsGameOver() const { return m_isGameOver; }

	protected:
		//Placeholder temp - should go to helpers or smth.
		float RandomFloatRange(float a, float b)
		{
			return ((b - a) * ((float)rand() / RAND_MAX)) + a;
		}

		void CreateBackGround();
		void UpdateBackGround();

		void CreateCountDown();
		void UpdateCountDown();

		void CreateScoreBoard();
		void UpdateScoreBoard();

		void CreateMole();

		PlayerEntity* m_player;
		GameEngine::Entity* m_backGround;
		GameEngine::Entity* m_CountDown;
		GameEngine::Entity* m_ScoreBoard;

		std::vector<GameEngine::Entity*> m_obstacles;
		std::vector<GameEngine::Entity*> m_holes; // 9 holes
		GameEngine::Entity* m_mole; // 1 mole

		float m_lastObstacleSpawnTimer;
	
		bool  m_isGameOver;
	};
}
