#pragma once
#ifndef SEMOUSE_H
#define SEMOUSE_H

#include <Box2D/Box2D.h>
#include "seVector2f.h"

namespace se {

	/**
	* Mouse Pos
	*/
	class Mouse
	{
	public:
		Mouse();
		~Mouse();
		static void onDown(se::Vector2f pos, b2World *world, b2Body *ground);
		static void onUp(b2World *world);
		static void update(se::Vector2f pos);

	private:
		static b2MouseJointDef def;
		static b2MouseJoint* mouseJoint;
	};


	/**
	* Callback for mouse pos query
	*/
	class QueryCallback : public b2QueryCallback
	{
	public:
		/**
		* Pass the position of where you want to check for collision
		*/
		QueryCallback(b2Vec2 p);
		bool ReportFixture(b2Fixture* fixture);

		b2Vec2 pos;
		b2Fixture* fixture;
	};
}

#endif // SEMOUSE_H

