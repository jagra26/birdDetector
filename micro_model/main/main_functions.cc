#include "main_functions.h"
namespace {
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* input = nullptr;
  TfLiteTensor* output = nullptr;

  constexpr int kTensorArenaSize = 120 * 2048;
  uint8_t tensor_arena[kTensorArenaSize];
} // namespace

const uint8_t* inputs[] = {
  bem_te_vi,
  sabia,
  ganso,
  cachorro,
  urubu,
  cascavel,
  gato,
  galinha,
  leao,
};

#define NUM_OF_INPUTS sizeof(inputs)/sizeof(inputs[0])

void model_setup(){

  model = tflite::GetModel(g_model);

  static tflite::MicroMutableOpResolver<7> resolver;
  resolver.AddConv2D();
  resolver.AddMaxPool2D();
  resolver.AddSoftmax();
  resolver.AddRelu();
  resolver.AddReshape();
  resolver.AddFullyConnected();
  resolver.AddLogistic();

  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    MicroPrintf("AllocateTensors() failed");
    return;
  }

  input = interpreter->input(0);
  output = interpreter->output(0);
}

void inferences(){

  for (size_t i = 0; i < NUM_OF_INPUTS; i++)
  {
    MicroPrintf("Saída do Modelo para a entrada %d: ", i + 1);
    memcpy(input->data.uint8, inputs[i], INPUT_LEN * sizeof(unsigned char));
    result();
  }
}

void result(){

  uint8_t model_out;

  interpreter->Invoke();
  model_out = output->data.uint8[0] - 127;

  if(model_out){
    MicroPrintf("PERTENCE A UM BEM-TE-VI\n");
  }
  else{
    MicroPrintf("NÃO PERTENCE A UM BEM-TE-VI\n");
  }

  vTaskDelay(1000 / portTICK_PERIOD_MS);
}
