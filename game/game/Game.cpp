#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

Manager manager;
auto& player(manager.addEntity());

const char* mapfile = "assets/tiles2.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnimies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnimies));
auto& colliders(manager.getGroup(groupColliders));

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "subsystems initiaized" << std::endl;


		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "window created..." << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderererer created..." << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
	
	map = new Map();

	Map::LoadMap("assets/map3.map", 25, 20);

	player.addComponents<TransformComponent>(400.0f, 150.0f,32,32,2);
	player.addComponents<SpriteComponent>("assets/boi_multi.png",true);
	player.addComponents<KeyboardController>();
	player.addComponents<ColliderComponent>("player");
	player.addGroup(groupPlayers);
}


void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}

}

void Game::update()
{
	manager.refresh();
	manager.update();
	
	

	//Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	//int pSpeed = player.getComponent<TransformComponent>().speed;

	if(player.getComponent<TransformComponent>().position.x > 800)
	{
		for (auto t : tiles) 
		{
			t->getComponent<TileComponent>().destRect.x += -800;
		}
		player.getComponent<TransformComponent>().position.x += -800;
	}

	if (player.getComponent<TransformComponent>().position.x < 0)
	{
		for (auto t : tiles)
		{
			t->getComponent<TileComponent>().destRect.x += 800;
		}
		player.getComponent<TransformComponent>().position.x += 800;
	}
	
	if(player.getComponent<TransformComponent>().position.y > 640)
	{
		for (auto t : tiles) 
		{
			t->getComponent<TileComponent>().destRect.y += -640;
		}
		player.getComponent<TransformComponent>().position.y += -640;
	}

	if (player.getComponent<TransformComponent>().position.y < 0)
	{
		for (auto t : tiles)
		{
			t->getComponent<TileComponent>().destRect.y += 640;
		}
		player.getComponent<TransformComponent>().position.y += 640;
	}


}



void Game::render()
{
	SDL_RenderClear(renderer);
	
	for (auto& t : tiles)
	{
		t->draw();
	}
	
	for (auto& p : players)
	{
		p->draw();
	}
	
	for (auto& e : enemies)
	{
		e->draw();
	}
	
	for (auto& c : colliders)
	{
		c->draw();
	}


	SDL_RenderPresent(renderer);
	
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "game cleaned" << std::endl;
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) 
{
	auto& tile(manager.addEntity());
	tile.addComponents<TileComponent>(srcX, srcY, xpos, ypos, mapfile); //////
	tile.addGroup(groupMap);
}