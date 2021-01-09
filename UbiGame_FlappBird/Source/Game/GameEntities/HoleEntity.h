#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/RenderComponent.h"

namespace Game
{

	class HoleEntity : public GameEngine::Entity
	{
	public:
		HoleEntity();
		~HoleEntity();

		virtual void OnAddToWorld() override;
		virtual void OnRemoveFromWorld() override;

	protected:
		GameEngine::RenderComponent* m_renderComponent;
	};
}
