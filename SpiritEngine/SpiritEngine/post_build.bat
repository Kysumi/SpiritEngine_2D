@echo off 

SET SFML=SFML-2.4.2\bin
SET LUA=LuaJIT

set DEBUG_LIST=(%SFML%\sfml-system-d-2.dll %SFML%\sfml-window-d-2.dll %SFML%\sfml-graphics-d-2.dll)
set RELEASE_LIST=(%SFML%\sfml-system-2.dll %SFML%\sfml-window-2.dll %SFML%\sfml-graphics-2.dll)

set LibsFolder=%cd%\..\..\Libs
set DebugFolder=%cd%\..\Debug\
set ReleaseFolder=%cd%\..\Release\
set SEMAC=%cd%\..\..\SEMAC\SEMAC\

IF %1 == -release (
	echo Release Mode
	xcopy ".\Content" "%ReleaseFolder%Content\" /Y /S
	xcopy ".\Content" "%SEMAC%Content\" /Y /S
	for %%i in %RELEASE_LIST% do copy "%LibsFolder%\%%i" "%ReleaseFolder%"
)
IF %1 == -debug (
	echo Debug Mode
	xcopy ".\Content" "%DebugFolder%Content\" /Y /S
	xcopy ".\Content" "%SEMAC%Content\" /Y /S
	for %%i in %DEBUG_LIST% do copy "%LibsFolder%\%%i" "%DebugFolder%"
)


