#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"


//This one allows for movement and obstacle detection,
class PlayerHitCountComponent : public GameEngine::CollidableComponent
{
  public:
  	PlayerHitCountComponent();
  	virtual ~PlayerHitCountComponent();

  	void OnAddToWorld() override;
  	void OnRemoveFromWorld() override;

  	void Update() override;
    int getHitCount();

  protected:
    int hitCount;
};
