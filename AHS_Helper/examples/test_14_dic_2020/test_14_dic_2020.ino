#define BLYNK_PRINT Serial

//This libraries down below can be added by installing the board manager
//for esp8266 gotted and added in preferences from this link:
//http://arduino.esp8266.com/stable/package_esp8266com_index.json

//NODE MCU ESP8266 PINOUT -> https://esp8266-shop.com/esp8266-guide/esp8266-nodemcu-pinout/ 
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#include <temp_and_hum.h>
#include <DallasTemperature.h>
#include <DHT_U.h>
#include <DHT.h>


#define DHTPIN 5            // Digital pin connected to the DHT sensor		//GPIO-5 //D1
#define DHTTYPE DHT11       // DHT 11
//#define DHTTYPE DHT22     // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

#define ONE_WIRE_BUS 4		// Digital pin connected to the ds18b20 sensor		//GPIO-5 //D2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// arrays to hold device address
DallasTemperature ds18Sensor(&oneWire);

// arrays to hold device address
DeviceAddress addr; 



char auth[] = "_uUTfyn9qF0OmhfzE3oRJJwKg2V0HplV";
char ssid[] = "98283963HARMOOB";
char pass[] = "1090504523";


/********************************************
	WRAPPER FUNCITIONS AND EXTRA-FUNCITIONS 
********************************************/

#define ERROR_VAL -1345								//arbitrary value for raising errors

double getTemp(String command){						//wraper function for getting temperature using DHT11
	if (command == "ds")
		return getTemp(ds18Sensor, addr);

	else if (command == "dht") 
		return getTemp(dht);

	else{
		Serial.print("ERROR, el comando ingresado fue: "); 
		Serial.print(command);
		Serial.println("Los comandos son: 'ds'->ds18b20/'dht'->DHT11");
		return ERROR_VAL;
	}
}


double getHum(){
	return getHum(dht);					//wraper function for getting the humidity using DHT11
}


/*********************
		SETUP
*********************/
void setup() {
	Serial.begin(9600);
	delay(150);
	
	dht.begin();
	delay(150);

	Serial.print(getTemp("ds"));
	delay(150);
	Serial.print(getTemp("dht"));
}


/**********************************
				LOOP
***********************************/
void loop(){

	delay(150);
	Serial.print(getTemp("ds"));
	delay(150);
	Serial.print(getTemp("dht"));
}
