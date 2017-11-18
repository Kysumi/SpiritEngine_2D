#ifndef SECIRCLESHAPE_H
#define SECIRCLESHAPE_H

#include "seShape.h"
#include "Renderable.h"
#include <SFML/Graphics.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace se {

	class CircleShape : public se::Shape, public se::Rendering::Renderable
	{
	public:
		CircleShape();
		CircleShape(b2BodyType bt, float radius,float friction);
		~CircleShape();

		virtual void update() override;
		virtual void setPostion(se::Vector2f position) override;
		virtual void setWorld(b2World & world) override;
		virtual se::Vector2f getPosition() override;
		virtual void setColor(sf::Color c) override;

	private:

		virtual void Draw(sf::RenderTarget * target) override;

		sf::CircleShape _shape;
		b2CircleShape _bodyShape;

	};
}



#endif // !SECIRCLESHAPE

