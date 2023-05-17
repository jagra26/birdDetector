#include "driver/i2s_pdm.h"
#include "driver/i2s_types.h"
#include "common.h"

#define TIME_MAX_RECORD_SECONDS 5
#define PDM_SAMPLE_RATE (12 * 1024)
#define MIC_RECORD_BITS_SIZE (1 * PDM_SAMPLE_RATE * 16 / 8)
#define MIC_RECORD (MIC_RECORD_BITS_SIZE * TIME_MAX_RECORD_SECONDS)
#define STACK_MIC_DEPTH (1024 * 2)

bool check_mic_recording_status();

void additional_seconds();

void suspend_mic_task();

void continue_mic_task();

void mic_record();

void mic_init();