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

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /home/panesico/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/231.8770.66/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/panesico/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/231.8770.66/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/panesico/CLionProjects/minishell_parser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/panesico/CLionProjects/minishell_parser/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MINISHELL.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MINISHELL.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MINISHELL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MINISHELL.dir/flags.make

CMakeFiles/MINISHELL.dir/srcs/builtins.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/builtins.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/builtins.c
CMakeFiles/MINISHELL.dir/srcs/builtins.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MINISHELL.dir/srcs/builtins.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/builtins.c.o -MF CMakeFiles/MINISHELL.dir/srcs/builtins.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/builtins.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/builtins.c

CMakeFiles/MINISHELL.dir/srcs/builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/builtins.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/builtins.c > CMakeFiles/MINISHELL.dir/srcs/builtins.c.i

CMakeFiles/MINISHELL.dir/srcs/builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/builtins.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/builtins.c -o CMakeFiles/MINISHELL.dir/srcs/builtins.c.s

CMakeFiles/MINISHELL.dir/srcs/export.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/export.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/export.c
CMakeFiles/MINISHELL.dir/srcs/export.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MINISHELL.dir/srcs/export.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/export.c.o -MF CMakeFiles/MINISHELL.dir/srcs/export.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/export.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/export.c

CMakeFiles/MINISHELL.dir/srcs/export.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/export.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/export.c > CMakeFiles/MINISHELL.dir/srcs/export.c.i

CMakeFiles/MINISHELL.dir/srcs/export.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/export.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/export.c -o CMakeFiles/MINISHELL.dir/srcs/export.c.s

CMakeFiles/MINISHELL.dir/srcs/main.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/main.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/main.c
CMakeFiles/MINISHELL.dir/srcs/main.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MINISHELL.dir/srcs/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/main.c.o -MF CMakeFiles/MINISHELL.dir/srcs/main.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/main.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/main.c

CMakeFiles/MINISHELL.dir/srcs/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/main.c > CMakeFiles/MINISHELL.dir/srcs/main.c.i

CMakeFiles/MINISHELL.dir/srcs/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/main.c -o CMakeFiles/MINISHELL.dir/srcs/main.c.s

CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/qvalidate.c
CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o -MF CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/qvalidate.c

CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/qvalidate.c > CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.i

CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/qvalidate.c -o CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.s

CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/rvalidate.c
CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o -MF CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/rvalidate.c

CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/rvalidate.c > CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.i

CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/rvalidate.c -o CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.s

CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/to_double_pointer.c
CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o -MF CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/to_double_pointer.c

CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/to_double_pointer.c > CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.i

CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/to_double_pointer.c -o CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.s

CMakeFiles/MINISHELL.dir/srcs/unset.c.o: CMakeFiles/MINISHELL.dir/flags.make
CMakeFiles/MINISHELL.dir/srcs/unset.c.o: /home/panesico/CLionProjects/minishell_parser/srcs/unset.c
CMakeFiles/MINISHELL.dir/srcs/unset.c.o: CMakeFiles/MINISHELL.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/MINISHELL.dir/srcs/unset.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MINISHELL.dir/srcs/unset.c.o -MF CMakeFiles/MINISHELL.dir/srcs/unset.c.o.d -o CMakeFiles/MINISHELL.dir/srcs/unset.c.o -c /home/panesico/CLionProjects/minishell_parser/srcs/unset.c

CMakeFiles/MINISHELL.dir/srcs/unset.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MINISHELL.dir/srcs/unset.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/panesico/CLionProjects/minishell_parser/srcs/unset.c > CMakeFiles/MINISHELL.dir/srcs/unset.c.i

CMakeFiles/MINISHELL.dir/srcs/unset.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MINISHELL.dir/srcs/unset.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/panesico/CLionProjects/minishell_parser/srcs/unset.c -o CMakeFiles/MINISHELL.dir/srcs/unset.c.s

# Object files for target MINISHELL
MINISHELL_OBJECTS = \
"CMakeFiles/MINISHELL.dir/srcs/builtins.c.o" \
"CMakeFiles/MINISHELL.dir/srcs/export.c.o" \
"CMakeFiles/MINISHELL.dir/srcs/main.c.o" \
"CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o" \
"CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o" \
"CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o" \
"CMakeFiles/MINISHELL.dir/srcs/unset.c.o"

# External object files for target MINISHELL
MINISHELL_EXTERNAL_OBJECTS =

libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/builtins.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/export.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/main.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/qvalidate.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/rvalidate.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/to_double_pointer.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/srcs/unset.c.o
libMINISHELL.a: CMakeFiles/MINISHELL.dir/build.make
libMINISHELL.a: CMakeFiles/MINISHELL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libMINISHELL.a"
	$(CMAKE_COMMAND) -P CMakeFiles/MINISHELL.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MINISHELL.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MINISHELL.dir/build: libMINISHELL.a
.PHONY : CMakeFiles/MINISHELL.dir/build

CMakeFiles/MINISHELL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MINISHELL.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MINISHELL.dir/clean

CMakeFiles/MINISHELL.dir/depend:
	cd /home/panesico/CLionProjects/minishell_parser/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/panesico/CLionProjects/minishell_parser /home/panesico/CLionProjects/minishell_parser /home/panesico/CLionProjects/minishell_parser/cmake-build-debug /home/panesico/CLionProjects/minishell_parser/cmake-build-debug /home/panesico/CLionProjects/minishell_parser/cmake-build-debug/CMakeFiles/MINISHELL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MINISHELL.dir/depend

