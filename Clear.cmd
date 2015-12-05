@echo off

SetLocal EnableExtensions

set extensions=*.suo *.sdf *.vcxproj.user
set directories=Debug Release ipch .vs

set cmdDelete=del /A- /F /Q %extensions%
set cmdDeleteDirs=rmdir /S /Q %directories%

%cmdDeleteDirs% 2>nul
%cmdDelete% 2>nul

for /F "delims=" %%I in ('dir "%cd%" /AD /B /S') do (
	pushd %%I
	%cmdDeleteDirs% 2>nul
	%cmdDelete% 2>nul
	popd
)