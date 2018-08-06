#!/bin/bash
for ARG in `cat $1`
do
    sample=`echo ${ARG} | awk -F"." '{print $3}' | awk -F"_" '{print $4"_"$5"_"$6}'`

    NUMBER=`ami show dataset info "${ARG}" | grep datasetNumber`
    NUMBER=${NUMBER/datasetNumber/}
    NUMBER=${NUMBER//[[:space:]]/}
    NUMBER=${NUMBER/:/}
    XSec=`ami show dataset info "${ARG}" | grep approx_crossSection`
    XSec=${XSec/approx_crossSection/}
    XSec=${XSec//[[:space:]]/}
    XSec=${XSec/:/}
    echo -e " ${sample} & ${NUMBER}  & 80000  & ${XSec}"
    echo -e '\\noalign{\smallskip}\hline\\noalign{\smallskip}'

#	echo -e "if (filename->Index(\"${NUMBER}\")>0) Xsection = ${XSec};"
done
