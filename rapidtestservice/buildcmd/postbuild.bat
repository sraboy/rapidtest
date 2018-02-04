echo Running postbuild commands...
@echo off

REM Called as: call PostBuild.bat "$(TargetPath)" "$(ProjectName)"

REM If you're not running VS as administrator, this will fail.

set targetpath=%~1
set projectname=%~2

echo Creating service: %projectname%
sc create  %projectname% binPath= "%targetpath%"
