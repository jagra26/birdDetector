#include "mic.h"
#include "state_machine.h"

static struct mic_config_t {
    bool mic_recording;
    uint8_t mic_seconds_additional;
    uint16_t bytes_write;
    uint32_t partition_size;
    i2s_chan_handle_t rx_handle;
    StackType_t stack_mic[STACK_MIC_DEPTH];
    StaticTask_t mic_buffer;
    TaskHandle_t mic_handle;
} self = {
    .mic_recording = false,
    .mic_seconds_additional = 0,
    .bytes_write = BUFFER_MIC_SIZE,
    .partition_size = 0,
    .rx_handle = NULL,
    .mic_handle = NULL,
};

static i2s_chan_handle_t mic_init_channel(){
    i2s_chan_handle_t rx_handle;
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    i2s_new_channel(&chan_cfg, NULL, &rx_handle);
    i2s_pdm_rx_config_t pdm_rx_cfg = {
            .clk_cfg = I2S_PDM_RX_CLK_DEFAULT_CONFIG(PDM_SAMPLE_RATE),
//            {
//                    .sample_rate_hz = 16000,
//                    .clk_src = SOC_MOD_CLK_PLL_F160M,
//                    .mclk_multiple = I2S_MCLK_MULTIPLE_128,
//                    .dn_sample_mode = I2S_PDM_DSR_8S,
//            },
            .slot_cfg = I2S_PDM_RX_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
//            {
//                    .data_bit_width = I2S_DATA_BIT_WIDTH_16BIT,
//                    .slot_bit_width = I2S_SLOT_BIT_WIDTH_AUTO,
//                    .slot_mask = I2S_PDM_SLOT_LEFT,
//                    .slot_mode = I2S_SLOT_MODE_MONO,
//            },
            .gpio_cfg = {
                    .clk = PIN_MIC_CLOCK,
                    .din = PIN_MIC_DATA,
                    .invert_flags = {
                            .clk_inv = false,
                    },
            },
    };
    i2s_channel_init_pdm_rx_mode(rx_handle, &pdm_rx_cfg);
    i2s_channel_enable(rx_handle);

    return rx_handle;
}

bool check_mic_recording_status(){
    return self.mic_recording;
}

void additional_seconds(){
    if(self.partition_size > (MIC_RECORD + (MIC_RECORD_BITS_SIZE * (self.mic_seconds_additional + 3)))) {
        self.mic_seconds_additional += 3;
    }
}

void mic_record() {
    esp_err_t err = ESP_OK;
    int flash_wr_size = get_mic_write();
    gpio_set_level(GPIO_NUM_22, 1);
    size_t bytes_read = 0;
    printf("Iniciando gravacao\n");
    self.mic_recording = true;
    uint8_t reader_buffer_mic[BUFFER_MIC_SIZE];
    while (flash_wr_size < (MIC_RECORD + (MIC_RECORD_BITS_SIZE * self.mic_seconds_additional))) {
        err = i2s_channel_read(self.rx_handle, (void *)reader_buffer_mic, self.bytes_write, &bytes_read,
                               portMAX_DELAY);
        if (err) {
            //TODO: checar se aparecerá algum erro
        }
        flash_wr_size += self.bytes_write;
        save_data(reader_buffer_mic, self.bytes_write);
    }
    save_data(DATA_FINISH_TRANSFER, DATA_MAX_FINISH);
    self.mic_seconds_additional = 0;
    self.mic_recording = false;
    printf("acabou de gravar\n");
    gpio_set_level(GPIO_NUM_22, 0);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
}

void mic_init(){
    self.rx_handle = mic_init_channel();
    self.partition_size = control_partitions(GET_MIC_PARTITION_SIZE);
    printf("Tamanho da particao: %lu\n", self.partition_size);
    gpio_set_direction(GPIO_NUM_22, GPIO_MODE_OUTPUT);
}