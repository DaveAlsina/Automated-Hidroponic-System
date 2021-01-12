#ifndef _ec_meter_h_
#define _ec_meter_h_

#include "Arduino.h"						//another cool library that can be used https://roboticsbackend.com/arduino-stl-library/
#include "temp_and_hum.h" 

using namespace std;


class EcMeter{

	private:
		//conversion rates from EC to ppm depending on the country
		const float USA_ppmConversion = 0.5;
		const float EU_ppmConversion = 0.64;
		const float AUS_ppmConversion = 0.7;	

		float PPMconversion;				//variable for storing the set conversion factor

		//compensating for temperature 
		//The value below will change depending on what chemical solution we are measuring
		//0.019 is generaly considered the standard for plant nutrients [google "Temperature compensation EC" for more info

		const float TemperatureCoef = 0.019;

		//pins and resistance values needed to work with the DIY sensor
		int R1, Ra, ECPin, ECGround, ECPower;

		//cell constant for EC Measurements
		float K;

		//voltage input, needed for calculations
		float Vin;

		//copy of ds18b20 sensor 
		DallasTemperature tempProbe;	

		//remember that 'DeviceAddress' is defined in the library 'DallasTemperature'
		//as an array of 8 uint8_t elements
		uint8_t probeAddr[8];					

	public: 

		/* ->	VoltageInput (voltage of the arduino module)
		 * ->	r1			 (resistor's resistance value)
		 * ->	ra			 (Resistance of powering Pins)
		 * ->	ecPin		 (signal pin of the sensor)
		 * ->	ecPower		 (pin that sends power to the sensor)
		 * ->	ecGround	 (arduino's pin that is used as GND)
		 * ->	constant	 (constant value of the cell) 
		 * ->	probe		 (instance of ds18b20 sensor)
		 * ->	addr		 (ds18b20 address) 
		 */

		EcMeter(float VoltageInput, int r1, int ra, int ecPin, int ecPower, int ecGround, float constant, 
				DallasTemperature& probe, const uint8_t* addr);

		~EcMeter(){};	

		void begin();						//sets up the sensor 

		//OUTPUT: EC measurement
		double getEC();								//takes the measurement the minimum waiting time between readings is 
													//4 seconds

		bool chgConvertFact(String conv);
};


#endif
