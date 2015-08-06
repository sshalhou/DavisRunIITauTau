/* FlatTupleGenerator imp */
#include "DavisRunIITauTau/FlatTupleGenerator/interface/FlatTupleGenerator.h" 



////////////////////////////////////////////
//	--- class constructor
////////////////////////////////////////////


FlatTupleGenerator::FlatTupleGenerator(const edm::ParameterSet& iConfig):
pairSrc_(iConfig.getParameter<edm::InputTag>("pairSrc" )),
indepSrc_(iConfig.getParameter<edm::InputTag>("indepSrc" )),
NAME_(iConfig.getParameter<string>("NAME" )),
EventCutSrc_(iConfig.getParameter<edm::ParameterSet>("EventCutSrc")),
LeptonCutVecSrc_(iConfig.getParameter<std::vector<edm::ParameterSet>>("LeptonCutVecSrc"))
{



	/* read in the EventCutSrc varaibles */

	tauIDsToKeep = EventCutSrc_.getParameter<std::vector<std::string> >("tauIDsToKeep"); 
  assert(THE_MAX>=tauIDsToKeep.size());

  triggerSummaryChecks = EventCutSrc_.getParameter<std::vector<std::string> >("triggerSummaryChecks"); 
  assert(THE_MAX>=triggerSummaryChecks.size());

	keepOS = EventCutSrc_.getParameter<bool>("keepOS");
	keepSS = EventCutSrc_.getParameter<bool>("keepSS");
	keepTauEsNominal = EventCutSrc_.getParameter<bool>("keepTauEsNominal");
	keepTauEsUp = EventCutSrc_.getParameter<bool>("keepTauEsUp");
	keepTauEsDown = EventCutSrc_.getParameter<bool>("keepTauEsDown");
	rankByPtSum = EventCutSrc_.getParameter<bool>("rankByPtSum");
	rankByIsolation = EventCutSrc_.getParameter<bool>("rankByIsolation");
	assert(rankByPtSum!=rankByIsolation);
	electronIsolationForRank = EventCutSrc_.getParameter<std::string>("electronIsolationForRank");
	muonIsolationForRank = EventCutSrc_.getParameter<std::string>("muonIsolationForRank");
	tauIDisolationForRank = EventCutSrc_.getParameter<std::string>("tauIDisolationForRank");

  electronIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("electronIsolationForRelIsoBranch");
  muonIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("muonIsolationForRelIsoBranch");
  tauIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("tauIsolationForRelIsoBranch");
  vetoElectronIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("vetoElectronIsolationForRelIsoBranch");
  vetoMuonIsolationForRelIsoBranch = EventCutSrc_.getParameter<std::string>("vetoMuonIsolationForRelIsoBranch");

  jetIDcut  = EventCutSrc_.getParameter<std::string>("jetIDcut");
  BjetIDcut  = EventCutSrc_.getParameter<std::string>("BjetIDcut");
  jetLeptonDRmin = EventCutSrc_.getParameter<double>("jetLeptonDRmin");

 



}


//////////////////////////////////////////////////
// class destructor 
//////////////////////////////////////////////////

FlatTupleGenerator::~FlatTupleGenerator(){}

