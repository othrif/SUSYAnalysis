
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
export OUTPUT_FOLDER=$1
export BASE_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v36/
mkdir -p $BASE_PATH
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v36/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

######################
# Gtt 
######################

analyze-v36 $OUTPUT_FOLDER ttn1_900_5000_545 $INPUT_PATH/user.othrif.370103.MGPy8EG_A14N_GG_ttn1_900_5000_545.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1000_5000_645 $INPUT_PATH/user.othrif.370108.MGPy8EG_A14N_GG_ttn1_1000_5000_645.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1100_5000_745 $INPUT_PATH/user.othrif.370113.MGPy8EG_A14N_GG_ttn1_1100_5000_745.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_855 $INPUT_PATH/user.othrif.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_945 $INPUT_PATH/user.othrif.370128.MGPy8EG_A14N_GG_ttn1_1300_5000_945.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_1045 $INPUT_PATH/user.othrif.370136.MGPy8EG_A14N_GG_ttn1_1400_5000_1045.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_1145 $INPUT_PATH/user.othrif.370143.MGPy8EG_A14N_GG_ttn1_1500_5000_1145.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_1245 $INPUT_PATH/user.othrif.370151.MGPy8EG_A14N_GG_ttn1_1600_5000_1245.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_1345 $INPUT_PATH/user.othrif.370159.MGPy8EG_A14N_GG_ttn1_1700_5000_1345.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_1445 $INPUT_PATH/user.othrif.370168.MGPy8EG_A14N_GG_ttn1_1800_5000_1445.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_1545 $INPUT_PATH/user.othrif.370177.MGPy8EG_A14N_GG_ttn1_1900_5000_1545.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1645 $INPUT_PATH/user.othrif.370187.MGPy8EG_A14N_GG_ttn1_2000_5000_1645.s2608_r6282_output.root



