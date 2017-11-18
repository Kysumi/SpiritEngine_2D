#include "stdafx.h"
#include "seVector2f.h"
#include <math.h>

namespace se
{
	se::Vector2f Zero = se::Vector2f(0,0);

	Vector2f::Vector2f() : sf::Vector2f(){}
	Vector2f::Vector2f(float x, float y) : sf::Vector2f(x,y){}
	Vector2f::~Vector2f(){}

	float Vector2f::getMagnitude()
	{		
		return sqrt(x * x + y * y);
	}

	void Vector2f::setMagnitude(float mag)
	{
		float angle = getAngle();
		
		x = cos(angle) * mag;
		y = sin(angle) * mag;
	}
	
	float Vector2f::getAngle()
	{
		return atan2f(y, x);
	}

	void Vector2f::setAngle(float angle)
	{
		float mag = getMagnitude();

		x = cos(angle) * mag;
		y = sin(angle) * mag;

	}
	
	void Vector2f::normalize()
	{
		x /= getMagnitude();
		y /= getMagnitude();
	}

	void Vector2f::perpcw()
	{
		float vX = x;
		float vY = y;
		x = 0 - vY;
		y = vX;
	}

	void Vector2f::perpccw()
	{
		float vX = x;
		float vY = y;
		x = y;
		y = -vX;
	}

	float Vector2f::product(se::Vector2f b)
	{
		return x * b.x + y * b.y;
	}
    
    void Vector2f::scale(se::Vector2f b)
    {
        x *= b.x;
        y *= b.y;
    }

    b2Vec2 Vector2f::toB2Vect()
	{
		float ppm = se::Config::getSetting(se::Config_Float::PIXEL_PER_METER);
		return b2Vec2(x / ppm, y / ppm);
	}
    
    se::Vector2f Vector2f::getScaled()
    {
        float scaleX, scaleY;
        se::Vector2f position(x,y);
        
        sf::Vector2u curSize = g_RenderManager.GetRenderWindow()->getSize();
        se::Vector2f origSize = se::Vector2f(Config::getSetting(WINDOW_WIDTH), Config::getSetting(WINDOW_HEIGHT));
        
        scaleX = curSize.x / origSize.x;
        scaleY = curSize.y / origSize.y;
        
        position.x /= scaleX;
        position.y /= scaleY;
        return position;
    }
}
