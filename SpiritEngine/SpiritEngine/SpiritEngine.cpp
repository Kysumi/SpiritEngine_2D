// SpiritEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "BoxShape.h"
#include "RenderManager.h"
#include "PolygonShape.h"
#include "Box2D/Box2D.h"
#include "seMouse.h"
#include "seCircleShape.h"

extern se::Rendering::Manager g_RenderManager;
const int PPM = 30;

int main() {

	bool pausedStep = true;
	
	se::Config::load();
	se::Content::setup();
	se::Localization::load();
	g_RenderManager.Setup();
	se::InputManager::setup();
	
	g_RenderManager.GetRenderWindow()->setVerticalSyncEnabled(true);

	se::g_Console.setup();

	b2Vec2 gravity(0.0f,0.9f);
	b2World world(gravity);

	/**
	* Want to move this stuff out asap.
	*/

	// The green box in scene
	se::BoxShape groundShape(b2BodyType::b2_staticBody, se::Vector2f(800, 20), 0, 0.5,0.5);
	groundShape.setPosition(400, 600); 
	groundShape.setWorld(world);
	groundShape.setColor(sf::Color::Green);

	se::BoxShape groundShape1(b2BodyType::b2_staticBody, se::Vector2f(20, 100000), 0, 0.5, 0.5);
	groundShape1.setPosition(0, -49390);
	groundShape1.setWorld(world);
	groundShape1.setColor(sf::Color::Green);

	se::BoxShape groundShape2(b2BodyType::b2_staticBody, se::Vector2f(20, 100000), 0, 0.5, 0.5);
	groundShape2.setPosition(800, -49390);
	groundShape2.setWorld(world);
	groundShape2.setColor(sf::Color::Green);
	
	const int boxes = 10;
	const int polys = 10;
	const int circles = 10;
	float zoom = 1.0f;
	float zoomStep = 0.01f;

	se::BoxShape* box[boxes];
	for (int i = 0; i < circles; i++)
	{
		box[i] = new se::BoxShape(b2_dynamicBody, se::Vector2f(rand() % 10 + 15, rand() % 10 + 15), 0.5, 0.9, 0.5);
		box[i]->setPosition(700, 0 - i * 10);
		box[i]->setWorld(world);
	}

	se::CircleShape* circle[circles];
	for (int i = 0; i < circles; i++)
	{
		circle[i] = new se::CircleShape(b2_dynamicBody, rand() % 10 + 8, 0.8);
		circle[i]->setPosition(100, 0 - i * 10);
		circle[i]->setWorld(world);
	}

	se::PolygonShape* good[polys];
	for (int i = 0; i < polys; i++) 
	{
		good[i] = new se::PolygonShape(b2_dynamicBody, rand() % 10 + 8, 10.0f,rand() %6 + 3);
		good[i]->setPosition(400, 0 - i * 10);
		good[i]->setWorld(world);
	}
	
	/**
	* End of stuff to remove
	*/
	sf::Clock clock;

	float currentTime = clock.getElapsedTime().asMilliseconds();
	const int updateFPS = 60;
	const float dt = 1.0f / updateFPS;

	float elapsedTime = 0.0f;
	float accumulator = 0.0f;

	sf::View view(sf::FloatRect(0, 0, se::Config::getSetting(se::WINDOW_WIDTH), se::Config::getSetting(se::WINDOW_HEIGHT)));

	while (g_RenderManager.GetRenderWindow()->isOpen())
	{
		g_RenderManager.GetRenderWindow()->setView(view);
		
		if(se::Config::getSetting(se::SHOW_FPS))
			g_RenderManager.GetRenderWindow()->setTitle(se::Localization::getLocal("Title") + " - " +std::to_string(se::Tools::getFPS()));
		else
			g_RenderManager.GetRenderWindow()->setTitle(se::Localization::getLocal("Title"));
		
		sf::Event events;

		while (g_RenderManager.GetRenderWindow()->pollEvent(events))
		{
			switch (events.type)
			{
				case sf::Event::Closed:
					g_RenderManager.GetRenderWindow()->close();
					break;
				case sf::Event::KeyReleased:
					se::InputManager::keyReleased(events.key.code);
					break;
					
				case sf::Event::KeyPressed:
					se::InputManager::keyPressed(events.key.code);
					break;
					
				case sf::Event::Resized:
				{
					sf::View cView = g_RenderManager.GetRenderWindow()->getView();
					cView.setSize(events.size.width, events.size.height);
					break;
				}

				/**
				*	Mouse stuff
				*/
				case sf::Event::MouseButtonReleased:
					se::Mouse::onUp(&world);//Destroy the joint
					break;
					
				//{}For the scope
				case sf::Event::MouseButtonPressed:
				{
					sf::Vector2f pos = g_RenderManager.GetRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*g_RenderManager.GetRenderWindow()));
					se::Vector2f nPos = se::Vector2f(pos.x, pos.y);
					
					se::Mouse::onDown(nPos, &world, groundShape.getBox2dBody());
					break;
				}
				/**
				* Mouse end
				*/
			}
		}

		if (se::InputManager::isKeyDown(se::P1_JUMP))
			pausedStep = !pausedStep;

		if (se::InputManager::isKeyDown(se::P1_LEFT)) {
			se::Content::load("./Content/Assets/Textures/Logo.png");
			se::Content::load("./Content/Assets/Textures/pixle.png");
		}

		if (se::InputManager::isKeyDown(se::P2_UP))
			zoom -= zoomStep;
		if (se::InputManager::isKeyDown(se::P2_DOWN))
			zoom += zoomStep;
		if (se::InputManager::isKeyDown(se::P2_LEFT))
			zoom = 1.0f;

			view.zoom(zoom);

		if (se::InputManager::isKeyDown(se::P1_UP))
			if (se::Content::isLoaded("./Content/Assets/Textures/Logo.png", true))
				se::Tools::Print("Content Loaded");

		if (se::InputManager::isKeyDown(se::P1_RIGHT))
			se::Content::reload();		

		const int newTime = clock.getElapsedTime().asMilliseconds();
		float frameTime = static_cast<float> (newTime - currentTime) / 1000.0f;

		// Our orignal loops was right just needed this :/
		if (frameTime > 0.25f)
			frameTime = 0.25f;

		currentTime = newTime;
		accumulator += frameTime;

		// Logic update
		while (accumulator >= dt)
		{			
			elapsedTime += dt;
			accumulator -= dt;

			world.Step(dt, se::Config::getSetting(se::B2_VELOCITY), se::Config::getSetting(se::B2_POSITION));

			for (int i = 0; i < boxes; i++) {
				box[i]->update();
			}

			for (int i = 0; i < polys; i++) {
				good[i]->update();
			}

			for (int i = 0; i < circles; i++) {
				circle[i]->update();
			}
		}

		const float alpha = accumulator / dt;

		//World pos
		sf::Vector2f pos = g_RenderManager.GetRenderWindow()->mapPixelToCoords(sf::Mouse::getPosition(*g_RenderManager.GetRenderWindow()));
		se::Vector2f nPos(pos.x, pos.y);
		se::Mouse::update(nPos);
		
		g_RenderManager.Run();
	}

	return 0;
}
