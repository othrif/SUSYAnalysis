#!/bin/bash

# ./grid_submit.sh
# setup grid
# Get list of files from the grid and process them with prun_me.py

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
asetup --release=20.1.4.10 --cmtconfig=x86_64-slc6-gcc48-opt --testarea=~/testarea/20.1.4.10/
localSetupDQ2Client
localSetupPandaClient
voms-proxy-init -voms atlas -valid 96:00
source /afs/cern.ch/atlas/software/tools/pyAMI/setup.sh
localSetupPyAMI


dq2-ls user.jpoveda.t0703_v25*_output.root/  | awk -F ":" '{print $2}' > tmp.list

for ARG in `cat tmp.list`
do
	./submit_othrif.sh $ARG
done

rm -f tmp.list
