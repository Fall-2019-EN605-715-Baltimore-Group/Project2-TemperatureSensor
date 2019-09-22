#!/usr/bin/env sh

while :
do
    cat /dev/ttyACM1 >> times_temperatures.csv
done
