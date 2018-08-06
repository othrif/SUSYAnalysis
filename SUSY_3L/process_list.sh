#!/bin/bash
for ARG in `cat $1`
do
    TAG=${ARG%/}
    MYTAG=${TAG/_AUET2BCTEQ6L1_/_}
    MYTAG=${TAG/.merge.NTUP_TRUTH./.TRUTH_MINI.}
    MYTAG=${TAG/.e1866_p1605/}
    ./plotter ${MYTAG} /data3/orifki/above_diag_mini/${ARG}/*.root*
done
