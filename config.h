struct Config {
	uint locationId;
	ushort deviceId;

	String serverAddress;
	ushort serverPort;

	ushort sampleRate;
	ushort dataSize;
	ushort numberBuffers;
	ushort sampleBufferSize;
	ushort recordBufferSize;
	ushort TCPBufferSize;
	ushort samplePin;

	ushort FFTfreq;
	ushort FFTbandwidth;
	ushort FFTWindowFunction;
};


// Config CONFIG = {}; 	// zero all the fields
Config getDefaultConfig();
void readSDConfig(const char*, Config&);
String readLine(SdFile *);
bool assignConfig(char*, String, Config&);
//void funcaodocrlh();

// use as
//Config CONFIG = getDefaultConfig();
//CONFIG.readSDConfig();
/*
void loop()  //TOP
{

 	Config CONFIG = getDefaultConfig();
	readSDConfig("configuration.txt", CONFIG);
	Serial.println(CONFIG.deviceId);
 	delay(1000);
}*/
