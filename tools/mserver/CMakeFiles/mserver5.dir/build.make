# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build

# Include any dependencies generated for this target.
include tools/mserver/CMakeFiles/mserver5.dir/depend.make

# Include the progress variables for this target.
include tools/mserver/CMakeFiles/mserver5.dir/progress.make

# Include the compile flags for this target's objects.
include tools/mserver/CMakeFiles/mserver5.dir/flags.make

tools/mserver/CMakeFiles/mserver5.dir/mserver5.c.o: tools/mserver/CMakeFiles/mserver5.dir/flags.make
tools/mserver/CMakeFiles/mserver5.dir/mserver5.c.o: ../tools/mserver/mserver5.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tools/mserver/CMakeFiles/mserver5.dir/mserver5.c.o"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mserver5.dir/mserver5.c.o   -c /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/mserver/mserver5.c

tools/mserver/CMakeFiles/mserver5.dir/mserver5.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mserver5.dir/mserver5.c.i"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/mserver/mserver5.c > CMakeFiles/mserver5.dir/mserver5.c.i

tools/mserver/CMakeFiles/mserver5.dir/mserver5.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mserver5.dir/mserver5.c.s"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/mserver/mserver5.c -o CMakeFiles/mserver5.dir/mserver5.c.s

tools/mserver/CMakeFiles/mserver5.dir/monet_version.c.o: tools/mserver/CMakeFiles/mserver5.dir/flags.make
tools/mserver/CMakeFiles/mserver5.dir/monet_version.c.o: tools/mserver/monet_version.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tools/mserver/CMakeFiles/mserver5.dir/monet_version.c.o"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mserver5.dir/monet_version.c.o   -c /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver/monet_version.c

tools/mserver/CMakeFiles/mserver5.dir/monet_version.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mserver5.dir/monet_version.c.i"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver/monet_version.c > CMakeFiles/mserver5.dir/monet_version.c.i

tools/mserver/CMakeFiles/mserver5.dir/monet_version.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mserver5.dir/monet_version.c.s"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver/monet_version.c -o CMakeFiles/mserver5.dir/monet_version.c.s

# Object files for target mserver5
mserver5_OBJECTS = \
"CMakeFiles/mserver5.dir/mserver5.c.o" \
"CMakeFiles/mserver5.dir/monet_version.c.o"

# External object files for target mserver5
mserver5_EXTERNAL_OBJECTS =

tools/mserver/mserver5: tools/mserver/CMakeFiles/mserver5.dir/mserver5.c.o
tools/mserver/mserver5: tools/mserver/CMakeFiles/mserver5.dir/monet_version.c.o
tools/mserver/mserver5: tools/mserver/CMakeFiles/mserver5.dir/build.make
tools/mserver/mserver5: common/options/libmoptions.a
tools/mserver/mserver5: common/utils/libmutils.a
tools/mserver/mserver5: common/utils/libmcrypt.a
tools/mserver/mserver5: gdk/libbat.so.21.1.1
tools/mserver/mserver5: monetdb5/tools/libmonetdb5.so.30.0.4
tools/mserver/mserver5: /usr/lib/x86_64-linux-gnu/libpcre.so
tools/mserver/mserver5: /usr/lib/x86_64-linux-gnu/libcrypto.so
tools/mserver/mserver5: tools/mserver/CMakeFiles/mserver5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable mserver5"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mserver5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/mserver/CMakeFiles/mserver5.dir/build: tools/mserver/mserver5

.PHONY : tools/mserver/CMakeFiles/mserver5.dir/build

tools/mserver/CMakeFiles/mserver5.dir/clean:
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver && $(CMAKE_COMMAND) -P CMakeFiles/mserver5.dir/cmake_clean.cmake
.PHONY : tools/mserver/CMakeFiles/mserver5.dir/clean

tools/mserver/CMakeFiles/mserver5.dir/depend:
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11 /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/mserver /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/mserver/CMakeFiles/mserver5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/mserver/CMakeFiles/mserver5.dir/depend
