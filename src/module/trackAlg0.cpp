#include "trackAlg0.h"

void trackAlg::move_mode(int8_t mode)
{
    motor_power_t motorPowers;
    switch(mode){
        case STOP:
            motorPowers.flw_MOT_power = 0;
            motorPowers.frw_MOT_power = 0;
            motorPowers.bcw_MOT_power = 0;
            break;
        case FRWRD_FS:
            motorPowers = FRWRD_FS_MOTPWR;
            break;
        case FRWRD_SS:
            motorPowers = FRWRD_SS_MOTPWR;
            break;
        case BCKWRD:
            motorPowers = FRWRD_SS_MOTPWR;
            motorPowers.frw_MOT_power = -1*motorPowers.frw_MOT_power;
            motorPowers.flw_MOT_power = -1*motorPowers.flw_MOT_power;
            motorPowers.bcw_MOT_power = -1*motorPowers.bcw_MOT_power;
            break;
        case FRWRD_RIGHT: //steer right = left faster
            motorPowers = STEER_RIGHT_MOTPWR;
            break;
        case FRWRD_LEFT: //steer left = right faster
            motorPowers = STEER_LEFT_MOTPWR;
            break;
        case HARD_FRWRD_RIGHT:
            motorPowers = HARDSTEER_RIGHT_MOTPWR;
            break;
        case HARD_FRWRD_LEFT:
            motorPowers = HARDSTEER_LEFT_MOTPWR;
            break;
    }
    _vehicle->set_motorPower(motorPowers);
}

void trackAlg::init(vehicle *_veh, IRsensors_t *ir) {
    _vehicle = _veh;
    irsensors = ir;
}

void trackAlg::readIr()
{
    irsensors->read();
}



void trackAlg::run()
{
    IRsensors_readings_t readings = irsensors->getReading();
    edgeBool = 0;
    if(CROSS_THRESH(readings.FR_val, IR_SENS_EDGE_THRESH))SBI(edgeBool, FR_IR_BIT);
    if(CROSS_THRESH(readings.FL_val, IR_SENS_EDGE_THRESH))SBI(edgeBool, FL_IR_BIT);
    if(CROSS_THRESH(readings.FFC_val, IR_SENS_EDGE_THRESH))SBI(edgeBool, FFC_IR_BIT);
    switch (edgeBool)
    {
    case 0:
        vehicle_moveMode = FRWRD_FS;
        move_mode(FRWRD_FS);
        break;
    
    case (1 << FFC_IR_BIT) | (1 << FL_IR_BIT): //FRONT LEFT_TRIGGERED steer right
        vehicle_moveMode = FRWRD_RIGHT;
        move_mode(FRWRD_RIGHT);
        break;
        
    case (1 << FL_IR_BIT):
        vehicle_moveMode = FRWRD_RIGHT;
        move_mode(FRWRD_RIGHT);
        break;

    case (1 << FFC_IR_BIT) | (1 << FR_IR_BIT): //FRONT RIGHT_TRIGGERED steer left
        vehicle_moveMode = FRWRD_LEFT;
        move_mode(HARD_FRWRD_LEFT);
        break;

    case ( 1<< FR_IR_BIT):
        vehicle_moveMode = FRWRD_LEFT;
        move_mode(FRWRD_LEFT);
        break;
        
    case ( 1 << FFC_IR_BIT):
        vehicle_moveMode = FRWRD_SS;
        move_mode(FRWRD_SS);
        break;

    default:
        vehicle_moveMode = ERR;
        break;
    }
}
uint8_t trackAlg::get_edgeBool()
{
    return edgeBool;
}

int8_t trackAlg::get_vehicleMoveMode()
{
    return vehicle_moveMode;
}
