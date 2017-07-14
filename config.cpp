#define LINE_BUFFER_SIZE 200
#define DELIM "="

#include <stdlib.h>
#include <stdio.h>
#include "Particle.h"
#include "string.h"
#include "SdFat.h"
#include "config.h"

Config getDefaultConfig(){
	Config c = {
		99999,			// locationId;
		2,			// deviceId;
		"servername.com",	// serverAddress;
		8000,			// serverPort;
		8000,			// sampleRate;
		128,			// dataSizeKB;
		2, 			// numberBuffers;
	};
	
	return c;
}
	
String readLine(SdFile* fd){
	String line = "";
	char lastChar = '\n';

	// skip initial or sequential \n or \r
	while(fd->available() && (lastChar == '\n' || lastChar == '\r' || lastChar == '\t' || lastChar == ' ')){
		lastChar = fd->read();
	}
	// the first char found is already stored in lastChar variable from the previous loop
	while(fd->available() && lastChar != '\n' && lastChar != '\r'){
		line += lastChar;
		lastChar = fd->read();
	}
	if(!fd->available() && lastChar != '\n' && lastChar != '\r' && lastChar != '\t' && lastChar != ' '){
		line += lastChar;
	}
	return line;
}

bool assignConfig(char* paramName, String val, Config &config){
	if(stricmp(paramName, "locationId") == 0) 	{ config.locationId 	= atoi(val); 	return true; }
	if(stricmp(paramName, "deviceId") == 0) 	{ config.deviceId 	= atoi(val); 	return true; }

	if(stricmp(paramName, "serverAddress") == 0) 	{ config.serverAddress	= val;		return true; }
	if(stricmp(paramName, "serverPort") == 0) 	{ config.serverPort 	= atoi(val); 	return true; }

	if(stricmp(paramName, "sampleRate") == 0) 	{ config.sampleRate 	= atoi(val); 	return true; }
	if(stricmp(paramName, "dataSize") == 0) 	{ config.dataSize 	= atoi(val); 	return true; }
	if(stricmp(paramName, "numberBuffers") == 0) 	{ config.numberBuffers 	= atoi(val); 	return true; }
	
	return false;
}


void readSDConfig(const char *aFilename, Config &config){
	// s.erase(0, s.find(delimiter) + delimiter.length());

	SdFile fd;
	if(!fd.open(aFilename)){
		Serial.println("error opening config.txt");
		return;
	}

	String line = "";
	char param_value[LINE_BUFFER_SIZE];
	char *delimPointer;
	int param_size;
	char param[LINE_BUFFER_SIZE];

	while(fd.available()){
		line = readLine(&fd);

		delimPointer = strstr(line, DELIM);
		// delimPointer += strlen(DELIM);

		param_size = strcspn(line, DELIM);
		strncpy(param, line, param_size);
		param[param_size] = '\0';	// strncpy does not NULL terminate string

		strncpy(param_value, delimPointer + strlen(DELIM), strlen(line));

		assignConfig(param, param_value, config);
	}
	fd.close();
}


// change Serial.println to the correspondent printing function in your environment
void printConfig(Config& config){
	Serial.println(config.locationId);
	Serial.println(config.deviceId);
	Serial.println(config.serverAddress);
	Serial.println(config.serverPort);
	Serial.println(config.sampleRate);
	Serial.println(config.dataSize);
	Serial.println(config.numberBuffers);
}
