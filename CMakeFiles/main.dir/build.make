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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/elannash/code/personal/rdbms

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/elannash/code/personal/rdbms

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c /Users/elannash/code/personal/rdbms/main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/main.cpp > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/main.cpp -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o: includes/binary_files/file_record.cpp
CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o -MF CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o.d -o CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o -c /Users/elannash/code/personal/rdbms/includes/binary_files/file_record.cpp

CMakeFiles/main.dir/includes/binary_files/file_record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/binary_files/file_record.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/binary_files/file_record.cpp > CMakeFiles/main.dir/includes/binary_files/file_record.cpp.i

CMakeFiles/main.dir/includes/binary_files/file_record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/binary_files/file_record.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/binary_files/file_record.cpp -o CMakeFiles/main.dir/includes/binary_files/file_record.cpp.s

CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o: includes/binary_files/utilities.cpp
CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o -MF CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o.d -o CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o -c /Users/elannash/code/personal/rdbms/includes/binary_files/utilities.cpp

CMakeFiles/main.dir/includes/binary_files/utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/binary_files/utilities.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/binary_files/utilities.cpp > CMakeFiles/main.dir/includes/binary_files/utilities.cpp.i

CMakeFiles/main.dir/includes/binary_files/utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/binary_files/utilities.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/binary_files/utilities.cpp -o CMakeFiles/main.dir/includes/binary_files/utilities.cpp.s

CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o: includes/command_line_interface/command_line_interface.cpp
CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o -MF CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o.d -o CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o -c /Users/elannash/code/personal/rdbms/includes/command_line_interface/command_line_interface.cpp

CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/command_line_interface/command_line_interface.cpp > CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.i

CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/command_line_interface/command_line_interface.cpp -o CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.s

CMakeFiles/main.dir/includes/parser/parser.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/parser/parser.cpp.o: includes/parser/parser.cpp
CMakeFiles/main.dir/includes/parser/parser.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/includes/parser/parser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/parser/parser.cpp.o -MF CMakeFiles/main.dir/includes/parser/parser.cpp.o.d -o CMakeFiles/main.dir/includes/parser/parser.cpp.o -c /Users/elannash/code/personal/rdbms/includes/parser/parser.cpp

CMakeFiles/main.dir/includes/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/parser/parser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/parser/parser.cpp > CMakeFiles/main.dir/includes/parser/parser.cpp.i

CMakeFiles/main.dir/includes/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/parser/parser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/parser/parser.cpp -o CMakeFiles/main.dir/includes/parser/parser.cpp.s

CMakeFiles/main.dir/includes/rpn/rpn.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/rpn/rpn.cpp.o: includes/rpn/rpn.cpp
CMakeFiles/main.dir/includes/rpn/rpn.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/includes/rpn/rpn.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/rpn/rpn.cpp.o -MF CMakeFiles/main.dir/includes/rpn/rpn.cpp.o.d -o CMakeFiles/main.dir/includes/rpn/rpn.cpp.o -c /Users/elannash/code/personal/rdbms/includes/rpn/rpn.cpp

CMakeFiles/main.dir/includes/rpn/rpn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/rpn/rpn.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/rpn/rpn.cpp > CMakeFiles/main.dir/includes/rpn/rpn.cpp.i

CMakeFiles/main.dir/includes/rpn/rpn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/rpn/rpn.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/rpn/rpn.cpp -o CMakeFiles/main.dir/includes/rpn/rpn.cpp.s

CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o: includes/shunting_yard/shunting_yard.cpp
CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o -MF CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o.d -o CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o -c /Users/elannash/code/personal/rdbms/includes/shunting_yard/shunting_yard.cpp

CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/shunting_yard/shunting_yard.cpp > CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.i

CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/shunting_yard/shunting_yard.cpp -o CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.s

CMakeFiles/main.dir/includes/sql/sql.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/sql/sql.cpp.o: includes/sql/sql.cpp
CMakeFiles/main.dir/includes/sql/sql.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/includes/sql/sql.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/sql/sql.cpp.o -MF CMakeFiles/main.dir/includes/sql/sql.cpp.o.d -o CMakeFiles/main.dir/includes/sql/sql.cpp.o -c /Users/elannash/code/personal/rdbms/includes/sql/sql.cpp

CMakeFiles/main.dir/includes/sql/sql.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/sql/sql.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/sql/sql.cpp > CMakeFiles/main.dir/includes/sql/sql.cpp.i

CMakeFiles/main.dir/includes/sql/sql.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/sql/sql.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/sql/sql.cpp -o CMakeFiles/main.dir/includes/sql/sql.cpp.s

CMakeFiles/main.dir/includes/table/table.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/table/table.cpp.o: includes/table/table.cpp
CMakeFiles/main.dir/includes/table/table.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/includes/table/table.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/table/table.cpp.o -MF CMakeFiles/main.dir/includes/table/table.cpp.o.d -o CMakeFiles/main.dir/includes/table/table.cpp.o -c /Users/elannash/code/personal/rdbms/includes/table/table.cpp