//////////////////////////////////////////////////
// ------------ method called for each event  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;



  //////////////
  // init values

  reInit();


  ///////////////
  // get inputs 

  edm::Handle< NtupleEventCollection > pairs;
  iEvent.getByLabel(pairSrc_, pairs);

  edm::Handle< NtuplePairIndependentInfoCollection > pairIndepInfos;
  iEvent.getByLabel(indepSrc_, pairIndepInfos);





  ///////////////////////////////////////////
  // for each event, store a vector of NtupleEvent (i.e. pair)
  // objects that pass the specified selection 
  // this is done separately for each channel since they are ranked
  // indep. from each other

  std::vector<NtupleEvent> retainedPairs_EleTau;
  retainedPairs_EleTau.clear();

  std::vector<NtupleEvent> retainedPairs_MuonTau;
  retainedPairs_MuonTau.clear();

  std::vector<NtupleEvent> retainedPairs_TauTau;
  retainedPairs_TauTau.clear();

  std::vector<NtupleEvent> retainedPairs_EleMuon;
  retainedPairs_EleMuon.clear();

  /////////////////////////////
  // 


  /////////////////////////////////////
  // now loop through the pairs in the current event
  // and figure out which ones to retain 

  for(std::size_t p = 0; p<pairs->size(); ++p )
  {
    NtupleEvent currentPair =   ((*pairs)[p]);

    bool keepSignPair = ((keepOS && currentPair.isOsPair()==1) || (keepSS && currentPair.isOsPair()!=1));
    
    bool keepTauEsVariant = (
      
      (keepTauEsNominal && currentPair.TauEsNumberSigmasShifted()==0.0) ||
      (keepTauEsNominal && isnan(currentPair.TauEsNumberSigmasShifted())) || /* for eMu, muMu, EleEle */
      (keepTauEsUp && currentPair.TauEsNumberSigmasShifted()==1.0) ||
      (keepTauEsDown && currentPair.TauEsNumberSigmasShifted()==-1.0) 

      );


    /* check if the cuts pass */

    bool leptonCutsPass = LeptonCutHelper.cutEvaluator(currentPair, LeptonCutVecSrc_);


   if(keepSignPair && keepTauEsVariant && leptonCutsPass) 
   {

    if(currentPair.CandidateEventType() == TupleCandidateEventTypes::EleTau) 
    { 
      retainedPairs_EleTau.push_back(currentPair);
    }

    else if(currentPair.CandidateEventType() == TupleCandidateEventTypes::MuonTau) 
    { 
      retainedPairs_MuonTau.push_back(currentPair);
    }
   
    else if(currentPair.CandidateEventType() == TupleCandidateEventTypes::TauTau) 
    { 
      retainedPairs_TauTau.push_back(currentPair);
    }

    else if(currentPair.CandidateEventType() == TupleCandidateEventTypes::EleMuon) 
    { 
      retainedPairs_EleMuon.push_back(currentPair);
    }
   }



  }

  /////////////////////////
  // next figure out how to rank the pairs 


  PairRankHelper rankHelper_EleMuon;
  PairRankHelper rankHelper_EleTau;
  PairRankHelper rankHelper_MuonTau;
  PairRankHelper rankHelper_TauTau;

  if(rankByPtSum) 
  {
    rankHelper_EleMuon.init(retainedPairs_EleMuon);
    rankHelper_EleTau.init(retainedPairs_EleTau);
    rankHelper_MuonTau.init(retainedPairs_MuonTau);
    rankHelper_TauTau.init(retainedPairs_TauTau);

  }


  else if(rankByIsolation) 
  {
    rankHelper_EleMuon.init(retainedPairs_EleMuon,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank);
    rankHelper_EleTau.init(retainedPairs_EleTau,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank);
    rankHelper_MuonTau.init(retainedPairs_MuonTau,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank);
    rankHelper_TauTau.init(retainedPairs_TauTau,electronIsolationForRank,muonIsolationForRank,tauIDisolationForRank);
  }

  // get the individual rank-pair std::pairs

  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_EleTau = rankHelper_EleTau.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_EleMuon = rankHelper_EleMuon.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_MuonTau = rankHelper_MuonTau.returnRankedPairVec();
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank_TauTau = rankHelper_TauTau.returnRankedPairVec();

  // combine the individual channel pairs into a single vector
  
  std::vector<std::pair<std::size_t,NtupleEvent>> retainedPairsWithRank;
  retainedPairsWithRank.clear();


  for(std::size_t v = 0; v<retainedPairsWithRank_EleTau.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_EleTau[v]);
  }
  for(std::size_t v = 0; v<retainedPairsWithRank_MuonTau.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_MuonTau[v]);
  }
  for(std::size_t v = 0; v<retainedPairsWithRank_TauTau.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_TauTau[v]);
  }

  for(std::size_t v = 0; v<retainedPairsWithRank_EleMuon.size(); ++v )
  {
    retainedPairsWithRank.push_back(retainedPairsWithRank_EleMuon[v]);
  }

  // check if any pairs from any channels are kept

  if(retainedPairsWithRank.size()==0) return;



  for(std::size_t p = 0; p<retainedPairsWithRank.size(); ++p )
  {

      reInit();

      pairRank = retainedPairsWithRank[p].first;
      if(pairRank!=0) continue; /* no reason to keep more than the best pair/event */


      ////////////////
      // fill some easy stuff first :

      run = iEvent.id().run();
      luminosityBlock = iEvent.id().luminosityBlock();
      event = iEvent.id().event();
      isRealData = iEvent.isRealData();
      treeInfoString = NAME_;

      AppliedLepCuts = LeptonCutHelper.getCutSummary(LeptonCutVecSrc_);

      ///////
      // now stuff depending on the current pair


  		NtupleEvent currentPair =   retainedPairsWithRank[p].second;


      VISMass = currentPair.VISMass()[0];
      
      
      ////////////////
      // fill the tauIDs for tau legs


        for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
        {
          
          if(currentPair.leg1().leptonType() == TupleLeptonTypes::aTau)
          {
              leg1_tauIDs[x]  =  currentPair.leg1().tauID(tauIDsToKeep[x]);
          }

          if(currentPair.leg2().leptonType() == TupleLeptonTypes::aTau)
          {
              leg2_tauIDs[x]  =  currentPair.leg2().tauID(tauIDsToKeep[x]);
          }

        }


      ////////////////
      // fill the triggerSummaryChecks for both legs


      for(std::size_t x = 0; x<triggerSummaryChecks.size();++x ) 
      {

        // check the OR of a specific version or a wildcard v* 
        std::string label_ = triggerSummaryChecks[x]; 
        std::string versionStrippedLabel_ = label_;
        versionStrippedLabel_.erase(label_.find("_v"),label_.length());

        float l1trig = 0.0;
        float l2trig = 0.0;

        if(currentPair.isLeg1GoodForHLTPath(label_)) l1trig = 1.0;
        else if(currentPair.isLeg1GoodForHLTPath(versionStrippedLabel_)) l1trig = 1.0;

        if(currentPair.isLeg2GoodForHLTPath(label_)) l2trig = 1.0;
        else if(currentPair.isLeg2GoodForHLTPath(versionStrippedLabel_)) l2trig = 1.0;

        leg1_GoodForHLTPath[x]  =  l1trig;
        leg2_GoodForHLTPath[x]  =  l2trig;
      }


      CandidateEventType = currentPair.CandidateEventType();


      TauEsNumberSigmasShifted = currentPair.TauEsNumberSigmasShifted();
      isOsPair = currentPair.isOsPair();
      SVMass = currentPair.SVMass()[0];
      MTmvaMET_leg1 = currentPair.MTmvaMET_leg1()[0];
      MTpfMET_leg1 = currentPair.MTpfMET_leg1()[0];
      MTmvaMET_leg2 = currentPair.MTmvaMET_leg2()[0];
      MTpfMET_leg2 = currentPair.MTpfMET_leg2()[0];
      mvaMET = currentPair.mvaMET()[0].pt();
      mvaMETphi = currentPair.mvaMET()[0].phi();
      mvaMET_cov00 = currentPair.mvaMET()[0].getSignificanceMatrix()[0][0];
      mvaMET_cov01 = currentPair.mvaMET()[0].getSignificanceMatrix()[0][1];
      mvaMET_cov10 = currentPair.mvaMET()[0].getSignificanceMatrix()[1][0];
      mvaMET_cov11 = currentPair.mvaMET()[0].getSignificanceMatrix()[1][1];
      pfMET = currentPair.pfMET()[0].pt();
      pfMETphi = currentPair.pfMET()[0].phi();

      pfMET_cov00 = currentPair.pfMET_cov00()[0];
      pfMET_cov01 = currentPair.pfMET_cov01()[0];
      pfMET_cov10 = currentPair.pfMET_cov10()[0];
      pfMET_cov11 = currentPair.pfMET_cov11()[0];  

      leg1_leptonType = currentPair.leg1().leptonType();
      leg1_dz = currentPair.leg1().dz();
      leg1_dxy = currentPair.leg1().dxy();
      leg1_EffectiveArea = currentPair.leg1().EffectiveArea();
      leg1_charge = currentPair.leg1().charge();
      leg1_PFpdgId = currentPair.leg1().PFpdgId();
      leg1_GENpdgId = currentPair.leg1().GENpdgId();
      leg1_GENMOTHERpdgId = currentPair.leg1().GENMOTHERpdgId();
      leg1_IP = currentPair.leg1().IP();
      leg1_IPerror = currentPair.leg1().IPerror();
      leg1_PUchargedHadronIso = currentPair.leg1().PUchargedHadronIso();
      leg1_chargedHadronIso = currentPair.leg1().chargedHadronIso();
      leg1_neutralHadronIso = currentPair.leg1().neutralHadronIso();
      leg1_photonIso = currentPair.leg1().photonIso();
      leg1_DepositR03ECal = currentPair.leg1().DepositR03ECal();
      leg1_DepositR03Hcal = currentPair.leg1().DepositR03Hcal();
      leg1_DepositR03TrackerOfficial = currentPair.leg1().DepositR03TrackerOfficial();
      leg1_isGlobalMuon = currentPair.leg1().isGlobalMuon();
      leg1_isGoodGlobalMuon = currentPair.leg1().isGoodGlobalMuon();
      leg1_passesMediumMuonId = currentPair.leg1().passesMediumMuonId();
      leg1_isLooseMuon = currentPair.leg1().isLooseMuon();
      leg1_isPFMuon = currentPair.leg1().isPFMuon();
      leg1_isSoftMuon = currentPair.leg1().isSoftMuon();
      leg1_isTightMuon = currentPair.leg1().isTightMuon();
      leg1_isTrackerMuon = currentPair.leg1().isTrackerMuon();
      leg1_muonCombQualChi2LocalPosition = currentPair.leg1().muonCombQualChi2LocalPosition();
      leg1_muonCombQualTrkKink = currentPair.leg1().muonCombQualTrkKink();
      leg1_muonGlobalTrackNormChi2 = currentPair.leg1().muonGlobalTrackNormChi2();
      leg1_muonInnerTrkValidFraction = currentPair.leg1().muonInnerTrkValidFraction();
      leg1_muonSegmentCompatibility = currentPair.leg1().muonSegmentCompatibility();
      leg1_raw_electronMVA = currentPair.leg1().raw_electronMVA();
      leg1_category_electronMVA = currentPair.leg1().category_electronMVA();
      leg1_passFail_electronMVA80 = currentPair.leg1().passFail_electronMVA80();
      leg1_passFail_electronMVA90 = currentPair.leg1().passFail_electronMVA90();
      leg1_passFail_electronCutBasedID = currentPair.leg1().passFail_electronCutBasedID();
      leg1_ooEmooP = currentPair.leg1().ooEmooP();
      leg1_full5x5_sigmaIetaIeta = currentPair.leg1().full5x5_sigmaIetaIeta();
      leg1_SuperClusterEta = currentPair.leg1().SuperClusterEta();
      leg1_hadronicOverEm = currentPair.leg1().hadronicOverEm();
      leg1_isEB = currentPair.leg1().isEB();
      leg1_isEBEEGap = currentPair.leg1().isEBEEGap();
      leg1_isEBEtaGap = currentPair.leg1().isEBEtaGap();
      leg1_isEBPhiGap = currentPair.leg1().isEBPhiGap();
      leg1_isEE = currentPair.leg1().isEE();
      leg1_isEEDeeGap = currentPair.leg1().isEEDeeGap();
      leg1_isEERingGap = currentPair.leg1().isEERingGap();
      leg1_deltaEtaSuperClusterTrackAtVtx = currentPair.leg1().deltaEtaSuperClusterTrackAtVtx();
      leg1_deltaPhiSuperClusterTrackAtVtx = currentPair.leg1().deltaPhiSuperClusterTrackAtVtx();
      leg1_sigmaEtaEta = currentPair.leg1().sigmaEtaEta();
      leg1_sigmaIetaIeta = currentPair.leg1().sigmaIetaIeta();
      leg1_sigmaIphiIphi = currentPair.leg1().sigmaIphiIphi();
      leg1_numberOfMissingInnerHits = currentPair.leg1().numberOfMissingInnerHits();
      leg1_numberOfMissingOuterHits = currentPair.leg1().numberOfMissingOuterHits();
      leg1_numberOfTrackHits = currentPair.leg1().numberOfTrackHits();
      leg1_passConversionVeto = currentPair.leg1().passConversionVeto();
      leg1_ZimpactTau = currentPair.leg1().ZimpactTau();
      leg1_dzTauVertex = currentPair.leg1().dzTauVertex();
      leg1_numStrips = currentPair.leg1().numStrips();
      leg1_numHadrons = currentPair.leg1().numHadrons();
      leg2_leptonType = currentPair.leg2().leptonType();
      leg2_dz = currentPair.leg2().dz();
      leg2_dxy = currentPair.leg2().dxy();
      leg2_EffectiveArea = currentPair.leg2().EffectiveArea();
      leg2_charge = currentPair.leg2().charge();
      leg2_PFpdgId = currentPair.leg2().PFpdgId();
      leg2_GENpdgId = currentPair.leg2().GENpdgId();
      leg2_GENMOTHERpdgId = currentPair.leg2().GENMOTHERpdgId();
      leg2_IP = currentPair.leg2().IP();
      leg2_IPerror = currentPair.leg2().IPerror();
      leg2_PUchargedHadronIso = currentPair.leg2().PUchargedHadronIso();
      leg2_chargedHadronIso = currentPair.leg2().chargedHadronIso();
      leg2_neutralHadronIso = currentPair.leg2().neutralHadronIso();
      leg2_photonIso = currentPair.leg2().photonIso();
      leg2_DepositR03ECal = currentPair.leg2().DepositR03ECal();
      leg2_DepositR03Hcal = currentPair.leg2().DepositR03Hcal();
      leg2_DepositR03TrackerOfficial = currentPair.leg2().DepositR03TrackerOfficial();
      leg2_isGlobalMuon = currentPair.leg2().isGlobalMuon();
      leg2_isGoodGlobalMuon = currentPair.leg2().isGoodGlobalMuon();
      leg2_passesMediumMuonId = currentPair.leg2().passesMediumMuonId();
      leg2_isLooseMuon = currentPair.leg2().isLooseMuon();
      leg2_isPFMuon = currentPair.leg2().isPFMuon();
      leg2_isSoftMuon = currentPair.leg2().isSoftMuon();
      leg2_isTightMuon = currentPair.leg2().isTightMuon();
      leg2_isTrackerMuon = currentPair.leg2().isTrackerMuon();
      leg2_muonCombQualChi2LocalPosition = currentPair.leg2().muonCombQualChi2LocalPosition();
      leg2_muonCombQualTrkKink = currentPair.leg2().muonCombQualTrkKink();
      leg2_muonGlobalTrackNormChi2 = currentPair.leg2().muonGlobalTrackNormChi2();
      leg2_muonInnerTrkValidFraction = currentPair.leg2().muonInnerTrkValidFraction();
      leg2_muonSegmentCompatibility = currentPair.leg2().muonSegmentCompatibility();
      leg2_raw_electronMVA = currentPair.leg2().raw_electronMVA();
      leg2_category_electronMVA = currentPair.leg2().category_electronMVA();
      leg2_passFail_electronMVA80 = currentPair.leg2().passFail_electronMVA80();
      leg2_passFail_electronMVA90 = currentPair.leg2().passFail_electronMVA90();
      leg2_passFail_electronCutBasedID = currentPair.leg2().passFail_electronCutBasedID();
      leg2_ooEmooP = currentPair.leg2().ooEmooP();
      leg2_full5x5_sigmaIetaIeta = currentPair.leg2().full5x5_sigmaIetaIeta();
      leg2_SuperClusterEta = currentPair.leg2().SuperClusterEta();
      leg2_hadronicOverEm = currentPair.leg2().hadronicOverEm();
      leg2_isEB = currentPair.leg2().isEB();
      leg2_isEBEEGap = currentPair.leg2().isEBEEGap();
      leg2_isEBEtaGap = currentPair.leg2().isEBEtaGap();
      leg2_isEBPhiGap = currentPair.leg2().isEBPhiGap();
      leg2_isEE = currentPair.leg2().isEE();
      leg2_isEEDeeGap = currentPair.leg2().isEEDeeGap();
      leg2_isEERingGap = currentPair.leg2().isEERingGap();
      leg2_deltaEtaSuperClusterTrackAtVtx = currentPair.leg2().deltaEtaSuperClusterTrackAtVtx();
      leg2_deltaPhiSuperClusterTrackAtVtx = currentPair.leg2().deltaPhiSuperClusterTrackAtVtx();
      leg2_sigmaEtaEta = currentPair.leg2().sigmaEtaEta();
      leg2_sigmaIetaIeta = currentPair.leg2().sigmaIetaIeta();
      leg2_sigmaIphiIphi = currentPair.leg2().sigmaIphiIphi();
      leg2_numberOfMissingInnerHits = currentPair.leg2().numberOfMissingInnerHits();
      leg2_numberOfMissingOuterHits = currentPair.leg2().numberOfMissingOuterHits();
      leg2_numberOfTrackHits = currentPair.leg2().numberOfTrackHits();
      leg2_passConversionVeto = currentPair.leg2().passConversionVeto();
      leg2_ZimpactTau = currentPair.leg2().ZimpactTau();
      leg2_numStrips = currentPair.leg2().numStrips();
      leg2_numHadrons = currentPair.leg2().numHadrons();
      leg2_dzTauVertex = currentPair.leg2().dzTauVertex();


      leg2_pt = currentPair.leg2().p4().pt();
      leg2_gen_pt = currentPair.leg2().gen_p4().pt();
      leg2_genMother_pt = currentPair.leg2().genMother_p4().pt();
      leg2_genJet_pt = currentPair.leg2().genJet_p4().pt();
      leg1_pt = currentPair.leg1().p4().pt();
      leg1_gen_pt = currentPair.leg1().gen_p4().pt();
      leg1_genMother_pt = currentPair.leg1().genMother_p4().pt();
      leg1_genJet_pt = currentPair.leg1().genJet_p4().pt();
      leg2_eta = currentPair.leg2().p4().eta();
      leg2_gen_eta = currentPair.leg2().gen_p4().eta();
      leg2_genMother_eta = currentPair.leg2().genMother_p4().eta();
      leg2_genJet_eta = currentPair.leg2().genJet_p4().eta();
      leg1_eta = currentPair.leg1().p4().eta();
      leg1_gen_eta = currentPair.leg1().gen_p4().eta();
      leg1_genMother_eta = currentPair.leg1().genMother_p4().eta();
      leg1_genJet_eta = currentPair.leg1().genJet_p4().eta();
      leg2_phi = currentPair.leg2().p4().phi();
      leg2_gen_phi = currentPair.leg2().gen_p4().phi();
      leg2_genMother_phi = currentPair.leg2().genMother_p4().phi();
      
      leg2_genJet_phi = currentPair.leg2().genJet_p4().phi();
      leg1_phi = currentPair.leg1().p4().phi();
      leg1_gen_phi = currentPair.leg1().gen_p4().phi();
      leg1_genMother_phi = currentPair.leg1().genMother_p4().phi();
      leg1_genJet_phi = currentPair.leg1().genJet_p4().phi();
      leg2_M = currentPair.leg2().p4().M();
      leg2_gen_M = currentPair.leg2().gen_p4().M();
      leg2_genMother_M = currentPair.leg2().genMother_p4().M();
      leg2_genJet_M = currentPair.leg2().genJet_p4().M();
      leg1_M = currentPair.leg1().p4().M();
      leg1_gen_M = currentPair.leg1().gen_p4().M();
      leg1_genMother_M = currentPair.leg1().genMother_p4().M();
      leg1_genJet_M = currentPair.leg1().genJet_p4().M();



      /* set the relative isolation value dep. on the lepton type */

      if(currentPair.leg1().leptonType() == TupleLeptonTypes::anElectron)
      {
        leg1_RelIso = currentPair.leg1().relativeIsol(electronIsolationForRelIsoBranch);
      }

      else if(currentPair.leg1().leptonType() == TupleLeptonTypes::aMuon)
      {
        leg1_RelIso = currentPair.leg1().relativeIsol(muonIsolationForRelIsoBranch);
      }

      else if(currentPair.leg1().leptonType() == TupleLeptonTypes::aTau)
      {
        leg1_RelIso = currentPair.leg1().tauID(tauIsolationForRelIsoBranch);
      }


      if(currentPair.leg2().leptonType() == TupleLeptonTypes::anElectron)
      {
        leg2_RelIso = currentPair.leg2().relativeIsol(electronIsolationForRelIsoBranch);
      }

      else if(currentPair.leg2().leptonType() == TupleLeptonTypes::aMuon)
      {
        leg2_RelIso = currentPair.leg2().relativeIsol(muonIsolationForRelIsoBranch);
      }

      else if(currentPair.leg2().leptonType() == TupleLeptonTypes::aTau)
      {
        leg2_RelIso = currentPair.leg2().tauID(tauIsolationForRelIsoBranch);
      }

      /* fill veto lepton parameters, MUST FILL IN SAME ORDER FOR ELECTRONS & MUONS */

      for(std::size_t v = 0; v<currentPair.vetoElectron().size(); ++v)
      {
          veto_leptonType.push_back(currentPair.vetoElectron()[v].leptonType());
          veto_pt.push_back(currentPair.vetoElectron()[v].p4().pt());
          veto_eta.push_back(currentPair.vetoElectron()[v].p4().eta());
          veto_phi.push_back(currentPair.vetoElectron()[v].p4().phi());
          veto_M.push_back(currentPair.vetoElectron()[v].p4().M());
          veto_dxy.push_back(currentPair.vetoElectron()[v].dxy());
          veto_dz.push_back(currentPair.vetoElectron()[v].dz());
          veto_passesMediumMuonId.push_back(currentPair.vetoElectron()[v].passesMediumMuonId());
          veto_rawElectronMVA.push_back(currentPair.vetoElectron()[v].raw_electronMVA());
          veto_categoryElectronMVA.push_back(currentPair.vetoElectron()[v].category_electronMVA());
          veto_passElectronMVA80.push_back(currentPair.vetoElectron()[v].passFail_electronMVA80());
          veto_passElectronMVA90.push_back(currentPair.vetoElectron()[v].passFail_electronMVA90());
          veto_passElectronCutBased.push_back(currentPair.vetoElectron()[v].passFail_electronCutBasedID());
          veto_isTrackerGlobalPFMuon.push_back(0.0);         
          veto_RelIso.push_back(currentPair.vetoElectron()[v].relativeIsol(electronIsolationForRelIsoBranch));
          veto_charge.push_back(currentPair.vetoElectron()[v].charge());
      }

      for(std::size_t v = 0; v<currentPair.vetoMuon().size(); ++v)
      {
          veto_leptonType.push_back(currentPair.vetoMuon()[v].leptonType());
          veto_pt.push_back(currentPair.vetoMuon()[v].p4().pt());
          veto_eta.push_back(currentPair.vetoMuon()[v].p4().eta());
          veto_phi.push_back(currentPair.vetoMuon()[v].p4().phi());
          veto_M.push_back(currentPair.vetoMuon()[v].p4().M());
          veto_dxy.push_back(currentPair.vetoMuon()[v].dxy());
          veto_dz.push_back(currentPair.vetoMuon()[v].dz());
          veto_passesMediumMuonId.push_back(currentPair.vetoMuon()[v].passesMediumMuonId());
          veto_rawElectronMVA.push_back(currentPair.vetoMuon()[v].raw_electronMVA());
          veto_categoryElectronMVA.push_back(currentPair.vetoMuon()[v].category_electronMVA());
          veto_passElectronMVA80.push_back(currentPair.vetoMuon()[v].passFail_electronMVA80());
          veto_passElectronMVA90.push_back(currentPair.vetoMuon()[v].passFail_electronMVA90());
          veto_passElectronCutBased.push_back(currentPair.vetoMuon()[v].passFail_electronCutBasedID());
         
          float isTrackerGlobalPFMuon = (currentPair.vetoMuon()[v].isTrackerMuon() && \
                                         currentPair.vetoMuon()[v].isGlobalMuon() && \
                                         currentPair.vetoMuon()[v].isPFMuon());
          

          veto_isTrackerGlobalPFMuon.push_back(isTrackerGlobalPFMuon);         
          veto_RelIso.push_back(currentPair.vetoMuon()[v].relativeIsol(muonIsolationForRelIsoBranch));
          veto_charge.push_back(currentPair.vetoMuon()[v].charge());

      }


      /* access the pair independent info, making any needed adjustments for the current pair */

      NtuplePairIndependentInfo currentINDEP =   ((*pairIndepInfos)[0]);

      /* info about the primary vertex */
      NumberOfGoodVertices = currentINDEP.numberOfGoodVertices();
      vertex_NDOF = currentINDEP.primaryVertex().ndof();
      vertex_CHI2 = currentINDEP.primaryVertex().chi2();
      vertex_positionRho = currentINDEP.primaryVertex().position().Rho();
      vertex_positionX = currentINDEP.primaryVertex().position().x();
      vertex_positionY  = currentINDEP.primaryVertex().position().y();
      vertex_positionZ = currentINDEP.primaryVertex().position().z();
      vertex_positionTheta = currentINDEP.primaryVertex().position().theta();
      vertex_positionEta = currentINDEP.primaryVertex().position().eta();
      vertex_positionPhi = currentINDEP.primaryVertex().position().phi();

      /* pileup & other weights */
  
      puWeight = currentINDEP.puWeight();
      NumPileupInt = currentINDEP.NumPileupInt();
      NumTruePileUpInt = currentINDEP.NumTruePileUpInt();
      generatorEventWeight = currentINDEP.generatorEventWeight();
      hepNUP = currentINDEP.hepNUP();

      /* process the jets */
      jethelper.init(currentINDEP.jets(),jetIDcut,BjetIDcut,
                jetLeptonDRmin,currentPair.leg1(),currentPair.leg2());

      /* get the jets and bjets passing the cuts provided in init */
      std::vector<NtupleJet> goodJets = jethelper.PtOrderedPassingJets();
      std::vector<NtupleJet> goodBJets = jethelper.PtOrderedPassingBJets();

      numberOfJets =   goodJets.size();
      numberOfBJets =  goodBJets.size();
      numberOfJets30 = 0;



      /* now fill the FlatTuple jet vector */
      for(std::size_t j=0; j<goodJets.size(); ++j)
      {      
        if(goodJets[j].jet_p4().pt()>30) numberOfJets30++;  
        jets_pt.push_back(goodJets[j].jet_p4().pt());
        jets_eta.push_back(goodJets[j].jet_p4().eta());
        jets_phi.push_back(goodJets[j].jet_p4().phi());
        jets_M.push_back(goodJets[j].jet_p4().M());

        jets_PU_jetIdRaw.push_back(goodJets[j].PU_jetIdRaw());
        jets_PU_jetIdPassed.push_back(goodJets[j].PU_jetIdPassed());
        jets_PF_jetIdPassed.push_back(goodJets[j].PF_jetIdPassed());
        jets_defaultBtagAlgorithm_RawScore.push_back(goodJets[j].defaultBtagAlgorithm_RawScore());
        jets_defaultBtagAlgorithm_isPassed.push_back(goodJets[j].defaultBtagAlgorithm_isPassed());
        jets_PARTON_flavour.push_back(goodJets[j].PARTON_flavour());
        jets_HADRON_flavour.push_back(goodJets[j].HADRON_flavour());

      }

      /* now fill the FlatTuple bjet vector */
      for(std::size_t j=0; j<goodBJets.size(); ++j)
      {        
        bjets_pt.push_back(goodBJets[j].jet_p4().pt());
        bjets_eta.push_back(goodBJets[j].jet_p4().eta());
        bjets_phi.push_back(goodBJets[j].jet_p4().phi());
        bjets_M.push_back(goodBJets[j].jet_p4().M());

        bjets_PU_jetIdRaw.push_back(goodBJets[j].PU_jetIdRaw());
        bjets_PU_jetIdPassed.push_back(goodBJets[j].PU_jetIdPassed());
        bjets_PF_jetIdPassed.push_back(goodBJets[j].PF_jetIdPassed());
        bjets_defaultBtagAlgorithm_RawScore.push_back(goodBJets[j].defaultBtagAlgorithm_RawScore());
        bjets_defaultBtagAlgorithm_isPassed.push_back(goodBJets[j].defaultBtagAlgorithm_isPassed());
        bjets_PARTON_flavour.push_back(goodBJets[j].PARTON_flavour());
        bjets_HADRON_flavour.push_back(goodBJets[j].HADRON_flavour());

      }
 

      /* fill the gen level info, for now ~ exaclty as in Ntuple */

      genhelper.init(currentINDEP.genParticles(),currentPair.leg1(),currentPair.leg2(),
                     currentPair.CandidateEventType());

      
      genParticle_pdgId = genhelper.genParticle_pdgId();
      genParticle_status = genhelper.genParticle_status();
      genParticle_pt = genhelper.genParticle_pt();
      genParticle_eta = genhelper.genParticle_eta();
      genParticle_phi = genhelper.genParticle_phi();
      genParticle_M = genhelper.genParticle_M();
      genDaughter_pdgId = genhelper.genDaughter_pdgId();
      genDaughter_status = genhelper.genDaughter_status();
      genDaughter_pt = genhelper.genDaughter_pt();
      genDaughter_eta = genhelper.genDaughter_eta();
      genDaughter_phi = genhelper.genDaughter_phi();
      genDaughter_M = genhelper.genDaughter_M();
      genMother_pdgId = genhelper.genMother_pdgId();
      genMother_status = genhelper.genMother_status();
      genMother_pt = genhelper.genMother_pt();
      genMother_eta = genhelper.genMother_eta();
      genMother_phi = genhelper.genMother_phi();
      genMother_M = genhelper.genMother_M();

      EventHasZtoTauTau = genhelper.EventHasZtoTauTau();
      EventHasZtoEE = genhelper.EventHasZtoEE();
      EventHasZtoMM = genhelper.EventHasZtoMM();
      isDY_genZTTcase1 = genhelper.isDY_genZTTcase1();
      isDY_genZTTcase2 = genhelper.isDY_genZTTcase2();
      isDY_genZTTcaseEmbedded = genhelper.isDY_genZTTcaseEmbedded();
      isDY_genZL = genhelper.isDY_genZL();
      isDY_genZJcase1 = genhelper.isDY_genZJcase1();
      isDY_genZJcase2 = genhelper.isDY_genZJcase2();
      isDY_genZTTcase3 = genhelper.isDY_genZTTcase3();
      isDY_genZLL = genhelper.isDY_genZLL();
      isDY_genZJcase3 = genhelper.isDY_genZJcase3();

      if(currentPair.leg1().leptonType() != TupleLeptonTypes::aTau)
      { /* same for both legs, but current ntuple forgot to include this for taus */
        rho = currentPair.leg1().rho("fixedGridRhoFastjetAll"); 
      }

      FlatTuple->Fill();

  }



}



