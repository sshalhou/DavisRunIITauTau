 DavisRunIITauTau : Code For H->tau tau Run II analysis
------------------



For Quick Start (on SL6 only):
------------------

- CMSSW/Certificate prelims :

setenv GIT_ASKPASS

voms-proxy-init -voms cms --valid=72:00

source /cvmfs/cms.cern.ch/cmsset_default.csh


- create a working area and then 

setenv SCRAM_ARCH slc6_amd64_gcc481 

cmsrel CMSSW_7_2_3_patch1

cmsenv

(git cms-init) # might be needed

- for MVA MET (13 TeV Training) : 

https://twiki.cern.ch/twiki/bin/view/CMS/MVAMet#CMSSW_7_2_X_requires_slc6_MiniAO


git cms-addpkg PhysicsTools/PatAlgos

git cms-addpkg FWCore/Version

git-cms-merge-topic -u cms-met:72X-13TeV-Training-30Jan15


- For Electron MVA ID (Phys14 version)

git cms-merge-topic HuguesBrun:trigElecIdInCommonIsoSelection720


- Clone the Davis Code :

git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau

- Compile : 

scram b -j 20



