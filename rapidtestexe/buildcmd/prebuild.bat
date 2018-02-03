echo Running prebuild commands...
@echo off
REM
REM To ensure nothing sensitive gets thrown on GitHub by a wanton `git add .` these commands
REM must be run once after checkout. I *really* wish this was doable via .gitattributes but, 
REM since it's not, I figured a pre-build command will make it less likely I screw up later.
REM
REM To undo it and add more boiler-plate, just use `--no-assume-unchanged`, commit and re-run these.
REM

git update-index --assume-unchanged ./gitignore_inc/proprietary.h
git update-index --assume-unchanged ./gitignore_src/proprietary.cpp

REM Do things