//////////////////////////////////////////////////
// ------------ method called to reset values and clear vectors each event ----
//////////////////////////////////////////////////

 void FlatTupleGenerator::reInit()
 {


   run = 0;
   luminosityBlock = 0;
   event = 0;
   pairRank = 999;
   isRealData  = 0;
   treeInfoString = "NULL";
   VISMass  = NAN;
   AppliedLepCuts.clear();

  for(int r =0; r<THE_MAX;++r)
  {  leg1_tauIDs[r] = NAN;
     leg2_tauIDs[r] = NAN;
  }

  for(int r =0; r<THE_MAX;++r)
  {  leg1_GoodForHLTPath[r] = NAN;
     leg2_GoodForHLTPath[r] = NAN;
  }


  CandidateEventType = -999; 
  TauEsNumberSigmasShifted = NAN;
  isOsPair = -999;
  SVMass = NAN;
  MTmvaMET_leg1 = NAN;
  MTpfMET_leg1 = NAN;
  MTmvaMET_leg2 = NAN;
  MTpfMET_leg2 = NAN;
  mvaMET = NAN;
  mvaMETphi = NAN;
  mvaMET_cov00 = NAN;
  mvaMET_cov01 = NAN; 
  mvaMET_cov10 = NAN; 
  mvaMET_cov11 = NAN;   
  pfMET = NAN;
  pfMETphi = NAN;
  pfMET_cov00 = NAN; 
  pfMET_cov01 = NAN; 
  pfMET_cov10 = NAN; 
  pfMET_cov11 = NAN;   

  leg1_dz = NAN;
  leg1_dxy = NAN;
  leg1_EffectiveArea = NAN;
  leg1_IP = NAN;
  leg1_IPerror = NAN;
  leg1_PUchargedHadronIso = NAN;
  leg1_chargedHadronIso = NAN;
  leg1_neutralHadronIso = NAN;
  leg1_photonIso = NAN;
  leg1_DepositR03ECal = NAN;
  leg1_DepositR03Hcal = NAN;
  leg1_DepositR03TrackerOfficial = NAN;
  leg1_isGlobalMuon = NAN;
  leg1_isGoodGlobalMuon = NAN;
  leg1_passesMediumMuonId = NAN;
  leg1_isLooseMuon = NAN;
  leg1_isPFMuon = NAN;
  leg1_isSoftMuon = NAN;
  leg1_isTightMuon = NAN;
  leg1_isTrackerMuon = NAN;
  leg1_muonCombQualChi2LocalPosition = NAN;
  leg1_muonCombQualTrkKink = NAN;
  leg1_muonGlobalTrackNormChi2 = NAN;
  leg1_muonInnerTrkValidFraction = NAN;
  leg1_muonSegmentCompatibility = NAN;
  leg1_raw_electronMVA = NAN;
  leg1_category_electronMVA = NAN;
  leg1_passFail_electronMVA80 = NAN;
  leg1_passFail_electronMVA90 = NAN;
  leg1_passFail_electronCutBasedID = NAN;
  leg1_ooEmooP = NAN;
  leg1_full5x5_sigmaIetaIeta = NAN;
  leg1_SuperClusterEta = NAN;
  leg1_hadronicOverEm = NAN;
  leg1_isEB = NAN;
  leg1_isEBEEGap = NAN;
  leg1_isEBEtaGap = NAN;
  leg1_isEBPhiGap = NAN;
  leg1_isEE = NAN;
  leg1_isEEDeeGap = NAN;
  leg1_isEERingGap = NAN;
  leg1_deltaEtaSuperClusterTrackAtVtx = NAN;
  leg1_deltaPhiSuperClusterTrackAtVtx = NAN;
  leg1_sigmaEtaEta = NAN;
  leg1_sigmaIetaIeta = NAN;
  leg1_sigmaIphiIphi = NAN;
  leg1_numberOfMissingInnerHits = NAN;
  leg1_numberOfMissingOuterHits = NAN;
  leg1_numberOfTrackHits = NAN;
  leg1_passConversionVeto = NAN;
  leg1_ZimpactTau = NAN;
  leg1_dzTauVertex = NAN;
  leg1_numStrips = NAN;
  leg1_numHadrons = NAN;
  leg2_dz = NAN;
  leg2_dxy = NAN;
  leg2_EffectiveArea = NAN;
  leg2_IP = NAN;
  leg2_IPerror = NAN;
  leg2_PUchargedHadronIso = NAN;
  leg2_chargedHadronIso = NAN;
  leg2_neutralHadronIso = NAN;
  leg2_photonIso = NAN;
  leg2_DepositR03ECal = NAN;
  leg2_DepositR03Hcal = NAN;
  leg2_DepositR03TrackerOfficial = NAN;
  leg2_isGlobalMuon = NAN;
  leg2_isGoodGlobalMuon = NAN;
  leg2_passesMediumMuonId = NAN;
  leg2_isLooseMuon = NAN;
  leg2_isPFMuon = NAN;
  leg2_isSoftMuon = NAN;
  leg2_isTightMuon = NAN;
  leg2_isTrackerMuon = NAN;
  leg2_muonCombQualChi2LocalPosition = NAN;
  leg2_muonCombQualTrkKink = NAN;
  leg2_muonGlobalTrackNormChi2 = NAN;
  leg2_muonInnerTrkValidFraction = NAN;
  leg2_muonSegmentCompatibility = NAN;
  leg2_raw_electronMVA = NAN;
  leg2_category_electronMVA = NAN;
  leg2_passFail_electronMVA80 = NAN;
  leg2_passFail_electronMVA90 = NAN;
  leg2_passFail_electronCutBasedID = NAN;
  leg2_ooEmooP = NAN;
  leg2_full5x5_sigmaIetaIeta = NAN;  
  leg2_SuperClusterEta = NAN;
  leg2_hadronicOverEm = NAN;
  leg2_isEB = NAN;
  leg2_isEBEEGap = NAN;
  leg2_isEBEtaGap = NAN;
  leg2_isEBPhiGap = NAN;
  leg2_isEE = NAN;
  leg2_isEEDeeGap = NAN;
  leg2_isEERingGap = NAN;
  leg2_deltaEtaSuperClusterTrackAtVtx = NAN;
  leg2_deltaPhiSuperClusterTrackAtVtx = NAN;
  leg2_sigmaEtaEta = NAN;
  leg2_sigmaIetaIeta = NAN;
  leg2_sigmaIphiIphi = NAN;
  leg2_numberOfMissingInnerHits = NAN;
  leg2_numberOfMissingOuterHits = NAN;
  leg2_numberOfTrackHits = NAN;
  leg2_passConversionVeto = NAN;
  leg2_ZimpactTau = NAN;
  leg2_numStrips = NAN;
  leg2_numHadrons = NAN;
  leg2_dzTauVertex = NAN;


  leg1_leptonType = -999;
  leg1_charge = -999;
  leg1_PFpdgId = -999;
  leg1_GENpdgId = -999;
  leg1_GENMOTHERpdgId = -999;
  leg2_leptonType = -999;
  leg2_charge = -999;
  leg2_PFpdgId = -999;
  leg2_GENpdgId = -999;
  leg2_GENMOTHERpdgId = -999;


  leg2_pt = NAN;
  leg2_gen_pt = NAN;
  leg2_genMother_pt = NAN;
  leg2_genJet_pt = NAN;
  leg1_pt = NAN;
  leg1_gen_pt = NAN;
  leg1_genMother_pt = NAN;
  leg1_genJet_pt = NAN;
  leg2_eta = NAN;
  leg2_gen_eta = NAN;
  leg2_genMother_eta = NAN;
  leg2_genJet_eta = NAN;
  leg1_eta = NAN;
  leg1_gen_eta = NAN;
  leg1_genMother_eta = NAN;
  leg1_genJet_eta = NAN;
  leg2_phi = NAN;
  leg2_gen_phi = NAN;
  leg2_genMother_phi = NAN;
  leg2_genJet_phi = NAN;
  leg1_phi = NAN;
  leg1_gen_phi = NAN;
  leg1_genMother_phi = NAN;
  leg1_genJet_phi = NAN;
  leg2_M = NAN;
  leg2_gen_M = NAN;
  leg2_genMother_M = NAN;
  leg2_genJet_M = NAN;
  leg1_M = NAN;
  leg1_gen_M = NAN;
  leg1_genMother_M = NAN;
  leg1_genJet_M = NAN;
  leg1_RelIso = NAN;
  leg2_RelIso = NAN;

  veto_leptonType.clear(); 
  veto_pt.clear(); 
  veto_eta.clear(); 
  veto_phi.clear(); 
  veto_M.clear(); 
  veto_charge.clear(); 
  veto_dxy.clear(); 
  veto_dz.clear(); 
  veto_RelIso.clear(); 
  veto_passesMediumMuonId.clear(); 
  veto_rawElectronMVA.clear(); 
  veto_categoryElectronMVA.clear(); 
  veto_passElectronMVA80.clear(); 
  veto_passElectronMVA90.clear(); 
  veto_passElectronCutBased.clear(); 
  veto_isTrackerGlobalPFMuon.clear(); 

  NumberOfGoodVertices = -999;
  vertex_NDOF = NAN;
  vertex_CHI2 = NAN;
  vertex_positionRho = NAN;
  vertex_positionX = NAN;
  vertex_positionY  = NAN;
  vertex_positionZ = NAN;
  vertex_positionTheta = NAN;
  vertex_positionEta = NAN;
  vertex_positionPhi = NAN;

  puWeight = NAN;
  NumPileupInt = NAN;
  NumTruePileUpInt = NAN;
  generatorEventWeight = NAN;
  hepNUP = -999;



  numberOfJets30 = -999;
  numberOfJets = -999;
  numberOfBJets = -999;
  jets_pt.clear();
  jets_eta.clear();
  jets_phi.clear();
  jets_M.clear();
  jets_PU_jetIdRaw.clear();
  jets_PU_jetIdPassed.clear();
  jets_PF_jetIdPassed.clear();
  jets_defaultBtagAlgorithm_RawScore.clear();
  jets_defaultBtagAlgorithm_isPassed.clear();
  jets_PARTON_flavour.clear();
  jets_HADRON_flavour.clear();
  bjets_pt.clear();
  bjets_eta.clear();
  bjets_phi.clear();
  bjets_M.clear();
  bjets_PU_jetIdRaw.clear();
  bjets_PU_jetIdPassed.clear();
  bjets_PF_jetIdPassed.clear();
  bjets_defaultBtagAlgorithm_RawScore.clear();
  bjets_defaultBtagAlgorithm_isPassed.clear();
  bjets_PARTON_flavour.clear();
  bjets_HADRON_flavour.clear();


  genParticle_pdgId.clear();
  genParticle_status.clear();
  genParticle_pt.clear();
  genParticle_eta.clear();
  genParticle_phi.clear();
  genParticle_M.clear();
  genDaughter_pdgId.clear();
  genDaughter_status.clear();
  genDaughter_pt.clear();
  genDaughter_eta.clear();
  genDaughter_phi.clear();
  genDaughter_M.clear();
  genMother_pdgId.clear();
  genMother_status.clear();
  genMother_pt.clear();
  genMother_eta.clear();
  genMother_phi.clear();
  genMother_M.clear();

  EventHasZtoTauTau = 0;       
  EventHasZtoEE = 0;          
  EventHasZtoMM = 0;          
  isDY_genZTTcase1 = 0;       
  isDY_genZTTcase2 = 0;       
  isDY_genZTTcaseEmbedded = 0; 
  isDY_genZL = 0;              
  isDY_genZJcase1 = 0;         
  isDY_genZJcase2 = 0;         
  isDY_genZTTcase3 = 0;        
  isDY_genZLL = 0;             
  isDY_genZJcase3 = 0;         
  rho  = NAN;

 }

 //////////////////////////////////////////////////
