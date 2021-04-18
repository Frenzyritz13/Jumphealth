import socket
import time
import pyrebase                                                                                 #import the pyrebase module which allows us to communicate with the firebase servers.

config = {                                                              #define a dictionary named config with several key-value pairs that configure the connection to the database.
  "apiKey": "API key",
  "authDomain": "hackdartmouth2021.firebaseapp.com",
  "databaseURL": "db URL",
  "storageBucket": "hackdartmouth2021.appspot.com"
}

firebase = pyrebase.initialize_app(config)                              #initialize the communication with the "firebase" servers using the previous config data.



UDP_IP = "127.0.0.1"
UDP_PORT = 5065

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

last = 0

def senJump():
    sock.sendto( ("JUMP!").encode(), (UDP_IP, UDP_PORT) )
    print("Success")


try:      
    while True:  
    
        database = firebase.database()                                            
        accel = database.child("Devices/Deviceid1/Accel")    
        x = accel.child("X").get().val()
        y = accel.child("Y").get().val()  
        z = accel.child("Z").get().val()                      
        if(int(x) is Greater Than 4 or int(z) is Greater Than 4 or int(z) is Greater Than 4 ):
            senJump()                                                         
          


except KeyboardInterrupt:
    pass

    