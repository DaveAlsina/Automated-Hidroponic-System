#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <SPI.h>
#include <BH1750.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define seaLevelPressure_Hpa (1013.25);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "";
char pass[] = "";

Adafruit_BME280 bme;          //I2C
BH1750 lightMeter(0x23);      //I2C

BlynkTimer timer;

//function which asks for the readings and sends them to blynk
void sendData();


void setup() {

  Serial.begin(9600);
  while (!Serial);                    //time to get serial running
  Blynk.begin(auth, ssid, pass);      //start connection with blink

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3)

  // begin returns a boolean that can be used to detect setup problems.

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
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
  }

  //calls 'sendData' every 5 secs
  timer.setInterval(5000L, sendData);


}

void loop() {
  Blynk.run();
  timer.run();
}



void sendData() {

  double pressure = bme.readPressure() / 100.0F; //hPa
  double hum = bme.readHumidity();
  double temp = bme.readTemperature();
  double lux = lightMeter.readLightLevel();

  Blynk.virtualWrite(V1, pressure);
  Blynk.virtualWrite(V2, hum);
  Blynk.virtualWrite(V3, temp);
  Blynk.virtualWrite(V4, lux);
}
