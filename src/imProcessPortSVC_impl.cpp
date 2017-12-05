// -*-C++-*-
/*!
 * @file  imProcessPortSVC_impl.cpp
 * @brief Service implementation code of imProcessPort.idl
 *
 */

#include "imProcessPortSVC_impl.h"
#include "imProcessLib.h"

#include <omp.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/viz.hpp>

/*
 * Example implementational code for IDL interface ComImProcess
 */
ComImProcessSVC_impl::ComImProcessSVC_impl(
		RTC::InPort<RTC::CameraImage> *m_c_i,
		RTC::CameraImage *m_c,
		RTC::InPort<RTC::CameraImage> *m_d_i,
		RTC::CameraImage *m_d,
		RTC::InPort<RTC::CameraImage> *m_ir_i,
		RTC::CameraImage *m_ir) {

	//Dong Code
	gCupMax = -1;

	if(NeedRecord)
	{
		if(!CreateFolder_NowTime())
		{
			NeedRecord = false;
			std::cout<<"Create Folder failed!!!!"<<std::endl;
		}
	}

	m_color_inIn = m_c_i;
	m_color_in = m_c;
	m_depth_inIn = m_d_i;
	m_depth_in = m_d;
	m_ir_in = m_ir;
	m_ir_inIn = m_ir_i;

}

ComImProcessSVC_impl::ComImProcessSVC_impl() {
	// Please add extra constructor code here.
}

ComImProcessSVC_impl::~ComImProcessSVC_impl() {
	// Please add extra destructor code here.
}

/*
 * Methods corresponding to IDL attributes and operations
 */
// ======================================================================
//
//	process image
//
// =======================================================================

// ======================================================================
//
//	get image
//
// =======================================================================
RTC::CameraImage* ComImProcessSVC_impl::get_colorImage(::CORBA::Boolean& ref) {

	RTC::CameraImage* color = new RTC::CameraImage();

	std::cout << "exe get color image" << std::endl;
	if (m_color_inIn->isNew()) {
		m_color_inIn->read();
		std::cout << "discover new data" << std::endl;
		ref = true;
		*color = *m_color_in;
		return color;
	}

	std::cout << "not discover new data" << std::endl;
	ref = false;
	return color;
}

RTC::CameraImage* ComImProcessSVC_impl::get_irImage(::CORBA::Boolean& ref) {

	RTC::CameraImage* ir = new RTC::CameraImage();

	std::cout << "exe get ir image" << std::endl;
	if (m_ir_inIn->isNew()) {
		m_ir_inIn->read();
		std::cout << "discover new data" << std::endl;
		ref = true;
		*ir = *m_ir_in;
		return ir;
	}
	std::cout << "not discover new data" << std::endl;
	ref = false;
	return ir;
}

RTC::CameraImage* ComImProcessSVC_impl::get_depthImage(::CORBA::Boolean& ref) {

	RTC::CameraImage* depth = new RTC::CameraImage();

	std::cout << "exe get depth image" << std::endl;
	if (m_depth_inIn->isNew()) {
		m_depth_inIn->read();
		std::cout << "discover new data" << std::endl;
		ref = false;
		*depth = *m_depth_in;
		return depth;
	}
	std::cout << "not discover new data" << std::endl;
	ref = true;
	return depth;
}

// ======================================================================
//
//	save image
//
// =======================================================================

::CORBA::Boolean ComImProcessSVC_impl::save_colorImage(const char* str) {

	std::cout << "exe save color image" << std::endl;
	if (m_color_inIn->isNew()) {
		m_color_inIn->read();
		std::cout << "discover new data" << std::endl;

		cv::Mat color;
		cvt_RTCcolor_to_CVcolor(*m_color_in, color);

		cv::imwrite(str, color);

		return true;
	}
	std::cout << "not discover new data" << std::endl;
	return false;
}

::CORBA::Boolean ComImProcessSVC_impl::save_irImage(const char* str) {

	std::cout << "exe save ir image" << std::endl;
	if (m_ir_inIn->isNew()) {
		m_ir_inIn->read();
		std::cout << "discover new data" << std::endl;

		cv::Mat ir;
		cvt_RTCir_to_CVir(*m_ir_in, ir);

		cv::imwrite(str, ir);

		return true;
	}
	std::cout << "not discover new data" << std::endl;
	return false;
}

