#ifndef BOXSHAPE_H
#define BOXSHAPE_H

#include "seShape.h"
#include <SFML/Graphics.hpp>
#include "Renderable.h"
#include "seVector2f.h"

namespace se {

	class BoxShape : public se::Shape, public se::Rendering::Renderable
	{
	public:
		BoxShape();
		/**
		* All done in pixels now
		*/
		BoxShape(b2BodyType bt, se::Vector2f size, float weight, float friction, float bounce);
		~BoxShape();

		void resetPosition(b2World & world);
		virtual void update() override;
		virtual void setPostion(se::Vector2f pos) override;
		
        virtual void setSize(float x, float y) override;
        
		virtual void setWorld(b2World & world) override;
		virtual se::Vector2f getPosition() override;
		virtual void setColor(sf::Color c) override;

	private:
		sf::RectangleShape _shape;

		// Inherited via Renderable
		virtual void Draw(sf::RenderTarget * target) override;
	};
}

#endif // !BOXSHAPE_H


