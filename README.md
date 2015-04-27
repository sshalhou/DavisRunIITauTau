------------------
DavisRunIITauTau : Code For H->tau tau Run II analysis
------------------

For Quick Start (on SL6 only):

- CMSSW/Certificate prelims :

		setenv GIT_ASKPASS

		voms-proxy-init -voms cms --valid=72:00

		source /cvmfs/cms.cern.ch/cmsset_default.csh


- create a working area and then :

		setenv SCRAM_ARCH slc6_amd64_gcc481 

		cmsrel CMSSW_7_2_3_patch1

		cd CMSSW_7_2_3_patch1/src/

		cmsenv

		(git cms-init) # might be needed

- For Electron MVA ID (Phys14 version)

		git cms-merge-topic HuguesBrun:trigElecIdInCommonIsoSelection720


- For Muon Effective Area (following LLR's guide on this)

		git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
		
		cd Muon/MuonAnalysisTools 
		
		git checkout master -- interface/MuonEffectiveArea.h 

		cd -

- for MVA MET (13 TeV Training) & MET SIG: 

		(see : https://twiki.cern.ch/twiki/bin/view/CMS/MVAMet#CMSSW_7_2_X_requires_slc6_MiniAO)



		git cms-addpkg PhysicsTools/PatAlgos

		git cms-addpkg FWCore/Version

		git-cms-merge-topic -u cms-met:72X-MetSig-150311


		git-cms-merge-topic -u cms-met:72X-13TeV-Training-30Jan15

		cd RecoMET/METPUSubtraction/

		git clone https://github.com/rfriese/RecoMET-METPUSubtraction data

		cd -

- Clone the Davis Code :

		git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau

- Compile : 

		scram b -j 20

- Test Run (remember to change the miniAOD input file):
		
		cmsRun DavisRunIITauTau/runIIntuple_v0.py


