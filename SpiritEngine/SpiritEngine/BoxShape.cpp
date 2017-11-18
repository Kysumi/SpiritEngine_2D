#include "stdafx.h"
#include "BoxShape.h"

int n = 0;


///Initializes the boxshape obj
se::BoxShape::BoxShape()
{
}

/**
* Size is done in pixels
*/
se::BoxShape::BoxShape(b2BodyType bt, se::Vector2f size, float weight, float friction, float bounce)
{
	//Representation of the object
	_shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
	_shape.setSize(size);

	//Physical object	
	bodyDef.type = bt; 

	bodyShape.SetAsBox(size.toB2Vect().x / 2, size.toB2Vect().y / 2); //Remember b2d draws by halfs

	weight = (size.x * size.x) * 0.01f;
	
	/**
	*Paramaters for fixture
	*/
	bodyFix.shape = &bodyShape;
	bodyFix.density = weight; //Weight
	bodyFix.friction = friction; 
	bodyFix.restitution = bounce;
}

se::BoxShape::~BoxShape()
{

}

void se::BoxShape::setWorld(b2World &world)
{
	//Setting obj to world and applying the fixture to it
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&bodyFix);
}

se::Vector2f se::BoxShape::getPosition()
{
	se::Vector2f pos(_shape.getPosition().x, _shape.getPosition().y);
	return pos;
}

void se::BoxShape::setColor(sf::Color c)
{
	_shape.setFillColor(c);
}

void se::BoxShape::update()
{
	//Updating the visual of the box to the box2d copy
	b2Vec2 pos = body->GetPosition(); //Temp store saves two calls guess its better 
	_shape.setPosition(pos.x * se::Config::getSetting(PIXEL_PER_METER), pos.y * se::Config::getSetting(PIXEL_PER_METER));

	_shape.setRotation(body->GetAngle()*(180 / b2_pi));
}

void se::BoxShape::setPostion(se::Vector2f pos)
{
	_shape.setPosition(pos);
	_shape.setOrigin(_shape.getSize().x / 2, _shape.getSize().y / 2); //centering the sfml shape on b2d
	bodyDef.position.Set(pos.toB2Vect().x, pos.toB2Vect().y);
}

void se::BoxShape::setSize(float x, float y)
{
	_shape.setSize(sf::Vector2f(x , y ));

	_shape.setOrigin((float)x/2, (float)y/2);
	//bodyShape.SetAsBox(x/PPM, y/PPM); //Size?
}

void se::BoxShape::Draw(sf::RenderTarget * target)
{
	target->draw(_shape);
}
