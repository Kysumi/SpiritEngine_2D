#ifndef POLYGONSHAPE_H
#define POLYGONSHAPE_H

#include <SFML/Graphics.hpp>
#include "seShape.h"
#include "Renderable.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace se {

	class PolygonShape : public se::Shape, public se::Rendering::Renderable
	{
	public:
		PolygonShape();
		/**
		* Maximum number of sides is 8
		* Radius is in pixels
		*/
		PolygonShape(b2BodyType bt, float radius, float friction, int numSides);

		~PolygonShape();

		void setRadius(float radius);
		
		// Inherited via Shape
		virtual void update() override;
		virtual void setPostion(se::Vector2f position) override;
		virtual void setWorld(b2World & world) override;
		virtual se::Vector2f getPosition() override;
		virtual void setColor(sf::Color c) override;

	private:
		sf::CircleShape _shape;

		/**
		* Finds the starting angle
		*/
		float findAngle(int numSides, float centreAngle);
		/**
		* Fills the verts array with the cordinates 
		*/
		void createArray(int numSides, float startAngle, float centerAngle, float radius);

		b2Vec2 verts[8];

		// Inherited via Renderable
		virtual void Draw(sf::RenderTarget * target) override;
	};
}
#endif // !PolygonShape
