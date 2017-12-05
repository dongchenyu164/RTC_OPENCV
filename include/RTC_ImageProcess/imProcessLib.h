
// ======================================================================
//
//	include
//
// =======================================================================

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/viz.hpp>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// ======================================================================
//
//	include For Dong
//
// =======================================================================
#include <iomanip>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>

#include <sys/stat.h>
#include <sys/types.h>
// ======================================================================
//
//	arguments
//
// =======================================================================

// ======================================================================
//
//	prototype declaration
//
// =======================================================================
void cvt_RTCcolor_to_CVcolor(RTC::CameraImage& rtc_color, cv::Mat& color);
void cvt_RTCdepth_to_CVdepth(RTC::CameraImage& rtc_depth, cv::Mat& depth);
void cvt_RTCir_to_CVir(RTC::CameraImage& rtc_ir, cv::Mat& ir);

int CupProcess(cv::Mat BackGround, cv::Mat EmptyCup);
//int OriginCupProcess(Mat RealTimeLiquidLevel, Mat EmptyCup);
int LiquidLevelCupProcess(cv::Mat RealTimeLiquidLevel, cv::Mat EmptyCup);
