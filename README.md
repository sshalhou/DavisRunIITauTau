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
git clone -n https://github.com/cms-analysis/EgammaAnalysis-ElectronTools EGamma/EGammaAnalysisTools 
cd EGamma/EGammaAnalysisTools
git checkout c0db796 -- interface/ElectronEffectiveArea.h


git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau
