#include "HoleEntity.h"

#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <SFML/Graphics.hpp>

using namespace Game;

HoleEntity::HoleEntity()
{
	m_renderComponent = AddComponent<GameEngine::RenderComponent>();
	m_renderComponent->SetFillColor(sf::Color::Red);
	// m_renderComponent->SetTexture(GameEngine::eTexture::Tileset);
	m_renderComponent->SetZLevel(2);

	AddComponent<GameEngine::CollidableComponent>();
}


HoleEntity::~HoleEntity()
{

}


void HoleEntity::OnAddToWorld()
{
	Entity::OnAddToWorld();
}


void HoleEntity::OnRemoveFromWorld()
{
	Entity::OnRemoveFromWorld();
}
