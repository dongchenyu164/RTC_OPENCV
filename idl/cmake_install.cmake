# Install script for directory: /home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "idl")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/include/rtc_imageprocess-1/idl" TYPE FILE FILES
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/imProcessPort.idl"
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/InterfaceDataTypes.idl"
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/BasicDataType.idl"
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/ExtendedDataTypes.idl"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "idl")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/components/include/rtc_imageprocess-1/rtc_imageprocess/idl" TYPE FILE FILES
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/imProcessPort.hh"
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/InterfaceDataTypes.hh"
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/BasicDataType.hh"
    "/home/dong/Workspace/dong/rtc/RTC_ImageProcess/idl/ExtendedDataTypes.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

