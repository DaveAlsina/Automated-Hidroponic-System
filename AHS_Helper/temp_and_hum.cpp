#ifndef _temp_and_hum_cpp_
#define _temp_and_hum_cpp_

#include "Arduino.h"
#include "temp_and_hum.h"


//INPUT: puntero a array de double (data), y el tamaño del array (sz)
//OUTPUT: ninguna, modifica el array en posición

void insertionSort(double* data, uint8_t sz){

	for(uint8_t i = 0; i<sz; i++){

		const double key = data[i];
		uint8_t count = i;										//contador asistente

		//si la llave es menor que el elemento antetior 
		//'sube el elemento anterior' y disminuye el contador
		//así hasta llegar a la posición indicada

		while((count > 1) and (data[count - 1] > key)){
			count--;
			data[count] = data[count];
		}
			data[count] = key;									//posiciona la llave en su lugar correcto
	}

}



//INPUT: objeto de clase DHT, 'nMeasurements' numero de mediciones a tomar antes de encontrar la mediana
//OUTPUT: temperatura 

double getTemp(DHT_Unified& obj, uint8_t nMeasurements, uint32_t& delayTime){

	double measurements[nMeasurements];							//array para guardar las mediciones tomadas
	// Get temperature event and print its value.
	sensors_event_t event;

	for(uint8_t i = 0; i < nMeasurements; i++){					//toma de mediciones

		obj.temperature().getEvent(&event);
		measurements[i] = event.temperature;                                                  
		delay(delayTime);                                                                                         
	}

	insertionSort(measurements, nMeasurements);					//ordenado del array
	
	const uint8_t mid = nMeasurements/2;						//extracción de la mediana
	double ans = measurements[mid] + measurements[mid+1];

	if (nMeasurements % 2 == 0)
		ans /= 2; 
	else
		ans = measurements[mid + 1];
	
	
	return	ans;
}


//INPUT: objeto de la clase DHT, 'nMeasurements' numero de mediciones a tomar antes de encontrar la mediana 
//OUTPUT: humedad

double getHum(DHT_Unified& obj, uint8_t nMeasurements, uint32_t& delayTime){

	double measurements[nMeasurements];							//array para guardar las mediciones tomadas
	// Get temperature event and print its value.
	sensors_event_t event;

	                                                                                                 
	for(uint8_t i = 0; i<nMeasurements; i++){                   //toma de mediciones

		obj.humidity().getEvent(&event);
		measurements[i] = event.relative_humidity;                                                  
		delay(delayTime);                                                                                         
	}                                                                                                       
                                                                                                            
	insertionSort(measurements, nMeasurements);                 //ordenado del array
                                                                                                            
	const uint8_t mid = nMeasurements/2;                        //extracción de la mediana
	double ans = measurements[mid] + measurements[mid+1];

	if (nMeasurements % 2 == 0)
		ans /= 2; 
	else
		ans = measurements[mid + 1];


	return	ans;
}


//INPUT: objeto de clase DHT, 'nMeasurements' numero de mediciones a tomar antes de encontrar la mediana
//OUTPUT: temperatura 

//recuerde que el 'DeviceAddress' es un alias para: 'uint8_t DeviceAddress [8]'
double getTemp(DallasTemperature obj, const byte* addr, uint8_t nMeasurements){		 
																
	double measurements[nMeasurements];							//array para guardar las mediciones tomadas
                                                                                                            
	for(uint8_t i = 0; i<nMeasurements; i++){                   //toma de mediciones
		measurements[i] = obj.getTempC(addr);                                                               
		delay(200);                                                                                         
	}                                                                                                       
                                                                                                            
	insertionSort(measurements, nMeasurements);                 //ordenado del array
	                                                                                                        
	const uint8_t mid = nMeasurements/2;                        //extracción de la mediana
	double ans = measurements[mid] + measurements[mid+1];

	if (nMeasurements % 2 == 0)
		ans /= 2; 
	else
		ans = measurements[mid + 1];

	return	ans;
}


#endif
