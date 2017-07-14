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
		99999,	// locationId;
		2,		// deviceId; // 2 = Photon

		"li1097-240.members.linode.com",	//serverAddress;
		8301,	// serverPort;

		8000,	// sampleRate;
		128,	// dataSizeKB;
		2, 		// numberBuffers;
		24,		// sampleBufferSizeKB;
		128,	// recordBufferSize;
		1024, 	// TCPBufferSize;
		11, 	// samplePin;	// A1

		400,	// FFTfreq;
		50,		// FFTbandwidth;
		1,		// FFTWindowFunction	// 1

	};
		return c;
	}
	/*Config c = {
		12345,	// locationId;
		12345,		// deviceId; // 2 = Photon

		"0987654",	//serverAddress;
		12345,	// serverPort;

		12345,	// sampleRate;
		12345,	// dataSizeKB;
		12345, 		// numberBuffers;
		12345,		// sampleBufferSizeKB;
		12345,	// recordBufferSize;
		12345, 	// TCPBufferSize;
		12345, 	// samplePin;	// A1

		12345,	// FFTfreq;
		12345,		// FFTbandwidth;
		12345,		// FFTWindowFunction	// 1
	};*/

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

	if(stricmp(paramName, "locationId") == 0) 				{ config.locationId 					= atoi(val); 	return true; }
	if(stricmp(paramName, "deviceId") == 0) 					{ config.deviceId 						= atoi(val); 	return true; }

	if(stricmp(paramName, "serverAddress") == 0) 			{ config.serverAddress	 		= val;				return true; }
	if(stricmp(paramName, "serverPort") == 0) 				{ config.serverPort 				= atoi(val); 	return true; }

	if(stricmp(paramName, "sampleRate") == 0) 				{ config.sampleRate 				= atoi(val); 	return true; }
	if(stricmp(paramName, "dataSize") == 0) 					{ config.dataSize 					= atoi(val); 	return true; }
	if(stricmp(paramName, "numberBuffers") == 0) 			{ config.numberBuffers 			= atoi(val); 	return true; }
	if(stricmp(paramName, "sampleBufferSize") == 0)		{ config.sampleBufferSize 	= atoi(val); 	return true; }
	if(stricmp(paramName, "recordBufferSize") == 0)		{ config.recordBufferSize 	= atoi(val); 	return true; }
	if(stricmp(paramName, "TCPBufferSize") == 0) 			{ config.TCPBufferSize 			= atoi(val); 	return true; }
	if(stricmp(paramName, "samplePin") == 0) 					{ config.samplePin 					= atoi(val); 	return true; }

	if(stricmp(paramName, "FFTfreq") == 0) 						{ config.FFTfreq 						= atoi(val); 	return true; }
	if(stricmp(paramName, "FFTbandwidth") == 0) 			{ config.FFTbandwidth 			= atoi(val); 	return true; }
	if(stricmp(paramName, "FFTWindowFunction") == 0) 	{ config.FFTWindowFunction	= atoi(val); 	return true; }

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
