# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/algolab/Desktop/vb_shared/CGAL/maximizeit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/Desktop/vb_shared/CGAL/maximizeit

# Include any dependencies generated for this target.
include CMakeFiles/maximizeit.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maximizeit.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maximizeit.dir/flags.make

CMakeFiles/maximizeit.dir/maximizeit.cpp.o: CMakeFiles/maximizeit.dir/flags.make
CMakeFiles/maximizeit.dir/maximizeit.cpp.o: maximizeit.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/algolab/Desktop/vb_shared/CGAL/maximizeit/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/maximizeit.dir/maximizeit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/maximizeit.dir/maximizeit.cpp.o -c /home/algolab/Desktop/vb_shared/CGAL/maximizeit/maximizeit.cpp

CMakeFiles/maximizeit.dir/maximizeit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maximizeit.dir/maximizeit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/algolab/Desktop/vb_shared/CGAL/maximizeit/maximizeit.cpp > CMakeFiles/maximizeit.dir/maximizeit.cpp.i

CMakeFiles/maximizeit.dir/maximizeit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maximizeit.dir/maximizeit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/algolab/Desktop/vb_shared/CGAL/maximizeit/maximizeit.cpp -o CMakeFiles/maximizeit.dir/maximizeit.cpp.s

CMakeFiles/maximizeit.dir/maximizeit.cpp.o.requires:
.PHONY : CMakeFiles/maximizeit.dir/maximizeit.cpp.o.requires

CMakeFiles/maximizeit.dir/maximizeit.cpp.o.provides: CMakeFiles/maximizeit.dir/maximizeit.cpp.o.requires
	$(MAKE) -f CMakeFiles/maximizeit.dir/build.make CMakeFiles/maximizeit.dir/maximizeit.cpp.o.provides.build
.PHONY : CMakeFiles/maximizeit.dir/maximizeit.cpp.o.provides

CMakeFiles/maximizeit.dir/maximizeit.cpp.o.provides.build: CMakeFiles/maximizeit.dir/maximizeit.cpp.o

# Object files for target maximizeit
maximizeit_OBJECTS = \
"CMakeFiles/maximizeit.dir/maximizeit.cpp.o"

# External object files for target maximizeit
maximizeit_EXTERNAL_OBJECTS =

maximizeit: CMakeFiles/maximizeit.dir/maximizeit.cpp.o
maximizeit: CMakeFiles/maximizeit.dir/build.make
maximizeit: /usr/lib/i386-linux-gnu/libmpfr.so
maximizeit: /usr/lib/i386-linux-gnu/libgmp.so
maximizeit: /usr/lib/libCGAL_Core.so
maximizeit: /usr/lib/libCGAL.so
maximizeit: /usr/lib/i386-linux-gnu/libboost_thread.so
maximizeit: /usr/lib/i386-linux-gnu/libboost_system.so
maximizeit: /usr/lib/i386-linux-gnu/libpthread.so
maximizeit: /usr/lib/libCGAL_Core.so
maximizeit: /usr/lib/libCGAL.so
maximizeit: /usr/lib/i386-linux-gnu/libboost_thread.so
maximizeit: /usr/lib/i386-linux-gnu/libboost_system.so
maximizeit: /usr/lib/i386-linux-gnu/libpthread.so
maximizeit: CMakeFiles/maximizeit.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable maximizeit"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maximizeit.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maximizeit.dir/build: maximizeit
.PHONY : CMakeFiles/maximizeit.dir/build

CMakeFiles/maximizeit.dir/requires: CMakeFiles/maximizeit.dir/maximizeit.cpp.o.requires
.PHONY : CMakeFiles/maximizeit.dir/requires

CMakeFiles/maximizeit.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maximizeit.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maximizeit.dir/clean

CMakeFiles/maximizeit.dir/depend:
	cd /home/algolab/Desktop/vb_shared/CGAL/maximizeit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/Desktop/vb_shared/CGAL/maximizeit /home/algolab/Desktop/vb_shared/CGAL/maximizeit /home/algolab/Desktop/vb_shared/CGAL/maximizeit /home/algolab/Desktop/vb_shared/CGAL/maximizeit /home/algolab/Desktop/vb_shared/CGAL/maximizeit/CMakeFiles/maximizeit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maximizeit.dir/depend

