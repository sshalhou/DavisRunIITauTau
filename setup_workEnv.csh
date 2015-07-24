voms-proxy-init -voms cms --valid=72:00

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc491

cmsenv
source /cvmfs/cms.cern.ch/crab3/crab.csh
cmsenv
