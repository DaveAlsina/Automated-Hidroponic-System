#include "temp_and_hum.h"
#include "ec_meter.h"

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature dsProbe(&oneWire);
DeviceAddress addr = {0x28, 0xAA, 0x4E, 0x48, 0x48, 0x14, 0x01, 0xA7};

EcMeter ecProbe(3.3, 1000, 25, 5, 6, 7, 2.1, dsProbe, addr);



void setup(){

	Serial.begin(9600);
	Serial.println("EC meter Example Code");

	//start up the sensor
	dsProbe.begin();
	ecProbe.begin();
}


void loop(){

	Serial.println("Taking measurements");
	const pair <double, double> ec =  ecProbe.getEC();
	Serial.println();
	Serial.println();

	Serial.print("Measurements: EC-> ");	Serial.print(ec.first); 
	Serial.print("\t ppm-> ");				Serial.print(ec.second);
	Serial.println();
	Serial.println("--------------------------------------------------");
}
