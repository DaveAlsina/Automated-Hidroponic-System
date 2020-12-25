#ifndef _temp_and_hum_h_
#define _temp_and_hum_h_

#include <inttypes.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <OneWire.h>
#include "DallasTemperature.h"


//INPUT: array of doubles (data), size of array (sz)
//OUTPUT: (sorts internally the arrayin upward order)

void insertionSort(double* data, uint8_t sz); 


//INPUT: DHT object 
//OUTPUT: ambiental temperature (double)

double getTemp(DHT_Unified& obj, uint8_t nMeasurements, uint32_t& delayTime);	


//INPUT: DHT obj, uint8_t nMeasurementsect 
//OUTPUT: relative humidity (double)

double getHum(DHT_Unified& obj, uint8_t nMeasurements, uint32_t& delayTime); 

//INPUT: DallasTemperature obj, uint8_t nMeasurementsect
//OUTPUT: measured temperature (double) 

double getTemp(DallasTemperature obj, const uint8_t* addr, uint8_t nMeasurements);


#endif
