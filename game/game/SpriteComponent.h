#pragma once

#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "Animation.h"
#include <Map>

class SpriteComponent : public Component
{
private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	
	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 4, 100);
		Animation walkd = Animation(1, 4, 100);
		Animation walka = Animation(2, 4, 100);
		Animation walks = Animation(3, 4, 100);
		Animation walkw = Animation(4, 4, 100);


		animations.emplace("idle", idle);
		animations.emplace("walkd", walkd);
		animations.emplace("walka", walka);
		animations.emplace("walkw", walkw);
		animations.emplace("walks", walks);

		Play("idle");

		setTex(path);
	}

	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path)
	{
		texture = textureManager::LoadTexture(path);
	}

	void init() override 
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		

	}
	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}
	void draw() override
	{
		textureManager::Draw(texture, srcRect, destRect);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};