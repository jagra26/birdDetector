# birdDetector

## Requirements:

```bash
sudo apt-get install pkg-config
```
```bash
sudo apt-get install libsndfile-dev
```
```bash
sudo apt-get install fftw3 fftw3-dev pkg-config
```
```bash
sudo apt install libcairo2-dev
```
```bash
cd snd
cd build
cmake ..
make
./birdDetector --no-border ../../audio_0.wav 96 96 test.png
```

# Micro Model

This example is designed to demonstrate the absolute basics of using [TensorFlow
Lite for Microcontrollers](https://www.tensorflow.org/lite/microcontrollers).
It includes the full end-to-end workflow of training a model, converting it for
use with TensorFlow Lite for Microcontrollers for running inference on a
microcontroller.

## To run the micro-model, follow the below commands

```bash
cd micro_model
```


## Deploy to ESP32

The following instructions will help you build and deploy this sample
to [ESP32](https://www.espressif.com/en/products/hardware/esp32/overview)
devices using the [ESP IDF](https://github.com/espressif/esp-idf).

### Install the ESP IDF

Follow the instructions of the
[ESP-IDF get started guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html)
to setup the toolchain and the ESP-IDF itself.

The next steps assume that the
[IDF environment variables are set](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#step-4-set-up-the-environment-variables) :

 * The `IDF_PATH` environment variable is set
 * `idf.py` and Xtensa-esp32 tools (e.g. `xtensa-esp32-elf-gcc`) are in `$PATH`


### Building the example

Set the chip target (For esp32s3 target, IDF version `release/v4.4` is needed):

```bash
idf.py set-target esp32s3
```

Then build with `idf.py`

```bash 
idf.py build
```

### Load and run the example

To flash (replace `/dev/ttyUSB0` with the device serial port):
```bash
idf.py --port /dev/ttyUSB0 flash
```

Monitor the serial output:
```
idf.py --port /dev/ttyUSB0 monitor
```

Use `Ctrl+]` to exit.

The previous two commands can be combined:
```
idf.py --port /dev/ttyUSB0 flash monitor
```

# Source Model

The micro-model was created usig the model present int the directory below:
 ```bash
 python_model/modelo_bemtevi.ipynb
 ```