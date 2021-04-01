#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "/home/david/Desktop/AHS/bme280_bh1750/mqtt/network_secrets.h"

#define seaLevelPressure_Hpa (1013.25);

// 1) Change WiFiClient to WiFiSSLClient.
// 2) Change port value from 1883 to 8883.
// 3) Change broker value to a server with a known SSL/TLS root certificate 
//    flashed in the WiFi module.

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "";
const int port = 1883;


// Your WiFi credentials.
// Set password to "" for open networks.

String topics[5] = {"Esp8266!D4ta/pressure/", "Esp8266!D4ta/temp/", "Esp8266!D4ta/hum/", "Esp8266!D4ta/lux/"};
String deviceId = "10370001";

char ssid[] = SECRET_SSID; 
char pass[] = SECRET_PASS;

Adafruit_BME280 bme;          //I2C
BH1750 lightMeter(0x23);      //I2C


//function which asks for the readings and sends them to blynk
void sendata();


void setup() {

	Serial.begin(9600);

	while (!Serial){
	  ;                    //time to get serial running
	}


	// Initialize the I2C bus (BH1750 library doesn't do this automatically)
	Wire.begin();
	// On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3)

	// begin returns a boolean that can be used to detect setup problems.

	while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
		// failed, retry
		Serial.print(".");
		delay(5000);
	}

	Serial.println("You're connected to the network");
	Serial.println();
	
	mqttClient.setUsernamePassword("ccctest1", "ccctest1_nuncasupecomoseescribe");


  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();


	if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2)) {

		Serial.println(F("BH1750 Advanced begin"));
	} else {
		Serial.println(F("Error initialising BH1750"));
	}

	// start bme sensor with the address
	bool status = bme.begin(0x76);

	// You can also pass in a Wire library object like &Wire2
	// status = bme.begin(0x76, &Wire2)

	if (!status) {
		Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
		Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
		Serial.print("  ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
		Serial.print("  ID of 0x56-0x58 represents a BMP 280,\n");
		Serial.print("  ID of 0x60 represents a BME 280.\n");
		Serial.print("  ID of 0x61 represents a BME 680.\n");
	}
}

void loop() {
  mqttClient.poll();
  sendata();
  delay(55*1000);
}



void sendata() {


	//mediciones: [presión en hPa, humedad, temperatura, lux]
	double measurement[5] = {bme.readPressure()/100.0F,  bme.readTemperature(), bme.readHumidity(), lightMeter.readLightLevel()};

	//creación de las payload con los datos a ser enviado a cada tema
	String payloads[5] = { "", "", "", "" };

	for(int i = 0; i < 4; i++)
		payloads[i] += measurement[i];
	
	//seteo de las variables para envío del mensaje via protocolo mqtt
	bool retained = false; 
	int qos = 2; 
	bool dup = false;
	
	for(int i = 0; i < 4; i++){
		mqttClient.beginMessage( topics[i]+deviceId, payloads[i].length(), retained, qos, dup);
		mqttClient.print(payloads[i]);
		mqttClient.endMessage();

    Serial.println();
    Serial.print(topics[i]+deviceId);
    Serial.print("/");
    Serial.print(payloads[i]);
    Serial.println();
	}
 
}
