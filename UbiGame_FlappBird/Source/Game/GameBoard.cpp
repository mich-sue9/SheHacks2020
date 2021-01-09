#include <stdlib.h>
#include <time.h>       /* time */

#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/EntitySystem/Components/BackgroundComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/ObstacleEntity.h"
#include "Game/GameEntities/HoleEntity.h"
#include "Game/GameEntities/MoleEntity.h"
#include <GameEngine/EntitySystem/Components/TextComponent.h>

using namespace Game;

static const int N_ROW = 3;
static const int N_COL = 3;

static const float DISTANCE_BETWEEN_HOLES = 160.f; // pixel
static const sf::Vector2f TOP_LEFT_CORNER(100.f, 90.f);
static const sf::Vector2f HOLE_SIZE(60.f, 60.f);
static const sf::Vector2f MOLE_SIZE(60.f, 60.f);

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_backGround(nullptr)
	, m_CountDown(nullptr)
	, m_ScoreBoard(nullptr)
	, m_lastObstacleSpawnTimer(0.f)
	, m_isGameOver(false)
{
	m_player = new PlayerEntity();

	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(50.f, 50.f));
	m_player->SetSize(sf::Vector2f(40.f, 40.f));

	CreateCountDown();
	CreateBackGround();
	CreateMole();



	//Debug
	for (int a = 0; a < 3; ++a)
	{
		//SpawnNewRandomObstacles();
	}
}


GameBoard::~GameBoard()
{

}


void GameBoard::Update()
{
	float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();
	if (!m_isGameOver)
	{
		m_lastObstacleSpawnTimer -= dt;
		if (m_lastObstacleSpawnTimer <= 0.f)
		{
			// SpawnNewRandomObstacles();
			// SpawnNewRandomTiledObstacles();
			UpdateMole();
		}

		// UpdateObstacles(dt);
		// int random = RandomFloatRange(1, 3);//

		int value = (int)dt % 10;

		UpdateBackGround();
		UpdatePlayerDying();

	}
}

void GameBoard::UpdateMole() {
		/* initialize random seed: */
	  srand (time(NULL));

	  /* generate secret number from 0 1 2 */
	  int row = rand() % N_ROW;
	  int col = rand() % N_COL;

		m_mole->SetPos(sf::Vector2f(TOP_LEFT_CORNER.x + row * DISTANCE_BETWEEN_HOLES,
			TOP_LEFT_CORNER.y + col * DISTANCE_BETWEEN_HOLES-20));
}


void GameBoard::UpdateObstacles(float dt)
{
	static float obstacleSpeed = 100.f;

	for (std::vector<GameEngine::Entity*>::iterator it = m_obstacles.begin(); it != m_obstacles.end();)
	{
		GameEngine::Entity* obstacle = (*it);
		sf::Vector2f currPos = obstacle->GetPos();
		currPos.x -= obstacleSpeed * dt;
		obstacle->SetPos(currPos);
		//If we are to remove ourselves
		if (currPos.x < -50.f)
		{
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(obstacle);
			it = m_obstacles.erase(it);
		}
		else
		{
			it++;
		}
	}
}


void GameBoard::UpdatePlayerDying()
{
	bool noGameOver = GameEngine::CameraManager::IsFollowCameraEnabled();

	if (noGameOver)
		return;

	static float xToPlayerDie = 0.f;
	if (m_player->GetPos().x < xToPlayerDie)
	{
		m_isGameOver = true;
	}
}


