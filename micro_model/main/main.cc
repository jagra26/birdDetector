#include "main_functions.h"

extern "C" void app_main(void) {
  setup();
  
  while (true) {
    loop();
    vTaskDelay(1000/ portTICK_PERIOD_MS);
    //MicroPrintf("ENTREI NO MODELO");
  }
}
