# DavisRunIITauTau
repo for Run II TauTau analysis code 

# CMSSW settings (checked only at LPC for now)

setenv GIT_ASKPASS
voms-proxy-init -voms cms --valid=72:00
source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc481

# login stuff 

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc481 


# getting started

git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau
cd DavisRunIITauTau/
cmsrel CMSSW_7_2_0
cd CMSSW_7_2_0/src
cmsenv 
git cms-init
#source /cvmfs/cms.cern.ch/crab3/crab.csh ruins many things with python setup
ln -s ../../UserCode UserCode
scram b -j 20
#setenv PYTHONHOME /cvmfs/cms.cern.ch/slc6_amd64_gcc481/external/python/2.7.6

# alternate approach

cmsrel CMSSW_7_2_0
cd CMSSW_7_2_0/src
cmsenv 
git cms-init

# electron ID
git cms-merge-topic HuguesBrun:trigElecIdInCommonIsoSelection720

git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau
