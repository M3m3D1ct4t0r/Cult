#pragma once

#include "Components.h"
#include "SDL.h"
#include <string>


class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	TransformComponent* transform;
	


	ColliderComponent(std::string t)
	{
		tag = t;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponents<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override
	{
		if(tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		
		//collider.x = Game::pVel.x  
		//collider.x = Game::pVel.x  

	}


};