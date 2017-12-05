#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "RTC_ImageProcess" for configuration ""
set_property(TARGET RTC_ImageProcess APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(RTC_ImageProcess PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil;opencv_calib3d;opencv_core;opencv_features2d;opencv_flann;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_ml;opencv_objdetect;opencv_photo;opencv_shape;opencv_stitching;opencv_superres;opencv_video;opencv_videoio;opencv_videostab;opencv_viz;opencv_aruco;opencv_bgsegm;opencv_bioinspired;opencv_ccalib;opencv_datasets;opencv_dnn;opencv_dpm;opencv_face;opencv_freetype;opencv_fuzzy;opencv_line_descriptor;opencv_optflow;opencv_phase_unwrapping;opencv_plot;opencv_reg;opencv_rgbd;opencv_saliency;opencv_stereo;opencv_structured_light;opencv_surface_matching;opencv_text;opencv_tracking;opencv_xfeatures2d;opencv_ximgproc;opencv_xobjdetect;opencv_xphoto"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/RTC_ImageProcess.so"
  IMPORTED_SONAME_NOCONFIG "RTC_ImageProcess.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS RTC_ImageProcess )
list(APPEND _IMPORT_CHECK_FILES_FOR_RTC_ImageProcess "${_IMPORT_PREFIX}/components/lib/RTC_ImageProcess.so" )

# Import target "RTC_ImageProcessComp" for configuration ""
set_property(TARGET RTC_ImageProcessComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(RTC_ImageProcessComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/RTC_ImageProcessComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS RTC_ImageProcessComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_RTC_ImageProcessComp "${_IMPORT_PREFIX}/components/bin/RTC_ImageProcessComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
