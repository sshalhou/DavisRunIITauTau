#!/bin/tcsh

# setup access

voms-proxy-init -voms cms --valid=72:00

# some defaults

source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc530

if ( -d CMSSW_8_0_20) then
        echo 'directory CMSSW_8_0_20 already exits, doing nothing further'
        exit 1
endif


# create the working area
	
cmsrel CMSSW_8_0_20
cd CMSSW_8_0_20/src/
cmsenv


# set up git

git cms-init

# electron ID ----> cut based ID/mva ID are already integrated into this release but cuts must be modified
# muon ID --> already integrated into this release but cuts must be modified
# PF jet ID --> no new code cuts must be modifed
# PU jet ID --> for this rel, no code is needed but must follow recalc instructions
# JEC --> method unchanged from 76X no code is needed
# b-jets -> no new code, should update sf code

# PF MET UNC 

git cms-addpkg CondTools/BTau
git cms-merge-topic cms-met:METRecipe_8020



# MVA MET : 

git cms-addpkg RecoMET/METPUSubtraction
git cms-addpkg DataFormats/METReco
git remote add -f mvamet https://github.com/rfriese/cmssw.git
git checkout mvamet/mvamet8020 -b mvamet
mkdir RecoMET/METPUSubtraction/data
cd RecoMET/METPUSubtraction/data
wget https://github.com/rfriese/cmssw/raw/MVAMET2_beta_0.6/RecoMET/METPUSubtraction/data/weightfile.root
cd $CMSSW_BASE/src

# PF MET  :

git cms-addpkg DataFormats/PatCandidates

# for PF MET, manual patch applied 
# Additionally, apply these two patches: 
# - https://github.com/vhbb/cmssw/pull/524/commits/1dd40d418ddc3f769daff7aff5a37a81edd1c9a9 
# - https://github.com/vhbb/cmssw/pull/524/commits/3c18062dc38f56c01c6ee68da5cf79951208bd16
# instead I have modified the files directly (these are fine in 820X)

cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/METReco/MET.h_mod DataFormats/METReco/interface/MET.h
cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/METReco/MET.cc_mod DataFormats/METReco/src/MET.cc
cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/PatCandidates/MET.cc_mod DataFormats/PatCandidates/src/MET.cc


# SVFIt 

git clone git@github.com:veelken/SVfit_standalone.git TauAnalysis/SVfitStandalone
cd TauAnalysis/SVfitStandalone/
git checkout HIG-16-006
cd $CMSSW_BASE/src

# MET RECOIL CORRECTIONS (SAME CODE FOR PF AND MVA MET)
git clone https://github.com/CMS-HTT/RecoilCorrections.git  HTT-utilities/RecoilCorrections 


# pilup reweight code -- this is done to turn of cout statements
git cms-addpkg PhysicsTools/Utilities
sed -i 's/std::cout/\/\/std::cout/g' PhysicsTools/Utilities/src/LumiReWeighting.cc


# for muon effective area 

git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
cd Muon/MuonAnalysisTools 
git checkout master -- interface/MuonEffectiveArea.h 
cd -

# add CL software ---> this does not work in 8X, and seemingly there is no branch in which it will work
# git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
# cd HiggsAnalysis/CombinedLimit
# git checkout 74x-root6 # is there a newer branch?
# cd -


# relocate the davis code
mv ../../DavisRunIITauTau .

# copy the PU reweight files 
cp /afs/cern.ch/work/a/adewit/public/pileup-hists-2016/MC_Spring16_PU25ns_V1.root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/.
cp /afs/cern.ch/user/a/anehrkor/public/Data_Pileup_2016_July22.root DavisRunIITauTau/RunTimeDataInput/data/PileUpReWeightFiles/.



# get the right JER SF file for this release
# if new file, need to code the change in runIIoneStep_v0.py and runIIntuple_v0.py


mkdir DavisRunIITauTau/RunTimeDataInput/data/JER_FILES
wget https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV6_MC/Spring16_25nsV6_MC_SF_AK4PFchs.txt .
wget https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV6_MC/Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt .
mv Spring16_25nsV6_MC_SF_AK4PFchs.txt DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/.
mv Spring16_25nsV6_MC_PtResolution_AK4PFchs.txt DavisRunIITauTau/RunTimeDataInput/data/JER_FILES/.


# Add in the new MET filter code needed for 8020X and beyond in 2016 
# see: https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#Notes_regarding_the_ICHEP_datase
git cms-merge-topic -u cms-met:fromCMSSW_8_0_20_postICHEPfilter


# get the BTAG SF CSV File  and EFF root files 
# if the file is new, need to change the name used in FlatTupleConfig_cfi.py

mkdir DavisRunIITauTau/RunTimeDataInput/data/BTAGSF
cp /afs/cern.ch/user/s/sshalhou/public/CMSSW_8X_MODS/CSVv2_ichep.csv .
mv CSVv2_ichep.csv DavisRunIITauTau/RunTimeDataInput/data/BTAGSF/.

# so far in 80X only a single WP eff. is available for sf > 1 case 
# if the file is new, need to change the name used in FlatTupleConfig_cfi.py

mkdir DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF
cp /afs/cern.ch/work/a/adewit/public/MSSM2016/tagging_efficiencies_ichep2016.root DavisRunIITauTau/RunTimeDataInput/data/BTAGEFF/.


# Lepton Eff for Muon & Electron for Spring 16
# check that the correct  files used (they are hard-coded in generateH2TauSyncTree.cc)
cd DavisRunIITauTau/AnalysisRunII/Analysis/
git clone https://github.com/CMS-HTT/LeptonEff-interface.git HTT-utilities
cd HTT-utilities/LepEffInterface
git clone https://github.com/CMS-HTT/LeptonEfficiencies.git data
cd ${CMSSW_BASE}/src

# compile

scram b -j 20
