# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tjsiasun/work/queue_frame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tjsiasun/work/queue_frame/build

# Include any dependencies generated for this target.
include CMakeFiles/APP_RUN.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/APP_RUN.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/APP_RUN.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/APP_RUN.dir/flags.make

CMakeFiles/APP_RUN.dir/main.cpp.o: CMakeFiles/APP_RUN.dir/flags.make
CMakeFiles/APP_RUN.dir/main.cpp.o: ../main.cpp
CMakeFiles/APP_RUN.dir/main.cpp.o: CMakeFiles/APP_RUN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tjsiasun/work/queue_frame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/APP_RUN.dir/main.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APP_RUN.dir/main.cpp.o -MF CMakeFiles/APP_RUN.dir/main.cpp.o.d -o CMakeFiles/APP_RUN.dir/main.cpp.o -c /home/tjsiasun/work/queue_frame/main.cpp

CMakeFiles/APP_RUN.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APP_RUN.dir/main.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tjsiasun/work/queue_frame/main.cpp > CMakeFiles/APP_RUN.dir/main.cpp.i

CMakeFiles/APP_RUN.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APP_RUN.dir/main.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tjsiasun/work/queue_frame/main.cpp -o CMakeFiles/APP_RUN.dir/main.cpp.s

CMakeFiles/APP_RUN.dir/queue_frame.cpp.o: CMakeFiles/APP_RUN.dir/flags.make
CMakeFiles/APP_RUN.dir/queue_frame.cpp.o: ../queue_frame.cpp
CMakeFiles/APP_RUN.dir/queue_frame.cpp.o: CMakeFiles/APP_RUN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tjsiasun/work/queue_frame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/APP_RUN.dir/queue_frame.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APP_RUN.dir/queue_frame.cpp.o -MF CMakeFiles/APP_RUN.dir/queue_frame.cpp.o.d -o CMakeFiles/APP_RUN.dir/queue_frame.cpp.o -c /home/tjsiasun/work/queue_frame/queue_frame.cpp

CMakeFiles/APP_RUN.dir/queue_frame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APP_RUN.dir/queue_frame.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tjsiasun/work/queue_frame/queue_frame.cpp > CMakeFiles/APP_RUN.dir/queue_frame.cpp.i

CMakeFiles/APP_RUN.dir/queue_frame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APP_RUN.dir/queue_frame.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tjsiasun/work/queue_frame/queue_frame.cpp -o CMakeFiles/APP_RUN.dir/queue_frame.cpp.s

CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o: CMakeFiles/APP_RUN.dir/flags.make
CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o: ../threadpool/threadPool.cpp
CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o: CMakeFiles/APP_RUN.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tjsiasun/work/queue_frame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o -MF CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o.d -o CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o -c /home/tjsiasun/work/queue_frame/threadpool/threadPool.cpp

CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tjsiasun/work/queue_frame/threadpool/threadPool.cpp > CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.i

CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tjsiasun/work/queue_frame/threadpool/threadPool.cpp -o CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.s

# Object files for target APP_RUN
APP_RUN_OBJECTS = \
"CMakeFiles/APP_RUN.dir/main.cpp.o" \
"CMakeFiles/APP_RUN.dir/queue_frame.cpp.o" \
"CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o"

# External object files for target APP_RUN
APP_RUN_EXTERNAL_OBJECTS =

APP_RUN: CMakeFiles/APP_RUN.dir/main.cpp.o
APP_RUN: CMakeFiles/APP_RUN.dir/queue_frame.cpp.o
APP_RUN: CMakeFiles/APP_RUN.dir/threadpool/threadPool.cpp.o
APP_RUN: CMakeFiles/APP_RUN.dir/build.make
APP_RUN: CMakeFiles/APP_RUN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tjsiasun/work/queue_frame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable APP_RUN"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/APP_RUN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/APP_RUN.dir/build: APP_RUN
.PHONY : CMakeFiles/APP_RUN.dir/build

CMakeFiles/APP_RUN.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/APP_RUN.dir/cmake_clean.cmake
.PHONY : CMakeFiles/APP_RUN.dir/clean

CMakeFiles/APP_RUN.dir/depend:
	cd /home/tjsiasun/work/queue_frame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tjsiasun/work/queue_frame /home/tjsiasun/work/queue_frame /home/tjsiasun/work/queue_frame/build /home/tjsiasun/work/queue_frame/build /home/tjsiasun/work/queue_frame/build/CMakeFiles/APP_RUN.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/APP_RUN.dir/depend

