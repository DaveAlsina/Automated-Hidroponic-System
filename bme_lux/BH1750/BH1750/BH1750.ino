#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <Wire.h>
#include <BH1750.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).

char auth[] = "_uUTfyn9qF0OmhfzE3oRJJwKg2V0HplV";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[] = "SomosRUB";
char pass[] = "claro2015";


BH1750 lightMeter(0x23);
BlynkTimer timer;


void sendData();

void setup(){

  Serial.begin(9600);
  while(!Serial);     //time to get serial running
  Blynk.begin(auth, ssid, pass);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);

  // begin returns a boolean that can be used to detect setup problems.
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2)) {
    Serial.println(F("BH1750 Advanced begin"));
  }
  else {
    Serial.println(F("Error initialising BH1750"));
  }

  timer.setInterval(5000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendData(){
     if (lightMeter.measurementReady()) {
      float lux = lightMeter.readLightLevel();
      Serial.print("Light: ");
      Serial.print(lux);
      Serial.println(" lx");
    } 
  
}
