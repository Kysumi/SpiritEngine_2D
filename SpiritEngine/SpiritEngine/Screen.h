#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "seVector2f.h"

class Screen
{
public:
	Screen();
	~Screen();
    
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow *w) = 0;
    
    virtual void end() = 0;
    virtual void start() = 0;
    virtual void pause() = 0;
    
    bool isActive();
    void activate();
    void Deactivate();
    
    int drawOrder = 0;    
    
protected:
    se::Vector2f _size;
    bool _active;
    
    
};

#endif
