#include "stdafx.h"
#include "seMouse.h"
#include <iostream>

b2MouseJointDef se::Mouse::def;
b2MouseJoint* se::Mouse::mouseJoint;

se::Mouse::Mouse()
{

}


se::Mouse::~Mouse()
{

}

void se::Mouse::onDown(se::Vector2f pos, b2World *world, b2Body *ground)
{
	//If the mouse joint is already active skip
	if (mouseJoint != NULL)
		return;
    
    pos.getScaled();

	b2Vec2 vect;
	b2AABB aabb;
	
	vect.Set(0.001f, 0.001f); //Setting box size my guess?
	aabb.lowerBound = pos.toB2Vect() - vect;
	aabb.upperBound = pos.toB2Vect() + vect;
	//Call back wrapper
    se::QueryCallback callback(pos.toB2Vect());
	
	//Query the world to see if the small box is on anything
	world->QueryAABB(&callback, aabb);

	//if a fixture has been found at mouse click location
	if (callback.fixture)
    {		se::Tools::Print("Clicked");
		b2Body* body = callback.fixture->GetBody();

		b2MouseJointDef mouseDef;

		mouseDef.bodyA = ground;
		mouseDef.bodyB = body;
		mouseDef.target = pos.toB2Vect(); //Interesting..
		mouseDef.maxForce = 1000.0f * body->GetMass();

		mouseJoint = (b2MouseJoint*)world->CreateJoint(&mouseDef);
		body->SetAwake(true);
	}
}

void se::Mouse::onUp(b2World *world)
{
	if (mouseJoint)//Checking to see if the mouse joint exists
	{
		world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
}

void se::Mouse::update(se::Vector2f pos)
{
	if (mouseJoint)
	{
		mouseJoint->SetTarget(pos.toB2Vect());
	}
}

se::QueryCallback::QueryCallback(b2Vec2 p)
{
	pos = p;
	fixture = NULL;
}

bool se::QueryCallback::ReportFixture(b2Fixture* f)
{
	b2Body* body = f->GetBody();
	if (body->GetType() == b2_dynamicBody)
	{
		bool inside = f->TestPoint(pos);
		if (inside)
		{
			fixture = f;

			// We are done, terminate the query.
			return false;
		}
	}

	// Continue the query.
	return true;
}
