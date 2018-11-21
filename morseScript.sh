#!/bin/bash
#to do . make sure this directory exists
cd /home/pi/morse/

if [ -f msg.txt ]
then
#file found"
echo "SERVER BUSY. Someone else may be using this. Please try again in a moment"
else
#not found

sudo ./morseCode "$1" 80  2>&1

echo "Done"


fi