CMakeFiles/main.dir/includes/table/table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/table/table.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/table/table.cpp > CMakeFiles/main.dir/includes/table/table.cpp.i

CMakeFiles/main.dir/includes/table/table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/table/table.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/table/table.cpp -o CMakeFiles/main.dir/includes/table/table.cpp.s

CMakeFiles/main.dir/includes/token/child_tokens.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/token/child_tokens.cpp.o: includes/token/child_tokens.cpp
CMakeFiles/main.dir/includes/token/child_tokens.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/main.dir/includes/token/child_tokens.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/token/child_tokens.cpp.o -MF CMakeFiles/main.dir/includes/token/child_tokens.cpp.o.d -o CMakeFiles/main.dir/includes/token/child_tokens.cpp.o -c /Users/elannash/code/personal/rdbms/includes/token/child_tokens.cpp

CMakeFiles/main.dir/includes/token/child_tokens.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/token/child_tokens.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/token/child_tokens.cpp > CMakeFiles/main.dir/includes/token/child_tokens.cpp.i

CMakeFiles/main.dir/includes/token/child_tokens.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/token/child_tokens.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/token/child_tokens.cpp -o CMakeFiles/main.dir/includes/token/child_tokens.cpp.s

CMakeFiles/main.dir/includes/token/token.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/token/token.cpp.o: includes/token/token.cpp
CMakeFiles/main.dir/includes/token/token.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/main.dir/includes/token/token.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/token/token.cpp.o -MF CMakeFiles/main.dir/includes/token/token.cpp.o.d -o CMakeFiles/main.dir/includes/token/token.cpp.o -c /Users/elannash/code/personal/rdbms/includes/token/token.cpp

CMakeFiles/main.dir/includes/token/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/token/token.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/token/token.cpp > CMakeFiles/main.dir/includes/token/token.cpp.i

CMakeFiles/main.dir/includes/token/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/token/token.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/token/token.cpp -o CMakeFiles/main.dir/includes/token/token.cpp.s

CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o: includes/tokenizer/ftokenize.cpp
CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o -c /Users/elannash/code/personal/rdbms/includes/tokenizer/ftokenize.cpp

CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/tokenizer/ftokenize.cpp > CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.i

CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/tokenizer/ftokenize.cpp -o CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.s

CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o: includes/tokenizer/statemachinefunctions.cpp
CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o -c /Users/elannash/code/personal/rdbms/includes/tokenizer/statemachinefunctions.cpp

CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/tokenizer/statemachinefunctions.cpp > CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.i

CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/tokenizer/statemachinefunctions.cpp -o CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.s

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: includes/tokenizer/stokenize.cpp
CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o -MF CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o.d -o CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o -c /Users/elannash/code/personal/rdbms/includes/tokenizer/stokenize.cpp

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elannash/code/personal/rdbms/includes/tokenizer/stokenize.cpp > CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.i

CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elannash/code/personal/rdbms/includes/tokenizer/stokenize.cpp -o CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o" \
"CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o" \
"CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o" \
"CMakeFiles/main.dir/includes/parser/parser.cpp.o" \
"CMakeFiles/main.dir/includes/rpn/rpn.cpp.o" \
"CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o" \
"CMakeFiles/main.dir/includes/sql/sql.cpp.o" \
"CMakeFiles/main.dir/includes/table/table.cpp.o" \
"CMakeFiles/main.dir/includes/token/child_tokens.cpp.o" \
"CMakeFiles/main.dir/includes/token/token.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o" \
"CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

bin/main: CMakeFiles/main.dir/main.cpp.o
bin/main: CMakeFiles/main.dir/includes/binary_files/file_record.cpp.o
bin/main: CMakeFiles/main.dir/includes/binary_files/utilities.cpp.o
bin/main: CMakeFiles/main.dir/includes/command_line_interface/command_line_interface.cpp.o
bin/main: CMakeFiles/main.dir/includes/parser/parser.cpp.o
bin/main: CMakeFiles/main.dir/includes/rpn/rpn.cpp.o
bin/main: CMakeFiles/main.dir/includes/shunting_yard/shunting_yard.cpp.o
bin/main: CMakeFiles/main.dir/includes/sql/sql.cpp.o
bin/main: CMakeFiles/main.dir/includes/table/table.cpp.o
bin/main: CMakeFiles/main.dir/includes/token/child_tokens.cpp.o
bin/main: CMakeFiles/main.dir/includes/token/token.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/ftokenize.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/statemachinefunctions.cpp.o
bin/main: CMakeFiles/main.dir/includes/tokenizer/stokenize.cpp.o
bin/main: CMakeFiles/main.dir/build.make
bin/main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/elannash/code/personal/rdbms/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable bin/main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: bin/main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /Users/elannash/code/personal/rdbms && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/elannash/code/personal/rdbms /Users/elannash/code/personal/rdbms /Users/elannash/code/personal/rdbms /Users/elannash/code/personal/rdbms /Users/elannash/code/personal/rdbms/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

