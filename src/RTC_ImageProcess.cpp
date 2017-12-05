// -*- C++ -*-
/*!
 * @file  RTC_ImageProcess.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

// ======================================================================
//
//	include
//
// =======================================================================
#include "RTC_ImageProcess.h"
#include "imProcess.h"
#include "imProcessLib.h"

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/viz.hpp>

// ======================================================================
//
//	prototype declaration
//
// =======================================================================

// ======================================================================
//
//	main program
//
// =======================================================================

// Module specification
// <rtc-template block="module_spec">
static const char* rtc_imageprocess_spec[] = { "implementation_id",
		"RTC_ImageProcess", "type_name", "RTC_ImageProcess", "description",
		"ModuleDescription", "version", "1.0.0", "vendor", "Keisuke Nagano",
		"category", "Category", "activity_type", "PERIODIC", "kind",
		"DataFlowComponent", "max_instance", "1", "language", "C++",
		"lang_type", "compile", "" };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RTC_ImageProcess::RTC_ImageProcess(RTC::Manager* manager)
// <rtc-template block="initializer">
:
				RTC::DataFlowComponentBase(manager),
				m_command_inIn("command_in", m_command_in),
				m_color_inIn("color_in", m_color_in),
				m_depth_inIn("depth_in", m_depth_in),
				m_ir_inIn("ir_in", m_ir_in),
				m_command_outOut("command_out", m_command_out),
				m_value_outOut("value_out", m_value_out),
				m_svImProcessPort("svImProcess"),
				m_sv_ip(
						&m_color_inIn,
						&m_color_in,
						&m_depth_inIn,
						&m_depth_in,
						&m_ir_inIn,
						&m_ir_in)

// </rtc-template>
{
}

/*!
 * @brief destructor
 */
RTC_ImageProcess::~RTC_ImageProcess() {
}

RTC::ReturnCode_t RTC_ImageProcess::onInitialize() {
	// Registration: InPort/OutPort/Service
	// <rtc-template block="registration">
	// Set InPort buffers
	addInPort("command_in", m_command_inIn);
	addInPort("color_in", m_color_inIn);
	addInPort("depth_in", m_depth_inIn);
	addInPort("ir_in", m_ir_inIn);

	// Set OutPort buffer
	addOutPort("command_out", m_command_outOut);
	addOutPort("value_out", m_value_outOut);

	// Set service provider to Ports
	m_svImProcessPort.registerProvider("sv_ip", "ComImProcess", m_sv_ip);

	// Set service consumers to Ports

	// Set CORBA Service Ports
	addPort(m_svImProcessPort);

	// </rtc-template>

	// <rtc-template block="bind_config">
	// </rtc-template>

	return RTC::RTC_OK;
}

/*
 RTC::ReturnCode_t RTC_ImageProcess::onFinalize()
 {
 return RTC::RTC_OK;
 }
 */

/*
 RTC::ReturnCode_t RTC_ImageProcess::onStartup(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

/*
 RTC::ReturnCode_t RTC_ImageProcess::onShutdown(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

RTC::ReturnCode_t RTC_ImageProcess::onActivated(RTC::UniqueId ec_id) {
	return RTC::RTC_OK;
}

/*
 RTC::ReturnCode_t RTC_ImageProcess::onDeactivated(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

RTC::ReturnCode_t RTC_ImageProcess::onExecute(RTC::UniqueId ec_id) {

	if (m_command_inIn.isNew()) {
		//read new command
		m_command_inIn.read();

		std::cout << m_command_in.data << std::endl;

		image_process();

	}

	return RTC::RTC_OK;
}

/*
 RTC::ReturnCode_t RTC_ImageProcess::onAborting(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

RTC::ReturnCode_t RTC_ImageProcess::onError(RTC::UniqueId ec_id) {
	return RTC::RTC_OK;
}

/*
 RTC::ReturnCode_t RTC_ImageProcess::onReset(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

/*
 RTC::ReturnCode_t RTC_ImageProcess::onStateUpdate(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

/*
 RTC::ReturnCode_t RTC_ImageProcess::onRateChanged(RTC::UniqueId ec_id)
 {
 return RTC::RTC_OK;
 }
 */

extern "C" {

void RTC_ImageProcessInit(RTC::Manager* manager) {
	coil::Properties profile(rtc_imageprocess_spec);
	manager->registerFactory(
			profile,
			RTC::Create<RTC_ImageProcess>,
			RTC::Delete<RTC_ImageProcess>);
}

}
;

