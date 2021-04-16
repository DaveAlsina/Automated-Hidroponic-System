import csv
from pprint import pprint as pp

import paho.mqtt.client as mqtt

import datetime
import time 

def on_connect(client, userdata, flags, rc):

    print("Connected with result code "+str(rc))
    client.subscribe("Esp8266!D4ta/#")              #subscripción a todos los temas de la forma 'Esp8266!D4ta/*'

def on_message(client, userdata, message):

    msg = str(message.payload.decode("utf-8"))      #decodificación del mensaje enviado 
    topic = message.topic                           #obtención del tema de llegada del mensaje

    topic = topic.split('/')                        #obtención de la información importante que se encuentra
    topic = topic[1:]                               #expresada en el tema del mensajede llegada
                                                    #esto es de la forma: ['10370001','pressure']
                                                    #que es: ['identificador de sensor', 'variable enviada']


    print(topic)
    #agrego valores a la llave dada por el id del sensor (topic[0] contiene el id del sensor)
    #lo que contiene messages[topic[0]] es de la forma ['temperatura', 'humedad', 'presión atmosférica', 'lux']

    if topic[0] in messages.keys():
        messages[topic[0]][topic[1]] = msg 

    else:
        messages[topic[0]] = {}
        messages[topic[0]][topic[1]] = msg

    #cada una de las llaves en el diccionario es un identificador de sensor (sensor id)
    #entonces se chequea que para cada identificador en el diccionario (llave), se tenga
    #la cantidad suficiente de mediciones, si es suficiente entonces se guarda y se 
    #sobreescribe el valor para la llave particular

    for key in messages.keys():

        if len(messages[key]) == 4:

            #preparación de todos los datos para guardarlos en una fila del csv
            now = datetime.datetime.now()
            currtime = now.strftime("%Y-%m-%d %H:%M:%S")
            
            row = []                #lista que contiene los valores a guardarse en una fila del csv

            row.append(key)         #inserta el id al principio de la serie de datos
            row.append(currtime)    #inserta el la hora inmediatamente después del id

            row.append(messages[key]["temp"])
            row.append(messages[key]["hum"])
            row.append(messages[key]["pressure"])
            row.append(messages[key]["lux"])


            #escribe la fila al csv
            with open('sensor_data.csv', 'a+') as csvfile: 
                filewriter = csv.writer(csvfile, delimiter=',', quotechar='|', quoting=csv.QUOTE_MINIMAL)
                
                pp(row)
                filewriter.writerow(row)

            #vaciado del contenedor de datos para recibir datos nuevos
            messages[key] = {}



#diccionario para guardar los mensajes que llegan de una forma más ordenada
#los valores de las llaves en el diccionario serán los códigos que identifican a cada sensor
messages = {}

#definición del broker a usar 
mqttBroker = ""                     #ip del broker en red local
port = 1883                         #puerto a conectar

client = mqtt.Client()

client.on_message = on_message
client.on_connect = on_connect

client.username_pw_set(username="", password="")
client.connect(mqttBroker, port) #conexión al broker

client.loop_forever()
