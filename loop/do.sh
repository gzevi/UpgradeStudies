#!/bin/bash

make -j 8 || return $?

#OUTDIR=output/weights_8Aug17/
#OUTDIR=output/weights_16Aug17_eta_2p4/
#OUTDIR=output/weights_2Jul17/
#OUTDIR=output/newDelphes_17Jul17/
#OUTDIR=output/advanced3Jul17weights_2Sep17/
#OUTDIR=output/advanced8Aug17_2Sep17/
OUTDIR=output/advanced8Aug17_17Sep17/
LOGDIR=logs/
mkdir -p ${OUTDIR}
mkdir -p ${LOGDIR}

#most recent MC
#INDIR=/home/gzevi/UpgradeSkims11Apr17/
#INDIR=/home/gzevi//UpgradeSkims/advanced5May17/
#INDIR=/home/gzevi//UpgradeSkims/advanced3Jul17weights/  # full samples
#INDIR=/home/gzevi//UpgradeSkims/advanced19July17newerDelphes
INDIR=/home/gzevi//UpgradeSkims/advanced8Aug17/
#INDIR=~gzevi/public/UpgradeSkims/
#declare -a Samples=(LLB-4p-0-400)
#declare -a Samples=(BB-4p-0-300 BB-4p-300-700 BB-4p-700-1300 BB-4p-1300-2100 BB-4p-2100-100000)
#declare -a Samples=(ttB-4p-0-900) #  ttB-4p-900-1600 ttB-4p-1600-2500 ttB-4p-2500-100000)
#declare -a Samples=(BB-4p-0-300 BB-4p-300-700 BB-4p-700-1300 BB-4p-1300-2100 BB-4p-2100-100000 BBB-4p-0-600 BBB-4p-600-1300 BBB-4p-1300-100000 ttB-4p-0-900 ttB-4p-900-1600 ttB-4p-1600-2500 ttB-4p-2500-100000 )
#declare -a Samples=(Bj-4p-0-300 Bj-4p-300-600 Bj-4p-600-1100 Bj-4p-1100-1800 Bj-4p-1800-2700 Bj-4p-2700-3700 Bj-4p-3700-100000)
#declare -a Samples=(BB-4p-0-300 BB-4p-300-700 BB-4p-700-1300 BB-4p-1300-2100 BB-4p-2100-100000 BBB-4p-0-600 BBB-4p-600-1300 BBB-4p-1300-100000 ttB-4p-0-900 ttB-4p-900-1600 ttB-4p-1600-2500 ttB-4p-2500-100000 Bj-4p-0-300 Bj-4p-300-600 Bj-4p-600-1100 Bj-4p-1100-1800 Bj-4p-1800-2700 Bj-4p-2700-3700 Bj-4p-3700-100000)
declare -a Samples=(BB-4p-0-300 BB-4p-300-700 BB-4p-700-1300 BB-4p-1300-2100 BB-4p-2100-100000 BBB-4p-0-600 BBB-4p-600-1300 BBB-4p-1300-100000 ttB-4p-0-900 ttB-4p-900-1600 ttB-4p-1600-2500 ttB-4p-2500-100000 Bj-4p-0-300 Bj-4p-300-600 Bj-4p-600-1100 Bj-4p-1100-1800 Bj-4p-1800-2700 Bj-4p-2700-3700 Bj-4p-3700-100000 LL-4p-0-100 LL-4p-100-200 LL-4p-200-500 LL-4p-500-900 LL-4p-900-1400 LL-4p-1400-100000 LLB-4p-0-400 LLB-4p-400-900 LLB-4p-900-100000 ) 
#declare -a Samples=(BB-4p-0-300 BB-4p-300-700 BB-4p-700-1300 BB-4p-1300-2100 BB-4p-2100-100000 )

for SAMPLE in ${Samples[@]}; do

    # Get the xsec (in fb) and nevts   <-- Doesn't work for signal yet. Hack below
    # weight = (xsect*lumi)/nevents
    XSEC=`grep ${SAMPLE} configSkimmer.txt | awk '{print $6*1}'` # [fb]
    NEVTS=`grep ${SAMPLE} configSkimmer.txt | awk '{print $7*1}'`
    echo $XSEC, $NEVTS

    echo nice -n 10 ./runLooper ${INDIR} ${SAMPLE} ${OUTDIR} ${XSEC} ${NEVTS}
    eval "nohup ./runLooper ${INDIR} ${SAMPLE} ${OUTDIR} ${XSEC} ${NEVTS} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done

##INDIR=/home/gzevi/UpgradeSkims/advanced5May17nocut/
#INDIR=/home/gzevi/UpgradeSkims/advanced2Jul17weights/
INDIR=/home/gzevi/UpgradeSkims/advanced15Aug17newC2N4/
#INDIR=/home/gzevi//UpgradeSkims/advanced3Jul17weights/
declare -a Samples=(C2N4full)

for SAMPLE in ${Samples[@]}; do

#    XSEC=250.72 # from Suchita's email [fb]
    XSEC=144.26 # from Anadi's email [fb]
#    NEVTS=41000
    NEVTS=21777
    echo $XSEC, $NEVTS

    echo nice -n 10 ./runLooper ${INDIR} ${SAMPLE} ${OUTDIR} ${XSEC} ${NEVTS}
    eval "nohup ./runLooper ${INDIR} ${SAMPLE} ${OUTDIR} ${XSEC} ${NEVTS} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done