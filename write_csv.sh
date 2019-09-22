#!/usr/bin/env sh

## This simple script is meant to continually cature data from the Serial Port ACM0 from the host computer

while :
do
    cat /dev/ttyACM0 >> times_temperatures.csv
done
