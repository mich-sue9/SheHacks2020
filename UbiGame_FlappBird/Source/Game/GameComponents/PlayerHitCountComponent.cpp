#include "PlayerHitCountComponent.h"

#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"

#include <vector>
#include <iostream>

using namespace GameEngine;

PlayerHitCountComponent::PlayerHitCountComponent()
{
	hitCount = 0;
}


PlayerHitCountComponent::~PlayerHitCountComponent()
{

}


void PlayerHitCountComponent::OnAddToWorld()
{

}


void PlayerHitCountComponent::OnRemoveFromWorld()
{

}

void PlayerHitCountComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;

		AABBRect myBox = GetWorldAABB();
		// make the box slightly bigger so there's some overlap
		int epsilon = 3;
		myBox.left -= epsilon;
		myBox.top -= epsilon;
		myBox.height += epsilon;
		myBox.width += epsilon;

		std::cout << "myBox.left = " << myBox.left << std::endl;
		std::cout << "myBox.top = " << myBox.top << std::endl;

		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection))
		{
			if (PlayerHitCountComponent* component =
										GetEntity()->GetComponent<PlayerHitCountComponent>()){
				hitCount++;
				// std::cout << "Hit Count = " << hitCount << std::endl;
			}
		}
	}
}

int PlayerHitCountComponent::getHitCount() {
	return hitCount;
}
