#define BLYNK_PRINT Serial

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <DHT_U.h>

int i = 0; 

char auth[] = "";
char ssid[] = "";
char pass[] = "";

const byte pinDHT= 5;
const byte Relay_light = 4;
const byte Relay_dehumid = 14;          //In this iter (for me it's iter 7 but not officially on the records)
                                        //the relay turns on AND off a system of de humidification, which consists of
                                        // one fan that sucks the air into a structure, into the structure there is a 
                                        //pletier device which makes colder the air and makes it start to condensate 
                                        //and thus dehumidify the air of the sys. it also has another fan which cools down
                                        //the pletier cooler/heater.
                                        
long ut = 0;
long UT = 0;



BlynkTimer timer;
DHT dht(pinDHT, DHT11);


void requestTime() {
  Blynk.sendInternal("rtc", "sync");
}


BLYNK_WRITE(InternalPinRTC) {
  ut = param.asLong();
  UT = ut;
  Serial.println();
  Serial.println(ut);
  Serial.println();
  Serial.println(UT);
}

void light_control(){
  Serial.println();
  Serial.println(UT);
  UT += (1296000-18000);                            //the bias compensaton for gettin the right date
  float yr = (UT/31536000.00000);                     //"31536000" number of secs in 365 days 
  int Yr = (int) yr;                               //"cast" yr to its nongreedy rounded integer form
  Serial.println(String(yr) + " año decimal");
  Serial.println(String(Yr)+ " año entero");
  Serial.println();

  // Then get the number of remaining [days] to complete a year 
  float days = (yr-Yr) * 365.00000;                 //decimal expression of num of passed days in this year
  int Days = (int) days;                           //"cast" days to its nongreedy rounded integer form
  
  
  //Now let's find the [Month] we're in
  float months = days/30.00000;                     // decimal month we're in
  int Months = (int) months;                   //get the integer num of the month we're in
  Serial.println(String(Months) + " Mes entero");
  Serial.println();

  //Find the [Day] of the month we're in
  float mday = (months - Months)*30.00000;          //decimal day we're in
  int Mday = (int) mday;                            //day of the month we're in
  Serial.println(String(Mday) + " dia del mes entero");
  Serial.println();


  //specific [Hour] we're in  
  float hours = (days - Days)*24.00000;             //decimal quantity of hours passed
  int Hours = (int) (hours);                     // num of hours passed 
  Serial.println(String(Hours) +"hora del día entero");
  Serial.println();
  

  //specific [Minute] we're in 
  double minutes = ( (hours) - Hours)*60.00000;          //decimal quantity of minutes passed
  int Minutes  = (int) minutes;                 //minutes passed

  //specific [Second] we're in                    
   double secs = (minutes - Minutes)*60.00000;       //decimal version of secs passed
   int Secs = (int) secs;                      //secs passed

   Serial.println("");
   Serial.print( String(Yr+1970) + "/" + String(Months) + "/" + String(Mday) + " " + String(Hours) + ":" + String(Minutes)+ ":" + String(Secs));             


   if(Hours >= 5 && Hours <= 18){
      digitalWrite(Relay_light, HIGH);
      Serial.println(""); Serial.print("Light ON");      
    }else{
      digitalWrite(Relay_light, LOW);
      }  

  }



void getfromDHT11(){
   double t = dht.readTemperature();
   double hum = dht.readHumidity();

   Blynk.virtualWrite(V1, hum); 
   Blynk.virtualWrite(V2, t);     
  }



void internal_control(){   
   float t = dht.readTemperature();
   float hum = dht.readHumidity();

   if ((t>=22 or hum>=40)) {              //due to the fans efficency I have to startn since lower levels to circulate air well
    digitalWrite(Relay_dehumid, HIGH);
    }else{
      digitalWrite(Relay_dehumid, LOW);
      }          
  }





void setup() {
  Serial.begin(9600);
  delay(150);
  dht.begin();
  delay(150);
  
  pinMode(pinDHT, INPUT);
  pinMode(Relay_light, OUTPUT);
  pinMode(Relay_dehumid, OUTPUT);

  Blynk.begin(auth, ssid, pass);

  if (true){
    requestTime();
    delay(100);
    getfromDHT11();
    light_control();
    internal_control();
    i= 1;
  }

  timer.setInterval(60000L, getfromDHT11);        //
  timer.setInterval(40000L, internal_control);    //
  timer.setInterval(1800000L, requestTime);
  timer.setInterval(1800000L, light_control);

}



void loop() {
    
  Blynk.run();
  timer.run();
}
