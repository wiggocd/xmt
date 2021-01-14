@echo off

setlocal EnableDelayedExpansion

if "%1" == "tools" (
    GOTO :BuildTools
) else (
    GOTO :BuildSrc
)

:BuildSrc
set SRCDIR=src
set TOOLSDIR=tools
set RESOUTDIR=resource_inc
set CXX_IN=%SRCDIR%\main.cpp
set OUTDIR=bin
set OUT=%OUTDIR%\xmt.exe
set FLAGS=-m32 -static-libgcc -static-libstdc++ -static
set RESOURCES=src\scrpt_remove.bat
set BIN2C=%TOOLSDIR%\bin\bin2c.exe

if exist %OUTDIR% (
    rmdir /s /q %OUTDIR%
)

mkdir %OUTDIR%

if exist %RESOUTDIR% (
    rmdir /s /q %RESOUTDIR%
)

mkdir %RESOUTDIR%

if exist %OUTDIR% (
    for %%i in (%RESOURCES%) do (
        %BIN2C% -o %RESOUTDIR%\%%~ni".h" %%i
    )

    mkdir %OUTDIR%\obj

    g++ -c %CXX_IN% -o %OUTDIR%\obj\cxx.o
    g++ %FLAGS% bin\obj\* -o %OUT%
)

exit /B 0

:BuildTools
set SRCDIR=tools\src
set OUTDIR=tools\bin

rmdir /s /q %OUTDIR%
mkdir %OUTDIR%

if exist %OUTDIR% (
    for %%i in (%SRCDIR%\c\*) do (
        gcc %%i -o %OUTDIR%\%%~ni
    )
)

exit /B 0