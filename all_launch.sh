#!/bin/bash

launch -c launch.conf &
sleep 5
./destination_converter
sleep 1
matlab -nodisplay -r "addpath matlab_091217;simulationOne_shell; exit"
