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

- To Start 

		git cms-addpkg PhysicsTools/PatAlgos

		git cms-addpkg FWCore/Version



- for MVA MET (13 TeV Training) & MET SIG: (the cp and sed commands are all one long line)

		(see : https://twiki.cern.ch/twiki/bin/view/CMS/MVAMet#CMSSW_7_2_X_requires_slc6_MiniAO)

		git-cms-merge-topic -u cms-met:72X-13TeV-Training-30Jan15

		git-cms-merge-topic -u cms-met:72X-MetSig-150311

		sed -i 's/lPatPFTau->signalPFCands/lPatPFTau->signalCands/g' RecoMET/METPUSubtraction/plugins/PFMETProducerMVA.cc

		cd RecoMET/METPUSubtraction/

		git clone https://github.com/rfriese/RecoMET-METPUSubtraction data -b 72X-13TeV-Phys14_25_V4-26Mar15

		cd -

		cp /afs/cern.ch/user/s/sshalhou/public/INSTALL_PUBLIC_FILES/72X/mvaPFMEt_72X_Mar2015.db RecoMET/METPUSubtraction/data/.

		cp /afs/cern.ch/user/s/sshalhou/public/INSTALL_PUBLIC_FILES/72X/mvaPFMET_db_cfi.py RecoMET/METPUSubtraction/python/.

		sed -i 's/puJetIdForPFMVAMEt = pileupJetIdEvaluator.clone/from RecoMET.METPUSubtraction.mvaPFMET_db_cfi import mvaPFMEtGBRForestsFromDB\npuJetIdForPFMVAMEt = pileupJetIdEvaluator.clone/g' RecoMET/METPUSubtraction/python/mvaPFMET_cff.py

		scram b -j 20

- For Electron MVA ID (Phys14 version)

		git cms-merge-topic HuguesBrun:trigElecIdInCommonIsoSelection720


- For Muon Effective Area (following LLR's guide on this)

		git clone -n https://github.com/latinos/UserCode-sixie-Muon-MuonAnalysisTools Muon/MuonAnalysisTools 
		
		cd Muon/MuonAnalysisTools 
		
		git checkout master -- interface/MuonEffectiveArea.h 

		cd -


- SVMass code :

		git clone https://github.com/veelken/SVfit_standalone TauAnalysis/SVfitStandalone

- PileUp Reweight Code (Only adding locally in order to turn off default prints) :

		git cms-addpkg PhysicsTools/Utilities
		sed -i 's/std::cout/\/\/std::cout/g' PhysicsTools/Utilities/src/LumiReWeighting.cc

- Clone the Davis Code :

		git clone git@github.com:sshalhou/DavisRunIITauTau DavisRunIITauTau

- Compile : 

		scram b -j 20

- Test Run (remember to change the miniAOD input file):
		
		cmsRun DavisRunIITauTau/runIIntuple_v0.py

- NOTE : for CRAB3 the code+data limit on the tarball size is 100MB,
         in this case it is best to go to RecoMET/METPUSubtraction/data
         and keep only the following files :

		gbrmet_7_2_X_MINIAOD_BX25PU20_Mar2015.root
		
		gbrphi_7_2_X_MINIAOD_BX25PU20_Mar2015.root
		
		gbru1cov_7_2_X_MINIAOD_BX25PU20_Mar2015.root
		
		gbru2cov_7_2_X_MINIAOD_BX25PU20_Mar2015.root

		mvaPFMEt_72X_Mar2015.db
		
		- make sure to also delete : RecoMET/METPUSubtraction/data/.git
		- you should also remove : EgammaAnalysis/ElectronTools/data/CSA14

