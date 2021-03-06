#include "MoleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

MoleEntity::MoleEntity()
{
	m_renderComponent = AddComponent<GameEngine::SpriteRenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	m_renderComponent->SetTexture(GameEngine::eTexture::BG2);
	m_renderComponent->SetZLevel(2);
	m_renderComponent->SetTileIndex(0, 0);

	AddComponent<GameEngine::CollidableComponent>();
}


MoleEntity::~MoleEntity()
{

}


void MoleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void MoleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
