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

The usage is
