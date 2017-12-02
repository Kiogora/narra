
## Narra - An LED Signage Development Project

This repository contains hardware designs and software for Narra, an open source, BLE advertising and control, LED signage platform. The project utilises the ESP32 and the ESP-IDF framework. The signage device had to be able to be controlled over BLE via a mobile connection with web bluetooth running on the client web browser that would control the signage device functions such as what to display and change the device state by writing to predefined BLE characteristics.

The hardware is made with the open-source PCB design tool [Kicad](http://kicad-pcb.org/). The hardware designs include:

1. A custom programmer that made using a common commercial off the shelf CP210x Uart-USB converter.
2. The LED driver board as at different versions.
3. A custom ESP32 module, friendly for development and product placement made from the ESP WROOM32. It is meant to be programmed using the programmer above.


The fimware is divided into different components that are abstracted from each other and written in Pure C utilising the ESP-IDF framework and include:

1. ble_api- Contains utilities to control the BLE hardware. Interacts directly with the ESP BLE HAL. It is strictly written with multiple level of sanity checks on the input data from user prior to writing to flash.

2. common_api-Contains constants and definitions that persist across source files.

3. controller_api- Contains the abstraction layer that enables/disables the display as well as verification that the text as UTF-8.

4. external_libs- External libraries that are used. The one currently used is a modified version of the utf_8 decoder library by Bjoern Hoehrman.

5. loader_api- API that is used to load from flash newly written variables via BLE. This is done at boot and after update via BLE dynamically.

6. updater_api- API that is used to update the system variables in flash.

7. renderer_api- This is the API that is heavily tied to the hardware itself and display method. The current display method is a row-scan method that takes advantage of the human persistence of vision.It also includes a header file containg the implemented character glyphs.

7. main file- Is used to setup the various tasks and coordinates the various task interactions.

### Building and uploading the code to device

Setup development environment using the build script in the utils/build folder:

```shell
cd utils/build
sh setup.sh
```
Now build the firmware and flash to device over UART:
```shell
cd ../../firmware
make flash
``` 

The firmware uis build for extensibility thus to support new languages, one just has to:

1. create the glyphs that represent the characters for that language and add to the existing in renderer_api/include/glyphmap.h .

2. Change the allowed character UTF-8 codepoint ranges in  common_api/narra_defines "UTF-8 implementation defines" section and add your own following the UTF-8 encoding ranges.

3. Add the checks for the above codepoint defines in the renderer so that your new implementation is recognised. 

### Contributors

[Alois Mbutura](alois.live) "aloismbutura@gmail.com"

Felix omwansa "omwansafelixa@gmail.com"

See CONTRIBUTORS file