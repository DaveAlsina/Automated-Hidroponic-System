#ifndef _temp_and_hum_h_
#define _temp_and_hum_h_

#include <inttypes.h>
#include "../DHT_sensor_library/DHT.h"
#include <OneWire.h>
#include "../DallasTemperature/DallasTemperature.h"


//INPUT: array of doubles (data), size of array (sz)
//OUTPUT: (sorts internally the arrayin upward order)

void insertionSort(double* data, uint8_t sz); 


//INPUT: DHT object 
//OUTPUT: ambiental temperature (double)

double getTemp(DHT obj);	


//INPUT: DHT object 
//OUTPUT: relative humidity (double)

double getHum(DHT obj); 

//INPUT: DallasTemperature object
//OUTPUT: measured temperature (double) 

double getTemp(DallasTemperature obj, DeviceAddress addr);


#endif
