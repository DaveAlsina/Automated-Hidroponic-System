#ifndef _temp_and_hum_cpp_
#define _temp_and_hum_cpp_

#include "Arduino.h"
#include "temp_and_hum.h"
#include <utility>


//INPUT: puntero a array de double (data), y el tamaño del array (sz)
//OUTPUT: ninguna, modifica el array en posición

void insertionSort(double* data, uint8_t sz){

	for(uint8_t i = 0; i<sz; i++){

		double key = data[i];
		uint8_t count = i;              //contador asistente

		//si la llave es menor que el elemento antetior 
		//'sube el elemento anterior' y disminuye el contador
		//así hasta llegar a la posición indicada

		while((count > 1) and (data[count - 1] > key)){
			data--;
			data[count] = data[count];
		}
			data[count] = key;      //posiciona la llave en su lugar correcto
	}
}



//INPUT: objeto de clase DHT
//OUTPUT: temperatura 

double getTemp(DHT obj){

	double measurements[10];

	for(uint8_t i = 0; i<10; i++){
		measurements[i] = obj.readTemperature();
		delay(200);
	}

	insertionSort(measurements, 10); 
	
	double ans = measurements[5] + measurements[6];
	ans /= 2; 

	return	ans;
}


//INPUT: objeto de la clase DHT
//OUTPUT: humedad

double getHum(DHT obj){

	double measurements[10];

	for(uint8_t i = 0; i<10; i++){
		measurements[i] = obj.readHumidity();
		delay(200);
	}

	insertionSort(measurements, 10); 
	
	double ans = measurements[5] + measurements[6];
	ans /= 2; 

	return	ans;
}


//INPUT: objeto de clase DHT
//OUTPUT: temperatura 

double getTemp(DallasTemperature obj, DeviceAddress addr){

	double measurements[10];

	for(uint8_t i = 0; i<10; i++){
		measurements[i] = obj.getTempC(addr);
		delay(200);
	}

	insertionSort(measurements, 10); 
	
	double ans = measurements[5] + measurements[6];
	ans /= 2; 

	return	ans;
}


#endif
