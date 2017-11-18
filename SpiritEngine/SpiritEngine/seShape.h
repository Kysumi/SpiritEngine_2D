#ifndef SESHAPE_H
#define SESHAPE_H

#include <Box2D/Box2D.h>
#include "seVector2f.h"
#include <SFML/Graphics.hpp>

namespace se {

	class Shape
	{
	public:
		Shape() {};
		~Shape() {};

		/**
		* Updates the visual representation of the object
		*/
		virtual void update() = 0;
		/**
		* Sets size of the shape both box2d and sfml
		*/
		virtual void setSize(float x, float y) {};
		/**
		* Sets shapes position both in sfml and box2d
		*/
		virtual void setPosition(int x, int y)
		{
			se::Vector2f pos(x, y);
			setPostion(pos);
		};
		/**
		* Sets shapes position both in sfml and box2d
		*/
		virtual void setPosition(float x, float y)
		{
			se::Vector2f pos(x, y);
			setPostion(pos);
		};
		/**
		* Sets shapes position both in sfml and box2d
		*/
		virtual void setPostion(se::Vector2f position) = 0;
		/**
		* For setting the shape to the Box2d world
		*/
		virtual void setWorld(b2World &world) = 0;
		/**
		* Gets the shapes position in pixels
		*/
		virtual se::Vector2f getPosition() = 0;
		/**
		* For setting the color of the SFML shape
		*/
        virtual void setColor(sf::Color c) = 0;
		/**
		* Gets the box2d body for manipulation
		*/
		virtual b2Body* getBox2dBody()
		{
			return body;
		};
		
	protected:

		b2Body *body;
		b2BodyDef bodyDef;
		b2PolygonShape bodyShape;
		b2FixtureDef bodyFix;
	};
		
}


#endif // !SESHAPE_H
