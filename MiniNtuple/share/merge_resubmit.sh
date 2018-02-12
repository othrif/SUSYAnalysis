#!/bin/bash
# ./merge_submit.sh 

export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
lsetup asetup 
asetup --release=20.7.3 --cmtconfig=x86_64-slc6-gcc48-opt --testarea=~/testarea/

rm -f list-resubmit.list Ximo.list MiniNtuple.list

ls /UserDisk2/othrif/data/Ximo/v44-3 | grep user.othrif  > Ximo.list
ls /UserDisk2/othrif/data/MiniNtuple/v44-3 | grep user.othrif  > MiniNtuple.list

TEST_FILE=Ximo.list
CHECK_FILE=MiniNtuple.list

## for each line in TEST_FILE
while read line ; do

    ## check if line exist in CHECK_FILE; then assign result to variable
#echo $line
    X=$(grep "^${line}$" ${CHECK_FILE})

    ## if variable is blank (meaning TEST_FILE line not found in CHECK_FILE)
    ## print 'false' and exit
    if [[ -z $X ]] ; then
#        echo -n "$line"
		echo $line >> list-resubmit.list
    fi

done < ${TEST_FILE}


for ARG in `cat list-resubmit.list`
do
   	python run_me.py $ARG
done

rm -f list-resubmit.list Ximo.list MiniNtuple.list