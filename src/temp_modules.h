#pragma once
#include "core/debug_interface.h"
#include "core/delta_sys.h"
#include "module/IRsensor.h"
#include "module/trackAlg0.h"

void inspect_vehicle();
void inspect_IRsensors(IRsensors_readings_t &);
void inspect_Alg(trackAlg &);
