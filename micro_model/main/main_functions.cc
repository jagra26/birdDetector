#include "main_functions.h"
#include "model.h"
#include "input.h"
#include "string.h"

namespace {
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int kTensorArenaSize = 119 * 2048;
uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

void setup() {

  model = tflite::GetModel(g_model);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    MicroPrintf("Model provided is schema version %d not equal to supported "
                "version %d.", model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  static tflite::MicroMutableOpResolver<7> resolver;
  resolver.AddConv2D();
  resolver.AddMaxPool2D();
  resolver.AddSoftmax();
  resolver.AddRelu();
  resolver.AddReshape();
  resolver.AddFullyConnected();
  resolver.AddLogistic();


  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize);
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

  memcpy(input->data.uint8, sabia, 37716 * sizeof(unsigned char));  
  
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    MicroPrintf("Invoke failed");
    return;
  }
}

// The name of this function is important for Arduino compatibility.
void loop() {
  MicroPrintf("Saída do Modelo:");
  int8_t out = output->data.int8[0];
  //out = out & 0b01111111;
  MicroPrintf("out_value: %d\n", out);
}
