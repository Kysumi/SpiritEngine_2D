--[[
	Window Settings
]]--

WindowTitle = "Spirit Engine" --Now moved to locals
WindowHeight = 600
WindowWidth = 800
ShowFps = true

Language = "en"



--[[
	World Settings
]]--
--World scale for converting from meteres to pixels
PixelPerMeter = 30.0
TimeStep = 1 / 180.0
B2Velocity = 8
B2Position = 3


--[[
	User control settings
	Do we want to worry about converting it from string to keycode?
	Maybe later. see if there a cheat way otherwise i have to make a switch statement lel
	Or lookup table
]]--
Input_Debounce = 200 --ms

PlayerOne_Up = 22
PlayerOne_Down = 18
PlayerOne_Left = 0
PlayerOne_Right = 3
--PlayerOne_Jump = 57
--PlayerOne_Fire = 38
--PlayerOne_Crouch = 2
--PlayerOne_Strafe_Left = 16
--PlayerOne_Strafe_Right = 4

--PlayerTwo_Up = 74
--PlayerTwo_Down = 73
--PlayerTwo_Left = 0
--PlayerTwo_Right = 3
--PlayerTwo_Jump = 57
--PlayerTwo_Fire = 38
--PlayerTwo_Crouch = 2
--PlayerTwo_Strafe_Left = 16
--PlayerTwo_Strafe_Right = 4
