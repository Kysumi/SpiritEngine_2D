#include "stdafx.h"
#include "InputManager.h"

bool se::InputManager::KeyState[LAST_INPUT];
long se::InputManager::KeyDebounce[LAST_INPUT];
//std::map<se::InputType, bool> se::InputManager::LastState;
float se::InputManager::MinDebounce = 0;
sf::Clock se::InputManager::RunTime;


se::InputManager::InputManager()
{

}


se::InputManager::~InputManager()
{

}

void se::InputManager::setup()
{
	MinDebounce = Config::getSetting(INPUT_DEBOUNCE);


	for (size_t i = INPUT_FIRST+1; i < LAST_INPUT; i++)
	{
		int keyCode = Config::getSetting((InputType)i);

		KeyDebounce[(InputType)i] = 0;
		KeyState[(InputType)i] = false;
		//LastState[(InputType)i] = false;

	}

}

void se::InputManager::update()
{
	//for (size_t i = INPUT_FIRST; i < LAST_INPUT; i++)
	//{
	//	int keyCode = Config::getSetting((InputType)i);

	//	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyCode))
	//		KeyState[keyCode] = true;

	//}

}

void se::InputManager::keyPressed(int key)
{
	if(isInputType(key) != LAST_INPUT)
		KeyState[isInputType(key)] = true;
}

void se::InputManager::keyReleased(int key)
{
	if (isInputType(key) != LAST_INPUT)
		KeyState[isInputType(key)] = false;
}

bool se::InputManager::isKeyDown(InputType key)
{
	InputType keyCode = key;

	if (KeyState[keyCode] && ( RunTime.getElapsedTime().asMilliseconds() - KeyDebounce[keyCode]) >= MinDebounce) 
	{
		KeyDebounce[keyCode] = RunTime.getElapsedTime().asMilliseconds();
		return true;
	}

	return false;
}

bool se::InputManager::isKeyDownRaw(InputType key)
{
	InputType keyCode = key;
	return KeyState[keyCode];
}
