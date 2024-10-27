import time
import paho.mqtt.client as mqtt_client
import random
import socket
import sys
import hashlib
from getmac import get_mac_address as gma
import serial
def get_photo(cmd:str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    str_resp=None
    connection.write(cmd.encode())
    if response_len>0:
        resp : bytes=connection.read(response_len)
        int_resp : str = int.from_bytes(resp)
    return int_resp

stream_state=False

hashmac=hashlib.md5(gma().encode()).hexdigest()
pub_id=hashmac
broker="broker.emqx.io"
client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2, 
    hashmac
)
def on_message(client, userdata, message):
    global stream_state
    data = str(message.payload.decode("utf-8"))
    if data=="on":
        stream_state=True
    elif data=="off":
        stream_state=False
client.connect(broker)
client.on_message=on_message
client.loop_start()

responses={'d':7,#led off
            'u':6,#led on
            'p':1}#1023,zerofill to leftside
port_photo="COM5"
connection_photo=serial.Serial(port_photo,timeout=1)
client.subscribe(f"lab/{pub_id}/photo/activate_stream")
stream_time=time.time()
inst_time=time.time()
avg_time=time.time()
minmax_time=time.time()
min_val=1000000
max_val=0
arr=[]
while True:
    photo_val:str=get_photo('p',responses['p'],connection_photo)*4
    if min_val>photo_val and photo_val>0:
        min_val=photo_val
    if max_val<photo_val:
        max_val=photo_val
    if len(arr)<100:
        arr+=[photo_val]
    else:
        arr=arr[1:]+[photo_val]
    avg=sum(arr)/len(arr)
    if stream_state and time.time()-stream_time>0.1:
        stream_time=time.time()
        client.publish(f"lab/{pub_id}/photo/stream", photo_val)
    if stream_state and time.time()-inst_time>1:
        inst_time=time.time()
        client.publish(f"lab/{pub_id}/photo/instant", int(100*photo_val/1024))
    if stream_state and time.time()-avg_time>1:
        avg_time=time.time()
        client.publish(f"lab/{pub_id}/photo/average", int(100*avg/1024))
    if stream_state and time.time()-minmax_time>5:
        minmax_time=time.time()
        client.publish(f"lab/{pub_id}/photo/min", min_val)
        client.publish(f"lab/{pub_id}/photo/max", max_val)
        
client.disconnect()
client.loop_stop()


