#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/AnimationComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/CollidablePhysicsComponent.h"
#include "Game/GameComponents/PlayerMovementComponent.h"
// #include "Game/GameComponents/PlayerHitCountComponent.h"

namespace Game
{

	class PlayerEntity : public GameEngine::Entity
	{
	public:
		PlayerEntity();
		~PlayerEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

		int getHitCount();

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
		PlayerMovementComponent*	 m_playerMovementComponent;
		GameEngine::CollidablePhysicsComponent*	 m_playerHitCountComponent;
		GameEngine::AnimationComponent* m_animComponent;
	};
}
