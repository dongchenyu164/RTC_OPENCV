# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dong/Workspace/dong/rtc/RTC_ImageProcess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dong/Workspace/dong/rtc/RTC_ImageProcess

# Utility rule file for ExtendedDataTypes_TGT.

# Include the progress variables for this target.
include idl/CMakeFiles/ExtendedDataTypes_TGT.dir/progress.make

idl/CMakeFiles/ExtendedDataTypes_TGT: idl/ExtendedDataTypesSK.cc
idl/CMakeFiles/ExtendedDataTypes_TGT: idl/ExtendedDataTypes.hh
idl/CMakeFiles/ExtendedDataTypes_TGT: idl/ExtendedDataTypesDynSK.cc

idl/ExtendedDataTypesSK.cc: idl/ExtendedDataTypes.idl
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dong/Workspace/dong/rtc/RTC_ImageProcess/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Compiling /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/ExtendedDataTypes.idl"
	cd /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl && python /usr/bin/rtm-skelwrapper --include-dir= --skel-suffix=Skel --stub-suffix=Stub --idl-file=ExtendedDataTypes.idl
	cd /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl && /usr/bin/omniidl -bcxx -Wba -nf -Wbuse_quotes -I/usr/include/openrtm-1.1/rtm/idl /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/ExtendedDataTypes.idl

idl/ExtendedDataTypes.hh: idl/ExtendedDataTypesSK.cc

idl/ExtendedDataTypesDynSK.cc: idl/ExtendedDataTypesSK.cc

ExtendedDataTypes_TGT: idl/CMakeFiles/ExtendedDataTypes_TGT
ExtendedDataTypes_TGT: idl/ExtendedDataTypesSK.cc
ExtendedDataTypes_TGT: idl/ExtendedDataTypes.hh
ExtendedDataTypes_TGT: idl/ExtendedDataTypesDynSK.cc
ExtendedDataTypes_TGT: idl/CMakeFiles/ExtendedDataTypes_TGT.dir/build.make
.PHONY : ExtendedDataTypes_TGT

# Rule to build all files generated by this target.
idl/CMakeFiles/ExtendedDataTypes_TGT.dir/build: ExtendedDataTypes_TGT
.PHONY : idl/CMakeFiles/ExtendedDataTypes_TGT.dir/build

idl/CMakeFiles/ExtendedDataTypes_TGT.dir/clean:
	cd /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl && $(CMAKE_COMMAND) -P CMakeFiles/ExtendedDataTypes_TGT.dir/cmake_clean.cmake
.PHONY : idl/CMakeFiles/ExtendedDataTypes_TGT.dir/clean

idl/CMakeFiles/ExtendedDataTypes_TGT.dir/depend:
	cd /home/dong/Workspace/dong/rtc/RTC_ImageProcess && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dong/Workspace/dong/rtc/RTC_ImageProcess /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl /home/dong/Workspace/dong/rtc/RTC_ImageProcess /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/CMakeFiles/ExtendedDataTypes_TGT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : idl/CMakeFiles/ExtendedDataTypes_TGT.dir/depend

