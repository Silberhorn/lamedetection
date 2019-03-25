import serial
import time
import sys
import termios
import tty

comm = ""
inkey_buffer = 1

def inkey():
    fd=sys.stdin.fileno()
    remember_attributes=termios.tcgetattr(fd)
    tty.setraw(sys.stdin.fileno())
    character=sys.stdin.read(inkey_buffer)
    termios.tcsetattr(fd,termios.TCSADRAIN, remember_attributes)
    return character



s = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(4)

s.write("w")

time.sleep(2)



while comm != "p":
	comm = (inkey())
	print(comm)
	s.write(comm)

s.close()


def inkey():
    fd=sys.stdin.fileno()
    remember_attributes=termios.tcgetattr(fd)
    tty.setraw(sys.stdin.fileno())
    character=sys.stdin.read(inkey_buffer)
    termios.tcsetattr(fd,termios.TCSADRAIN, remember_attributes)
    return character
