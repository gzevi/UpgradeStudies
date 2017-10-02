#! /bin/bash

LOGDIR=logs
mkdir -p ${LOGDIR}


#OUTPATH=/home/gzevi/UpgradeSkims/advanced3Jul17weights
#OUTPATH=/home/gzevi/UpgradeSkims/advanced12Jul17newDelphes
#OUTPATH=/home/gzevi/UpgradeSkims/advanced17Jul17oldDelphesAddMass
OUTPATH=/home/gzevi/UpgradeSkims/advanced15Aug17newC2N4
#OUTPATH=/home/gzevi/UpgradeSkims/synchWithBasil8Jul17
#OUTPATH=.
mkdir -p ${OUTPATH}

# Basil's skims
#INPATH=root://eoscms.cern.ch//eos/cms/store/user/bschneid/SUSY_Upgrade_Skimmer/output12_BB
#declare -a Samples=(BB0_ntuple)

## Central samples
INEOS=root://eoscms.cern.ch/
INPATH=/eos/cms/store/group/upgrade/delphes_output/DelphesFromLHE_333pre16_2016Aug/


### New Central samples
#INEOS=root://cmseos.fnal.gov/
#INPATH=/store/user/snowmass/noreplica/DelphesFromLHE_342pre03_2017July/ 
#xrdfs root://cmseos.fnal.gov/ ls /store/user/snowmass/noreplica/DelphesFromLHE_342pre03_2017July/

#declare -a Samples=(BB-4p-0-300-v1510_14TEV_200PU BB-4p-1300-2100-v1510_14TEV_200PU BB-4p-2100-100000-v1510_14TEV_200PU BB-4p-300-700-v1510_14TEV_200PU BB-4p-700-1300-v1510_14TEV_200PU LLB-4p-0-400-v1510_14TEV_200PU LLB-4p-400-900-v1510_14TEV_200PU LLB-4p-900-100000-v1510_14TEV_200PU)
#declare -a Samples=(BB-4p-0-300-v1510_14TEV_200PU BB-4p-1300-2100-v1510_14TEV_200PU BB-4p-2100-100000-v1510_14TEV_200PU BB-4p-300-700-v1510_14TEV_200PU BB-4p-700-1300-v1510_14TEV_200PU BBB-4p-0-600-v1510_14TEV_200PU BBB-4p-600-1300-v1510_14TEV_200PU BBB-4p-1300-100000-v1510_14TEV_200PU ttB-4p-0-900-v1510_14TEV_200PU ttB-4p-1600-2500-v1510_14TEV_200PU ttB-4p-2500-100000-v1510_14TEV_200PU ttB-4p-900-1600-v1510_14TEV_200PU)
#declare -a Samples=(Bj-4p-0-300-v1510_14TEV_200PU Bj-4p-300-600-v1510_14TEV_200PU Bj-4p-600-1100-v1510_14TEV_200PU Bj-4p-1100-1800-v1510_14TEV_200PU Bj-4p-1800-2700-v1510_14TEV_200PU Bj-4p-2700-3700-v1510_14TEV_200PU Bj-4p-3700-100000-v1510_14TEV_200PU)





#
## Suchita's C2N4 (eos)
##INPATH=root://eoscms.cern.ch//eos/cms/store/cmst3/group/susy/upgrade/C2N4_delphised/
##declare -a Samples=(delphised_substructure_200PU) # not a very descriptive name unfortunately
#
#


# Submit without using wildcard: "Samples" contains folder names, but then
# we figure out filenames in each folder and submit one job per file
for SAMPLE in ${Samples[@]}
  do
    echo Loopling over ${INPATH}/${SAMPLE}
#    for FILE in `eos ls ${INPATH}/${SAMPLE}/`
    for FILE in `xrdfs ${INEOS} ls ${INPATH}/${SAMPLE}`
    do
#	echo $FILE
	echo root -b -l -q advancedskim.C\(\"$INPATH/${SAMPLE}\",\"$OUTPATH\",\"$FILE\"\)
    	nohup root -b -l -q advancedskim.C\(\"$INPATH/${SAMPLE}\",\"$OUTPATH\",\"$FILE\"\) >& ${LOGDIR}/log_${FILE}.txt &
#	echo root -b -l -q  skim.C\(\"$INPATH/${SAMPLE}\",\"$OUTPATH\",\"$FILE\"\)
#    	nohup root -b -l -q skim.C\(\"$INPATH/${SAMPLE}\",\"$OUTPATH\",\"$FILE\"\) >& ${LOGDIR}/log_${FILE}.txt &
    done
done

## Suchita's C2N4 (local)
INPATH=/home/gzevi/C2N4delphes_15Aug17/
declare -a Samples=(C2N4full) # not a very descriptive name unfortunately

## Submit with wildcards. IF eos is mounted, then this work and can submit one job per folder
for SAMPLE in ${Samples[@]}
do
    echo root -b -l -q advancedskim.C\(\"$INPATH/${SAMPLE}\",\"$OUTPATH\",\"$FILE\"\)
    root -b -l -q advancedskim.C\(\"$INPATH\",\"$OUTPATH\",\"$SAMPLE\"\) >& ${LOGDIR}/log_${SAMPLE}.txt &
done


## Delphes validation samples
#INPATH=/home/gzevi/VBF_HToZZTo4L_M125_14TeV_200PU/Delphes/
#OUTPATH=/home/gzevi/VBF_HToZZTo4L_M125_14TeV_200PU/DelphesSkims/
#mkdir -p ${OUTPATH}
#
#declare -a Samples=(VBF_HToZZTo4L_M125_14TeV)
#for SAMPLE in ${Samples[@]}
#do
#    echo root -b -l -q advancedskim.C\(\"$INPATH/${SAMPLE}\",\"$OUTPATH\",\"$FILE\"\)
#    root -b -l -q advancedskim.C\(\"$INPATH\",\"$OUTPATH\",\"$SAMPLE\"\) >& ${LOGDIR}/log_${SAMPLE}.txt &
#done
