import serial
import time

s = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(4)

s.write("w")

time.sleep(2)
response = s.readline()
print(response)

s.write("a")

time.sleep(2)
response = s.readline()
print(response)

s.write("d")

time.sleep(2)
response = s.readline()
print(response)

s.write("s")

time.sleep(2)
response = s.readline()
print(response)

s.write("c")

s.close()
