#for i in $(ls MiniNtuple/v28/); do echo $i | awk -F'.' '{print "analyze-v36 $OUTPUT_FOLDER " $3 "." $4 " $INPUT_PATH/"$i}'; done | grep BB  >> runSignal_BB_onestepC1.sh

#!/bin/bash

# Analyze samples according to desired grouping

if ! type -p "analyze-v36" > /dev/null; then
	printf "Setting up the environment...\n"
	source rcSetup.sh
fi

printf "Compiling...\n"
rc compile

# path to input files
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v36 

# output folder name
if [ $# -eq 0 ]
  then
    printf "\nERROR: No output folder supplied\n\n"
	return # change to exit when not sourcing
fi

export BASE_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v36/
mkdir -p $BASE_PATH
export OUTPUT_FOLDER=$1
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v36/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

analyze-v36 $OUTPUT_FOLDER BB_onestepC1_350_175_75 $INPUT_PATH/user.othrif.372300.MGPy8EG_A14N_BB_onestepC1_350_175_75_SS2L.a766_r6282_output.root

#<<EOF 
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_400_150_50 $INPUT_PATH/user.othrif.372301.MGPy8EG_A14N_BB_onestepC1_400_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_400_190_90 $INPUT_PATH/user.othrif.372302.MGPy8EG_A14N_BB_onestepC1_400_190_90_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_400_225_125 $INPUT_PATH/user.othrif.372303.MGPy8EG_A14N_BB_onestepC1_400_225_125_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_450_150_50 $INPUT_PATH/user.othrif.372304.MGPy8EG_A14N_BB_onestepC1_450_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_450_200_100 $INPUT_PATH/user.othrif.372305.MGPy8EG_A14N_BB_onestepC1_450_200_100_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_450_240_140 $INPUT_PATH/user.othrif.372306.MGPy8EG_A14N_BB_onestepC1_450_240_140_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_450_275_175 $INPUT_PATH/user.othrif.372307.MGPy8EG_A14N_BB_onestepC1_450_275_175_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_500_150_50 $INPUT_PATH/user.othrif.372308.MGPy8EG_A14N_BB_onestepC1_500_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_500_200_100 $INPUT_PATH/user.othrif.372309.MGPy8EG_A14N_BB_onestepC1_500_200_100_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_500_250_150 $INPUT_PATH/user.othrif.372310.MGPy8EG_A14N_BB_onestepC1_500_250_150_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_500_290_190 $INPUT_PATH/user.othrif.372311.MGPy8EG_A14N_BB_onestepC1_500_290_190_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_500_325_225 $INPUT_PATH/user.othrif.372312.MGPy8EG_A14N_BB_onestepC1_500_325_225_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_550_200_100 $INPUT_PATH/user.othrif.372313.MGPy8EG_A14N_BB_onestepC1_550_200_100_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_550_250_150 $INPUT_PATH/user.othrif.372314.MGPy8EG_A14N_BB_onestepC1_550_250_150_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_550_300_200 $INPUT_PATH/user.othrif.372315.MGPy8EG_A14N_BB_onestepC1_550_300_200_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_550_340_240 $INPUT_PATH/user.othrif.372316.MGPy8EG_A14N_BB_onestepC1_550_340_240_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_550_375_275 $INPUT_PATH/user.othrif.372317.MGPy8EG_A14N_BB_onestepC1_550_375_275_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_600_150_50 $INPUT_PATH/user.othrif.372318.MGPy8EG_A14N_BB_onestepC1_600_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_600_250_150 $INPUT_PATH/user.othrif.372319.MGPy8EG_A14N_BB_onestepC1_600_250_150_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_600_300_200 $INPUT_PATH/user.othrif.372320.MGPy8EG_A14N_BB_onestepC1_600_300_200_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_600_350_250 $INPUT_PATH/user.othrif.372321.MGPy8EG_A14N_BB_onestepC1_600_350_250_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_600_390_290 $INPUT_PATH/user.othrif.372322.MGPy8EG_A14N_BB_onestepC1_600_390_290_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_600_425_325 $INPUT_PATH/user.othrif.372323.MGPy8EG_A14N_BB_onestepC1_600_425_325_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_650_200_100 $INPUT_PATH/user.othrif.372324.MGPy8EG_A14N_BB_onestepC1_650_200_100_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_650_300_200 $INPUT_PATH/user.othrif.372325.MGPy8EG_A14N_BB_onestepC1_650_300_200_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_650_350_250 $INPUT_PATH/user.othrif.372326.MGPy8EG_A14N_BB_onestepC1_650_350_250_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_650_400_300 $INPUT_PATH/user.othrif.372327.MGPy8EG_A14N_BB_onestepC1_650_400_300_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_650_440_340 $INPUT_PATH/user.othrif.372328.MGPy8EG_A14N_BB_onestepC1_650_440_340_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_650_475_375 $INPUT_PATH/user.othrif.372329.MGPy8EG_A14N_BB_onestepC1_650_475_375_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_150_50 $INPUT_PATH/user.othrif.372330.MGPy8EG_A14N_BB_onestepC1_700_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_250_150 $INPUT_PATH/user.othrif.372331.MGPy8EG_A14N_BB_onestepC1_700_250_150_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_350_250 $INPUT_PATH/user.othrif.372332.MGPy8EG_A14N_BB_onestepC1_700_350_250_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_400_300 $INPUT_PATH/user.othrif.372333.MGPy8EG_A14N_BB_onestepC1_700_400_300_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_450_350 $INPUT_PATH/user.othrif.372334.MGPy8EG_A14N_BB_onestepC1_700_450_350_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_490_390 $INPUT_PATH/user.othrif.372335.MGPy8EG_A14N_BB_onestepC1_700_490_390_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_700_525_425 $INPUT_PATH/user.othrif.372336.MGPy8EG_A14N_BB_onestepC1_700_525_425_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_200_100 $INPUT_PATH/user.othrif.372337.MGPy8EG_A14N_BB_onestepC1_750_200_100_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_300_200 $INPUT_PATH/user.othrif.372338.MGPy8EG_A14N_BB_onestepC1_750_300_200_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_400_300 $INPUT_PATH/user.othrif.372339.MGPy8EG_A14N_BB_onestepC1_750_400_300_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_450_350 $INPUT_PATH/user.othrif.372340.MGPy8EG_A14N_BB_onestepC1_750_450_350_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_500_400 $INPUT_PATH/user.othrif.372341.MGPy8EG_A14N_BB_onestepC1_750_500_400_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_540_440 $INPUT_PATH/user.othrif.372342.MGPy8EG_A14N_BB_onestepC1_750_540_440_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_750_575_475 $INPUT_PATH/user.othrif.372343.MGPy8EG_A14N_BB_onestepC1_750_575_475_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_150_50 $INPUT_PATH/user.othrif.372344.MGPy8EG_A14N_BB_onestepC1_800_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_250_150 $INPUT_PATH/user.othrif.372345.MGPy8EG_A14N_BB_onestepC1_800_250_150_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_350_250 $INPUT_PATH/user.othrif.372346.MGPy8EG_A14N_BB_onestepC1_800_350_250_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_450_350 $INPUT_PATH/user.othrif.372347.MGPy8EG_A14N_BB_onestepC1_800_450_350_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_500_400 $INPUT_PATH/user.othrif.372348.MGPy8EG_A14N_BB_onestepC1_800_500_400_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_550_450 $INPUT_PATH/user.othrif.372349.MGPy8EG_A14N_BB_onestepC1_800_550_450_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_590_490 $INPUT_PATH/user.othrif.372350.MGPy8EG_A14N_BB_onestepC1_800_590_490_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_800_625_525 $INPUT_PATH/user.othrif.372351.MGPy8EG_A14N_BB_onestepC1_800_625_525_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_200_100 $INPUT_PATH/user.othrif.372352.MGPy8EG_A14N_BB_onestepC1_850_200_100_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_300_200 $INPUT_PATH/user.othrif.372353.MGPy8EG_A14N_BB_onestepC1_850_300_200_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_400_300 $INPUT_PATH/user.othrif.372354.MGPy8EG_A14N_BB_onestepC1_850_400_300_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_500_400 $INPUT_PATH/user.othrif.372355.MGPy8EG_A14N_BB_onestepC1_850_500_400_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_550_450 $INPUT_PATH/user.othrif.372356.MGPy8EG_A14N_BB_onestepC1_850_550_450_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_600_500 $INPUT_PATH/user.othrif.372357.MGPy8EG_A14N_BB_onestepC1_850_600_500_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_640_540 $INPUT_PATH/user.othrif.372358.MGPy8EG_A14N_BB_onestepC1_850_640_540_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_850_675_575 $INPUT_PATH/user.othrif.372359.MGPy8EG_A14N_BB_onestepC1_850_675_575_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_150_50 $INPUT_PATH/user.othrif.372360.MGPy8EG_A14N_BB_onestepC1_900_150_50_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_250_150 $INPUT_PATH/user.othrif.372361.MGPy8EG_A14N_BB_onestepC1_900_250_150_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_350_250 $INPUT_PATH/user.othrif.372362.MGPy8EG_A14N_BB_onestepC1_900_350_250_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_450_350 $INPUT_PATH/user.othrif.372363.MGPy8EG_A14N_BB_onestepC1_900_450_350_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_550_450 $INPUT_PATH/user.othrif.372364.MGPy8EG_A14N_BB_onestepC1_900_550_450_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_600_500 $INPUT_PATH/user.othrif.372365.MGPy8EG_A14N_BB_onestepC1_900_600_500_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_650_550 $INPUT_PATH/user.othrif.372366.MGPy8EG_A14N_BB_onestepC1_900_650_550_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_690_590 $INPUT_PATH/user.othrif.372367.MGPy8EG_A14N_BB_onestepC1_900_690_590_SS2L.a766_r6282_output.root
analyze-v36 $OUTPUT_FOLDER BB_onestepC1_900_725_625 $INPUT_PATH/user.othrif.372368.MGPy8EG_A14N_BB_onestepC1_900_725_625_SS2L.a766_r6282_output.root

#EOF