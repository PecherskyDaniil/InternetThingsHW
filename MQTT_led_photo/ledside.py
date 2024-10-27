import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib
import serial
import numpy as np

global old_photo
global new_photo
global datastore
global count_photo
global trend
global minp
global maxp
minp=0
maxp=1024
trend=0
old_photo=0
new_photo=0
datastore=[]
count_photo=0
broker="broker.emqx.io"

responses={'d':7,
            'u':6,
            'p':1}

port_led="COM5"
pub_id="" # подставьте свой pub_id
h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
sub_id = h.hexdigest()[10:20]


def avg(data):
    return sum(data)/len(data)
def send_command(cmd:str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    str_resp=None
    connection.write(cmd.encode())
    if response_len>0:
        resp : bytes=connection.read(response_len)
        str_resp : str = resp.decode()
    return str_resp
def on_message(client, userdata, message):
    global old_photo
    global new_photo
    global datastore
    global count_photo
    global trend
    global minp
    global maxp
    d = str(message.payload.decode("utf-8"))
    if (message.topic==f"lab/{pub_id}/photo/instant"):
        datastore.append(float(d))
        count_photo+=1
        if count_photo>0:
            old_photo=new_photo
            new_photo=avg(datastore)
            datastore=[]
            count_photo=0
        if (new_photo-old_photo)>2:
            trend=0
        else:
            trend=1
    elif (message.topic==f"lab/{pub_id}/photo/min"):
        minp=float(d)
    elif (message.topic==f"lab/{pub_id}/photo/max"):
        maxp=float(d)
    elif (message.topic==f"lab/{pub_id}/photo/stream"):
        if (float(d)>avg([minp,maxp]) and trend==0):
            send_command('u',responses['u'],connection_led)
        else:
            send_command('d',responses['d'],connection_led)
            
connection_led=serial.Serial(port_led,timeout=0)

client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION1, 
    sub_id
)
client.on_message=on_message

print("Connecting to broker",broker)
client.connect(broker) 
client.loop_start() 
print("Subcribing")
client.subscribe([(f"lab/{pub_id}/photo/average",0),(f"lab/{pub_id}/photo/instant",0),\
                  (f"lab/{pub_id}/photo/stream",0),\
                  (f"lab/{pub_id}/photo/min",0),(f"lab/{pub_id}/photo/max",0)])
time.sleep(1800)
client.disconnect()
client.loop_stop()

