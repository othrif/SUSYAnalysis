# path to input files
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v47_0

# output folder name
if [ $# -eq 0 ]
  then
    printf "\nERROR: No output folder supplied\n\n"
	return # change to exit when not sourcing
fi
export OUTPUT_FOLDER=$1
export BASE_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v48/
mkdir -p $BASE_PATH
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v48/$OUTPUT_FOLDER
mkdir -p $OUTPUT_PATH

######################
# Gtt 
######################

# above diagonal
nohup optimize $OUTPUT_FOLDER ttn1_700_5000_355 $INPUT_PATH/user.othrif.370189.MGPy8EG_A14N23LO_GG_ttn1_700_5000_355_4body*.root > nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_700_5000_400 $INPUT_PATH/user.othrif.370190.MGPy8EG_A14N23LO_GG_ttn1_700_5000_400_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_700_5000_440 $INPUT_PATH/user.othrif.370191.MGPy8EG_A14N23LO_GG_ttn1_700_5000_440_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_700_5000_465 $INPUT_PATH/user.othrif.370192.MGPy8EG_A14N23LO_GG_ttn1_700_5000_465_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_700_5000_490 $INPUT_PATH/user.othrif.370193.MGPy8EG_A14N23LO_GG_ttn1_700_5000_490_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_800_5000_455 $INPUT_PATH/user.othrif.370195.MGPy8EG_A14N23LO_GG_ttn1_800_5000_455_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_800_5000_500 $INPUT_PATH/user.othrif.370196.MGPy8EG_A14N23LO_GG_ttn1_800_5000_500_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_800_5000_540 $INPUT_PATH/user.othrif.370197.MGPy8EG_A14N23LO_GG_ttn1_800_5000_540_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_800_5000_565 $INPUT_PATH/user.othrif.370198.MGPy8EG_A14N23LO_GG_ttn1_800_5000_565_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_800_5000_590 $INPUT_PATH/user.othrif.370199.MGPy8EG_A14N23LO_GG_ttn1_800_5000_590_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_555 $INPUT_PATH/user.othrif.370200.MGPy8EG_A14N23LO_GG_ttn1_900_5000_555_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_600 $INPUT_PATH/user.othrif.370201.MGPy8EG_A14N23LO_GG_ttn1_900_5000_600_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_640 $INPUT_PATH/user.othrif.370202.MGPy8EG_A14N23LO_GG_ttn1_900_5000_640_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_665 $INPUT_PATH/user.othrif.370203.MGPy8EG_A14N23LO_GG_ttn1_900_5000_665_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_690 $INPUT_PATH/user.othrif.370204.MGPy8EG_A14N23LO_GG_ttn1_900_5000_690_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_655 $INPUT_PATH/user.othrif.370205.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_655_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_700 $INPUT_PATH/user.othrif.370206.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_700_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_740 $INPUT_PATH/user.othrif.370207.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_740_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_765 $INPUT_PATH/user.othrif.370208.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_765_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_790 $INPUT_PATH/user.othrif.370209.MGPy8EG_A14N23LO_GG_ttn1_1000_5000_790_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_755 $INPUT_PATH/user.othrif.370210.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_755_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_800 $INPUT_PATH/user.othrif.370211.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_800_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_840 $INPUT_PATH/user.othrif.370212.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_840_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_865 $INPUT_PATH/user.othrif.370213.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_865_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_890 $INPUT_PATH/user.othrif.370214.MGPy8EG_A14N23LO_GG_ttn1_1100_5000_890_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_900 $INPUT_PATH/user.othrif.370217.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_900_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_940 $INPUT_PATH/user.othrif.370218.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_940_4body_Np0*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_940 $INPUT_PATH/user.othrif.370219.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_940_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_965 $INPUT_PATH/user.othrif.370220.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_965_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_990 $INPUT_PATH/user.othrif.370221.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_990_5body_Np0*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_990 $INPUT_PATH/user.othrif.370222.MGPy8EG_A14N23LO_GG_ttn1_1200_5000_990_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_955 $INPUT_PATH/user.othrif.370223.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_955_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_1000 $INPUT_PATH/user.othrif.370224.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_1000_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_1040 $INPUT_PATH/user.othrif.370225.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_1040_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_1065 $INPUT_PATH/user.othrif.370226.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_1065_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_1090 $INPUT_PATH/user.othrif.370227.MGPy8EG_A14N23LO_GG_ttn1_1300_5000_1090_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1055 $INPUT_PATH/user.othrif.370228.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1055_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1100 $INPUT_PATH/user.othrif.370229.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1100_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1140 $INPUT_PATH/user.othrif.370230.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1140_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1165 $INPUT_PATH/user.othrif.370231.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1165_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1190 $INPUT_PATH/user.othrif.370232.MGPy8EG_A14N23LO_GG_ttn1_1400_5000_1190_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1255 $INPUT_PATH/user.othrif.370233.MGPy8EG_A14N23LO_GG_ttn1_1600_5000_1255_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1340 $INPUT_PATH/user.othrif.370234.MGPy8EG_A14N23LO_GG_ttn1_1600_5000_1340_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1390 $INPUT_PATH/user.othrif.370235.MGPy8EG_A14N23LO_GG_ttn1_1600_5000_1390_5body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1455 $INPUT_PATH/user.othrif.370236.MGPy8EG_A14N23LO_GG_ttn1_1800_5000_1455_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1540 $INPUT_PATH/user.othrif.370237.MGPy8EG_A14N23LO_GG_ttn1_1800_5000_1540_4body*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1590 $INPUT_PATH/user.othrif.370238.MGPy8EG_A14N23LO_GG_ttn1_1800_5000_1590_5body*.root >> nohup_ttn1.log 


#<<EOF 
#below diagonal
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_1 $INPUT_PATH/user.othrif.370100.MGPy8EG_A14N_GG_ttn1_900_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_200 $INPUT_PATH/user.othrif.370101.MGPy8EG_A14N_GG_ttn1_900_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_400 $INPUT_PATH/user.othrif.370102.MGPy8EG_A14N_GG_ttn1_900_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_900_5000_545 $INPUT_PATH/user.othrif.370103.MGPy8EG_A14N_GG_ttn1_900_5000_545*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_1 $INPUT_PATH/user.othrif.370104.MGPy8EG_A14N_GG_ttn1_1000_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_200 $INPUT_PATH/user.othrif.370105.MGPy8EG_A14N_GG_ttn1_1000_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_400 $INPUT_PATH/user.othrif.370106.MGPy8EG_A14N_GG_ttn1_1000_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_600 $INPUT_PATH/user.othrif.370107.MGPy8EG_A14N_GG_ttn1_1000_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1000_5000_645 $INPUT_PATH/user.othrif.370108.MGPy8EG_A14N_GG_ttn1_1000_5000_645*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_1 $INPUT_PATH/user.othrif.370109.MGPy8EG_A14N_GG_ttn1_1100_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_200 $INPUT_PATH/user.othrif.370110.MGPy8EG_A14N_GG_ttn1_1100_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_400 $INPUT_PATH/user.othrif.370111.MGPy8EG_A14N_GG_ttn1_1100_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1100_5000_600 $INPUT_PATH/user.othrif.370112.MGPy8EG_A14N_GG_ttn1_1100_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_1 $INPUT_PATH/user.othrif.370114.MGPy8EG_A14N_GG_ttn1_1200_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_100 $INPUT_PATH/user.othrif.370115.MGPy8EG_A14N_GG_ttn1_1200_5000_100*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_200 $INPUT_PATH/user.othrif.370116.MGPy8EG_A14N_GG_ttn1_1200_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_400 $INPUT_PATH/user.othrif.370117.MGPy8EG_A14N_GG_ttn1_1200_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_600 $INPUT_PATH/user.othrif.370118.MGPy8EG_A14N_GG_ttn1_1200_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_700 $INPUT_PATH/user.othrif.370119.MGPy8EG_A14N_GG_ttn1_1200_5000_700*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_800 $INPUT_PATH/user.othrif.370120.MGPy8EG_A14N_GG_ttn1_1200_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_845 $INPUT_PATH/user.othrif.370121.MGPy8EG_A14N_GG_ttn1_1200_5000_845*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1200_5000_855 $INPUT_PATH/user.othrif.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_1 $INPUT_PATH/user.othrif.370123.MGPy8EG_A14N_GG_ttn1_1300_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_200 $INPUT_PATH/user.othrif.370124.MGPy8EG_A14N_GG_ttn1_1300_5000_200*.root >> nohup_ttn1.log 
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_400 $INPUT_PATH/user.othrif.370125.MGPy8EG_A14N_GG_ttn1_1300_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_600 $INPUT_PATH/user.othrif.370126.MGPy8EG_A14N_GG_ttn1_1300_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_800 $INPUT_PATH/user.othrif.370127.MGPy8EG_A14N_GG_ttn1_1300_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1300_5000_945 $INPUT_PATH/user.othrif.370128.MGPy8EG_A14N_GG_ttn1_1300_5000_945*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1 $INPUT_PATH/user.othrif.370129.MGPy8EG_A14N_GG_ttn1_1400_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_100 $INPUT_PATH/user.othrif.370130.MGPy8EG_A14N_GG_ttn1_1400_5000_100*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_200 $INPUT_PATH/user.othrif.370131.MGPy8EG_A14N_GG_ttn1_1400_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_400 $INPUT_PATH/user.othrif.370132.MGPy8EG_A14N_GG_ttn1_1400_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_600 $INPUT_PATH/user.othrif.370133.MGPy8EG_A14N_GG_ttn1_1400_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_800 $INPUT_PATH/user.othrif.370134.MGPy8EG_A14N_GG_ttn1_1400_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1000 $INPUT_PATH/user.othrif.370135.MGPy8EG_A14N_GG_ttn1_1400_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1400_5000_1045 $INPUT_PATH/user.othrif.370136.MGPy8EG_A14N_GG_ttn1_1400_5000_1045*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_1 $INPUT_PATH/user.othrif.370137.MGPy8EG_A14N_GG_ttn1_1500_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_200 $INPUT_PATH/user.othrif.370138.MGPy8EG_A14N_GG_ttn1_1500_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_400 $INPUT_PATH/user.othrif.370139.MGPy8EG_A14N_GG_ttn1_1500_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_600 $INPUT_PATH/user.othrif.370140.MGPy8EG_A14N_GG_ttn1_1500_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_800 $INPUT_PATH/user.othrif.370141.MGPy8EG_A14N_GG_ttn1_1500_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_1000 $INPUT_PATH/user.othrif.370142.MGPy8EG_A14N_GG_ttn1_1500_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1500_5000_1145 $INPUT_PATH/user.othrif.370143.MGPy8EG_A14N_GG_ttn1_1500_5000_1145*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1 $INPUT_PATH/user.othrif.370144.MGPy8EG_A14N_GG_ttn1_1600_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_200 $INPUT_PATH/user.othrif.370145.MGPy8EG_A14N_GG_ttn1_1600_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_400 $INPUT_PATH/user.othrif.370146.MGPy8EG_A14N_GG_ttn1_1600_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_600 $INPUT_PATH/user.othrif.370147.MGPy8EG_A14N_GG_ttn1_1600_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_800 $INPUT_PATH/user.othrif.370148.MGPy8EG_A14N_GG_ttn1_1600_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1000 $INPUT_PATH/user.othrif.370149.MGPy8EG_A14N_GG_ttn1_1600_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1200 $INPUT_PATH/user.othrif.370150.MGPy8EG_A14N_GG_ttn1_1600_5000_1200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1600_5000_1245 $INPUT_PATH/user.othrif.370151.MGPy8EG_A14N_GG_ttn1_1600_5000_1245*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_1 $INPUT_PATH/user.othrif.370152.MGPy8EG_A14N_GG_ttn1_1700_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_200 $INPUT_PATH/user.othrif.370153.MGPy8EG_A14N_GG_ttn1_1700_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_400 $INPUT_PATH/user.othrif.370154.MGPy8EG_A14N_GG_ttn1_1700_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_600 $INPUT_PATH/user.othrif.370155.MGPy8EG_A14N_GG_ttn1_1700_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_800 $INPUT_PATH/user.othrif.370156.MGPy8EG_A14N_GG_ttn1_1700_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_1000 $INPUT_PATH/user.othrif.370157.MGPy8EG_A14N_GG_ttn1_1700_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_1200 $INPUT_PATH/user.othrif.370158.MGPy8EG_A14N_GG_ttn1_1700_5000_1200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1700_5000_1345 $INPUT_PATH/user.othrif.370159.MGPy8EG_A14N_GG_ttn1_1700_5000_1345*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1 $INPUT_PATH/user.othrif.370160.MGPy8EG_A14N_GG_ttn1_1800_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_200 $INPUT_PATH/user.othrif.370161.MGPy8EG_A14N_GG_ttn1_1800_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_400 $INPUT_PATH/user.othrif.370162.MGPy8EG_A14N_GG_ttn1_1800_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_600 $INPUT_PATH/user.othrif.370163.MGPy8EG_A14N_GG_ttn1_1800_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_800 $INPUT_PATH/user.othrif.370164.MGPy8EG_A14N_GG_ttn1_1800_5000_800*.root >> nohup_ttn1.log 
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1000 $INPUT_PATH/user.othrif.370165.MGPy8EG_A14N_GG_ttn1_1800_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1200 $INPUT_PATH/user.othrif.370166.MGPy8EG_A14N_GG_ttn1_1800_5000_1200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1400 $INPUT_PATH/user.othrif.370167.MGPy8EG_A14N_GG_ttn1_1800_5000_1400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1800_5000_1445 $INPUT_PATH/user.othrif.370168.MGPy8EG_A14N_GG_ttn1_1800_5000_1445*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_1 $INPUT_PATH/user.othrif.370169.MGPy8EG_A14N_GG_ttn1_1900_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_200 $INPUT_PATH/user.othrif.370170.MGPy8EG_A14N_GG_ttn1_1900_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_400 $INPUT_PATH/user.othrif.370171.MGPy8EG_A14N_GG_ttn1_1900_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_600 $INPUT_PATH/user.othrif.370172.MGPy8EG_A14N_GG_ttn1_1900_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_800 $INPUT_PATH/user.othrif.370173.MGPy8EG_A14N_GG_ttn1_1900_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_1000 $INPUT_PATH/user.othrif.370174.MGPy8EG_A14N_GG_ttn1_1900_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_1200 $INPUT_PATH/user.othrif.370175.MGPy8EG_A14N_GG_ttn1_1900_5000_1200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_1400 $INPUT_PATH/user.othrif.370176.MGPy8EG_A14N_GG_ttn1_1900_5000_1400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_1900_5000_1545 $INPUT_PATH/user.othrif.370177.MGPy8EG_A14N_GG_ttn1_1900_5000_1545*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_1 $INPUT_PATH/user.othrif.370178.MGPy8EG_A14N_GG_ttn1_2000_5000_1*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_200 $INPUT_PATH/user.othrif.370179.MGPy8EG_A14N_GG_ttn1_2000_5000_200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_400 $INPUT_PATH/user.othrif.370180.MGPy8EG_A14N_GG_ttn1_2000_5000_400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_600 $INPUT_PATH/user.othrif.370181.MGPy8EG_A14N_GG_ttn1_2000_5000_600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_800 $INPUT_PATH/user.othrif.370182.MGPy8EG_A14N_GG_ttn1_2000_5000_800*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_1000 $INPUT_PATH/user.othrif.370183.MGPy8EG_A14N_GG_ttn1_2000_5000_1000*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_1200 $INPUT_PATH/user.othrif.370184.MGPy8EG_A14N_GG_ttn1_2000_5000_1200*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_1400 $INPUT_PATH/user.othrif.370185.MGPy8EG_A14N_GG_ttn1_2000_5000_1400*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_1600 $INPUT_PATH/user.othrif.370186.MGPy8EG_A14N_GG_ttn1_2000_5000_1600*.root >> nohup_ttn1.log &
nohup optimize $OUTPUT_FOLDER ttn1_2000_5000_1645 $INPUT_PATH/user.othrif.370187.MGPy8EG_A14N_GG_ttn1_2000_5000_1645*.root >> nohup_ttn1.log 
#EOF