# use: hadd.sh output/test/

cd $1
hadd -f Bjall.root Bj-4p-*.root
hadd -f BBall.root BB-4p-*.root
hadd -f BBBall.root BBB-4p-*.root
hadd -f ttBall.root ttB-4p-*.root
hadd -f LLBall.root LLB-4p-*.root
hadd -f LLall.root LL-4p-*.root
cd -
