@echo off

setlocal EnableDelayedExpansion
set SRCDIR=src
set IN=%SRCDIR%\main.cpp
set OUTDIR=bin
set OUT=%OUTDIR%\xmt.exe
set FLAGS=-m32 -static-libgcc -static-libstdc++ -static
set RESOURCES=src\scrpt_remove.bat

rmdir /s /q %OUTDIR%
mkdir %OUTDIR%

if exist %OUTDIR% (
    mkdir %OUTDIR%\obj

    for %%i in (%RESOURCES%) do (
        set o=%OUTDIR%\obj\%%~ni.o
        objcopy --prefix-symbol=_ --input-target binary --output-target pe-i386 --binary-architecture i386 %%i !o!
    )
    
    g++ %FLAGS% bin\obj\* %IN% -o %OUT%
)
