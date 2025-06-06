# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mike/Documents/piolib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mike/Documents/piolib

# Include any dependencies generated for this target.
include examples/CMakeFiles/quadenc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/quadenc.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/quadenc.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/quadenc.dir/flags.make

examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.o: examples/CMakeFiles/quadenc.dir/flags.make
examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.o: examples/quadrature_encoder.c
examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.o: examples/CMakeFiles/quadenc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mike/Documents/piolib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.o"
	cd /home/mike/Documents/piolib/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.o -MF CMakeFiles/quadenc.dir/quadrature_encoder.c.o.d -o CMakeFiles/quadenc.dir/quadrature_encoder.c.o -c /home/mike/Documents/piolib/examples/quadrature_encoder.c

examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/quadenc.dir/quadrature_encoder.c.i"
	cd /home/mike/Documents/piolib/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mike/Documents/piolib/examples/quadrature_encoder.c > CMakeFiles/quadenc.dir/quadrature_encoder.c.i

examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/quadenc.dir/quadrature_encoder.c.s"
	cd /home/mike/Documents/piolib/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mike/Documents/piolib/examples/quadrature_encoder.c -o CMakeFiles/quadenc.dir/quadrature_encoder.c.s

# Object files for target quadenc
quadenc_OBJECTS = \
"CMakeFiles/quadenc.dir/quadrature_encoder.c.o"

# External object files for target quadenc
quadenc_EXTERNAL_OBJECTS = \
"/home/mike/Documents/piolib/CMakeFiles/pio.dir/piolib.c.o" \
"/home/mike/Documents/piolib/CMakeFiles/pio.dir/pio_rp1.c.o"

examples/quadenc: examples/CMakeFiles/quadenc.dir/quadrature_encoder.c.o
examples/quadenc: CMakeFiles/pio.dir/piolib.c.o
examples/quadenc: CMakeFiles/pio.dir/pio_rp1.c.o
examples/quadenc: examples/CMakeFiles/quadenc.dir/build.make
examples/quadenc: examples/CMakeFiles/quadenc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mike/Documents/piolib/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable quadenc"
	cd /home/mike/Documents/piolib/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/quadenc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/quadenc.dir/build: examples/quadenc
.PHONY : examples/CMakeFiles/quadenc.dir/build

examples/CMakeFiles/quadenc.dir/clean:
	cd /home/mike/Documents/piolib/examples && $(CMAKE_COMMAND) -P CMakeFiles/quadenc.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/quadenc.dir/clean

examples/CMakeFiles/quadenc.dir/depend:
	cd /home/mike/Documents/piolib && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mike/Documents/piolib /home/mike/Documents/piolib/examples /home/mike/Documents/piolib /home/mike/Documents/piolib/examples /home/mike/Documents/piolib/examples/CMakeFiles/quadenc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/quadenc.dir/depend

