#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/Util/SoundManager.h"
namespace GameEngine
{
	class BackgroundComponent : public GameEngine::Component
	{
	public:
		BackgroundComponent();
		virtual ~BackgroundComponent();
		virtual void OnAddToWorld() override;
	private:
		GameEngine::SoundManager::SoundId m_backgroundSoundId;
	};
}