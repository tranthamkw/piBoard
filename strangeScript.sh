#!/bin/bash

cd /home/pi/strange/

if [ -f msg.txt ]
then
#file found"
echo "SERVER BUSY. Someone else may be using this. Please try again in a moment"
else
#not found

sudo ./strangerThing "$1" 500 500  2>&1

echo "Done"


fi
