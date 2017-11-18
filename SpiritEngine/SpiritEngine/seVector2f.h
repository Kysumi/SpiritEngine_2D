#ifndef SE_VECTOR2F_H
#define SE_VECTOR2F_H
#include "SFML/System/Vector2.hpp"
#include "Box2D/Box2D.h"

namespace se
{
	class Vector2f :
		public sf::Vector2f
	{
	public:
		Vector2f();
		Vector2f(float x, float y);
		~Vector2f();

		static se::Vector2f Zero;

		float getMagnitude();
		void setMagnitude(float mag);

		float getAngle();
		void setAngle(float angle);

		void normalize();

		void perpcw();
		void perpccw();

		float product(se::Vector2f b);
        
        void scale(se::Vector2f b);

		/**
		* Converts the pixel location to the  
		* Box2d location (/PPM)
		*/
		b2Vec2 toB2Vect();
        
        /**
        * Converts click location on their screen to the original resolution 
        * for the world location
        */
        se::Vector2f getScaled();
	};
}
#endif // !SE_VECTOR2F_H
