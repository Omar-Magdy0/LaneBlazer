#pragma once
#include "core/core.h"

//COMMUNICATION
#define DEBUG_ CONF_ENABLE
#if defined(DEBUG_) && ENABLED(DEBUG_)
    #define DEBUG_PORT 1        //1 for UART1,  2 for UART2...., TCP so on
    #define DEBUG_PORT_BAUD 115200         //IF choice was a UART
    #define DEBUG_BUFFER_SIZE 40
    #define DEBUG_PARSER CONF_ENABLE
#endif


#define COMMAND_BUFFER_SIZE 32
#define COMMAND_DELIMETER " "
//COMMUNICATION END


//MOTION SYSTEM DEFINED (USEFull for later configuration)
#define VEHICLE_MOTION_SYSTEM DELTA_DOUBLE_FRONT_NOSERVO
//MOTOR DRIVER TYPE
#define MOTOR_DRIVER L293D
/*-------------------PINS-------------------*/

/*---MOTOR---*/
#define MOT_PWM_RES_BITS 16
#define MOT_PWM_RES_FREQ 1000
//FRW_MOT : FRONT RIGHT WHEEL MOTOR   ;   D1 and D2 : direction Control Pins  ; EN : Enable Pin  ; Logic : Logic for certain state
#define FRW_MOT_D1 PB13//pin
#define FRW_MOT_D2 PB12//pin
#define FRW_MOT_EN PB6  //pin
#define FRW_MOT_FRWRD_D1_LOGIC HIGH 
#define FRW_MOT_EN_LOGIC HIGH  //pin
#define FRW_DCMOT_DEADZONE 45 //40% duty cycle deadzone

//FLW_MOT : FRONT LEFT WHEEL MOTOR   ;   D1 and D2 : direction Control Pins  ; EN : Enable Pin  ; Logic : Logic for certain state
#define FLW_MOT_D1 PB14//pin
#define FLW_MOT_D2 PB15//pin
#define FLW_MOT_EN PB7//pin
#define FLW_MOT_FRWRD_D1_LOGIC LOW
#define FLW_MOT_EN_LOGIC HIGH  //pin
#define FLW_DCMOT_DEADZONE 45 //duty cycle deadzone

//BCW_MOT : BACK CENTER WHEEL MOTOR   ;   D1 and D2 : direction Control Pins  ; EN : Enable Pin  ; Logic : Logic for certain state
#define BACK_WHEEL_MOTOR CONF_ENABLE
#if defined(BACK_WHEEL_MOTOR) && ENABLED(BACK_WHEEL_MOTOR)
#define BCW_MOT_D1 PB4//pin
#define BCW_MOT_D2 PB5//pin
#define BCW_MOT_EN PB1//pin
#define BCW_MOT_FRWRD_D1_LOGIC HIGH  //pin
#define BCW_MOT_EN_LOGIC HIGH  //pin
#define BCW_DCMOT_DEADZONE 45 //duty cycle deadzone
#endif
/*---ENCODER---*/
#define ENCODER_TIMEOUT_US 500000
#define ENCODER_MIN_DT_US 1000
#define MIN_PULSES_LS 10 // Minimum number of pulses to consider high-speed mode for encoder calculations

