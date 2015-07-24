#!/bin/tcsh

# setup access

voms-proxy-init -voms cms --valid=72:00

# some defaults

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc491

if ( -d CMSSW_7_4_7) then
        echo 'directory CMSSW_7_4_7 already exits, doing nothing further'
        exit 1
endif


# create the working area
	
cmsrel CMSSW_7_4_7
cd CMSSW_7_4_7/src/
cmsenv

# mva met installation

git cms-addpkg RecoMET/METPUSubtraction/
cd RecoMET/METPUSubtraction/
git clone https://github.com/rfriese/RecoMET-METPUSubtraction data -b 74X-13TeV-Summer15-July2015
cd -
echo "please ignore stuff about detached head..."
echo "copying files, this can take a while ..."
cp /afs/cern.ch/user/s/sshalhou/public/INSTALL_PUBLIC_FILES/74X/mvaPFMET_db_cfi.py RecoMET/METPUSubtraction/python/.
sed -i 's/puJetIdForPFMVAMEt = pileupJetIdEvaluator.clone/from RecoMET.METPUSubtraction.mvaPFMET_db_cfi import mvaPFMEtGBRForestsFromDB\npuJetIdForPFMVAMEt = pileupJetIdEvaluator.clone/g' RecoMET/METPUSubtraction/python/mvaPFMET_cff.py
cp /afs/cern.ch/user/s/sshalhou/public/INSTALL_PUBLIC_FILES/74X/mvaPFMEt_747_25ns_Mar2015.db RecoMET/METPUSubtraction/data/.

# for muon effective area

git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
cd Muon/MuonAnalysisTools 
git checkout master -- interface/MuonEffectiveArea.h 
cd -

# for sv mass
git clone git@github.com:veelken/SVfit_standalone.git TauAnalysis/SVfitStandalone
cd TauAnalysis/SVfitStandalone/
git checkout svFit_2015Apr03
cd -

# pilup reweight code
git cms-addpkg PhysicsTools/Utilities
sed -i 's/std::cout/\/\/std::cout/g' PhysicsTools/Utilities/src/LumiReWeighting.cc

# move the Davis code into the reight area

mv ../../DavisRunIITauTau .

# compile

scram b -j 20
