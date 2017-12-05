# RTC_ImageProcess CMake config file
#
# This file sets the following variables:
# RTC_ImageProcess_FOUND - Always TRUE.
# RTC_ImageProcess_INCLUDE_DIRS - Directories containing the RTC_ImageProcess include files.
# RTC_ImageProcess_IDL_DIRS - Directories containing the RTC_ImageProcess IDL files.
# RTC_ImageProcess_LIBRARIES - Libraries needed to use RTC_ImageProcess.
# RTC_ImageProcess_DEFINITIONS - Compiler flags for RTC_ImageProcess.
# RTC_ImageProcess_VERSION - The version of RTC_ImageProcess found.
# RTC_ImageProcess_VERSION_MAJOR - The major version of RTC_ImageProcess found.
# RTC_ImageProcess_VERSION_MINOR - The minor version of RTC_ImageProcess found.
# RTC_ImageProcess_VERSION_REVISION - The revision version of RTC_ImageProcess found.
# RTC_ImageProcess_VERSION_CANDIDATE - The candidate version of RTC_ImageProcess found.

message(STATUS "Found RTC_ImageProcess-1.0.0")
set(RTC_ImageProcess_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(RTC_ImageProcess_INCLUDE_DIRS
#    "/usr/local/include/rtc_imageprocess-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(RTC_ImageProcess_IDL_DIRS
#    "/usr/local/include/rtc_imageprocess-1/idl")
set(RTC_ImageProcess_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(RTC_ImageProcess_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(RTC_ImageProcess_LIBRARIES
        "/usr/local/components/lib/librtc_imageprocess.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(RTC_ImageProcess_LIBRARIES
        "/usr/local/components/lib/librtc_imageprocess.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(RTC_ImageProcess_DEFINITIONS ${<dependency>_DEFINITIONS})

set(RTC_ImageProcess_VERSION 1.0.0)
set(RTC_ImageProcess_VERSION_MAJOR 1)
set(RTC_ImageProcess_VERSION_MINOR 0)
set(RTC_ImageProcess_VERSION_REVISION 0)
set(RTC_ImageProcess_VERSION_CANDIDATE )

