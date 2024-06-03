@echo off

cls


set PROTEUS_PATH=C:\Proteus-Pro-7.7-SP2\MODELS
if not exist "%PROTEUS_PATH%" goto :ERR


set DLL_DIR=Debug
if exist Release set DLL_DIR=Release
set DLL_PATH=%DLL_DIR%\ILI9325.DLL

echo Instaling %DLL_DIR% . . .
if not exist %DLL_PATH% goto :ErrDll
echo copy /y /b  %DLL_PATH%  %PROTEUS_PATH%\ILI9325.DLL
     copy /y /b  %DLL_PATH%  %PROTEUS_PATH%\ILI9325.DLL
echo Done!

goto :EOF


:ERR
echo Could not find %PROTEUS_PATH%
echo Check Proteus installation path and update the PROTEUS_PATH variable.
goto :EOF


:ErrDll
echo Dll path `%DLL_PATH%' not found!
echo Build the project to make .dll files.
goto :EOF


:EOF

