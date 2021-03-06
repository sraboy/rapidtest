# rapidtest

###### DANGER! Please don't blindly run anything in this repo. The `master` branch is innocuous, except for the potentially dangerous use of `system("pause")`, but I use this to test, save, backup, blindly execute or tinker with arbitrary code.

### Why?

To save me 5 minutes at least a dozen times a month.

### What?

I'm constantly creating/recreating a simple VS2017 projects and solutions for playing with something cool I found online or testing bits of code before inclusion in a larger project. Often I find myself wasting time setting up test projects with all the same settings and later regretting losing some snippet I'd tinkered with at some point but removed for a new test.

I decided to set up a nice solution with a bunch of common properties and configurations. In `master`, you'll find the following:

#### Solution/Repo Settings
 * A modified version of [this .gitignore](https://github.com/github/gitignore/blob/master/VisualStudio.gitignore). 
 * `inc` and `lib` subdirectories
 * `inc\common.h` for solution-wide includes
 * `inc\debug.h` for C-compatible debug output in user-mode or kernel-mode
 * Batch Build enabled for Win32, x64, Debug and Release
 * `update_template.cmd` to automate updating the templates and check-in the "proprietary" files (see below)
 
#### Project Common Settings

These apply only to projects in `master`, since those are the templates. Obviously some items, like compiler switches, don't apply for Linux, which uses g++.

 * Set to use C++17 (Linux is `/std=gnu++11` until they get non-experimental C++17 support)
 * Warning Level 4 (`-Wall` on Linux)
 * Code Analysis on build
 * Output "Assembly, Machine Code and Source" (/FAcs) to `$(IntDir)`
 * Not using pre-compiled headers
 * Pre-build, pre-link and post-build commands, each launching `BAT` files in `$(ProjectDir)buildcmd`
 * Intermediate/Build directory: `$(ProjectDir)build\$(Platform)_$(Configuration)\`
 * Output directory: `$(SolutionDir)$(Platform)_$(Configuration)\`
 * Subdirectories (all included in the project's filters):
	* `buildcmd` with `prebuild.bat`, `prelink.bat`, `postbuild.bat`
	* `gitignore_inc` and `inc` as Additional Include Directories
	* `lib` as an Additional Library Directory
	* `src` and `gitignore_src` for implementation files
	* `gitignore_*` dirs each have a `.gitignore` to ignore everything but `.gitignore` and the `proprietary.[h|cpp]` within. This is where you can dump code that for one reason or another, you don't want committed to GitHub (e.g., it's proprietary or part of some other project).
 * Some boilerplate code with namespaces, includes, etc
 * The Linux project has `%LocalAppData%\lxss\rootfs\usr\local\include\` and `%LocalAppData%\lxss\rootfs\usr\include\` as Additional Include Directories, which point to the current user's WSL rootfs. These are in addition to the standard headers provided by Visual Studio because I was having some issues building otherwise. You'll also notice some funny business in the directory settings for remote build/debug to work around bugs in VS.
 
Since `proprietary.h` and `proprietary.cpp` are tracked files, git will never ignore them. To help prevent an unwitting `git add .` from staging code that ought not to be committed, I've employed a cheap hack with the pre-build event through two commands in `prebuild.bat`: 
```
git update-index --assume-unchanged ./gitignore_inc/proprietary.h
git update-index --assume-unchanged ./gitignore_src/proprietary.cpp
```

These two commands only need to be run once locally but I develop on several VMs and often start with a fresh clone. Since there's no way to use `.gitignore` or `.gitattributes` to achieve the same effect, and I really wanted these two files already part of these project templates, I figured I'm likely to build at least once before trying to commit anything, so this will help me in case I forget.

### License

Unless otherwise noted (e.g. `debug.h` is MIT), the `master` branch is optionally "public domain" or [CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/). Other than that, beware, because I may have committed borrowed testing code under any arbitrary license.
