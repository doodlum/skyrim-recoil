@echo off

RMDIR dist /S /Q

cmake -S . --preset=skyrim --check-stamp-file "build\skyrim\CMakeFiles\generate.stamp"
if %ERRORLEVEL% NEQ 0 exit 1
cmake --build build/skyrim --config Release
if %ERRORLEVEL% NEQ 0 exit 1

xcopy "build\skyrim\release\*.dll" "dist\SKSE\Plugins\" /I /Y

xcopy "package" "dist" /I /Y /E

pause