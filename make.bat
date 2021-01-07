@echo off

set SRCDIR=src
set IN=%SRCDIR%\main.cpp
set OUTDIR=bin
set OUT=%OUTDIR%\xmt.exe
set FLAGS=-m32 -static-libgcc -static-libstdc++

rmdir /s /q %OUTDIR%
mkdir %OUTDIR%
g++ %FLAGS% %IN% -o %OUT%