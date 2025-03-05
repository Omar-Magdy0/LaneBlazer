#include "temp_modules.h"

void inspect_vehicle(){
  veh_cntrlType type;
  veh_state_t state = vehicle_laneBlazer->get_vehicleState();
  veh_state_t target = vehicle_laneBlazer->get_vehicleTarget();
  motor_power_t mot = vehicle_laneBlazer->get_motorPower();
  debug_out("target_SPD %f", target.veh_spd_mm_s);
  debug_out("target_angV %f", target.veh_angV_rad_s);
  debug_out("target_FRW_angV %f", target.frw_angV_rad_s);
  debug_out("target_FLW_angV %f", target.flw_angV_rad_s);
  debug_out("current_SPD %f", state.veh_spd_mm_s);
  debug_out("current_angV %f", state.veh_angV_rad_s);
  debug_out("current_FRW_angV %f", state.frw_angV_rad_s);
  debug_out("current_FLW_angV %f", state.flw_angV_rad_s);
  debug_out("right_power %f", mot.frw_MOT_power);
  debug_out("left power %f", mot.flw_MOT_power);
  debug_out("back power %f", mot.bcw_MOT_power);
}


void inspect_IRsensors(IRsensors_readings_t &readings)
{
  debug_out<int>("FR SENSOR %d", readings.FR_val);
  debug_out<int>("FL SENSOR %d", readings.FL_val);
  debug_out<int>("FFC SENSOR %d", readings.FFC_val);
}

void inspect_Alg(trackAlg &alg){
  uint8_t edgeBool = alg.get_edgeBool();
  bool fr_edge = BV(edgeBool, FR_IR_BIT);
  bool fl_edge = BV(edgeBool, FL_IR_BIT);
  bool ffc_edge = BV(edgeBool, FFC_IR_BIT);
  debug_out<bool>("FR EDGE DETECTED %d", fr_edge);
  debug_out<bool>("FL EDGE DETECTED %d", fl_edge);
  debug_out<bool>("FFC EDGE DETECTED %d", ffc_edge);
  debug_out<int>("MOVE MODE %d", alg.get_vehicleMoveMode());
}