#!/bin/bash
# ./merge_submit.sh 

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
asetup --release=20.7.3 --cmtconfig=x86_64-slc6-gcc48-opt --testarea=~/testarea/

rm -f list.list

ls /UserDisk2/othrif/data/Ximo/v44 | grep user.othrif  > list.list

for ARG in `cat list.list`
do
	python run_me.py $ARG
done

rm -f list.list