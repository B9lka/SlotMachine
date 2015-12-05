@echo off

call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
msbuild /p:Configuration=Debug slot_machine.sln
msbuild /p:Configuration=Release slot_machine.sln
pause>nul