@echo off

call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
msbuild /p:Configuration=Debug Slot_machine.sln
msbuild /p:Configuration=Release Slot_machine.sln
pause>nul