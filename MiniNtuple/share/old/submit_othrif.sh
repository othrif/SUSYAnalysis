#!/bin/bash
echo "Processing dataset : "$1
# Shorten dataset name for ouput name
DATAFRAG=${1}

# General
DATAFRAG=${DATAFRAG%/} # Remove trailing backslash
DATAFRAG=${DATAFRAG/user.jpoveda./} 
DATAFRAG=${DATAFRAG/physics_Main/data}
DATAFRAG=${DATAFRAG/_output.root/}


#Shorten generator names
DATAFRAG=${DATAFRAG/MadGraphPythia8/MGP8}
DATAFRAG=${DATAFRAG/aMcAtNloHerwigppEvtGen/aMcAtNHEG}
DATAFRAG=${DATAFRAG/PowhegPythia/PP}
DATAFRAG=${DATAFRAG/PowhegPythia8/PP8}
DATAFRAG=${DATAFRAG/EvtGen/EG}

# other
DATAFRAG=${DATAFRAG/UEEE5_CTEQ6L1_CT10ME/}
DATAFRAG=${DATAFRAG/Filter/Filt}
DATAFRAG=${DATAFRAG/Veto/Ve}
DATAFRAG=${DATAFRAG/DAOD_SUSY2/dSUSY2}


prun -v --exec "python prun_me.py %IN" --outDS user.othrif.${DATAFRAG}.v20.1.4.10 --inDS $1 --outputs out1.root --nFilesPerJob 3 --athenaTag 20.1.4.10 --noBuild --cmtConfig=x86_64-slc6-gcc48-opt --maxFileSize=100000000
# --destSE BNL-OSG2_LOCALGROUPDISK
#MWT2_UC_LOCALGROUPDISK

# --excludedSite ANALY_FZU
# --cloud US
#--useAthenaPackages 

