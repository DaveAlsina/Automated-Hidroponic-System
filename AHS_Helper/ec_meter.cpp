#ifndef _ec_meter_cpp_
#define _ec_meter_cpp_

#include "ec_meter.h"

using namespace std;

EcMeter::EcMeter(float VoltageInput, int r1, int ra, int ecPin, int ecPower, int ecGround, float constant, 
				DallasTemperature& probe, const uint8_t* addr){

	//initializes all of the resistance values and pins
	R1 = r1 + ra;
	Ra = ra; 
	ECPin = ecPin; 
	ECGround = ecGround; 
	ECPower = ecPower; 

	//initializes the voltage input data 
	Vin = VoltageInput;

	//initializes the constant of the probe and the probe internal copy
	K = constant;
	tempProbe = probe;

	for(int  i = 0; i < 8; i++)				//copies the address of to probe to the local variable 'probeAddr' 
		probeAddr[i] = addr[i];
	
	PPMconversion = AUS_ppmConversion;		//sets the default conversion factor
}

double EcMeter::getEC(){
	
	//*********Reading temp Of Solution *******************//
	const double temp = getTemp(tempProbe, probeAddr, 3);	

	//************Estimates Resistance of Liquid ****************//

	digitalWrite(ECPower,HIGH);
	float raw = analogRead(ECPin);
	raw = analogRead(ECPin);						// This is not a mistake, First reading will be low beause if charged a capacitor
	digitalWrite(ECPower,LOW);

	//***************** Converts to EC **************************//

	const float Vdrop = (Vin*raw)/1024.0;
	float Rc = (Vdrop*R1)/(Vin-Vdrop);
	Rc = Rc-Ra;										//acounting for Digital Pin Resitance
	const double EC = 1000/(Rc*K);

	//*************Compensating For Temperaure********************//

	const double EC25  =  EC/ (1+ TemperatureCoef*(temp - 25.0));
	//const double ppm = (EC25)*(PPMconversion*1000);

	double ans = EC25;
	return ans;
}


void EcMeter::begin(){
	pinMode(ECPin, INPUT);
	pinMode(ECPower, OUTPUT);
	pinMode(ECGround, OUTPUT);
	digitalWrite(ECGround, LOW);	
}


#endif
