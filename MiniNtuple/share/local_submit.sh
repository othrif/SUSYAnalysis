#!/bin/bash
# ./process.sh samples.list

for ARG in `cat $1`
do
	python run_me.py $ARG
done

