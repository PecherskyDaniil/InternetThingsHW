import serial
import time
import matplotlib.pyplot as plt
import numpy as np

plt.style.use('ggplot')

def live_plotter(x_vec,y1_data,line1,identifier='',pause_time=0.1):
    if line1==[]:
        # this is the call to matplotlib that allows dynamic plotting
        plt.ion()
        fig = plt.figure(figsize=(13,6))
        ax = fig.add_subplot(111)
        # create a variable for the line so we can later update it
        line1, = ax.plot(x_vec,y1_data,'-o',alpha=0.8)        
        #update plot label/title
        plt.ylabel('Y Label')
        plt.title('INFRO_VAL: {}'.format(identifier))
        plt.show()
    
    # after the figure, axis, and line are created, we only need to update the y-data
    line1.set_ydata(y1_data)
    # adjust limits if new data goes beyond bounds
    if np.min(y1_data)<=line1.axes.get_ylim()[0] or np.max(y1_data)>=line1.axes.get_ylim()[1]:
        plt.ylim([np.min(y1_data)-np.std(y1_data),np.max(y1_data)+np.std(y1_data)])
    # this pauses the data so the figure/axis can catch up - the amount of pause can be altered above
    plt.pause(pause_time)
    
    # return line so we can update it again in the next iteration
    return line1
    
responses = {'i': 1,
             'u':1}  # 0 -> 1023 zero fill to leftside
port = "COM5" # "COM4" or similar for windows
# "COM4" or similar for windows
connection = serial.Serial(port, timeout=1) # baudrate=9600
line1 = []
line2=[]
size=100
x_vec = np.linspace(0,1,size+1)[0:-1]
y_vec = np.zeros(len(x_vec))
def get_d(cmd:str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    str_resp=None
    connection.write(cmd.encode())
    if response_len>0:
        resp : bytes=connection.read(response_len)
        int_resp : str = int.from_bytes(resp)
    return int_resp
i_all=[]
u_all=[]
while True:
    i_val:str=get_d('i',responses['i'],connection)*4
    u_val=get_d('u',responses['u'],connection)*4
    y_vec[:-1]=y_vec[1:]
    y_vec[-1] = i_val
    i_all.append(i_val)
    u_all.append(u_val/(29.1))
    line1 = live_plotter(x_vec,y_vec,line1)
    if len(set(list(map(int,u_all))))/25>0.9:
        break
    print(len(set(list(map(int,u_all))))/25)
plt.figure()
#plt.scatter(u_all,i_all)
p30 = np.poly1d(np.polyfit(u_all,i_all, 3))
xp=np.linspace(min(u_all), max(u_all), 100)
_ = plt.plot(u_all,i_all, '.', xp, p30(xp), '-')
plt.show()
