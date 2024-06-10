@echo off

call :CleanDir . %1%
goto:EOF



:CleanDir
del /q %1\*.aux
del /q %1\*.acn
del /q %1\*.idx
del /q %1\*.toc
del /q %1\*.xdy
del /q %1\*.acr
del /q %1\*.alg
del /q %1\*.aux
del /q %1\*.bbl
del /q %1\*.blg
del /q %1\*.blo
del /q %1\*.bls
del /q %1\*.glg
del /q %1\*.glo
del /q %1\*.gls
del /q %1\*.glsdefs
del /q %1\*.idx
del /q %1\*.ind
del /q %1\*.log
del /q %1\*.out
del /q %1\*.toc
del /q %1\*.xdy

del /q %1\*.synctex
del /q %1\*.lof
del /q %1\*.lot
del /q %1\*.mw
del /q %1\*.bak
del /q %1\*.ilg

del /q %1\.*.ptd
del /q /aH %1\.*.ptd
del /q %1\bidiTeXMaker.txt

del /q %1\*.synctex(busy)
del /q %1\*.synctex.gz
del /q %1\*.tar.gz

REM Cleaning pdf files.
IF "%2%" == "--all" (
	echo Cleaning pdfs . . .
	del /q %1\*.pdf
)

echo `%1' cleaned!
:EOF

