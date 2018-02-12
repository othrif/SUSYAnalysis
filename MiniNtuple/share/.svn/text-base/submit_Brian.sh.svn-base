#!/bin/bash
echo "Processing dataset : "$1
# Shorten dataset name for ouput name
DATAFRAG=${1:16}
# Remove trailing backslash
DATAFRAG=${DATAFRAG%/}
prun --exec "python prun_me.py %IN"  --outDS user.BrianTMartin.${DATAFRAG}.MINI.v16.1.1 --inDS $1 --outputs out1.root --nFilesPerJob 5 --athenaTag 16.0.2 --useAthenaPackages --noBuild
