# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/ds/github.com/codenotes/linux/algorithms/algo4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ds/github.com/codenotes/linux/algorithms/algo4

# Include any dependencies generated for this target.
include CMakeFiles/splaytree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/splaytree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/splaytree.dir/flags.make

CMakeFiles/splaytree.dir/splaytree.c.o: CMakeFiles/splaytree.dir/flags.make
CMakeFiles/splaytree.dir/splaytree.c.o: splaytree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ds/github.com/codenotes/linux/algorithms/algo4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/splaytree.dir/splaytree.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/splaytree.dir/splaytree.c.o   -c /home/ds/github.com/codenotes/linux/algorithms/algo4/splaytree.c

CMakeFiles/splaytree.dir/splaytree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/splaytree.dir/splaytree.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ds/github.com/codenotes/linux/algorithms/algo4/splaytree.c > CMakeFiles/splaytree.dir/splaytree.c.i

CMakeFiles/splaytree.dir/splaytree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/splaytree.dir/splaytree.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ds/github.com/codenotes/linux/algorithms/algo4/splaytree.c -o CMakeFiles/splaytree.dir/splaytree.c.s

CMakeFiles/splaytree.dir/splaytree.c.o.requires:

.PHONY : CMakeFiles/splaytree.dir/splaytree.c.o.requires

CMakeFiles/splaytree.dir/splaytree.c.o.provides: CMakeFiles/splaytree.dir/splaytree.c.o.requires
	$(MAKE) -f CMakeFiles/splaytree.dir/build.make CMakeFiles/splaytree.dir/splaytree.c.o.provides.build
.PHONY : CMakeFiles/splaytree.dir/splaytree.c.o.provides

CMakeFiles/splaytree.dir/splaytree.c.o.provides.build: CMakeFiles/splaytree.dir/splaytree.c.o


# Object files for target splaytree
splaytree_OBJECTS = \
"CMakeFiles/splaytree.dir/splaytree.c.o"

# External object files for target splaytree
splaytree_EXTERNAL_OBJECTS =

bin/splaytree: CMakeFiles/splaytree.dir/splaytree.c.o
bin/splaytree: CMakeFiles/splaytree.dir/build.make
bin/splaytree: CMakeFiles/splaytree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ds/github.com/codenotes/linux/algorithms/algo4/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/splaytree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/splaytree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/splaytree.dir/build: bin/splaytree

.PHONY : CMakeFiles/splaytree.dir/build

CMakeFiles/splaytree.dir/requires: CMakeFiles/splaytree.dir/splaytree.c.o.requires

.PHONY : CMakeFiles/splaytree.dir/requires

CMakeFiles/splaytree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/splaytree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/splaytree.dir/clean

CMakeFiles/splaytree.dir/depend:
	cd /home/ds/github.com/codenotes/linux/algorithms/algo4 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ds/github.com/codenotes/linux/algorithms/algo4 /home/ds/github.com/codenotes/linux/algorithms/algo4 /home/ds/github.com/codenotes/linux/algorithms/algo4 /home/ds/github.com/codenotes/linux/algorithms/algo4 /home/ds/github.com/codenotes/linux/algorithms/algo4/CMakeFiles/splaytree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/splaytree.dir/depend

