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
include tools/monetdbe/CMakeFiles/monetdbe.dir/depend.make

# Include the progress variables for this target.
include tools/monetdbe/CMakeFiles/monetdbe.dir/progress.make

# Include the compile flags for this target's objects.
include tools/monetdbe/CMakeFiles/monetdbe.dir/flags.make

tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe.c.o: tools/monetdbe/CMakeFiles/monetdbe.dir/flags.make
tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe.c.o: ../tools/monetdbe/monetdbe.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe.c.o"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monetdbe.dir/monetdbe.c.o   -c /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe/monetdbe.c

tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monetdbe.dir/monetdbe.c.i"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe/monetdbe.c > CMakeFiles/monetdbe.dir/monetdbe.c.i

tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monetdbe.dir/monetdbe.c.s"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe/monetdbe.c -o CMakeFiles/monetdbe.dir/monetdbe.c.s

tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe_mapi.c.o: tools/monetdbe/CMakeFiles/monetdbe.dir/flags.make
tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe_mapi.c.o: ../tools/monetdbe/monetdbe_mapi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe_mapi.c.o"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monetdbe.dir/monetdbe_mapi.c.o   -c /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe/monetdbe_mapi.c

tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe_mapi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monetdbe.dir/monetdbe_mapi.c.i"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe/monetdbe_mapi.c > CMakeFiles/monetdbe.dir/monetdbe_mapi.c.i

tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe_mapi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monetdbe.dir/monetdbe_mapi.c.s"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe/monetdbe_mapi.c -o CMakeFiles/monetdbe.dir/monetdbe_mapi.c.s

tools/monetdbe/CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.o: tools/monetdbe/CMakeFiles/monetdbe.dir/flags.make
tools/monetdbe/CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.o: ../clients/mapiclient/dump.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object tools/monetdbe/CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.o"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.o   -c /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/clients/mapiclient/dump.c

tools/monetdbe/CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.i"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/clients/mapiclient/dump.c > CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.i

tools/monetdbe/CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.s"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/clients/mapiclient/dump.c -o CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.s

# Object files for target monetdbe
monetdbe_OBJECTS = \
"CMakeFiles/monetdbe.dir/monetdbe.c.o" \
"CMakeFiles/monetdbe.dir/monetdbe_mapi.c.o" \
"CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.o"

# External object files for target monetdbe
monetdbe_EXTERNAL_OBJECTS =

tools/monetdbe/libmonetdbe.so.1.0.2: tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe.c.o
tools/monetdbe/libmonetdbe.so.1.0.2: tools/monetdbe/CMakeFiles/monetdbe.dir/monetdbe_mapi.c.o
tools/monetdbe/libmonetdbe.so.1.0.2: tools/monetdbe/CMakeFiles/monetdbe.dir/__/__/clients/mapiclient/dump.c.o
tools/monetdbe/libmonetdbe.so.1.0.2: tools/monetdbe/CMakeFiles/monetdbe.dir/build.make
tools/monetdbe/libmonetdbe.so.1.0.2: common/options/libmoptions.a
tools/monetdbe/libmonetdbe.so.1.0.2: common/utils/libmutils.a
tools/monetdbe/libmonetdbe.so.1.0.2: common/stream/libstream.so.14.0.4
tools/monetdbe/libmonetdbe.so.1.0.2: gdk/libbat.so.21.1.1
tools/monetdbe/libmonetdbe.so.1.0.2: monetdb5/tools/libmonetdb5.so.30.0.4
tools/monetdbe/libmonetdbe.so.1.0.2: sql/backends/monet5/libmonetdbsql.so.11.39.11
tools/monetdbe/libmonetdbe.so.1.0.2: tools/monetdbe/CMakeFiles/monetdbe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C shared library libmonetdbe.so"
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monetdbe.dir/link.txt --verbose=$(VERBOSE)
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && $(CMAKE_COMMAND) -E cmake_symlink_library libmonetdbe.so.1.0.2 libmonetdbe.so.1 libmonetdbe.so

tools/monetdbe/libmonetdbe.so.1: tools/monetdbe/libmonetdbe.so.1.0.2
	@$(CMAKE_COMMAND) -E touch_nocreate tools/monetdbe/libmonetdbe.so.1

tools/monetdbe/libmonetdbe.so: tools/monetdbe/libmonetdbe.so.1.0.2
	@$(CMAKE_COMMAND) -E touch_nocreate tools/monetdbe/libmonetdbe.so

# Rule to build all files generated by this target.
tools/monetdbe/CMakeFiles/monetdbe.dir/build: tools/monetdbe/libmonetdbe.so

.PHONY : tools/monetdbe/CMakeFiles/monetdbe.dir/build

tools/monetdbe/CMakeFiles/monetdbe.dir/clean:
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe && $(CMAKE_COMMAND) -P CMakeFiles/monetdbe.dir/cmake_clean.cmake
.PHONY : tools/monetdbe/CMakeFiles/monetdbe.dir/clean

tools/monetdbe/CMakeFiles/monetdbe.dir/depend:
	cd /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11 /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/tools/monetdbe /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe /home/wyf/PIM4DB-May2021-SP1/MonetDB-11.39.11/build/tools/monetdbe/CMakeFiles/monetdbe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/monetdbe/CMakeFiles/monetdbe.dir/depend
