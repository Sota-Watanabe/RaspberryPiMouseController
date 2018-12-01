// -*- C++ -*-
/*!
 * @file  RasPiMouseController.h
 * @brief Controll RasPiMouse
 * @date  $Date$
 *
 * @author Sota Watanabe cy16179@shibaura-it.ac.jp
 * $Id$
 */

#ifndef RASPIMOUSECONTROLLER_H
#define RASPIMOUSECONTROLLER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <time.h>

using namespace std;

/*!
 * @class RasPiMouseController
 * @brief Controll RasPiMouse
 *
 *このコンポーネントはRaspberryPiMouseRTCというコンポーネントに命令を出力するためのコンポーネントである。
 *詳細としては入力された値によってRaspberryPiMouseRTCに送る値(target_velocity)を変える。この送る値はRaspberryPiMouseが回転する移動量と方向(符号)である。
 *また999の値が入力としてきた場合は「なし」を意味している。
 *それ以外の値の場合は移動距離と方向(符号)を意味しているので、if文で条件分岐をし、移動速度を出力として渡す。
 *その際、移動距離が0であり、値が999でない場合は目的物の正面にあるので三秒以上のその状態の場合、throw_judgeにtrueを渡す
 *
 *RTMではじめるロボットアプリ開発 : robot technology middleware / セック著. -- 工学社, 2015. -- (I/O books).
 *Raspberry Piで学ぶROSロボット入門 / 上田隆一著. -- 日経BP社, 2017.
 *やさしいPython入門 / 日向俊二著. -- 第2版. -- カットシステム, 2018.
 */
class RasPiMouseController
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  RasPiMouseController(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~RasPiMouseController();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   * 始まってすぐ動かないようにm_target_velocity.dataをすべて0にし、setTimestampをし、m_target_velocityOutに書き込む
   *
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
  /***
   * onDeactivated時に停止させる
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *入力された値によってRaspberryPiMouseRTCに送る値(target_velocity)を変える。この送る値はRaspberryPiMouseが回転する移動量と方向(符号)である。
   *また999の値が入力としてきた場合は「なし」を意味している。
   *それ以外の値の場合は移動距離と方向(符号)を意味しているので、if文で条件分岐をし、移動速度を出力として渡す。
   *その際、移動距離が0であり、値が999でない場合は目的物の正面にあるので三秒以上のその状態の場合、throw_judgeにtrueを渡す
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  range
   * - DefaultValue: 2
   */
  int m_range;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedLong m_target_point;
  /*!
   */
  InPort<RTC::TimedLong> m_target_pointIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedVelocity2D m_target_velocity;
  /*!
   */
  OutPort<RTC::TimedVelocity2D> m_target_velocityOut;
  RTC::TimedBoolean m_throw_judge;
  /*!
   */
  OutPort<RTC::TimedBoolean> m_throw_judgeOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  // </rtc-template>
	 clock_t lastTime = 0;
  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void RasPiMouseControllerInit(RTC::Manager* manager);
};

#endif // RASPIMOUSECONTROLLER_H
