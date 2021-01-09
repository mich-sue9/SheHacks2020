#include "BackgroundComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SoundComponent.h"
using namespace GameEngine;
BackgroundComponent::BackgroundComponent()
{
}
BackgroundComponent::~BackgroundComponent()
{
}
void BackgroundComponent::OnAddToWorld()
{
	if (GameEngine::SoundComponent* const soundComponent = GetEntity()->GetComponent<GameEngine::SoundComponent>())
	{
		m_backgroundSoundId = soundComponent->LoadSoundFromFile("Resources/snd/background.ogg");
		soundComponent->PlaySound(m_backgroundSoundId);
	}
}