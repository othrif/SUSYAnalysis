#!/bin/bash

# ./grid_submit.sh
# setup grid
# Get list of files from the grid and process them with prun_me.py

for ARG in `cat $1`
do
	./submit_othrif.sh $ARG
done


