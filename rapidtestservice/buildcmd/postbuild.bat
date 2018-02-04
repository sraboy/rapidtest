echo Running postbuild commands...
@echo off

REM Called as: call PostBuild.bat "$(TargetPath)" "$(ProjectName)" [install|noinstall]

REM If you're not running VS as administrator, this will fail.

set targetpath=%~1
set projectname=%~2

if "%~3"=="noinstall" goto :eof

echo Creating service: %projectname%
sc create  %projectname% binPath= "%targetpath%"
