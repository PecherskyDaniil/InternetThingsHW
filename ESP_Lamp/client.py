import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib
import questionary

broker="broker.emqx.io"

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
sub_id = h.hexdigest()[10:20]
            
client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION1, 
    sub_id
)
lamp_id=questionary.text("What's lamp do you want send commands to? (id)").ask()
print("Connecting to broker",broker)
client.connect(broker) 
client.loop_start()
dec=0
print(f"/pech/esplamp/{lamp_id}")
p=0
start_time=int(time.time())
while (True):
    cur_time=int(time.time())-start_time
    if cur_time%60>(20+dec//2) and cur_time%60<(40-(dec+1)//2):
        client.publish(f"/pech/esplamp/{lamp_id}","u")
        p=1
    else:
        client.publish(f"/pech/esplamp/{lamp_id}","d")
        if p==1:
            p=0
            if dec==10:
                dec=-1
            dec+=1
    
    time.sleep(0.1)
    print(time.time())
client.disconnect()
client.loop_stop()