void GameBoard::SpawnNewRandomObstacles()
{
	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 50.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;

	static float minObstacleHeight = 50.f;
	static float maxObstacleHeight = 170.f;
	static float minObstacleWidth = 20.f;
	static float maxObstacleWidth = 40.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(RandomFloatRange(minObstacleWidth, maxObstacleWidth), RandomFloatRange(minObstacleHeight, maxObstacleHeight));

	SpawnNewObstacle(pos, size);

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewRandomTiledObstacles()
{
	static int minObstacleCount = 2;
	static int maxObstacleCount = 7;

	static float minNextSpawnTime = 0.3f;
	static float maxNextSpawnTime = 0.7f;

	static float minObstacleXPos = 350.f;
	static float maxObstacleXPos = 450.f;
	static float minObstacleYPos = 20.f;
	static float maxObstacleYPos = 450.f;

	sf::Vector2f pos = sf::Vector2f(RandomFloatRange(minObstacleXPos, maxObstacleXPos), RandomFloatRange(minObstacleYPos, maxObstacleYPos));
	sf::Vector2f size = sf::Vector2f(32.f, 32.f);

	int obstacleCount = (int)RandomFloatRange((float)minObstacleCount, (float)maxObstacleCount);
	for (int a = 0; a < obstacleCount; ++a)
	{
		SpawnNewObstacle(pos, size);
		pos.y += size.y;
	}

	m_lastObstacleSpawnTimer = RandomFloatRange(minNextSpawnTime, maxNextSpawnTime);
}


void GameBoard::SpawnNewObstacle(const sf::Vector2f& pos, const sf::Vector2f& size)
{
	ObstacleEntity* obstacle = new ObstacleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(obstacle);
	obstacle->SetPos(pos);
	obstacle->SetSize(sf::Vector2f(size.x, size.y));

	m_obstacles.push_back(obstacle);
}


void GameBoard::CreateBackGround()
{
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = bgEntity->AddComponent<GameEngine::SpriteRenderComponent>();
	GameEngine::SoundComponent* const sound = bgEntity -> AddComponent<GameEngine::SoundComponent>();
	GameEngine::BackgroundComponent* backgroundComponent = bgEntity->AddComponent<GameEngine::BackgroundComponent>();


	render->SetTexture(GameEngine::eTexture::BG);
	render->SetZLevel(0);
	bgEntity->SetPos(sf::Vector2f(250.f, 250.f));
	bgEntity->SetSize(sf::Vector2f(500.f, 500.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);

	m_backGround = bgEntity;
	//create the holes

	for (int i = 0; i < N_ROW; i++) {
		for (int j = 0; j < N_COL; j++) {
			GameEngine::Entity* hole = new GameEngine::Entity();
			GameEngine::SpriteRenderComponent* render = hole->AddComponent<GameEngine::SpriteRenderComponent>();

			//set position
			hole->SetPos(sf::Vector2f(TOP_LEFT_CORNER.x + i * DISTANCE_BETWEEN_HOLES,
				TOP_LEFT_CORNER.y + j * DISTANCE_BETWEEN_HOLES));
			hole->SetSize(sf::Vector2f(HOLE_SIZE.x, HOLE_SIZE.y));

			//set render texture
			render->SetFillColor(sf::Color::Red);
			render->SetTexture(GameEngine::eTexture::Tileset);
			render->SetZLevel(1);
			GameEngine::GameEngineMain::GetInstance()->AddEntity(hole);

			m_holes.push_back(hole);
		}
	}
}

void GameBoard::CreateMole() {

	MoleEntity* mole = new MoleEntity();
	GameEngine::GameEngineMain::GetInstance()->AddEntity(mole);

	/* initialize random seed: */
  srand (time(NULL));

  /* generate secret number from 0 1 2 */
  int row = rand() % N_ROW;
  int col = rand() % N_COL;

	mole->SetPos(sf::Vector2f(TOP_LEFT_CORNER.x + row * DISTANCE_BETWEEN_HOLES,
		TOP_LEFT_CORNER.y + col * DISTANCE_BETWEEN_HOLES-20));
	mole->SetSize(sf::Vector2f(MOLE_SIZE.x, MOLE_SIZE.y));

	m_mole = mole;
}

void GameBoard::UpdateBackGround()
{
	if (!m_backGround || !m_player)
		return;

	if (!GameEngine::CameraManager::IsFollowCameraEnabled())
		return;

	m_backGround->SetPos(m_player->GetPos());
}

void Game::GameBoard::CreateCountDown()
{
	GameEngine::Entity* CountDown = new GameEngine::Entity();
	GameEngine::TextComponent* render = CountDown->AddComponent<GameEngine::TextComponent>();

	render->SetFont("Resources/fonts/arial.ttf");
	render->SetText("Score", 20, sf::Color::Black);
	render->SetZLevel(1);
	CountDown->SetPos(sf::Vector2f(10.f, 10.f));
	CountDown->SetSize(sf::Vector2f(100.f, 100.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(CountDown);

	m_CountDown = CountDown;
}

void Game::GameBoard::UpdateCountDown()
{

}

void Game::GameBoard::CreateScoreBoard()
{
}

void Game::GameBoard::UpdateScoreBoard()
{
}

