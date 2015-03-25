# DavisRunIITauTau
repo for Run II TauTau analysis code 

# CMSSW settings (checked only at LPC for now)

setenv GIT_ASKPASS
voms-proxy-init -voms cms --valid=72:00
source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc481 


# getting started

cmsrel CMSSW_7_2_0
cd CMSSW_7_2_0/src
cmsenv 
git cms-init

# electron MVA ID
git cms-merge-topic HuguesBrun:trigElecIdInCommonIsoSelection720

# mva MET
#https://twiki.cern.ch/twiki/bin/view/CMS/MVAMet#CMSSW_7_2_X_requires_slc6_MiniAO
git cms-addpkg PhysicsTools/PatAlgos
git cms-addpkg FWCore/Version
git-cms-merge-topic -u cms-met:72X-13TeV-Training-30Jan15

# davis code

git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau
