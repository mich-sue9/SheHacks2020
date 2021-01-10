#include <stdlib.h>

#include "GameBoard.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
#include "GameEngine/EntitySystem/Components/BackgroundComponent.h"
#include "GameEngine/Util/CameraManager.h"
#include "Game/GameEntities/PlayerEntity.h"
#include "Game/GameEntities/MoleEntity.h"
#include <GameEngine/EntitySystem/Components/TextComponent.h>

using namespace Game;

static const int N_ROW = 3;
static const int N_COL = 3;

static const float DISTANCE_BETWEEN_HOLES = 160.f; // pixel
static const sf::Vector2f TOP_LEFT_CORNER(100.f, 90.f);
static const sf::Vector2f HOLE_SIZE(60.f, 60.f);
static const sf::Vector2f MOLE_SIZE(60.f, 60.f);

GameEngine::TextComponent* CountDownrender;
GameEngine::TextComponent* scoreRender;
sf::Time m_countDownTimer;
sf::Clock m_clock;

int countDownTime = 60;
bool isGameOver;
bool cleanGame;

GameBoard::GameBoard()
	: m_player(nullptr)
	, m_backGround(nullptr)
	, m_CountDown(nullptr)
	, m_ScoreBoard(nullptr)
	, m_lastObstacleSpawnTimer(0.f)
{
	m_player = new PlayerEntity();
	m_clock.restart();
	isGameOver = false;
	cleanGame = false;

	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_player);
	m_player->SetPos(sf::Vector2f(50.f, 50.f));
	m_player->SetSize(sf::Vector2f(40.f, 40.f));

	CreateCountDown();
	CreateScoreBoard();
	CreateBackGround();
	CreateMole();
}


GameBoard::~GameBoard(){}


void GameBoard::Update()
{

	if (!isGameOver)
	{
		UpdateCountDown();
		UpdateMole();
		UpdateBackGround();
		UpdateScoreBoard();
	}
	else if (!cleanGame){
		//Remove everything on the board
	    GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_player);
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_mole);
		GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_CountDown);
		//remove all the holes
		for (auto& hole : m_holes) {
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(hole);
		}

		//change the place of the score to center of the display
		m_ScoreBoard->SetPos(sf::Vector2f(150.f, 150.f));
		scoreRender->SetText("Score: " + std::to_string(m_player->getHitCount()), 50, sf::Color::Black);
		cleanGame = true;
	}
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

void GameBoard::UpdateMole() {
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number from 0 1 2 */
	int row = rand() % N_ROW;
	int col = rand() % N_COL;

	m_mole->SetPos(sf::Vector2f(TOP_LEFT_CORNER.x + row * DISTANCE_BETWEEN_HOLES,
		TOP_LEFT_CORNER.y + col * DISTANCE_BETWEEN_HOLES - 20));
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
	CountDownrender = CountDown->AddComponent<GameEngine::TextComponent>();
	//get time
	m_countDownTimer = m_clock.getElapsedTime();
	int time = (int)m_countDownTimer.asSeconds();

	//set text
	CountDownrender->SetFont("Resources/fonts/arial.ttf");
	CountDownrender->SetText("Time: "+ std::to_string(time), 20, sf::Color::Black);
	CountDownrender->SetZLevel(1);
	CountDown->SetPos(sf::Vector2f(10.f, 10.f));
	CountDown->SetSize(sf::Vector2f(100.f, 100.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(CountDown);

	m_CountDown = CountDown;
}

void Game::GameBoard::UpdateCountDown()
{
	m_countDownTimer = m_clock.getElapsedTime();
	int time = (int)m_countDownTimer.asSeconds() - 2;
	CountDownrender->SetText("Time: " + std::to_string(time), 20, sf::Color::Black);
	if (time >= countDownTime) {
		isGameOver = true;
	}
}

void Game::GameBoard::CreateScoreBoard()
{
	GameEngine::Entity* ScoreBoard = new GameEngine::Entity();
	scoreRender = ScoreBoard->AddComponent<GameEngine::TextComponent>();
	int score = m_player->getHitCount();
	scoreRender->SetFont("Resources/fonts/arial.ttf");
	scoreRender->SetText("Score: " + std::to_string(score), 20, sf::Color::Black);
	scoreRender->SetZLevel(1);
	ScoreBoard->SetPos(sf::Vector2f(300.f, 10.f));
	ScoreBoard->SetSize(sf::Vector2f(100.f, 100.f));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(ScoreBoard);

	m_ScoreBoard = ScoreBoard;
}

void Game::GameBoard::UpdateScoreBoard()
{
	int score = m_player->getHitCount();
	scoreRender->SetText("Score: " + std::to_string(score), 20, sf::Color::Black);
}
