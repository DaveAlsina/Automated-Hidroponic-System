#include <DallasTemperature.h>
#include <DHT_U.h>
#include <DHT.h>
#include <temp_and_hum.h>


#define DHTPIN 5									// Digital pin connected to the DHT sensor		//GPIO-5 //D1
#define DHTTYPE DHT11								// DHT 11
//#define DHTTYPE DHT22								// DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21								// DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

#define ONE_WIRE_BUS 4								// Digital pin connected to the ds18b20 sensor		//GPIO-5 //D2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// arrays to hold device address
DallasTemperature ds18Sensor(&oneWire);

// arrays to hold device address
DeviceAddress addr;									//add the ds18b20 sensor address here


/********************************************
	WRAPPER FUNCITIONS AND EXTRA-FUNCITIONS 
********************************************/

#define ERROR_VAL -1345								//arbitrary value for raising errors

double getTemp(String command){						//wraper function for getting temperature using DHT11
	if (command == "ds")
		return getTemp(ds18Sensor, addr, 4);

	else if (command == "dht") 
		return getTemp(dht, 2);

	else{
		Serial.print("ERROR, el comando ingresado fue: "); 
		Serial.print(command);
		Serial.println("Los comandos son: 'ds'->ds18b20/'dht'->DHT11");
		return ERROR_VAL;
	}
}


double getHum(){
	return getHum(dht, 3);							//wraper function for getting the humidity using DHT11
}


/*********************
		SETUP
*********************/
void setup() {
	Serial.begin(9600);
	delay(150);
	
	dht.begin();
	delay(150);

	ds18Sensor.begin();
	delay(150);

	Serial.print(getTemp("ds"));
	Serial.print(getTemp("dht"));
}


/**********************************
				LOOP
***********************************/
void loop(){

	Serial.print(getTemp("ds"));
	Serial.print(getTemp("dht"));
	Serial.print(getHum());
}
