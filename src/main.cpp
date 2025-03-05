
/**
 * @file main.cpp
 * @brief FreeRTOS-based control system for an autonomous vehicle.
 */

#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "core/debug_interface.h"
#include "core/delta_sys.h"
#include "core/simple_parser.h"
#include "temp_modules.h"
#include "module/trackAlg0.h"

simple_parser parser; ///< Command parser instance
IRsensors_t IRsensors; ///< IR sensor module instance
trackAlg alg; ///< Tracking algorithm instance

/**
 * @brief Periodic task to print system status.
 * @param pvParameters Unused FreeRTOS parameter.
 */
void occasionalMessage(void *pvParameters){
  while(1) {
    debug_out("#######");
    inspect_vehicle();
    debug_out("$$$$$$$");
    IRsensors_readings_t readings = IRsensors.getReading();
    inspect_IRsensors(readings);
    debug_out("$$$$$$$");
    inspect_Alg(alg);
    debug_out("#######");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

/**
 * @brief Main control loop task.
 * @param pvParameters Unused FreeRTOS parameter.
 */
void controlLoop(void *pvParameters){
  TickType_t xLastWakeTime;
  uint32_t controlLoop_counter = 0;
  const TickType_t xPeriod = pdMS_TO_TICKS(FREQ_TO_PTIME(CNTRLLOOP_FREQ)*1000);
  // Initialise the xLastWakeTime variable with the current time.
  xLastWakeTime = xTaskGetTickCount();
  while(1){
    if((controlLoop_counter % CNTRLLOOP_TRACKALGSENSORREAD_FRATIO) == 0){
      alg.readIr();
    }
    if((controlLoop_counter % CNTRLLOOP_TRACKALGRUN_FRATIO) == 0){
      alg.run();
    }
    if((controlLoop_counter % CNTRLLOOP_VEHSENSORREAD_FRATIO) == 0){
      vehicle_laneBlazer->sensors_read();
    }
    if((controlLoop_counter % CNTRLLOOP_VEHCNTRLLOOP_FRATIO) == 0){
      vehicle_laneBlazer->control_loop();
    }
    vehicle_laneBlazer->motorPower_update();
    controlLoop_counter++;
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
  }
}

/**
 * @brief Command processing task.
 * @param pvParameters Unused FreeRTOS parameter.
 */
void cmd(void *pvParameters){
  while(1){
    char cmd[COMMAND_BUFFER_SIZE];
    if(Serial1.available()){
      int len = Serial1.readBytesUntil('\n', cmd, COMMAND_BUFFER_SIZE);
      cmd[len] = '\0';
      parser.reset();
      char* response = parser.parse(cmd);
      debug_out(response);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

/**
 * @brief Initializes hardware and starts FreeRTOS scheduler.
 */
void setup() {
  Serial1.begin(115200);
  debug_out("Initializing hardware.....");
  debug_out<int>("Vehicle_laneBlazer size = %d", sizeof(vehicle));
  vehicle_laneBlazer = new vehicle();
  if(vehicle_laneBlazer == NULL){
    debug_out("Initialization Failed OUT_OF_HEAP");
    while(1);
  }
  vehicle_laneBlazer->vehicle_init();
  alg.init(vehicle_laneBlazer, &IRsensors);
  IRsensors.init();
  debug_out("Hardware initialized.");
  // put your setup code here, to run once:
  xTaskCreate(occasionalMessage, "Occasional Message", 350, NULL, 1, NULL);
  xTaskCreate(controlLoop, "Control Loop", 350, NULL, 3, NULL);
  xTaskCreate(cmd, "Command Parser", 350, NULL, 1, NULL);
  vTaskStartScheduler();
}



/**
 * @brief Main loop (unused, as FreeRTOS takes control).
 */
void loop() {
  // FreeRTOS takes control
}