::CORBA::Boolean ComImProcessSVC_impl::save_depthImage(const char* str) {

	std::cout << "exe save depth image" << std::endl;
	if (m_depth_inIn->isNew()) {
		m_depth_inIn->read();
		std::cout << "discover new data" << std::endl;

		cv::Mat depth;
		cvt_RTCdepth_to_CVdepth(*m_depth_in, depth);

		cv::imwrite(str, depth);

		return true;
	}
	std::cout << "not discover new data" << std::endl;
	return false;
}

/**********************************************************************************************/
//int gCupMax = -1;
//cv::Mat gBackGround;
//cv::Mat gEmptyCup;

::CORBA::Long ComImProcessSVC_impl::getCupRimLevel_InPixle()
{
    int Res = 0;
	Res = CupProcess(ComImProcessSVC_impl::gBackGround.clone(), gEmptyCup.clone());

	cv::Mat tmp = ComImProcessSVC_impl::gEmptyCup.clone();
    cv::line(tmp, cv::Point(0, Res), cv::Point(640, Res), cv::Scalar(255, 0, 0));
	cv::imshow("口", tmp);
	gCupMax = Res;
    return Res;
}
::CORBA::Long ComImProcessSVC_impl::getLiquidLevel_InPixle()
{
    int Res = 0;
	static int count = 0;

    std::cout << "Excute getLiquidLevel_InPixle()" << std::endl;
    if (m_color_inIn->isNew())
    {
        m_color_inIn->read();
        std::cout << "Get new image!!!" << std::endl;

        cv::Mat RealTimeLiquidLevel;
		cvt_RTCcolor_to_CVcolor(*m_color_in, RealTimeLiquidLevel);

		if(NeedRecord)
			imwrite(Save_Path + "LiqLevel_" + std::to_string(count++) + ".png",RealTimeLiquidLevel);

        Res = LiquidLevelCupProcess(RealTimeLiquidLevel.clone(), gEmptyCup.clone());

        cv::line(RealTimeLiquidLevel, cv::Point(0, gCupMax), cv::Point(640, gCupMax), cv::Scalar(255, 0, 0));
		cv::line(RealTimeLiquidLevel, cv::Point(0, Res), cv::Point(640, Res), cv::Scalar(0, 255, 0));
		cv::line(RealTimeLiquidLevel, cv::Point(0, gCupMax + 80 - 10), cv::Point(640, gCupMax + 80 - 10), cv::Scalar(0, 0, 255));
		cv::imshow("液面", RealTimeLiquidLevel);

        return Res;
    }
    std::cout << "not discover new data" << std::endl;
    return -1;

}
::CORBA::Boolean ComImProcessSVC_impl::getBackgroundToAlgorithm()
{
    std::cout << "Excute getBackgroundToAlgorithm()" << std::endl;

    if (m_color_inIn->isNew())
    {
        m_color_inIn->read();
        std::cout << "Get background!!!" << std::endl;

        cvt_RTCcolor_to_CVcolor(*m_color_in, gBackGround);

		if(NeedRecord)
			imwrite(Save_Path + "BackGround.png" ,gBackGround);

        return true;
    }
    std::cout << "not discover new data" << std::endl;
    return false;
}
::CORBA::Boolean ComImProcessSVC_impl::getEmptyCupToAlgorithm()
{
    std::cout << "Excute getEmptyCupToAlgorithm()" << std::endl;

    if (m_color_inIn->isNew())
    {
        m_color_inIn->read();
        std::cout << "Get EmptyCup!!!" << std::endl;

        cvt_RTCcolor_to_CVcolor(*m_color_in, gEmptyCup);

		if(NeedRecord)
			imwrite(Save_Path + "EmptyCup.png",gEmptyCup);

        return true;
    }
    std::cout << "not discover new data" << std::endl;
    return false;
}

bool ComImProcessSVC_impl::CreateFolder_NowTime()
{
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream Time;
	Time << std::put_time(std::localtime(&t), "%Y-%m-%d_%H-%M-%S");
	ComImProcessSVC_impl::Save_Path = ComImProcessSVC_impl::Save_Root + Time.str() + "/";
	if(mkdir(ComImProcessSVC_impl::Save_Path.c_str(), S_IRWXU) == 0)
		return true;
	else
		return false;
}

/**********************************************************************************************/
// End of example implementational code

