nohup ./Analyzer/scripts/optBackground.sh $1_Background > background.log &
#source  Analyzer/scripts/optSignal_GG_2step_WZ.sh $1
#source  Analyzer/scripts/optSignal_GG_N2_SLN1.sh $1
nohup ./Analyzer/scripts/optSignal_GG_ttn1.sh $1_GG_ttn1 > GG_ttn1.log &
#source  Analyzer/scripts/optSignal_BB_onestepC1.sh $1
#source  Analyzer/scripts/optSignalAll.sh $1
