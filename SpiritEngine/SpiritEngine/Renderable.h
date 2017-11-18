#ifndef SE_RENDERABLE_H
#define SE_RENDERABLE_H
#include <SFML/Graphics.hpp>
namespace se
{

	namespace Rendering
	{
		class Renderable
		{
		public:
			Renderable();
			~Renderable();
			virtual void Draw(sf::RenderTarget * target) = 0;
		};
	}

}
#endif // !SE_RENDERABLE_H

