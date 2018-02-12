#!/bin/bash
echo "Processing dataset : "$1
# Shorten dataset name for ouput name
#DATAFRAG=${1:16}
DATAFRAG=${1}
# Remove trailing backslash
DATAFRAG=${DATAFRAG%/}
#this will reduce the length of datasets for the Gtt simulations
#DATAFRAG=${DATAFRAG/_UEEE3_CTEQ6L1_/_}
#DATAFRAG=${DATAFRAG/_AUET2CT10_/_}
DATAFRAG=${DATAFRAG/_AU2CT10_/_}
#DATAFRAG=${DATAFRAG/_AUET2BCTEQ6L1_/_}
#DATAFRAG=${DATAFRAG/_AUET2CTEQ6L1_/_}
#DATAFRAG=${DATAFRAG/_AUET2B_CTEQ6L1_/_}
DATAFRAG=${DATAFRAG/.NTUP_SUSY./.MINI.}
DATAFRAG=${DATAFRAG/.merge./.}
DATAFRAG=${DATAFRAG/_Auto_AUET2CTEQ6L1_/_}
prun --exec "python prun_me.py %IN" --outDS user.czhou.${DATAFRAG}.v17.8.5 --inDS $1 --outputs out1.root --nFilesPerJob 3 --athenaTag 17.0.4 --useAthenaPackages --noBuild
# --destSE BNL-OSG2_LOCALGROUPDISK
#MWT2_UC_LOCALGROUPDISK

# --excludedSite ANALY_FZU
# --cloud US


