idf_component_register(
    SRCS main.cc model.cc utils.cc
    PRIV_REQUIRES tflite-lib spi_flash
    INCLUDE_DIRS "")
