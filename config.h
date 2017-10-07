struct Config {
	uint locationId;
	ushort deviceId;

	String serverAddress;
	ushort serverPort;

	ushort sampleRate;
	ushort dataSize;
	ushort numberBuffers;
	
	boolean sendToServer;
};

Config getDefaultConfig();
void readSDConfig(const char*, Config&);
String readLine(SdFile *);
bool assignConfig(char*, String, Config&);
void printConfig(Config&);


// use as
/*
Config CONFIG = getDefaultConfig();
readSDConfig("configuration.txt", CONFIG);

Serial.println(CONFIG.deviceId);
*/
