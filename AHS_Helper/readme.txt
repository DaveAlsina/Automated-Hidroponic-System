Esta subcarpeta del proyecto es una librería que busca hacer más sencillo y ordenado 
el código que se vaya a emplear relativo a la toma de mediciones con los sensores:

1)	DHT11		(Humedad y temperatura)
2)	DS18B20		(Sonda de medición de temperatura)
3)	Sonda medidora de EC (DIY, EC(Electroconductividad))

En ella se hace uso de las librerias 'DHT' y 'DallasTemperature'.

Contiende unas funcionalidades extra para cada módulo
permitiendo obtener unas mediciónes más 'resistentes' a errores (es decir: que las mediciones 
que se guarden o envíen van a ser menos propensas a ser erroneas).

Además esta librería contiende un módulo para el manejo cómodo de un sensor DIY de Electroconductividad [EC]
las referencias al código original se encuentran acá:

https://hackaday.io/project/7008-fly-wars-a-hackers-solution-to-world-hunger/log/24646-three-dollar-ec-ppm-meter-arduino 

Información sobre como hacer una sonda de estas acá: 
https://www.youtube.com/watch?v=wHKHTTbyTrI 
https://www.youtube.com/watch?v=D6DL5K86U2c

[PD: muchas gracias Michael Ratcliffe]
