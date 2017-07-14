# Arduino Config Reader

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
1- change the struct Config (_config.h_) with the datatypes of your needs
2- change the text file that contains your configuration (_configuration.txt_)
3- change the function assignConfig (_config.cpp_) to assign the strings to each of the parameters you set in the structure (for instance to parse float, instead of int and strings).
4- add your paramteres to the function PrintConfig (_config.cpp_)

# Usage
The parameters are defined in the struct Config in config.h

- **getDefaultConfig** - returns a Config struct with the default values that are set inside that function (change them to your needs)
- **readSDConfig** - receives a filepath and a Config struct and modifies it with the contents of the file
- **printConfig** - receives a Config struct and prints out all its members
```
#include "config.h"

..... MAIN ....


Config CONFIG = getDefaultConfig();
readSDConfig("configuration.txt", CONFIG);

printConfig(CONFIG);
```

# Config file strucure
The file is made of a parameter for each new line (either terminated with \r (winodws) or \n (unix)
Each parameter is as follows:
```
Parameter=value
```

- The delimiter '=' can be set in the begining of _config.cpp_ file in the DELIM define
- No spaces can be used between the parameter name and the delimiter
- String Parameters should be stored in plain text without quotes and assigned in the function assignConfig (_config.cpp_) similar to how the parameter **serverAddress** in the example is set.
- Allows for blank lines

# Tested
Has been tested in the Particle Photon
