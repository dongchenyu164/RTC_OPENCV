// -*-C++-*-
/*!
 * @file  imProcessPortSVC_impl.h
 * @brief Service implementation header of imProcessPort.idl
 *
 */

#include "InterfaceDataTypesSkel.h"
#include "BasicDataTypeSkel.h"
#include "ExtendedDataTypesSkel.h"

#include "imProcessPortSkel.h"

#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

//
#include <opencv2/opencv.hpp>

#ifndef IMPROCESSPORTSVC_IMPL_H
#define IMPROCESSPORTSVC_IMPL_H

/*!
 * @class ComImProcessSVC_impl
 * Example class implementing IDL interface ComImProcess
 */
class ComImProcessSVC_impl: public virtual POA_ComImProcess,
		public virtual PortableServer::RefCountServantBase {
private:
	// Make sure all instances are built on the heap by making the
	// destructor non-public
	//virtual ~ComImProcessSVC_impl();

public:
	/*!
	 * @brief standard constructor
	 */
	ComImProcessSVC_impl(
			RTC::InPort<RTC::CameraImage> *m_c_i,
			RTC::CameraImage *m_c,
			RTC::InPort<RTC::CameraImage> *m_d_i,
			RTC::CameraImage *m_d,
			RTC::InPort<RTC::CameraImage> *m_ir_i,
			RTC::CameraImage *m_ir);
	ComImProcessSVC_impl();
	/*!
	 * @brief destructor
	 */
	virtual ~ComImProcessSVC_impl();

	// attributes and operations
	RTC::CameraImage* get_colorImage(::CORBA::Boolean& ref);
	RTC::CameraImage* get_irImage(::CORBA::Boolean& ref);
	RTC::CameraImage* get_depthImage(::CORBA::Boolean& ref);
	::CORBA::Boolean save_colorImage(const char* str);
	::CORBA::Boolean save_irImage(const char* str);
	::CORBA::Boolean save_depthImage(const char* str);

	::CORBA::Long getCupRimLevel_InPixle();
	::CORBA::Long getLiquidLevel_InPixle();
	::CORBA::Boolean getBackgroundToAlgorithm();
	::CORBA::Boolean getEmptyCupToAlgorithm();

	//User Variable
	bool NeedRecord = true;

	std::string Save_Path;
	const std::string Save_Root = "/home/dong/Workspace/dong/DataRecord/";// /home/dong/Workspace/dong/DataRecord/8989898
	int gCupMax;
	cv::Mat gBackGround;
	cv::Mat gEmptyCup;

	//User Function
	bool CreateFolder_NowTime();

	// ------------------ argument -----------------------------
	RTC::InPort<RTC::CameraImage> *m_color_inIn;
	RTC::CameraImage *m_color_in;
	RTC::InPort<RTC::CameraImage> *m_depth_inIn;
	RTC::CameraImage *m_depth_in;
	RTC::InPort<RTC::CameraImage> *m_ir_inIn;
	RTC::CameraImage *m_ir_in;

};

#endif // IMPROCESSPORTSVC_IMPL_H

