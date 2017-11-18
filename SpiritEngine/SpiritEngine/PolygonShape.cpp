#include "stdafx.h"
#include "PolygonShape.h"
#include <math.h>


se::PolygonShape::PolygonShape()
{

}

se::PolygonShape::PolygonShape(b2BodyType bt, float radius, float friction, int numSides)
{
	//Representation of the object
	_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	_shape.setRadius(radius);
	
	if(numSides == 4) //Stopping boxes from being made
		numSides = 5;
	
	_shape.setPointCount(numSides); //sfml representaion

	float centreAngle = 2 * M_PI / numSides;

	//Creates the points in the verts array
	createArray(numSides, findAngle(numSides, centreAngle), centreAngle, radius / se::Config::getSetting(PIXEL_PER_METER));

	//Physical object	
	bodyDef.type = bt;

	//http://www.iforce2d.net/b2dtut/fixtures
	bodyShape.Set(verts, numSides);
	
	/**
	* Finding area of polygon
	*/
	float weight = (((radius * radius) * numSides * sin(360/numSides)) / 2) * 0.08f;//Config this shit
	
	/**
	*Paramaters for fixture
	*/
	bodyFix.shape = &bodyShape;
	bodyFix.density = weight; 
	bodyFix.friction = friction;
	bodyFix.restitution = 0;
}


se::PolygonShape::~PolygonShape()
{

}

void se::PolygonShape::setRadius(float radius)
{
	_shape.setRadius(radius);
}

void se::PolygonShape::update()
{
	//Updating the visual of the box to the box2d copy
	b2Vec2 pos = body->GetPosition(); //Temp store saves two calls guess its better 
	_shape.setPosition(pos.x * se::Config::getSetting(PIXEL_PER_METER), pos.y * se::Config::getSetting(PIXEL_PER_METER));

	_shape.setRotation(body->GetAngle()*(180 / b2_pi));
}

void se::PolygonShape::setPostion(se::Vector2f pos)
{
	_shape.setPosition(pos);
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());
	bodyDef.position.Set(pos.toB2Vect().x, pos.toB2Vect().y);
}

void se::PolygonShape::setWorld(b2World & world)
{
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&bodyFix);
}

se::Vector2f se::PolygonShape::getPosition()
{
	se::Vector2f pos(_shape.getPosition().x, _shape.getPosition().y);
	return pos;
}

void se::PolygonShape::setColor(sf::Color c)
{
	_shape.setFillColor(c);
}

float se::PolygonShape::findAngle(int numSides, float centreAngle)
{
	float startAngle;
		if (numSides % 2 == 0)
		startAngle = M_PI / 2 - centreAngle / 2;
	else
		startAngle = M_PI / 2;

	return startAngle;
}

void se::PolygonShape::createArray(int numSides, float startAngle, float centerAngle, float radius)
{
	for (int i = 0; i < numSides; i++)
	{
		float ang = startAngle + (i * centerAngle);
		//The zero is centre point
		float x = 0 + radius * cos(ang);
		float y = 0 - radius * sin(ang);

		verts[i].Set(x, y);
	}
}

void se::PolygonShape::Draw(sf::RenderTarget * target)
{
	target->draw(_shape);
}
