#ifndef SE_INPUTMANAGER_H
#define SE_INPUTMANAGER_H
#include "Enums.h"

namespace se
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		static void setup();
		static void update();
		static void keyPressed(int key);
		static void keyReleased(int key);

		static bool isKeyDown(InputType key); //Debounce
		static bool isKeyDownRaw(InputType key); //No Debounce

		static InputType isInputType(int keyCode)
		{
			for (size_t i = INPUT_FIRST + 1; i < LAST_INPUT; i++)
			{
				if (Config::getSetting((InputType)i) == keyCode)
					return (InputType)i;
			}

			return LAST_INPUT;
		}

	private:
		static sf::Clock RunTime;
		static float MinDebounce;
		static bool KeyState[LAST_INPUT]; //True is down
		static long KeyDebounce[LAST_INPUT];

	};
}


#endif // !SE_INPUTMANAGER_H


