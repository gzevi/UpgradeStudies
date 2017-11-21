#!/bin/bash

make -j 8 || return $?

#OUTDIR=output/weights_8Aug17/
#OUTDIR=output/weights_16Aug17_eta_2p4/
#OUTDIR=output/weights_2Jul17/
#OUTDIR=output/newDelphes_17Jul17/
#OUTDIR=output/advanced3Jul17weights_2Sep17/
#OUTDIR=output/advanced8Aug17_2Sep17/
#OUTDIR=output/advanced8Aug17_17Sep17/
#OUTDIR=output/advanced8Aug17_2Oct17/ # Added run2 lepton weights (muons are still a hack)
#OUTDIR=output/advanced8Aug17_2Oct17_eta1p6/ # eta restricted tests
#OUTDIR=output/advanced16Oct17_16Oct17/ # New GenSim HGC samples
#OUTDIR=output/advancedSignal30Oct17 # Signal Grid, bugged
OUTDIR=output/advancedSignal14Nov17 # Signal Grid
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
#declare -a Samples=()

# HGC samples
#INDIR=/home/gzevi/UpgradeSkims/advanced16Oct17_HGC
#declare -a Samples=(TTWJetsAll.root)



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
#INDIR=/home/gzevi//UpgradeSkims/advanced3Jul17weights/

#INDIR=/home/gzevi/UpgradeSkims/advanced15Aug17newC2N4/ # Good until October 30 2017
#INDIR=/home/gzevi/UpgradeSkims/advancedSignal30Oct17/ # Signal Grid
INDIR=/home/gzevi/UpgradeSkims/advancedSignal14Nov17/ # Signal Grid

#declare -a Samples=(C2N4full)  # Good until October 30 2017
#declare -a Samples=(Decayed_C2N4_Baer_400_LSP_150_200PU)  # Signal Grid, 78107 events pre-skim
declare -a Samples=(Decayed_C2N4_Baer_400_LSP_150_200PU Decayed_C2N4_Baer_550_LSP_250_200PU Decayed_C2N4_Baer_700_LSP_250_200PU Decayed_C2N4_Baer_850_LSP_250_200PU Decayed_C2N4_Baer_450_LSP_150_200PU Decayed_C2N4_Baer_600_LSP_150_200PU Decayed_C2N4_Baer_750_LSP_150_200PU Decayed_C2N4_Baer_900_LSP_150_200PU Decayed_C2N4_Baer_450_LSP_250_200PU Decayed_C2N4_Baer_600_LSP_250_200PU Decayed_C2N4_Baer_750_LSP_250_200PU Decayed_C2N4_Baer_900_LSP_250_200PU Decayed_C2N4_Baer_500_LSP_150_200PU Decayed_C2N4_Baer_650_LSP_150_200PU Decayed_C2N4_Baer_800_LSP_150_200PU Decayed_C2N4_Baer_950_LSP_150_200PU Decayed_C2N4_Baer_500_LSP_250_200PU Decayed_C2N4_Baer_650_LSP_250_200PU Decayed_C2N4_Baer_800_LSP_250_200PU Decayed_C2N4_Baer_950_LSP_250_200PU Decayed_C2N4_Baer_550_LSP_150_200PU Decayed_C2N4_Baer_700_LSP_150_200PU Decayed_C2N4_Baer_850_LSP_150_200PU)



for SAMPLE in ${Samples[@]}; do

#    XSEC=144.26 # from Anadi's email [fb]
#    NEVTS=21777

    XSEC=`grep ${SAMPLE} SignalCrossSections.txt | awk '{print $2*1}'` # [fb]
    NEVTS=`grep ${SAMPLE} SignalCrossSections.txt | awk '{print $3*1}'`
    echo $XSEC, $NEVTS

    echo nice -n 10 ./runLooper ${INDIR} ${SAMPLE} ${OUTDIR} ${XSEC} ${NEVTS}
    eval "nohup ./runLooper ${INDIR} ${SAMPLE} ${OUTDIR} ${XSEC} ${NEVTS} >& ${LOGDIR}/log_${SAMPLE}.txt &"
done