#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}


	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -1;
				sprite->Play("walkw");
				break;
			case SDLK_a:
				transform->velocity.x = -1;
				sprite->Play("walka");
				break;
			case SDLK_s:
				transform->velocity.y = 1;
				sprite->Play("walks");
				break;
			case SDLK_d:
				transform->velocity.x = 1;
				sprite->Play("walkd");
				break;
			case SDLK_SPACE:
				transform->scale = 4;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				sprite->Play("idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->Play("idle");
				break;
			case SDLK_SPACE:
				transform->scale = 2;
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}
};