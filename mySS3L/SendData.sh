#for i in `cat data_retry.list `; do
#for i in `cat data16.txt data15.txt | grep data16_13TeV.periodC`; do
for i in `cat $1`; 
do
	echo $i; 

	tags=`echo $i | cut -d"." -f6 `

	isAF=`echo ${tags} | grep _a | wc -l`
	isFirstWeek=`echo ${tags} | grep r6633 | wc -l`

	echo "isAF: " ${isAF}
	echo "isFirstWeek: " ${isFirstWeek}

	tags=`echo $i | cut -d"." -f6 | cut -d"_" -f1,2,3`
	dsID=`echo $i | cut -d"." -f2`
	dsName=`echo $i | cut -d"." -f3,5`

	out=`echo user.othrif.t0858_v54.${dsID}.${dsName}.${tags}`

	echo ${out}

	echo python SS3LAnalysis/scripts/Run.py --isData 1 --ismc15c 0 --driver grid --inputDS $i --outputDS ${out}  --submitDir=$2; 
	python SS3LAnalysis/scripts/Run.py --isData 1 --ismc15c 0 --driver grid --inputDS $i --outputDS ${out}  --submitDir=$2; 

#if [ ${is50ns} -ge 1 ]; then
# echo "that's 50ns"
# if [ ${isAF} -ge 1 ]; then
# python SS3LAnalysis/scripts/Run.py --isData 0 --is50ns 1 --isAtlfast 1 --driver grid --inputDS $i; 
# else
# python SS3LAnalysis/scripts/Run.py --isData 0 --is50ns 1 --isAtlfast 0 --driver grid --inputDS $i; 
#else
# echo "it is 25ns"
# if [ ${isAF} -ge 1 ]; then
# python SS3LAnalysis/scripts/Run.py --isData 0 --is50ns 0 --isAtlfast 1 --driver grid --inputDS $i; 
# else
# python SS3LAnalysis/scripts/Run.py --isData 0 --is50ns 0 --isAtlfast 0 --driver grid --inputDS $i; 
#fi

done

