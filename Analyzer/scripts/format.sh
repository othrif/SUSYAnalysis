#!/bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
    var=`echo $line | awk -F" " '{print $2}'`
    echo -n "'$var', "
#    echo $var
<<EOF
    echo $line
    echo    " if($var){"
	echo          "is_SR = true;"
        echo "sprintf(hist_name, \"$var%s\", my_tag);"
	echo "         FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);"
	echo "       }"
EOF
<<EOF
echo    "sprintf(hname, \"${var}_%s\", tag);"
echo    "BookHistos(ftag, hname);"
EOF

done < "$1"for i in $(cat var)
do 
	echo "bool $i =  "
    echo "if($i){"
    echo "  is_SR = true;"
    echo "  sprintf(hist_name, \"$i%s\", my_tag);"
    echo "  FillHistos_Channels(ftag, hist_name, evt, lep, jet, bjet);"
    echo "}"
	echo ""

done


for i in $(cat var)
do 
	echo "sprintf(hname, \"${i}_%s\", tag);"
	echo "BookHistos(ftag, hname);"
	echo ""
done


for i in {1..19}; 
do 
	echo "distrRegion* paired_SR$i[N_unc_paired];"
	echo "distrRegion* unpaired_SR$i[N_unc_unpaired];"
	echo ""
done


for i in {1..19}; 
do 
	echo "paired_SR${i}[j] = (&(temp_set->SR${i}));"
done

for i in {1..19}; 
do 
	echo "unpaired_SR${i}[j] = (&(temp_set->SR${i}));"
done


for i in {1..19}; 
do 
	echo "draw_Region(set.SR$i, sig.SR$i, paired_SR$i, unpaired_SR$i, fit);"
done


SR3L0b1
SR3L0b2
SR3L1b1
SR3L1b2
SR0b1
SR0b2
SR1b1
SR1b2
SR3b1
SR3b2
SRlow
SRhigh
SR1b_3LSS
SR1b_DD_low
SR1b_DD_high
SR3b_DD
SR1b_GG
SRRPV0b
SRRPV3b