// ------------ method called once each job just before starting event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginJob() 
{

   /* create TTree */
   
  edm::Service<TFileService> fs;
  FlatTuple = fs->make<TTree>("FlatTuple","FlatTuple");







  //////////////
  // init values

    reInit(); 



  /* the branches */

  FlatTuple->Branch("run", &run);
  FlatTuple->Branch("luminosityBlock", &luminosityBlock);
  FlatTuple->Branch("event", &event);
  FlatTuple->Branch("pairRank",&pairRank);
  FlatTuple->Branch("isRealData", &isRealData);
  FlatTuple->Branch("treeInfoString", &treeInfoString);
  FlatTuple->Branch("AppliedLepCuts", &AppliedLepCuts);
  FlatTuple->Branch("VISMass", &VISMass);

  for(std::size_t x = 0; x<tauIDsToKeep.size();++x ) 
  {

  FlatTuple->Branch(("leg1_"+tauIDsToKeep.at(x)).c_str(), &leg1_tauIDs[x]);
  FlatTuple->Branch(("leg2_"+tauIDsToKeep.at(x)).c_str(), &leg2_tauIDs[x]);
  }


  for(std::size_t x = 0; x<triggerSummaryChecks.size();++x ) 
  {

    std::string versionStrippedName = triggerSummaryChecks.at(x);
    versionStrippedName.erase(versionStrippedName.find("_v"),versionStrippedName.length());

    std::cout<<versionStrippedName<<"\n";

    FlatTuple->Branch(("leg1_"+versionStrippedName).c_str(), &leg1_GoodForHLTPath[x]);
    FlatTuple->Branch(("leg2_"+versionStrippedName).c_str(), &leg2_GoodForHLTPath[x]);
  }

  FlatTuple->Branch("CandidateEventType", &CandidateEventType);
  FlatTuple->Branch("TauEsNumberSigmasShifted", &TauEsNumberSigmasShifted);
  FlatTuple->Branch("isOsPair", &isOsPair);
  FlatTuple->Branch("SVMass", &SVMass);
  FlatTuple->Branch("MTmvaMET_leg1", &MTmvaMET_leg1);
  FlatTuple->Branch("MTpfMET_leg1", &MTpfMET_leg1);
  FlatTuple->Branch("MTmvaMET_leg2", &MTmvaMET_leg2);
  FlatTuple->Branch("MTpfMET_leg2", &MTpfMET_leg2);
  FlatTuple->Branch("mvaMET", &mvaMET);
  FlatTuple->Branch("mvaMETphi", &mvaMETphi);
  FlatTuple->Branch("mvaMET_cov00", &mvaMET_cov00);
  FlatTuple->Branch("mvaMET_cov01", &mvaMET_cov01);
  FlatTuple->Branch("mvaMET_cov10", &mvaMET_cov10);
  FlatTuple->Branch("mvaMET_cov11", &mvaMET_cov11);
  FlatTuple->Branch("pfMET", &pfMET);
  FlatTuple->Branch("pfMETphi", &pfMETphi);
  FlatTuple->Branch("pfMET_cov00", &pfMET_cov00);
  FlatTuple->Branch("pfMET_cov01", &pfMET_cov01);
  FlatTuple->Branch("pfMET_cov10", &pfMET_cov10);
  FlatTuple->Branch("pfMET_cov11", &pfMET_cov11);

  FlatTuple->Branch("leg1_leptonType", &leg1_leptonType);
  FlatTuple->Branch("leg1_dz", &leg1_dz);
  FlatTuple->Branch("leg1_dxy", &leg1_dxy);
  FlatTuple->Branch("leg1_EffectiveArea", &leg1_EffectiveArea);
  FlatTuple->Branch("leg1_charge", &leg1_charge);
  FlatTuple->Branch("leg1_PFpdgId", &leg1_PFpdgId);
  FlatTuple->Branch("leg1_GENpdgId", &leg1_GENpdgId);
  FlatTuple->Branch("leg1_GENMOTHERpdgId", &leg1_GENMOTHERpdgId);
  FlatTuple->Branch("leg1_IP", &leg1_IP);
  FlatTuple->Branch("leg1_IPerror", &leg1_IPerror);
  FlatTuple->Branch("leg1_PUchargedHadronIso", &leg1_PUchargedHadronIso);
  FlatTuple->Branch("leg1_chargedHadronIso", &leg1_chargedHadronIso);
  FlatTuple->Branch("leg1_neutralHadronIso", &leg1_neutralHadronIso);
  FlatTuple->Branch("leg1_photonIso", &leg1_photonIso);
  FlatTuple->Branch("leg1_DepositR03ECal", &leg1_DepositR03ECal);
  FlatTuple->Branch("leg1_DepositR03Hcal", &leg1_DepositR03Hcal);
  FlatTuple->Branch("leg1_DepositR03TrackerOfficial", &leg1_DepositR03TrackerOfficial);
  FlatTuple->Branch("leg1_isGlobalMuon", &leg1_isGlobalMuon);
  FlatTuple->Branch("leg1_isGoodGlobalMuon", &leg1_isGoodGlobalMuon);
  FlatTuple->Branch("leg1_passesMediumMuonId", &leg1_passesMediumMuonId);
  FlatTuple->Branch("leg1_isLooseMuon", &leg1_isLooseMuon);
  FlatTuple->Branch("leg1_isPFMuon", &leg1_isPFMuon);
  FlatTuple->Branch("leg1_isSoftMuon", &leg1_isSoftMuon);
  FlatTuple->Branch("leg1_isTightMuon", &leg1_isTightMuon);
  FlatTuple->Branch("leg1_isTrackerMuon", &leg1_isTrackerMuon);
  FlatTuple->Branch("leg1_muonCombQualChi2LocalPosition", &leg1_muonCombQualChi2LocalPosition);
  FlatTuple->Branch("leg1_muonCombQualTrkKink", &leg1_muonCombQualTrkKink);
  FlatTuple->Branch("leg1_muonGlobalTrackNormChi2", &leg1_muonGlobalTrackNormChi2);
  FlatTuple->Branch("leg1_muonInnerTrkValidFraction", &leg1_muonInnerTrkValidFraction);
  FlatTuple->Branch("leg1_muonSegmentCompatibility", &leg1_muonSegmentCompatibility);
  FlatTuple->Branch("leg1_raw_electronMVA", &leg1_raw_electronMVA);
  FlatTuple->Branch("leg1_category_electronMVA", &leg1_category_electronMVA);
  FlatTuple->Branch("leg1_passFail_electronMVA80", &leg1_passFail_electronMVA80);
  FlatTuple->Branch("leg1_passFail_electronMVA90", &leg1_passFail_electronMVA90);
  FlatTuple->Branch("leg1_passFail_electronCutBasedID", &leg1_passFail_electronCutBasedID);
  FlatTuple->Branch("leg1_ooEmooP", &leg1_ooEmooP);
  FlatTuple->Branch("leg1_full5x5_sigmaIetaIeta", &leg1_full5x5_sigmaIetaIeta);
  FlatTuple->Branch("leg1_SuperClusterEta", &leg1_SuperClusterEta);
  FlatTuple->Branch("leg1_hadronicOverEm", &leg1_hadronicOverEm);
  FlatTuple->Branch("leg1_isEB", &leg1_isEB);
  FlatTuple->Branch("leg1_isEBEEGap", &leg1_isEBEEGap);
  FlatTuple->Branch("leg1_isEBEtaGap", &leg1_isEBEtaGap);
  FlatTuple->Branch("leg1_isEBPhiGap", &leg1_isEBPhiGap);
  FlatTuple->Branch("leg1_isEE", &leg1_isEE);
  FlatTuple->Branch("leg1_isEEDeeGap", &leg1_isEEDeeGap);
  FlatTuple->Branch("leg1_isEERingGap", &leg1_isEERingGap);
  FlatTuple->Branch("leg1_deltaEtaSuperClusterTrackAtVtx", &leg1_deltaEtaSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg1_deltaPhiSuperClusterTrackAtVtx", &leg1_deltaPhiSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg1_sigmaEtaEta", &leg1_sigmaEtaEta);
  FlatTuple->Branch("leg1_sigmaIetaIeta", &leg1_sigmaIetaIeta);
  FlatTuple->Branch("leg1_sigmaIphiIphi", &leg1_sigmaIphiIphi);
  FlatTuple->Branch("leg1_numberOfMissingInnerHits", &leg1_numberOfMissingInnerHits);
  FlatTuple->Branch("leg1_numberOfMissingOuterHits", &leg1_numberOfMissingOuterHits);
  FlatTuple->Branch("leg1_numberOfTrackHits", &leg1_numberOfTrackHits);
  FlatTuple->Branch("leg1_passConversionVeto", &leg1_passConversionVeto);
  FlatTuple->Branch("leg1_ZimpactTau", &leg1_ZimpactTau);
  FlatTuple->Branch("leg1_numStrips", &leg1_numStrips);
  FlatTuple->Branch("leg1_dzTauVertex", &leg1_dzTauVertex);
  FlatTuple->Branch("leg1_numHadrons", &leg1_numHadrons);
  FlatTuple->Branch("leg2_leptonType", &leg2_leptonType);
  FlatTuple->Branch("leg2_dz", &leg2_dz);
  FlatTuple->Branch("leg2_dxy", &leg2_dxy);
  FlatTuple->Branch("leg2_EffectiveArea", &leg2_EffectiveArea);
  FlatTuple->Branch("leg2_charge", &leg2_charge);
  FlatTuple->Branch("leg2_PFpdgId", &leg2_PFpdgId);
  FlatTuple->Branch("leg2_GENpdgId", &leg2_GENpdgId);
  FlatTuple->Branch("leg2_GENMOTHERpdgId", &leg2_GENMOTHERpdgId);
  FlatTuple->Branch("leg2_IP", &leg2_IP);
  FlatTuple->Branch("leg2_IPerror", &leg2_IPerror);
  FlatTuple->Branch("leg2_PUchargedHadronIso", &leg2_PUchargedHadronIso);
  FlatTuple->Branch("leg2_chargedHadronIso", &leg2_chargedHadronIso);
  FlatTuple->Branch("leg2_neutralHadronIso", &leg2_neutralHadronIso);
  FlatTuple->Branch("leg2_photonIso", &leg2_photonIso);
  FlatTuple->Branch("leg2_DepositR03ECal", &leg2_DepositR03ECal);
  FlatTuple->Branch("leg2_DepositR03Hcal", &leg2_DepositR03Hcal);
  FlatTuple->Branch("leg2_DepositR03TrackerOfficial", &leg2_DepositR03TrackerOfficial);
  FlatTuple->Branch("leg2_isGlobalMuon", &leg2_isGlobalMuon);
  FlatTuple->Branch("leg2_isGoodGlobalMuon", &leg2_isGoodGlobalMuon);
  FlatTuple->Branch("leg2_passesMediumMuonId", &leg2_passesMediumMuonId);
  FlatTuple->Branch("leg2_isLooseMuon", &leg2_isLooseMuon);
  FlatTuple->Branch("leg2_isPFMuon", &leg2_isPFMuon);
  FlatTuple->Branch("leg2_isSoftMuon", &leg2_isSoftMuon);
  FlatTuple->Branch("leg2_isTightMuon", &leg2_isTightMuon);
  FlatTuple->Branch("leg2_isTrackerMuon", &leg2_isTrackerMuon);
  FlatTuple->Branch("leg2_muonCombQualChi2LocalPosition", &leg2_muonCombQualChi2LocalPosition);
  FlatTuple->Branch("leg2_muonCombQualTrkKink", &leg2_muonCombQualTrkKink);
  FlatTuple->Branch("leg2_muonGlobalTrackNormChi2", &leg2_muonGlobalTrackNormChi2);
  FlatTuple->Branch("leg2_muonInnerTrkValidFraction", &leg2_muonInnerTrkValidFraction);
  FlatTuple->Branch("leg2_muonSegmentCompatibility", &leg2_muonSegmentCompatibility);
  FlatTuple->Branch("leg2_raw_electronMVA", &leg2_raw_electronMVA);
  FlatTuple->Branch("leg2_category_electronMVA", &leg2_category_electronMVA);
  FlatTuple->Branch("leg2_passFail_electronMVA80", &leg2_passFail_electronMVA80);
  FlatTuple->Branch("leg2_passFail_electronMVA90", &leg2_passFail_electronMVA90);
  FlatTuple->Branch("leg2_passFail_electronCutBasedID", &leg2_passFail_electronCutBasedID);
  FlatTuple->Branch("leg2_ooEmooP", &leg2_ooEmooP);
  FlatTuple->Branch("leg2_full5x5_sigmaIetaIeta", &leg2_full5x5_sigmaIetaIeta);
  FlatTuple->Branch("leg2_SuperClusterEta", &leg2_SuperClusterEta);
  FlatTuple->Branch("leg2_hadronicOverEm", &leg2_hadronicOverEm);
  FlatTuple->Branch("leg2_isEB", &leg2_isEB);
  FlatTuple->Branch("leg2_isEBEEGap", &leg2_isEBEEGap);
  FlatTuple->Branch("leg2_isEBEtaGap", &leg2_isEBEtaGap);
  FlatTuple->Branch("leg2_isEBPhiGap", &leg2_isEBPhiGap);
  FlatTuple->Branch("leg2_isEE", &leg2_isEE);
  FlatTuple->Branch("leg2_isEEDeeGap", &leg2_isEEDeeGap);
  FlatTuple->Branch("leg2_isEERingGap", &leg2_isEERingGap);
  FlatTuple->Branch("leg2_deltaEtaSuperClusterTrackAtVtx", &leg2_deltaEtaSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg2_deltaPhiSuperClusterTrackAtVtx", &leg2_deltaPhiSuperClusterTrackAtVtx);
  FlatTuple->Branch("leg2_sigmaEtaEta", &leg2_sigmaEtaEta);
  FlatTuple->Branch("leg2_sigmaIetaIeta", &leg2_sigmaIetaIeta);
  FlatTuple->Branch("leg2_sigmaIphiIphi", &leg2_sigmaIphiIphi);
  FlatTuple->Branch("leg2_numberOfMissingInnerHits", &leg2_numberOfMissingInnerHits);
  FlatTuple->Branch("leg2_numberOfMissingOuterHits", &leg2_numberOfMissingOuterHits);
  FlatTuple->Branch("leg2_numberOfTrackHits", &leg2_numberOfTrackHits);
  FlatTuple->Branch("leg2_passConversionVeto", &leg2_passConversionVeto);
  FlatTuple->Branch("leg2_ZimpactTau", &leg2_ZimpactTau);
  FlatTuple->Branch("leg2_numStrips", &leg2_numStrips);
  FlatTuple->Branch("leg2_numHadrons", &leg2_numHadrons);
  FlatTuple->Branch("leg2_dzTauVertex", &leg2_dzTauVertex);

  FlatTuple->Branch("leg2_pt", &leg2_pt);
  FlatTuple->Branch("leg2_gen_pt", &leg2_gen_pt);
  FlatTuple->Branch("leg2_genMother_pt", &leg2_genMother_pt);
  FlatTuple->Branch("leg2_genJet_pt", &leg2_genJet_pt);
  FlatTuple->Branch("leg1_pt", &leg1_pt);
  FlatTuple->Branch("leg1_gen_pt", &leg1_gen_pt);
  FlatTuple->Branch("leg1_genMother_pt", &leg1_genMother_pt);
  FlatTuple->Branch("leg1_genJet_pt", &leg1_genJet_pt);
  FlatTuple->Branch("leg2_eta", &leg2_eta);
  FlatTuple->Branch("leg2_gen_eta", &leg2_gen_eta);
  FlatTuple->Branch("leg2_genMother_eta", &leg2_genMother_eta);
  FlatTuple->Branch("leg2_genJet_eta", &leg2_genJet_eta);
  FlatTuple->Branch("leg1_eta", &leg1_eta);
  FlatTuple->Branch("leg1_gen_eta", &leg1_gen_eta);
  FlatTuple->Branch("leg1_genMother_eta", &leg1_genMother_eta);
  FlatTuple->Branch("leg1_genJet_eta", &leg1_genJet_eta);
  FlatTuple->Branch("leg2_phi", &leg2_phi);
  FlatTuple->Branch("leg2_gen_phi", &leg2_gen_phi);
  FlatTuple->Branch("leg2_genMother_phi", &leg2_genMother_phi);
  FlatTuple->Branch("leg2_genJet_phi", &leg2_genJet_phi);
  FlatTuple->Branch("leg1_phi", &leg1_phi);
  FlatTuple->Branch("leg1_gen_phi", &leg1_gen_phi);
  FlatTuple->Branch("leg1_genMother_phi", &leg1_genMother_phi);
  FlatTuple->Branch("leg1_genJet_phi", &leg1_genJet_phi);
  FlatTuple->Branch("leg2_M", &leg2_M);
  FlatTuple->Branch("leg2_gen_M", &leg2_gen_M);
  FlatTuple->Branch("leg2_genMother_M", &leg2_genMother_M);
  FlatTuple->Branch("leg2_genJet_M", &leg2_genJet_M);
  FlatTuple->Branch("leg1_M", &leg1_M);
  FlatTuple->Branch("leg1_gen_M", &leg1_gen_M);
  FlatTuple->Branch("leg1_genMother_M", &leg1_genMother_M);
  FlatTuple->Branch("leg1_genJet_M", &leg1_genJet_M);
  FlatTuple->Branch("leg1_RelIso",&leg1_RelIso);
  FlatTuple->Branch("leg2_RelIso",&leg2_RelIso);


  FlatTuple->Branch("veto_leptonType", &veto_leptonType);
  FlatTuple->Branch("veto_pt", &veto_pt);
  FlatTuple->Branch("veto_eta", &veto_eta);
  FlatTuple->Branch("veto_phi", &veto_phi);
  FlatTuple->Branch("veto_M", &veto_M);
  FlatTuple->Branch("veto_charge", &veto_charge);

  FlatTuple->Branch("veto_dxy", &veto_dxy);
  FlatTuple->Branch("veto_dz", &veto_dz);
  FlatTuple->Branch("veto_RelIso", &veto_RelIso);
  FlatTuple->Branch("veto_passesMediumMuonId", &veto_passesMediumMuonId);
  FlatTuple->Branch("veto_rawElectronMVA", &veto_rawElectronMVA);
  FlatTuple->Branch("veto_categoryElectronMVA", &veto_categoryElectronMVA);
  FlatTuple->Branch("veto_passElectronMVA80", &veto_passElectronMVA80);
  FlatTuple->Branch("veto_passElectronMVA90", &veto_passElectronMVA90);
  FlatTuple->Branch("veto_passElectronCutBased", &veto_passElectronCutBased);
  FlatTuple->Branch("veto_isTrackerGlobalPFMuon", &veto_isTrackerGlobalPFMuon);

  FlatTuple->Branch("NumberOfGoodVertices",&NumberOfGoodVertices);
  FlatTuple->Branch("vertex_NDOF",&vertex_NDOF);
  FlatTuple->Branch("vertex_CHI2",&vertex_CHI2);
  FlatTuple->Branch("vertex_positionRho",&vertex_positionRho);
  FlatTuple->Branch("vertex_positionX",&vertex_positionX);
  FlatTuple->Branch("vertex_positionY",&vertex_positionY);
  FlatTuple->Branch("vertex_positionZ",&vertex_positionZ);
  FlatTuple->Branch("vertex_positionTheta",&vertex_positionTheta);
  FlatTuple->Branch("vertex_positionEta",&vertex_positionEta);
  FlatTuple->Branch("vertex_positionPhi",&vertex_positionPhi);

  FlatTuple->Branch("puWeight",&puWeight);
  FlatTuple->Branch("NumPileupInt",&NumPileupInt);
  FlatTuple->Branch("NumTruePileUpInt",&NumTruePileUpInt);
  FlatTuple->Branch("generatorEventWeight",&generatorEventWeight);
  FlatTuple->Branch("hepNUP",&hepNUP);

  FlatTuple->Branch("numberOfJets", &numberOfJets);
  FlatTuple->Branch("numberOfJets30", &numberOfJets30);

  FlatTuple->Branch("numberOfBJets", &numberOfBJets);
  FlatTuple->Branch("jets_pt", &jets_pt);
  FlatTuple->Branch("jets_eta", &jets_eta);
  FlatTuple->Branch("jets_phi", &jets_phi);
  FlatTuple->Branch("jets_M", &jets_M);
  FlatTuple->Branch("jets_PU_jetIdRaw", &jets_PU_jetIdRaw);
  FlatTuple->Branch("jets_PU_jetIdPassed", &jets_PU_jetIdPassed);
  FlatTuple->Branch("jets_PF_jetIdPassed", &jets_PF_jetIdPassed);
  FlatTuple->Branch("jets_defaultBtagAlgorithm_RawScore", &jets_defaultBtagAlgorithm_RawScore);
  FlatTuple->Branch("jets_defaultBtagAlgorithm_isPassed", &jets_defaultBtagAlgorithm_isPassed);
  FlatTuple->Branch("jets_PARTON_flavour", &jets_PARTON_flavour);
  FlatTuple->Branch("jets_HADRON_flavour", &jets_HADRON_flavour);
  FlatTuple->Branch("bjets_pt", &bjets_pt);
  FlatTuple->Branch("bjets_eta", &bjets_eta);
  FlatTuple->Branch("bjets_phi", &bjets_phi);
  FlatTuple->Branch("bjets_M", &bjets_M);
  FlatTuple->Branch("bjets_PU_jetIdRaw", &bjets_PU_jetIdRaw);
  FlatTuple->Branch("bjets_PU_jetIdPassed", &bjets_PU_jetIdPassed);
  FlatTuple->Branch("bjets_PF_jetIdPassed", &bjets_PF_jetIdPassed);
  FlatTuple->Branch("bjets_defaultBtagAlgorithm_RawScore", &bjets_defaultBtagAlgorithm_RawScore);
  FlatTuple->Branch("bjets_defaultBtagAlgorithm_isPassed", &bjets_defaultBtagAlgorithm_isPassed);
  FlatTuple->Branch("bjets_PARTON_flavour", &bjets_PARTON_flavour);
  FlatTuple->Branch("bjets_HADRON_flavour", &bjets_HADRON_flavour);

  FlatTuple->Branch("genParticle_pdgId", &genParticle_pdgId);
  FlatTuple->Branch("genParticle_status", &genParticle_status);
  FlatTuple->Branch("genParticle_pt", &genParticle_pt);
  FlatTuple->Branch("genParticle_eta", &genParticle_eta);
  FlatTuple->Branch("genParticle_phi", &genParticle_phi);
  FlatTuple->Branch("genParticle_M", &genParticle_M);
  FlatTuple->Branch("genDaughter_pdgId", &genDaughter_pdgId);
  FlatTuple->Branch("genDaughter_status", &genDaughter_status);
  FlatTuple->Branch("genDaughter_pt", &genDaughter_pt);
  FlatTuple->Branch("genDaughter_eta", &genDaughter_eta);
  FlatTuple->Branch("genDaughter_phi", &genDaughter_phi);
  FlatTuple->Branch("genDaughter_M", &genDaughter_M);
  FlatTuple->Branch("genMother_pdgId", &genMother_pdgId);
  FlatTuple->Branch("genMother_status", &genMother_status);
  FlatTuple->Branch("genMother_pt", &genMother_pt);
  FlatTuple->Branch("genMother_eta", &genMother_eta);
  FlatTuple->Branch("genMother_phi", &genMother_phi);
  FlatTuple->Branch("genMother_M", &genMother_M);

  FlatTuple->Branch("EventHasZtoTauTau", &EventHasZtoTauTau);
  FlatTuple->Branch("EventHasZtoEE", &EventHasZtoEE);
  FlatTuple->Branch("EventHasZtoMM", &EventHasZtoMM);
  FlatTuple->Branch("isDY_genZTTcase1", &isDY_genZTTcase1);
  FlatTuple->Branch("isDY_genZTTcase2", &isDY_genZTTcase2);
  FlatTuple->Branch("isDY_genZTTcaseEmbedded", &isDY_genZTTcaseEmbedded);
  FlatTuple->Branch("isDY_genZL", &isDY_genZL);
  FlatTuple->Branch("isDY_genZJcase1", &isDY_genZJcase1);
  FlatTuple->Branch("isDY_genZJcase2", &isDY_genZJcase2);
  FlatTuple->Branch("isDY_genZTTcase3", &isDY_genZTTcase3);
  FlatTuple->Branch("isDY_genZLL", &isDY_genZLL);
  FlatTuple->Branch("isDY_genZJcase3", &isDY_genZJcase3);

  FlatTuple->Branch("rho", &rho);


}

//////////////////////////////////////////////////
// ------------ method called once each job just after ending the event loop  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endJob() {}


/*
//////////////////////////////////////////////////
// ------------ method called when starting to processes a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a run  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endRun(edm::Run const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when starting to processes a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method called when ending the processing of a luminosity block  ------------
//////////////////////////////////////////////////

void FlatTupleGenerator::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//////////////////////////////////////////////////
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
//////////////////////////////////////////////////
*/
void FlatTupleGenerator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
    //The following says we do not know what parameters are allowed so do no validation
    // Please change this to state exactly what you do use, even if it is no parameters
    edm::ParameterSetDescription desc;
    desc.setUnknown();
    descriptions.addDefault(desc);
  }
