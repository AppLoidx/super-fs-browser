# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lilith/spo_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lilith/spo_3

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lilith/spo_3/CMakeFiles /home/lilith/spo_3/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/lilith/spo_3/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named super-fs-browser

# Build rule for target.
super-fs-browser: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 super-fs-browser
.PHONY : super-fs-browser

# fast build rule for target.
super-fs-browser/fast:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/build
.PHONY : super-fs-browser/fast

client.o: client.c.o

.PHONY : client.o

# target to build an object file
client.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/client.c.o
.PHONY : client.c.o

client.i: client.c.i

.PHONY : client.i

# target to preprocess a source file
client.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/client.c.i
.PHONY : client.c.i

client.s: client.c.s

.PHONY : client.s

# target to generate assembly for a file
client.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/client.c.s
.PHONY : client.c.s

flist.o: flist.c.o

.PHONY : flist.o

# target to build an object file
flist.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/flist.c.o
.PHONY : flist.c.o

flist.i: flist.c.i

.PHONY : flist.i

# target to preprocess a source file
flist.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/flist.c.i
.PHONY : flist.c.i

flist.s: flist.c.s

.PHONY : flist.s

# target to generate assembly for a file
flist.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/flist.c.s
.PHONY : flist.c.s

main.o: main.c.o

.PHONY : main.o

# target to build an object file
main.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/main.c.o
.PHONY : main.c.o

main.i: main.c.i

.PHONY : main.i

# target to preprocess a source file
main.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/main.c.i
.PHONY : main.c.i

main.s: main.c.s

.PHONY : main.s

# target to generate assembly for a file
main.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/main.c.s
.PHONY : main.c.s

server.o: server.c.o

.PHONY : server.o

# target to build an object file
server.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/server.c.o
.PHONY : server.c.o

server.i: server.c.i

.PHONY : server.i

# target to preprocess a source file
server.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/server.c.i
.PHONY : server.c.i

server.s: server.c.s

.PHONY : server.s

# target to generate assembly for a file
server.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/server.c.s
.PHONY : server.c.s

slist.o: slist.c.o

.PHONY : slist.o

# target to build an object file
slist.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/slist.c.o
.PHONY : slist.c.o

slist.i: slist.c.i

.PHONY : slist.i

# target to preprocess a source file
slist.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/slist.c.i
.PHONY : slist.c.i

slist.s: slist.c.s

.PHONY : slist.s

# target to generate assembly for a file
slist.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/slist.c.s
.PHONY : slist.c.s

ui.o: ui.c.o

.PHONY : ui.o

# target to build an object file
ui.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/ui.c.o
.PHONY : ui.c.o

ui.i: ui.c.i

.PHONY : ui.i

# target to preprocess a source file
ui.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/ui.c.i
.PHONY : ui.c.i

ui.s: ui.c.s

.PHONY : ui.s

# target to generate assembly for a file
ui.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/ui.c.s
.PHONY : ui.c.s

utils.o: utils.c.o

.PHONY : utils.o

# target to build an object file
utils.c.o:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/utils.c.o
.PHONY : utils.c.o

utils.i: utils.c.i

.PHONY : utils.i

# target to preprocess a source file
utils.c.i:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/utils.c.i
.PHONY : utils.c.i

utils.s: utils.c.s

.PHONY : utils.s

# target to generate assembly for a file
utils.c.s:
	$(MAKE) -f CMakeFiles/super-fs-browser.dir/build.make CMakeFiles/super-fs-browser.dir/utils.c.s
.PHONY : utils.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... super-fs-browser"
	@echo "... client.o"
	@echo "... client.i"
	@echo "... client.s"
	@echo "... flist.o"
	@echo "... flist.i"
	@echo "... flist.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... server.o"
	@echo "... server.i"
	@echo "... server.s"
	@echo "... slist.o"
	@echo "... slist.i"
	@echo "... slist.s"
	@echo "... ui.o"
	@echo "... ui.i"
	@echo "... ui.s"
	@echo "... utils.o"
	@echo "... utils.i"
	@echo "... utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
