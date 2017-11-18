#ifndef SE_RENDERMANAGER_H
#define SE_RENDERMANAGER_H

#include <thread>
#include <mutex>

namespace se
{
	namespace Rendering
	{
        
        class Renderable;
		class Manager
		{
		public:
			Manager();
			~Manager();
			sf::RenderWindow * GetRenderWindow() { return _window; };
            void RegisterRenderable(Renderable * renderable) { _objects.push_back(renderable); };
			void Run();
			void Setup();
			bool IsOpen = false;
			std::mutex Mutex;


		private:
			void Draw();
			std::vector<Renderable *> _objects;
			sf::RenderWindow* _window;
			std::vector<sf::RenderTexture *> _layers;
			std::thread * _renderingThread;

		};


	}
    
}

extern se::Rendering::Manager g_RenderManager;
#endif // !SE_RENDERMANAGER_H
