#!/usr/bin/python

from socket import *
import time
import subprocess

SERVER = "localhost"
PORT = 27072

# start udps UDP server
p = subprocess.Popen(["./udps"])

print "running udps pid: %s ...\n" % p.pid

# give the udps server 1 second to ready
time.sleep(1)

print "sending test dgrams\n"
s = socket(AF_INET, SOCK_DGRAM)
s.sendto("test 1", (SERVER, PORT))
s.sendto("test 2", (SERVER, PORT))
s.sendto("test 3", (SERVER, PORT))

print "udps.log contents:\n" 
subprocess.call(["cat", "udps.log"])

print "\nkill ./udps udp server"
subprocess.Popen.kill(p)

print "\ndelete udps log test"
subprocess.call(["rm", "udps.log"])
