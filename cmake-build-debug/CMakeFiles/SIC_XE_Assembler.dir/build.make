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
CMAKE_COMMAND = /media/hesham/2CF88440F88409F2/Ubuntu/Clion/opt/clion-2018.1.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /media/hesham/2CF88440F88409F2/Ubuntu/Clion/opt/clion-2018.1.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/SIC_XE_Assembler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SIC_XE_Assembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SIC_XE_Assembler.dir/flags.make

CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o: CMakeFiles/SIC_XE_Assembler.dir/flags.make
CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o -c "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/src/main.cpp"

CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/src/main.cpp" > CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.i

CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/src/main.cpp" -o CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.s

CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.requires

CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.provides: CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/SIC_XE_Assembler.dir/build.make CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.provides

CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.provides.build: CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o


CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o: CMakeFiles/SIC_XE_Assembler.dir/flags.make
CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o: ../src/Instruction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o -c "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/src/Instruction.cpp"

CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/src/Instruction.cpp" > CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.i

CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/src/Instruction.cpp" -o CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.s

CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.requires:

.PHONY : CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.requires

CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.provides: CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.requires
	$(MAKE) -f CMakeFiles/SIC_XE_Assembler.dir/build.make CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.provides.build
.PHONY : CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.provides

CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.provides.build: CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o


# Object files for target SIC_XE_Assembler
SIC_XE_Assembler_OBJECTS = \
"CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o" \
"CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o"

# External object files for target SIC_XE_Assembler
SIC_XE_Assembler_EXTERNAL_OBJECTS =

SIC_XE_Assembler: CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o
SIC_XE_Assembler: CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o
SIC_XE_Assembler: CMakeFiles/SIC_XE_Assembler.dir/build.make
SIC_XE_Assembler: CMakeFiles/SIC_XE_Assembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SIC_XE_Assembler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SIC_XE_Assembler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SIC_XE_Assembler.dir/build: SIC_XE_Assembler

.PHONY : CMakeFiles/SIC_XE_Assembler.dir/build

CMakeFiles/SIC_XE_Assembler.dir/requires: CMakeFiles/SIC_XE_Assembler.dir/src/main.cpp.o.requires
CMakeFiles/SIC_XE_Assembler.dir/requires: CMakeFiles/SIC_XE_Assembler.dir/src/Instruction.cpp.o.requires

.PHONY : CMakeFiles/SIC_XE_Assembler.dir/requires

CMakeFiles/SIC_XE_Assembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SIC_XE_Assembler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SIC_XE_Assembler.dir/clean

CMakeFiles/SIC_XE_Assembler.dir/depend:
	cd "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler" "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler" "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug" "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug" "/media/hesham/2CF88440F88409F2/Engineering/My Workspace/SIC-XE Assembler/cmake-build-debug/CMakeFiles/SIC_XE_Assembler.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/SIC_XE_Assembler.dir/depend