#<<EOF 
analyze-v36 $OUTPUT_FOLDER ttn1_900_5000_1 $INPUT_PATH/user.othrif.370100.MGPy8EG_A14N_GG_ttn1_900_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_900_5000_200 $INPUT_PATH/user.othrif.370101.MGPy8EG_A14N_GG_ttn1_900_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_900_5000_400 $INPUT_PATH/user.othrif.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_900_5000_545 $INPUT_PATH/user.othrif.370103.MGPy8EG_A14N_GG_ttn1_900_5000_545.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1000_5000_1 $INPUT_PATH/user.othrif.370104.MGPy8EG_A14N_GG_ttn1_1000_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1000_5000_200 $INPUT_PATH/user.othrif.370105.MGPy8EG_A14N_GG_ttn1_1000_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1000_5000_400 $INPUT_PATH/user.othrif.370106.MGPy8EG_A14N_GG_ttn1_1000_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1000_5000_600 $INPUT_PATH/user.othrif.370107.MGPy8EG_A14N_GG_ttn1_1000_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1000_5000_645 $INPUT_PATH/user.othrif.370108.MGPy8EG_A14N_GG_ttn1_1000_5000_645.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1100_5000_1 $INPUT_PATH/user.othrif.370109.MGPy8EG_A14N_GG_ttn1_1100_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1100_5000_200 $INPUT_PATH/user.othrif.370110.MGPy8EG_A14N_GG_ttn1_1100_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1100_5000_400 $INPUT_PATH/user.othrif.370111.MGPy8EG_A14N_GG_ttn1_1100_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1100_5000_600 $INPUT_PATH/user.othrif.370112.MGPy8EG_A14N_GG_ttn1_1100_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_1 $INPUT_PATH/user.othrif.370114.MGPy8EG_A14N_GG_ttn1_1200_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_100 $INPUT_PATH/user.othrif.370115.MGPy8EG_A14N_GG_ttn1_1200_5000_100.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_200 $INPUT_PATH/user.othrif.370116.MGPy8EG_A14N_GG_ttn1_1200_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_400 $INPUT_PATH/user.othrif.370117.MGPy8EG_A14N_GG_ttn1_1200_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_600 $INPUT_PATH/user.othrif.370118.MGPy8EG_A14N_GG_ttn1_1200_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_700 $INPUT_PATH/user.othrif.370119.MGPy8EG_A14N_GG_ttn1_1200_5000_700.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_800 $INPUT_PATH/user.othrif.370120.MGPy8EG_A14N_GG_ttn1_1200_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_845 $INPUT_PATH/user.othrif.370121.MGPy8EG_A14N_GG_ttn1_1200_5000_845.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1200_5000_855 $INPUT_PATH/user.othrif.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_1 $INPUT_PATH/user.othrif.370123.MGPy8EG_A14N_GG_ttn1_1300_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_200 $INPUT_PATH/user.othrif.370124.MGPy8EG_A14N_GG_ttn1_1300_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_400 $INPUT_PATH/user.othrif.370125.MGPy8EG_A14N_GG_ttn1_1300_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_600 $INPUT_PATH/user.othrif.370126.MGPy8EG_A14N_GG_ttn1_1300_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_800 $INPUT_PATH/user.othrif.370127.MGPy8EG_A14N_GG_ttn1_1300_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1300_5000_945 $INPUT_PATH/user.othrif.370128.MGPy8EG_A14N_GG_ttn1_1300_5000_945.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_1 $INPUT_PATH/user.othrif.370129.MGPy8EG_A14N_GG_ttn1_1400_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_100 $INPUT_PATH/user.othrif.370130.MGPy8EG_A14N_GG_ttn1_1400_5000_100.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_200 $INPUT_PATH/user.othrif.370131.MGPy8EG_A14N_GG_ttn1_1400_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_400 $INPUT_PATH/user.othrif.370132.MGPy8EG_A14N_GG_ttn1_1400_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_600 $INPUT_PATH/user.othrif.370133.MGPy8EG_A14N_GG_ttn1_1400_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_800 $INPUT_PATH/user.othrif.370134.MGPy8EG_A14N_GG_ttn1_1400_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_1000 $INPUT_PATH/user.othrif.370135.MGPy8EG_A14N_GG_ttn1_1400_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1400_5000_1045 $INPUT_PATH/user.othrif.370136.MGPy8EG_A14N_GG_ttn1_1400_5000_1045.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_1 $INPUT_PATH/user.othrif.370137.MGPy8EG_A14N_GG_ttn1_1500_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_200 $INPUT_PATH/user.othrif.370138.MGPy8EG_A14N_GG_ttn1_1500_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_400 $INPUT_PATH/user.othrif.370139.MGPy8EG_A14N_GG_ttn1_1500_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_600 $INPUT_PATH/user.othrif.370140.MGPy8EG_A14N_GG_ttn1_1500_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_800 $INPUT_PATH/user.othrif.370141.MGPy8EG_A14N_GG_ttn1_1500_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_1000 $INPUT_PATH/user.othrif.370142.MGPy8EG_A14N_GG_ttn1_1500_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1500_5000_1145 $INPUT_PATH/user.othrif.370143.MGPy8EG_A14N_GG_ttn1_1500_5000_1145.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_1 $INPUT_PATH/user.othrif.370144.MGPy8EG_A14N_GG_ttn1_1600_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_200 $INPUT_PATH/user.othrif.370145.MGPy8EG_A14N_GG_ttn1_1600_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_400 $INPUT_PATH/user.othrif.370146.MGPy8EG_A14N_GG_ttn1_1600_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_600 $INPUT_PATH/user.othrif.370147.MGPy8EG_A14N_GG_ttn1_1600_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_800 $INPUT_PATH/user.othrif.370148.MGPy8EG_A14N_GG_ttn1_1600_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_1000 $INPUT_PATH/user.othrif.370149.MGPy8EG_A14N_GG_ttn1_1600_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_1200 $INPUT_PATH/user.othrif.370150.MGPy8EG_A14N_GG_ttn1_1600_5000_1200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1600_5000_1245 $INPUT_PATH/user.othrif.370151.MGPy8EG_A14N_GG_ttn1_1600_5000_1245.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_1 $INPUT_PATH/user.othrif.370152.MGPy8EG_A14N_GG_ttn1_1700_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_200 $INPUT_PATH/user.othrif.370153.MGPy8EG_A14N_GG_ttn1_1700_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_400 $INPUT_PATH/user.othrif.370154.MGPy8EG_A14N_GG_ttn1_1700_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_600 $INPUT_PATH/user.othrif.370155.MGPy8EG_A14N_GG_ttn1_1700_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_800 $INPUT_PATH/user.othrif.370156.MGPy8EG_A14N_GG_ttn1_1700_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_1000 $INPUT_PATH/user.othrif.370157.MGPy8EG_A14N_GG_ttn1_1700_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_1200 $INPUT_PATH/user.othrif.370158.MGPy8EG_A14N_GG_ttn1_1700_5000_1200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1700_5000_1345 $INPUT_PATH/user.othrif.370159.MGPy8EG_A14N_GG_ttn1_1700_5000_1345.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_1 $INPUT_PATH/user.othrif.370160.MGPy8EG_A14N_GG_ttn1_1800_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_200 $INPUT_PATH/user.othrif.370161.MGPy8EG_A14N_GG_ttn1_1800_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_400 $INPUT_PATH/user.othrif.370162.MGPy8EG_A14N_GG_ttn1_1800_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_600 $INPUT_PATH/user.othrif.370163.MGPy8EG_A14N_GG_ttn1_1800_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_800 $INPUT_PATH/user.othrif.370164.MGPy8EG_A14N_GG_ttn1_1800_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_1000 $INPUT_PATH/user.othrif.370165.MGPy8EG_A14N_GG_ttn1_1800_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_1200 $INPUT_PATH/user.othrif.370166.MGPy8EG_A14N_GG_ttn1_1800_5000_1200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_1400 $INPUT_PATH/user.othrif.370167.MGPy8EG_A14N_GG_ttn1_1800_5000_1400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1800_5000_1445 $INPUT_PATH/user.othrif.370168.MGPy8EG_A14N_GG_ttn1_1800_5000_1445.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_1 $INPUT_PATH/user.othrif.370169.MGPy8EG_A14N_GG_ttn1_1900_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_200 $INPUT_PATH/user.othrif.370170.MGPy8EG_A14N_GG_ttn1_1900_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_400 $INPUT_PATH/user.othrif.370171.MGPy8EG_A14N_GG_ttn1_1900_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_600 $INPUT_PATH/user.othrif.370172.MGPy8EG_A14N_GG_ttn1_1900_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_800 $INPUT_PATH/user.othrif.370173.MGPy8EG_A14N_GG_ttn1_1900_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_1000 $INPUT_PATH/user.othrif.370174.MGPy8EG_A14N_GG_ttn1_1900_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_1200 $INPUT_PATH/user.othrif.370175.MGPy8EG_A14N_GG_ttn1_1900_5000_1200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_1400 $INPUT_PATH/user.othrif.370176.MGPy8EG_A14N_GG_ttn1_1900_5000_1400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_1900_5000_1545 $INPUT_PATH/user.othrif.370177.MGPy8EG_A14N_GG_ttn1_1900_5000_1545.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1 $INPUT_PATH/user.othrif.370178.MGPy8EG_A14N_GG_ttn1_2000_5000_1.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_200 $INPUT_PATH/user.othrif.370179.MGPy8EG_A14N_GG_ttn1_2000_5000_200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_400 $INPUT_PATH/user.othrif.370180.MGPy8EG_A14N_GG_ttn1_2000_5000_400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_600 $INPUT_PATH/user.othrif.370181.MGPy8EG_A14N_GG_ttn1_2000_5000_600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_800 $INPUT_PATH/user.othrif.370182.MGPy8EG_A14N_GG_ttn1_2000_5000_800.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1000 $INPUT_PATH/user.othrif.370183.MGPy8EG_A14N_GG_ttn1_2000_5000_1000.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1200 $INPUT_PATH/user.othrif.370184.MGPy8EG_A14N_GG_ttn1_2000_5000_1200.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1400 $INPUT_PATH/user.othrif.370185.MGPy8EG_A14N_GG_ttn1_2000_5000_1400.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1600 $INPUT_PATH/user.othrif.370186.MGPy8EG_A14N_GG_ttn1_2000_5000_1600.s2608_r6282_output.root
analyze-v36 $OUTPUT_FOLDER ttn1_2000_5000_1645 $INPUT_PATH/user.othrif.370187.MGPy8EG_A14N_GG_ttn1_2000_5000_1645.s2608_r6282_output.root
#EOF

#analyze $OUTPUT_FOLDER ttn1_1400_5000_600 $INPUT_PATH/user.othrif.370133.MGPy8EG_A14N_GG_ttn1_1400_5000_600.root
#analyze $OUTPUT_FOLDER ttn1_1400_5000_800 $INPUT_PATH/user.othrif.370134.MGPy8EG_A14N_GG_ttn1_1400_5000_800.root
#analyze $OUTPUT_FOLDER ttn1_1400_5000_1000 $INPUT_PATH/user.othrif.370135.MGPy8EG_A14N_GG_ttn1_1400_5000_1000.root
