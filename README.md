# arduino_config_reader

Reads a configuration text file form an SDcard and stores the configuration values in a config struct that can be used throughout your program.
It is useful to pass parameters to the running software without having to reflash or recompile code, simply by changing some parameters in a text file.
Useful to 
- set device IDs on multiple devices running the same software
- defining input pins to read sensors
- definig servers address and ports to send data to
- etc...

Uses the library SDFile from sparkfun shield https://github.com/sparkfun/Shifting_microSD/blob/master/Firmware/uSD_Editor/uSD_Editor.ino
Although any other library will do, as long as it can read characters from a text file


# How to change parameters:
1- change the struct Config (config.h) with the datatypes of your needs
2- change the text file that contains your configuration
3- change the function assignConfig (config.cpp) to assign the strings to each of the parameters you set in the structure
4- add your paramteres to the function PrintConfig (config.cpp)

# Usage
The parameters are defined in the struct Config in config.h

- getDefaultConfig - returns a Config struct with the default values that are set inside that function (change them to your needs)
- readSDConfig - receives a filepath and a Config struct and modifies it with the contents of the file
- printConfig - receives a Config struct and prints out all its members
```
#include "config.h"

..... MAIN ....


Config CONFIG = getDefaultConfig();
readSDConfig("configuration.txt", CONFIG);

printConfig(CONFIG);
```

Has been tested in the Particle Photon
