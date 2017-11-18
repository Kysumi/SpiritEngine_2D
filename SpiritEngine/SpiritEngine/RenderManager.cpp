#include "stdafx.h"
#include "RenderManager.h"
#include "Renderable.h"
#include <chrono>
se::Rendering::Manager g_RenderManager;

namespace se
{
	namespace Rendering
	{

		Manager::Manager()
		{

		}


		Manager::~Manager()
		{

		}
		void Manager::Run()
		{
			IsOpen = true;
			//_renderingThread = new std::thread(&se::Rendering::Manager::Draw, &g_RenderManager);
			//_renderingThread->detach();
			Draw();
		}

		void Manager::Setup()
		{
			int x = se::Config::getSetting(se::Config_Int::WINDOW_WIDTH);
			
			_window = new sf::RenderWindow(sf::VideoMode(se::Config::getSetting(se::Config_Int::WINDOW_WIDTH),
														 se::Config::getSetting(se::Config_Int::WINDOW_HEIGHT),
														 32),
														 se::Localization::getLocal("Title"));
		}

		void Manager::Draw()
		{
			
			//float sleep = 1 / 120.0f;
			//while (_window->isOpen()) {
			//		Mutex.lock(); //Locking it so it will hang here untill objects is not longer being edited, then draw instantly
					//IsOpen = true;
					_window->clear();
					for (size_t i = 0; i < _objects.size(); i++)
					{
						((se::Rendering::Renderable*)_objects[i])->Draw(_window);// now just to prerender lel
					}

					_window->display();

					//Mutex.unlock();
					//std::this_thread::sleep_for(std::chrono::milliseconds(8));
			
			//}

			//IsOpen = false;

		}

	}
}
