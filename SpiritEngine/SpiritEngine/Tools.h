#ifndef SE_TOOLS_H
#define SE_TOOLS_H

#include <stdio.h>
#include <iostream>
#include "RenderManager.h"
#include "seVector2f.h"
#include "Config.h"
#include "Enums.h"

namespace se {

	class Tools
	{
        
        static sf::Clock elapsed;
        static float lastTime;

	public:
		Tools() {};
		~Tools() {};

		static void Print(std::string str, bool console = true) {
			std::cout << str << std::endl;
		}
        
        static float getFPS()
        {
            float currentTime = elapsed.restart().asSeconds();
            float fps = 1.f / (currentTime - lastTime);
            lastTime = currentTime;
            
            return  fps;
        }
	private:

	};
    
    
}


#endif // !SE_TOOLS_H
