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
CMAKE_SOURCE_DIR = /home/algolab/Desktop/vb_shared/CGAL/bistros

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/algolab/Desktop/vb_shared/CGAL/bistros

# Include any dependencies generated for this target.
include CMakeFiles/bistros.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bistros.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bistros.dir/flags.make

CMakeFiles/bistros.dir/bistros.cpp.o: CMakeFiles/bistros.dir/flags.make
CMakeFiles/bistros.dir/bistros.cpp.o: bistros.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/algolab/Desktop/vb_shared/CGAL/bistros/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/bistros.dir/bistros.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bistros.dir/bistros.cpp.o -c /home/algolab/Desktop/vb_shared/CGAL/bistros/bistros.cpp

CMakeFiles/bistros.dir/bistros.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bistros.dir/bistros.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/algolab/Desktop/vb_shared/CGAL/bistros/bistros.cpp > CMakeFiles/bistros.dir/bistros.cpp.i

CMakeFiles/bistros.dir/bistros.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bistros.dir/bistros.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/algolab/Desktop/vb_shared/CGAL/bistros/bistros.cpp -o CMakeFiles/bistros.dir/bistros.cpp.s

CMakeFiles/bistros.dir/bistros.cpp.o.requires:
.PHONY : CMakeFiles/bistros.dir/bistros.cpp.o.requires

CMakeFiles/bistros.dir/bistros.cpp.o.provides: CMakeFiles/bistros.dir/bistros.cpp.o.requires
	$(MAKE) -f CMakeFiles/bistros.dir/build.make CMakeFiles/bistros.dir/bistros.cpp.o.provides.build
.PHONY : CMakeFiles/bistros.dir/bistros.cpp.o.provides

CMakeFiles/bistros.dir/bistros.cpp.o.provides.build: CMakeFiles/bistros.dir/bistros.cpp.o

# Object files for target bistros
bistros_OBJECTS = \
"CMakeFiles/bistros.dir/bistros.cpp.o"

# External object files for target bistros
bistros_EXTERNAL_OBJECTS =

bistros: CMakeFiles/bistros.dir/bistros.cpp.o
bistros: CMakeFiles/bistros.dir/build.make
bistros: /usr/lib/i386-linux-gnu/libmpfr.so
bistros: /usr/lib/i386-linux-gnu/libgmp.so
bistros: /usr/lib/libCGAL_Core.so
bistros: /usr/lib/libCGAL.so
bistros: /usr/lib/i386-linux-gnu/libboost_thread.so
bistros: /usr/lib/i386-linux-gnu/libboost_system.so
bistros: /usr/lib/i386-linux-gnu/libpthread.so
bistros: /usr/lib/libCGAL_Core.so
bistros: /usr/lib/libCGAL.so
bistros: /usr/lib/i386-linux-gnu/libboost_thread.so
bistros: /usr/lib/i386-linux-gnu/libboost_system.so
bistros: /usr/lib/i386-linux-gnu/libpthread.so
bistros: CMakeFiles/bistros.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bistros"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bistros.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bistros.dir/build: bistros
.PHONY : CMakeFiles/bistros.dir/build

CMakeFiles/bistros.dir/requires: CMakeFiles/bistros.dir/bistros.cpp.o.requires
.PHONY : CMakeFiles/bistros.dir/requires

CMakeFiles/bistros.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bistros.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bistros.dir/clean

CMakeFiles/bistros.dir/depend:
	cd /home/algolab/Desktop/vb_shared/CGAL/bistros && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/algolab/Desktop/vb_shared/CGAL/bistros /home/algolab/Desktop/vb_shared/CGAL/bistros /home/algolab/Desktop/vb_shared/CGAL/bistros /home/algolab/Desktop/vb_shared/CGAL/bistros /home/algolab/Desktop/vb_shared/CGAL/bistros/CMakeFiles/bistros.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bistros.dir/depend

