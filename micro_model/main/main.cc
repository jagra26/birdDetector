#include "tensorflow/lite/micro/all_ops_resolver.h"
//#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_heap_caps.h>
//#include "tensorflow/lite/version.h"

#include "model.h"
#include "utils.h"



extern "C" void app_main(void) {

  const int kTensorArenaSize = 2048;
  uint8_t tensor_arena[kTensorArenaSize];

  const tflite::Model* model = ::tflite::GetModel(model_quantized_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf("Model provided is schema version %d not equal to supported version %d.", model->version(), TFLITE_SCHEMA_VERSION);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    return;
  }

  tflite::AllOpsResolver resolver;

  static tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, kTensorArenaSize);

  TfLiteStatus allocate_status = interpreter.AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    MicroPrintf("AllocateTensors() failed\n");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    return;
  }

  TfLiteTensor* input  = interpreter.input(0);
  TfLiteTensor* output = interpreter.output(0);


  //DEFINE A ENTRADA DO MODELO
  // input->data.f[0] = 0.;

  //CHAMA O MODELO COM A ENTRADA DEFINIDA
  // TfLiteStatus invoke_status = interpreter.Invoke();
  // if (invoke_status != kTfLiteOk) {
  //   MicroPrintf("Invoke() failed\n");
  //   return;
  // }

  //RECOLHE A SAÍDA DO MODELO
  // float value = output->data.f[0];

  while(true){
     MicroPrintf("OLÁ MUNDO");
     vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}
