import serial
import time

responses={'d':7,#led off
            'u':6,#led on
            'p':1}#1023,zerofill to leftside

port_led="COM5"
port_photo="COM6"
connection_led=serial.Serial(port_led,timeout=1)
connection_photo=serial.Serial(port_photo,timeout=1)

def send_command(cmd:str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    str_resp=None
    connection.write(cmd.encode())
    if response_len>0:
        resp : bytes=connection.read(response_len)
        str_resp : str = resp.decode()
    return str_resp
def get_photo(cmd:str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    str_resp=None
    connection.write(cmd.encode())
    if response_len>0:
        resp : bytes=connection.read(response_len)
        int_resp : str = int.from_bytes(resp)
    return int_resp
while True:
    photo_val:str=get_photo('p',responses['p'],connection_photo)*4
    #if len(photo_val_resp)!=0:
    #    photo_val=int(photo_val_resp)
    #else:
    #    photo_val=0
    print(photo_val)
    if (photo_val<300):
        resp=send_command('u',responses['u'],connection_led)
        #print(resp)
    else:
        resp=send_command('d',responses['d'],connection_led)
        #print(resp)
