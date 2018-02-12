FOLDER=$1
export INPUT_PATH=/UserDisk2/othrif/data/MiniNtuple/v36
export OUTPUT_PATH=/afs/cern.ch/work/o/othrif/workarea/results/v36/$FOLDER
mkdir -p $OUTPUT_PATH
analyze-v36 $FOLDER ttee_Np1 $INPUT_PATH/user.othrif.410112.MadGraphPythia8EvtGen_A14NNPDF23LO_ttee_Np1.s2726_r6282_output.root
analyze-v36 $FOLDER ttmumu_Np0 $INPUT_PATH/user.othrif.410113.MadGraphPythia8EvtGen_A14NNPDF23LO_ttmumu_Np0.s2726_r6282_output.root
analyze-v36 $FOLDER ttbar $INPUT_PATH/user.othrif.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.s2608_r7326_p2452_output.root
analyze-v36 $FOLDER GG_ttn1_1600_5000_1 $INPUT_PATH/user.othrif.370144.MGPy8EG_A14N_GG_ttn1_1600_5000_1.s2608_r6282_output.root
analyze-v36 $FOLDER GG_ttn1_1200_5000_400 $INPUT_PATH/user.othrif.370117.MGPy8EG_A14N_GG_ttn1_1200_5000_400.s2608_r6282_output.root
analyze-v36 $FOLDER GG_ttn1_1200_5000_855 $INPUT_PATH/user.othrif.370122.MGPy8EG_A14N_GG_ttn1_1200_5000_855.s2608_r6282_output.root
analyze-v36 $FOLDER GG_2stepWZ_1600_850_475_10 $INPUT_PATH/user.othrif.371264.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_1600_850_475_10.a766_r6282_output.root
analyze-v36 $FOLDER GG_2stepWZ_1600_1100_850_6 $INPUT_PATH/user.othrif.371269.MadGraphPythia8EvtGen_A14N_GG_2stepWZ_1600_1100_850_6.a766_r6282_output.root
analyze-v36 $FOLDER BB_onestepC1_550_200_100_SS2L $INPUT_PATH/user.othrif.372313.MGPy8EG_A14N_BB_onestepC1_550_200_100_SS2L.a766_r6282_output.root
analyze-v36 $FOLDER BB_onestepC1_550_375_275_SS2L $INPUT_PATH/user.othrif.372317.MGPy8EG_A14N_BB_onestepC1_550_375_275_SS2L.a766_r6282_output.root
analyze-v36 $FOLDER GG_N2_SLN1_1600_100_2L $INPUT_PATH/user.othrif.372472.MGPy8EG_A14N23LO_SM_GG_N2_SLN1_1600_100_2L.a766_r6282_output.root
analyze-v36 $FOLDER GG_N2_SLN1_1600_1100_2L $INPUT_PATH/user.othrif.372477.MGPy8EG_A14N23LO_SM_GG_N2_SLN1_1600_1100_2L.a766_r6282_output.root
