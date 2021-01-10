:LoopStart
if tasklist /FI "IMAGENAME equ %EXEC%" goto :LoopStart
del "%FILENAME%"