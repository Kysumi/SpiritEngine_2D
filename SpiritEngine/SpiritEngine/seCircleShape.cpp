#include "stdafx.h"
#include "seCircleShape.h"


se::CircleShape::CircleShape() 
{

}

se::CircleShape::CircleShape(b2BodyType bt, float radius, float friction)
{
	//Representation of the object
	_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	_shape.setRadius(radius);

	//Setting bodyType
	bodyDef.type = bt;

	_bodyShape.m_radius = radius / se::Config::getSetting(PIXEL_PER_METER);
	
	/**
	* Calulating weight
	*/
	float weight = (M_PI * (radius * radius)) * 0.01f;//Config this shit
	
	/**
	 *Paramaters for fixture
	 */
	bodyFix.shape = &_bodyShape;
	bodyFix.density = weight;
	bodyFix.friction = friction;
	bodyFix.restitution = 1.0f;
}

se::CircleShape::~CircleShape()
{

}

void se::CircleShape::update()
{
	//Updating the visual of the box to the box2d copy
	b2Vec2 pos = body->GetPosition(); //Temp store saves two calls guess its better 
	_shape.setPosition(pos.x * se::Config::getSetting(PIXEL_PER_METER), pos.y * se::Config::getSetting(PIXEL_PER_METER));

	_shape.setRotation(body->GetAngle()*(180 / b2_pi));
}

void se::CircleShape::setPostion(se::Vector2f pos)
{
	_shape.setPosition(pos);
	_shape.setOrigin(_shape.getRadius(), _shape.getRadius());
	bodyDef.position.Set(pos.toB2Vect().x, pos.toB2Vect().y);
}

void se::CircleShape::setWorld(b2World & world)
{
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&bodyFix);
}

se::Vector2f se::CircleShape::getPosition()
{
	se::Vector2f pos(_shape.getPosition().x, _shape.getPosition().y);
	return pos;
}

void se::CircleShape::setColor(sf::Color c)
{
	_shape.setFillColor(c);
}

void se::CircleShape::Draw(sf::RenderTarget * target)
{
	target->draw(_shape);
}