//FRW_ENC: FRONT RIGHT WHEEL ENCODER   ;   IN1 and IN2 : ENCODER OUTPUTS  ; LOGIC : THE DETECTION OF PULSE ON RISING vs FALLING EDGE  , RISING = 1, FALLING = 0
#define FRW_ENCODER CONF_ENABLE
#if defined(FRW_ENCODER) && ENABLED(FRW_ENCODER)
#define FRW_ENCODER_TYPE PULSE
#define FRW_ENC_IN1 PB9 //pin
#define FRW_ENC_IN2 -1//pin
#define FRW_ENC_IN1_DEF_PINSTATE INPUT_PULLUP
#define FRW_ENC_IN1_EDGE RISING
#define FRW_ENC_IN2_LOGIC -1
#define FRW_ENC_IN2_DEF_PINSTATE INPUT_PULLUP
#define FRW_ENC_PULSES_PER_REV 20
#define FRW_WHEEL_DIAMETER_MM 66
#endif
//FLW_ENC: FRONT LEFT WHEEL ENCODER   ;   IN1 and IN2 : ENCODER OUTPUTS  ; LOGIC : THE DETECTION OF PULSE ON RISING vs FALLING EDGE  , RISING = 1, FALLING = 0
#define FLW_ENCODER CONF_ENABLE
#if defined(FLW_ENCODER) && ENABLED(FLW_ENCODER)
#define FLW_ENCODER_TYPE PULSE
#define FLW_ENC_IN1 PB8 //pin
#define FLW_ENC_IN2 -1//pin
#define FLW_ENC_IN1_DEF_PINSTATE INPUT_PULLUP
#define FLW_ENC_IN1_EDGE RISING
#define FLW_ENC_IN2_LOGIC -1
#define FLW_ENC_IN2_DEF_PINSTATE INPUT_PULLUP
#define FLW_ENC_PULSES_PER_REV 20
#define FLW_WHEEL_DIAMETER_MM 66
#endif
//BCW_ENC: BACK CENTER WHEEL ENCODER   ;   IN1 and IN2 : ENCODER OUTPUTS  ; LOGIC : THE DETECTION OF PULSE ON RISING vs FALLING EDGE  , RISING = 1, FALLING = 0
//#define BCW_ENCODER CONF_ENABLE
#if defined(BCW_ENCODER) && ENABLED(BCW_ENCODER)
#define ENCODER_TYPE VOID
#define BCW_ENC_IN1 -1 //pin
#define BCW_ENC_IN2 -1//pin
#define BCW_ENC_IN1_LOGIC //THE DETECTION OF PULSE ON RISING vs FALLING EDGE  , RISING = 1, FALLING = 0
#define BCW_ENC_IN1_DEF_PINSTATE INPUT_PULLUP
#define BCW_ENC_IN1_EDGE RISING
#define BCW_ENC_IN2_LOGIC
#define BCW_ENC_IN2_DEF_PINSTATE INPUT_PULLUP 
#define BCW_ENC_PULSES_PER_REV 20
#define BCW_WHEEL_DIAMETER_MM 66
#endif
/*-------------IR_SENSORS--------------*/
#define IR_SENS_NUM 4
#define IR_SENS_TYPE ANALOG 
#define IR_SENS_EDGE_THRESH 200
#define ANALOG_RES_BITS 12
#define FR_IR_IN A2 //pin
#define FL_IR_IN A0 //pin
#define FFC_IR_IN A1//pin

/************* Vehicle and TRACK dimensions ****************/
#define WHEEL_TRACK 145
#define TRACK_WIDTH 200
/************ TRACK ALG0 *********************************** */
//RIGHT LEFT BACKWARDCENTER    for delta vehicles
#define FRWRD_FS_MOTPWR {70, 70, 70}
#define FRWRD_SS_MOTPWR {50, 50, 50}
#define STEER_RIGHT_MOTPWR {-90, 90, 60}
#define STEER_LEFT_MOTPWR {90, -90, 60}
#define HARDSTEER_RIGHT_MOTPWR {-90, 90, 60}
#define HARDSTEER_LEFT_MOTPWR {90, -90, 60}

/**************Control **************/
#define CNTRLLOOP_FREQ 25
#define CNTRLLOOP_VEHCNTRLLOOP_FRATIO 1//(ControlLoopFreq/VehicleControlLoopFreq) ratio
#define CNTRLLOOP_VEHSENSORREAD_FRATIO 25 //(ControlLoopFreq/SensorReadFreq) ratio
#define CNTRLLOOP_TRACKALGRUN_FRATIO 1 //(ControlLoopFreq/TrackAlgFreq) ratio
#define CNTRLLOOP_TRACKALGSENSORREAD_FRATIO 1 //(ControlLoopFreq/IRSensorReadFreq) ratio
#define L_R_WHEEL_KP 0.25
#define L_R_WHEEL_KI 0.1
#define L_R_WHEEL_KD 0.1
#define L_R_WHEEL_FF 0.1 //FEEDFORWARD TERM
#define L_R_MINOUTPUT_THRESH 10
#define L_R_WHEEL_MAX_POWER 100 //MAXIMUM duty for controlling the DC motors
#define L_R_WHEEL_MIN_POWER -100 //MINIMUM duty for controlling the DC motors

 