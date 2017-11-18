#ifndef SE_ENUMS_H
#define SE_ENUMS_H

namespace le
{
	enum LuaDataType {
		UKNOWN = 0,
	};
}

namespace se
{
	enum Config_String
	{
		WINDOW_TITLE = 0,
		LANGUAGE_LOCALIZATION,
		LAST_STRING_CONFIG //must stay at the end for creating the arrays.
	};
	enum Config_Int
	{
		WINDOW_WIDTH = 0,
		WINDOW_HEIGHT,
		B2_VELOCITY,
		B2_POSITION,
		INPUT_DEBOUNCE,
		LAST_INT_CONFIG //must stay at the end for creating the arrays.
	};
	enum Config_Float
	{
		PIXEL_PER_METER = 0,
		TIMESTEP,
		LAST_FLOAT_CONFIG //must stay at the end for creating the arrays.
	};
	enum Config_Boolean
	{
		SHOW_FPS = 0,
		LAST_BOOLEAN_CONFIG //must stay at the end for creating the arrays.
	};


	enum InputType 
	{
		INPUT_FIRST = LAST_INT_CONFIG + 1,
		P1_UP,
		P1_DOWN,
		P1_LEFT,
		P1_RIGHT,
		P1_JUMP,
		P1_FIRE,
		P1_CROUCH,
		P1_STRAFE_LEFT,
		P1_STRAFE_RIGHT,
	

		P2_UP,
		P2_DOWN,
		P2_LEFT,
		P2_RIGHT,
		P2_JUMP,
		P2_FIRE,
		P2_CROUCH,
		P2_STRAFE_LEFT,
		P2_STRAFE_RIGHT,


		LAST_INPUT //must stay at the end for creating the arrays.
	};
}



#endif // !SE_ENUMS_H
