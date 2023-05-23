
#ifndef MAIN_FUNCTIONS_H_
#define MAIN_FUNCTIONS_H_

// #include "tensorflow/lite/micro/all_ops_resolver.h"
#include <tensorflow/lite/micro/micro_mutable_op_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/system_setup.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/micro/micro_log.h>
#include <tensorflow/lite/c/common.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h">
// Expose a C friendly interface for main functions.
#ifdef __cplusplus
extern "C" {
#endif

void model_setup();

void inferences();

#ifdef __cplusplus
}
#endif

#endif  // MAIN_FUNCTIONS_H_
