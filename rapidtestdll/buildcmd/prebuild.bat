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

REM Since VS may parallelize the builds, another project may run the same pre-build events
REM at the same time, causing git to fail because of a lock, throwing a failure at the build
REM engine, which stops the build and shows you errors in the IDE. Therefore, we always return
REM success. Obviously, this could be dangerous but seeing as how this only ever has to succeed
REM once to be effective, it's worth the risk
exit 0

REM Do things

