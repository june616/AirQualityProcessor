# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/final_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/final_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/final_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final_project.dir/flags.make

CMakeFiles/final_project.dir/main.cpp.obj: CMakeFiles/final_project.dir/flags.make
CMakeFiles/final_project.dir/main.cpp.obj: ../main.cpp
CMakeFiles/final_project.dir/main.cpp.obj: CMakeFiles/final_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/final_project.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/final_project.dir/main.cpp.obj -MF CMakeFiles\final_project.dir\main.cpp.obj.d -o CMakeFiles\final_project.dir\main.cpp.obj -c C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\main.cpp

CMakeFiles/final_project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final_project.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\main.cpp > CMakeFiles\final_project.dir\main.cpp.i

CMakeFiles/final_project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final_project.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\main.cpp -o CMakeFiles\final_project.dir\main.cpp.s

# Object files for target final_project
final_project_OBJECTS = \
"CMakeFiles/final_project.dir/main.cpp.obj"

# External object files for target final_project
final_project_EXTERNAL_OBJECTS =

final_project.exe: CMakeFiles/final_project.dir/main.cpp.obj
final_project.exe: CMakeFiles/final_project.dir/build.make
final_project.exe: CMakeFiles/final_project.dir/linklibs.rsp
final_project.exe: CMakeFiles/final_project.dir/objects1.rsp
final_project.exe: CMakeFiles/final_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable final_project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\final_project.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final_project.dir/build: final_project.exe
.PHONY : CMakeFiles/final_project.dir/build

CMakeFiles/final_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\final_project.dir\cmake_clean.cmake
.PHONY : CMakeFiles/final_project.dir/clean

CMakeFiles/final_project.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\cmake-build-debug C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\cmake-build-debug C:\Users\nicho\Desktop\GitHub\CS5008_Group\AirQualityProcessor\final_project\cmake-build-debug\CMakeFiles\final_project.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final_project.dir/depend

