@echo off


call :CleanDir .
call :CleanDir Game
call :CleanDir Graphics
call :CleanDir Joystick
call :CleanDir LCD-Driver
call :CleanDir RTC

echo "Done."
REM pause
goto :EOF


:CleanDir
if exist  "%1\*.c!"    del   /f /q "%1\*.c!"
if exist  "%1\*.c@"    del   /f /q "%1\*.c@"
if exist  "%1\*.c_cbf" del   /f /q "%1\*.c_cbf"
if exist  "%1\*.c~"    del   /f /q "%1\*.c~"
if exist  "%1\*.fct"   del   /f /q "%1\*.fct"
if exist  "%1\*.h!"    del   /f /q "%1\*.h!"
if exist  "%1\*.h_cbf" del   /f /q "%1\*.h_cbf"
if exist  "%1\*.hdr"   del   /f /q "%1\*.hdr"
if exist  "%1\*.h~"    del   /f /q "%1\*.h~"
if exist  "%1\*.i"     del   /f /q "%1\*.i"
if exist  "%1\*.map"   del   /f /q "%1\*.map"
if exist  "%1\*.prj~"  del   /f /q "%1\*.prj~"
if exist  "%1\EXE"     rmdir /s /q "%1\EXE"
if exist  "%1\Linker"  rmdir /s /q "%1\Linker"
if exist  "%1\List"    rmdir /s /q "%1\List"
if exist  "%1\Obj"     rmdir /s /q "%1\Obj"
:goto :EOF


:EOF

