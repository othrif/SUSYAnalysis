export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh 
#asetup --release=20.1.4.10 --cmtconfig=x86_64-slc6-gcc48-opt --testarea=~/testarea/20.1.4.10/
asetup --release=20.7.3 --cmtconfig=x86_64-slc6-gcc48-opt --testarea=~/testarea/
#localSetupDQ2Client
#localSetupPandaClient
#voms-proxy-init -voms atlas -valid 96:00
#source /afs/cern.ch/atlas/software/tools/pyAMI/setup.sh
#localSetupPyAMI
