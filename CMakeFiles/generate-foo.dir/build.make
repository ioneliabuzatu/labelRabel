# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/ionelia/labelRabel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ionelia/labelRabel

# Utility rule file for generate-foo.

# Include the progress variables for this target.
include CMakeFiles/generate-foo.dir/progress.make

CMakeFiles/generate-foo: utils.cpp


generate-foo: CMakeFiles/generate-foo
generate-foo: CMakeFiles/generate-foo.dir/build.make

.PHONY : generate-foo

# Rule to build all files generated by this target.
CMakeFiles/generate-foo.dir/build: generate-foo

.PHONY : CMakeFiles/generate-foo.dir/build

CMakeFiles/generate-foo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/generate-foo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/generate-foo.dir/clean

CMakeFiles/generate-foo.dir/depend:
	cd /home/ionelia/labelRabel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ionelia/labelRabel /home/ionelia/labelRabel /home/ionelia/labelRabel /home/ionelia/labelRabel /home/ionelia/labelRabel/CMakeFiles/generate-foo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/generate-foo.dir/depend
