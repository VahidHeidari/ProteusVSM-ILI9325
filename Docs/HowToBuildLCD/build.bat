@echo off

REM Build script for making paper from .tex files.

set TEX_FILE=HowToBuildLCD



set WEEK_DAY=%date:~0,3%
set DAY=%date:~7,2%
set MOUNTH=%date:~4,2%
set YEAR=%date:~10,4%
set COMB_DATE=%YEAR%%MOUNTH%%DAY%-%WEEK_DAY%

set TEX_FILE_DATE=%TEX_FILE%-%COMB_DATE%


pdflatex -synctex=1 -halt-on-error -file-line-error %TEX_FILE% &&	^
bibtex8 -W %TEX_FILE% &&											^
pdflatex -synctex=1 -halt-on-error -file-line-error %TEX_FILE% &&	^
pdflatex -synctex=1 -halt-on-error -file-line-error %TEX_FILE% &&	^
echo Done! &&														^
copy /b %TEX_FILE%.pdf /b %TEX_FILE_DATE%.pdf &&					^
del %TEX_FILE%.pdf &&												^
start %TEX_FILE_DATE%.pdf

REM Flash cmd window to prompt end of building.
python -c "import ctypes; ctypes.windll.user32.FlashWindow(ctypes.windll.kernel32.GetConsoleWindow(), True)"

