#include "main_functions.h"
#include "model.h"
#include "input.h"
#include "string.h"

namespace {
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int kTensorArenaSize = 120 * 2048;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

static void tentative(uint8_t* input, int input_size);

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

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    MicroPrintf("AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);
}

void inferences() {

  uint8_t out;

  MicroPrintf("Saída do Modelo para a entrada 'Bem-te-vi':");
  memcpy(input->data.uint8, bem_te_vi, bem_te_vi_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);

  MicroPrintf("Saída do Modelo para a entrada 'Sabiá':");
  memcpy(input->data.uint8, sabia, sabia_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  
  MicroPrintf("Saída do Modelo para a entrada 'Ganso':");
  memcpy(input->data.uint8, ganso, ganso_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);

  MicroPrintf("Saída do Modelo para a entrada 'Cachorro':");
  memcpy(input->data.uint8, cachorro, cachorro_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);

  MicroPrintf("Saída do Modelo para a entrada 'Urubu':");
  memcpy(input->data.uint8, urubu, urubu_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  
  MicroPrintf("Saída do Modelo para a entrada 'Cascavel':");
  memcpy(input->data.uint8, cascavel, cascavel_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  
  MicroPrintf("Saída do Modelo para a entrada 'Gato':");
  memcpy(input->data.uint8, gato, gato_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  
  MicroPrintf("Saída do Modelo para a entrada 'Galinha':");
  memcpy(input->data.uint8, galinha, galinha_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);
  
  MicroPrintf("Saída do Modelo para a entrada 'Leão':");
  memcpy(input->data.uint8, leao, leao_len * sizeof(unsigned char));
  interpreter->Invoke();
  out = output->data.uint8[0] - 127;
  MicroPrintf("out_value: %u\n", out);
  vTaskDelay(2000 / portTICK_PERIOD_MS);  
}
