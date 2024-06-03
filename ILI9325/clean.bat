@echo off


cls

set PRJ_NAME=ILI9325


if exist .vs\%PRJ_NAME%\v15\ipch           rmdir /q /s .vs\%PRJ_NAME%\v15\ipch
if exist .vs\%PRJ_NAME%\v15\Browse.VC.*    del   /q /s .vs\%PRJ_NAME%\v15\Browse.VC.*
if exist .vs\%PRJ_NAME%\v15\Solution.VC.*  del   /q /s .vs\%PRJ_NAME%\v15\Solution.VC.*


call :RmRelDeb .
call :RmRelDeb %PRJ_NAME%

if "%1%" == "nopause" (
	echo The `nopuase' option received!
	goto :EOF
)

echo Paused for an input!
pause
goto :EOF



:RmRelDeb
if exist %1\Debug    rmdir /q /s %1\Debug
if exist %1\Release  rmdir /q /s %1\Release
if exist %1\bin      rmdir /q /s %1\bin
goto :EOF


:ClrBuildTemps
if exist %1\*.ilk   del /q /s %1\*.ilk
if exist %1\*.iobj  del /q /s %1\*.iobj
if exist %1\*.ipdb  del /q /s %1\*.ipdb
if exist %1\*.lib   del /q /s %1\*.lib
if exist %1\*.log   del /q /s %1\*.log
if exist %1\*.pdb   del /q /s %1\*.pdb
goto :EOF


:EOF

