#!/bin/tcsh

# setup access

voms-proxy-init -voms cms --valid=72:00

# some defaults

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc493

if ( -d CMSSW_7_6_3_patch2) then
        echo 'directory CMSSW_7_6_3_patch2 already exits, doing nothing further'
        exit 1
endif


# create the working area
	
cmsrel CMSSW_7_6_3_patch2
cd CMSSW_7_6_3_patch2/src/
cmsenv


# set up git

git cms-init



# electron ID ----> cut based ID/mva ID are already integrated into this release

# muon ID --> already integrated into this release

# for muon effective area

git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
cd Muon/MuonAnalysisTools 
git checkout master -- interface/MuonEffectiveArea.h 
cd -

# jets and jet energy corrections -- must be applied at ntuple level


# for sv mass
git clone git@github.com:veelken/SVfit_standalone.git TauAnalysis/SVfitStandalone
cd TauAnalysis/SVfitStandalone
echo "***** Ignore Detatched Head Warnings ...."
git checkout dd7cf43e3f930040959f7d700cef976307d7cec3
cd -

# pilup reweight code -- this is done to turn of cout statements
git cms-addpkg PhysicsTools/Utilities
sed -i 's/std::cout/\/\/std::cout/g' PhysicsTools/Utilities/src/LumiReWeighting.cc




# # MVA MET : for 7_6_X 

git cms-addpkg RecoMET/METPUSubtraction
git cms-addpkg DataFormats/METReco
git remote add -f mvamet https://github.com/rfriese/cmssw.git
git checkout MVAMET2_beta_0.6 -b mvamet
rm -rf RecoMET/METPUSubtraction/data/.git 


# add CL software

git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
cd HiggsAnalysis/CombinedLimit
git checkout 74x-root6 # is there a newer branch?
cd -

# get the recoil CORRECTIONS for MVA MET
git clone https://github.com/CMS-HTT/RecoilCorrections.git  HTT-utilities/RecoilCorrections 


# relocate the davis code
mv ../../DavisRunIITauTau .

# copy the PU reweight files 

cp /afs/cern.ch/work/a/adewit/public/pileup-hists/*root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/.

# get the right JER SF file for this release
# if new file, need to hardcode the change in NtuplePairIndependentInfoProducer.cc

mkdir DavisRunIITauTau/RunTimeDataInput/data/JER_FILES
wget https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall15_25nsV2_MC/Fall15_25nsV2_MC_SF_AK4PFchs.txt .
wget https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Fall15_25nsV2_MC/Fall15_25nsV2_MC_PtResolution_AK4PFchs.txt .
mv Fall15_25nsV2_MC_SF_AK4PFchs.txt DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/.

# compile

scram b -j 20
