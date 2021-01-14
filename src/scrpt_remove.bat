:LoopStart
tasklist | find /i "%EXEC%" >nul 2>&1
if ERRORLEVEL 1 (
    goto :Continue
else (
    goto :LoopStart
)

:Continue
del "%FILENAME%"
del "%~f0"