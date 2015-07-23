------------------
DavisRunIITauTau : Code For H->tau tau Run II analysis
------------------

For Quick Start (on SL6 only, CMSSW_7_4_7 and higher):

- CMSSW/Certificate prelims :

		setenv GIT_ASKPASS

		voms-proxy-init -voms cms --valid=72:00

		source /cvmfs/cms.cern.ch/cmsset_default.csh


- create a working area and then :

		setenv SCRAM_ARCH slc6_amd64_gcc491

		cmsrel CMSSW_7_4_7

		cd CMSSW_7_4_7/src/

		cmsenv

- MVA MET :

		git cms-addpkg RecoMET/METPUSubtraction/
		
		cd RecoMET/METPUSubtraction/

		git clone https://github.com/rfriese/RecoMET-METPUSubtraction data -b 74X-13TeV-Summer15-July2015

		(note ignore the message about detached head coming from last command, we don't contribute to this code only our Davis stuff)

		cd -

		# note need to update db file here , and root files in main python 
		cp /afs/cern.ch/user/s/sshalhou/public/INSTALL_PUBLIC_FILES/74X/mvaPFMET_db_cfi.py RecoMET/METPUSubtraction/python/.


		sed -i 's/puJetIdForPFMVAMEt = pileupJetIdEvaluator.clone/from RecoMET.METPUSubtraction.mvaPFMET_db_cfi import mvaPFMEtGBRForestsFromDB\npuJetIdForPFMVAMEt = pileupJetIdEvaluator.clone/g' RecoMET/METPUSubtraction/python/mvaPFMET_cff.py

		# needs updating
		cp /afs/cern.ch/user/s/sshalhou/public/INSTALL_PUBLIC_FILES/74X/mvaPFMEt_747_25ns_Mar2015.db RecoMET/METPUSubtraction/data/.


- For Muon Effective Area (following LLR's guide on this)

		git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
		
		cd Muon/MuonAnalysisTools 
		
		git checkout master -- interface/MuonEffectiveArea.h 

		cd -

- SV mass code :

		git clone git@github.com:veelken/SVfit_standalone.git TauAnalysis/SVfitStandalone
		
		cd TauAnalysis/SVfitStandalone/
		
		git checkout svFit_2015Apr03
		
		cd -

- PileUp Reweight Code (Only adding locally in order to turn off default prints) :

		git cms-addpkg PhysicsTools/Utilities
		
		sed -i 's/std::cout/\/\/std::cout/g' PhysicsTools/Utilities/src/LumiReWeighting.cc

- Clone the Davis Code :

		git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau
		
		cd DavisRunIITauTau
		
		git checkout 7_4_X
		
		cd -

- Compile :
	
		scram b -j 20

