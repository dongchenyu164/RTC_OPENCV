set(comp_srcs RTC_ImageProcess.cpp imProcessPortSVC_impl.cpp )
set(standalone_srcs RTC_ImageProcessComp.cpp)

if (DEFINED OPENRTM_INCLUDE_DIRS)
  string(REGEX REPLACE "-I" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_INCLUDE_DIRS "${OPENRTM_INCLUDE_DIRS}")
endif (DEFINED OPENRTM_INCLUDE_DIRS)

if (DEFINED OPENRTM_LIBRARY_DIRS)
  string(REGEX REPLACE "-L" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARY_DIRS "${OPENRTM_LIBRARY_DIRS}")
endif (DEFINED OPENRTM_LIBRARY_DIRS)

if (DEFINED OPENRTM_LIBRARIES)
  string(REGEX REPLACE "-l" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
  string(REGEX REPLACE " ;" ";"
    OPENRTM_LIBRARIES "${OPENRTM_LIBRARIES}")
endif (DEFINED OPENRTM_LIBRARIES)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR}/idl)
include_directories(${OPENRTM_INCLUDE_DIRS})
include_directories(${OMNIORB_INCLUDE_DIRS})
add_definitions(${OPENRTM_CFLAGS})
add_definitions(${OMNIORB_CFLAGS})

MAP_ADD_STR(comp_hdrs "../" comp_headers)

link_directories(${OPENRTM_LIBRARY_DIRS})
link_directories(${OMNIORB_LIBRARY_DIRS})

# ------------ nagano add code ------------------------------------

find_package(OpenCV REQUIRED)
#find_package(PCL 1.7 REQUIRED)

## --- GCC, GXX ---- ##
add_definitions(-std=gnu++11)
add_definitions("-v")
#add_definitions(${PCL_DEFINITIONS})

set ( additional_source	
	imProcess.cpp
	imProcessLib.cpp
	)
	
set ( additional_libraries
	${OpenCV_LIBS}
#	${PCL_LIBRARIES}
	)

include_directories(
	${OpenCV_INCLUDE_DIRS}
#	${PCL_INCLUDE_DIRS}
	)	

# ------------ end ------------------------------------------------


# --------- nagano change code ----------------------------------

#add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs}
#  ${comp_headers} ${ALL_IDL_SRCS})

add_library(${PROJECT_NAME} ${LIB_TYPE} ${comp_srcs} 
	${comp_headers} ${ALL_IDL_SRCS} ${additional_source})
	
# --------- end ---------------------------------------------

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_source_files_properties(${ALL_IDL_SRCS} PROPERTIES GENERATED 1)
if(NOT TARGET ALL_IDL_TGT)
  add_custom_target(ALL_IDL_TGT)
endif(NOT TARGET ALL_IDL_TGT)
add_dependencies(${PROJECT_NAME} ALL_IDL_TGT)
target_link_libraries(${PROJECT_NAME} ${OPENRTM_LIBRARIES})

# --------- nagano change code ----------------------------------
#add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
#  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS})
  
add_executable(${PROJECT_NAME}Comp ${standalone_srcs}
  ${comp_srcs} ${comp_headers} ${ALL_IDL_SRCS} ${additional_source})
# --------- end ---------------------------------------------

target_link_libraries(${PROJECT_NAME}Comp ${OPENRTM_LIBRARIES})

# --------- nagano add code ----------------------------------
target_link_libraries( ${PROJECT_NAME}Comp ${additional_libraries} )
target_link_libraries(${PROJECT_NAME} ${additional_libraries})

# --------- end ---------------------------------------------

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}Comp
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_INSTALL_DIR} COMPONENT component
    LIBRARY DESTINATION ${LIB_INSTALL_DIR} COMPONENT component
    ARCHIVE DESTINATION ${LIB_INSTALL_DIR} COMPONENT component)
install(EXPORT ${PROJECT_NAME}
    DESTINATION ${LIB_INSTALL_DIR}/${PROJECT_NAME}
    FILE ${PROJECT_NAME}Depends.cmake)
