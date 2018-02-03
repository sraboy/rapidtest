git update-index --no-assume-unchanged ./*/gitignore_inc/proprietary.h
git update-index --no-assume-unchanged ./*/gitignore_src/proprietary.cpp
git add .
git update-index --assume-unchanged ./*/gitignore_inc/proprietary.h
git update-index --assume-unchanged ./*/gitignore_src/proprietary.cpp
git status