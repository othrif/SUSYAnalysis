#for i in `cat allMC_mc.txt`; do
#for i in `cat list_part2.txt allSig.txt`; do
#for i in `cat allMC_mc.txt`; 
#for i in `cat test_mc.txt`; 
for i in `cat $1`; 
do
	echo $i; 

	tags=`echo $i | cut -d"." -f6 `
	echo $tags

	isAF=`echo ${tags} | grep _a | wc -l`
	isFirstWeek=`echo ${tags} | grep r6633 | wc -l`
	isMc15b=`echo ${tags} | grep 'a810\|r7326\|r7267\|r7360' | wc -l`
	isMc15c=`echo ${tags} | grep 'a818\|a821\|r7772\|r7725\|r8112\|r8129' | wc -l`


	echo "isAF: " ${isAF}
	echo "isFirstWeek: " ${isFirstWeek}

	tags=`echo $i | cut -d"." -f6 | cut -d"_" -f2,4,6 `
	dsID=`echo $i | cut -d"." -f2`
	dsName=`echo $i | cut -d"." -f3,5`
	der=`echo $i | cut -d"." -f5`
	echo ${dsName}
	dsName=`echo ${dsName:0:53} | cut -d"." -f1`
	dsName=`echo ${dsName}.${der}`
	echo ${dsName}

#	dsID=`echo $i | cut -d"." -f4`
# 	dsName=`echo $i | cut -d"." -f5`

    out=`echo user.othrif.test.${dsID}.${dsName}.${tags}`
#    out=`echo user.othrif.TESTv52.${dsID}.${dsName}.${tags}`

	echo ${out}

	echo python SS3LAnalysis/scripts/Run.py --isData 0 --isAtlfast ${isAF} --ismc15c ${isMc15c} --driver grid --inputDS $i --outputDS ${out} --submitDir=$2; 
	python SS3LAnalysis/scripts/Run.py --isData 0 --isAtlfast ${isAF} --ismc15c ${isMc15c} --driver grid --inputDS $i --outputDS ${out} --submitDir=$2; 

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

