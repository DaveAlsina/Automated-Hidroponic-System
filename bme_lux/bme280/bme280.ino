#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define seaLevelPressure_Hpa (1013.25);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "_uUTfyn9qF0OmhfzE3oRJJwKg2V0HplV";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "SomosRUB";
char pass[] = "claro2015";

Adafruit_BME280 bme; //I2C
BlynkTimer timer;

//function which asks for the readings and sends them to blynk
void sendData();


void setup(){
	
	Serial.begin(9600);
	while(!Serial);			//time to get serial running
	Blynk.begin(auth, ssid, pass);


    // default settings
    bool status = bme.begin(0x76);  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)

    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
        Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
        Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
        Serial.print("        ID of 0x60 represents a BME 280.\n");
        Serial.print("        ID of 0x61 represents a BME 680.\n");
    }
	
	//calls 'sendData' every 5 secs
	timer.setInterval(5000L, sendData);

}


void loop(){
  Blynk.run();
  timer.run();
}




void sendData(){

	double pressure = bme.readPressure() / 100.0F; //hPa
	double hum = bme.readHumidity();
	double temp = bme.readTemperature();

	Blynk.virtualWrite(V1, pressure);
	Blynk.virtualWrite(V2, hum);
	Blynk.virtualWrite(V3, temp);
}
