// -*- C++ -*-
/*!
 * @file  RasPiMouseController.cpp
 * @brief Controll RasPiMouse
 * @date $Date$
 *
 * $Id$
 */

#include "RasPiMouseController.h"

// Module specification
// <rtc-template block="module_spec">
static const char* raspimousecontroller_spec[] =
  {
    "implementation_id", "RasPiMouseController",
    "type_name",         "RasPiMouseController",
    "description",       "Controll RasPiMouse",
    "version",           "1.2.1",
    "vendor",            "RaspberryPiMouseMaster",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.range", "2",
    // Widget
    "conf.__widget__.range", "slider.1",
    // Constraints
    "conf.__constraints__.range", "0<=x<=5",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
RasPiMouseController::RasPiMouseController(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_target_pointIn("target_point", m_target_point),
    m_target_velocityOut("target_velocity", m_target_velocity),
    m_throw_judgeOut("throw_judge", m_throw_judge)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
RasPiMouseController::~RasPiMouseController()
{
}



RTC::ReturnCode_t RasPiMouseController::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("target_point", m_target_pointIn);
  
  // Set OutPort buffer
  addOutPort("target_velocity", m_target_velocityOut);
  addOutPort("throw_judge", m_throw_judgeOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("range", m_range, "2");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t RasPiMouseController::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RasPiMouseController::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RasPiMouseController::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t RasPiMouseController::onActivated(RTC::UniqueId ec_id)
{
	m_target_velocity.data.vx = 0;
	m_target_velocity.data.vy = 0;
	m_target_velocity.data.va = 0;
	setTimestamp(m_target_velocity);
	m_target_velocityOut.write();

	return RTC::RTC_OK;
}

RTC::ReturnCode_t RasPiMouseController::onDeactivated(RTC::UniqueId ec_id)
{
	m_target_velocity.data.vx = 0;
	m_target_velocity.data.vy = 0;
	m_target_velocity.data.va = 0;
	setTimestamp(m_target_velocity);
	m_target_velocityOut.write();
	return RTC::RTC_OK;
}


RTC::ReturnCode_t RasPiMouseController::onExecute(RTC::UniqueId ec_id)
{
	if (m_target_pointIn.isNew()){
		m_target_pointIn.read();
		long distance = abs(m_target_point.data);
		double rotate_velocity;
		if (distance == 999)rotate_velocity = 0;
		else if (distance > 30)rotate_velocity = 0.8;
		else if (distance > 20) rotate_velocity = 0.3;
		else if (distance > 10)rotate_velocity = 0.2;
		else if (distance > 5)rotate_velocity = 0.1;
		else if (distance > m_range)rotate_velocity = 0.05;
		else rotate_velocity = 0;

		if ((distance != 999) && (rotate_velocity == 0)){
			clock_t nowTime = clock();
			//std::cout << "margin : " << nowTime - lastTime << std::endl;
			//std::cout << "nowTime : " <<nowTime<< std::endl;
			if (lastTime == 0){
				lastTime = nowTime;
				//m_throw_judge.data = false;
			}
			else {
				if (nowTime - lastTime > 3000){				//‚ ‚Æ‚Å•ÏX
					lastTime = 0;
					m_throw_judge.data = true;
				}
			}
		}
		else {
			m_throw_judge.data = false; //Œ©‚Â‚©‚ç‚È‚¢
			lastTime = 0;
		}

		setTimestamp(m_throw_judge);
		m_throw_judgeOut.write();

		if (m_target_point.data > 0)rotate_velocity = rotate_velocity * -1;

		//std::cout << "rotate_velocity = " << rotate_velocity << std::endl;
		m_target_velocity.data.va = rotate_velocity;
		setTimestamp(m_target_velocity);
		m_target_velocityOut.write();

	}
	return RTC::RTC_OK;
}
/*
RTC::ReturnCode_t RasPiMouseController::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RasPiMouseController::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RasPiMouseController::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RasPiMouseController::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t RasPiMouseController::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void RasPiMouseControllerInit(RTC::Manager* manager)
  {
    coil::Properties profile(raspimousecontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<RasPiMouseController>,
                             RTC::Delete<RasPiMouseController>);
  }
  
};


