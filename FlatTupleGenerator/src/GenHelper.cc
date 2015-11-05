#include "DavisRunIITauTau/FlatTupleGenerator/interface/GenHelper.h"


/* constructor */

GenHelper::GenHelper(){}



/* initialization function */

void GenHelper::init(std::vector<NtupleGenParticle> genVec, NtupleLepton leg1, NtupleLepton leg2, int CandidateEventType )
{

	/* member data set to arguments */
	m_genVec.clear();
	m_genVec = genVec;
	m_leg1 = leg1;
	m_leg2 = leg2;
	m_CandidateEventType = CandidateEventType;	

	/* init member data */
	
	m_EventHasZtoTauTau = 0;
	m_EventHasZtoEE = 0;
	m_EventHasZtoMM = 0;
	m_isDY_genZTTcase1 = 0;        
	m_isDY_genZTTcase2 = 0;        
	m_isDY_genZTTcaseEmbedded = 0; 
	m_isDY_genZL = 0;              
	m_isDY_genZJcase1 = 0;         
	m_isDY_genZJcase2 = 0;         
	m_isDY_genZTTcase3 = 0;        
	m_isDY_genZLL = 0;             
	m_isDY_genZJcase3 = 0;         

	m_genParticle_pdgId.clear();
	m_genParticle_status.clear();


	m_genParticle_isPrompt.clear();
	m_genParticle_isPromptFinalState.clear();
	m_genParticle_isDirectPromptTauDecayProduct.clear();
	m_genParticle_isDirectPromptTauDecayProductFinalState.clear();


	m_genParticle_pt.clear();
	m_genParticle_eta.clear();
	m_genParticle_phi.clear();
	m_genParticle_M.clear();
	m_genDaughter_pdgId.clear();
	m_genDaughter_status.clear();
	m_genDaughter_pt.clear();
	m_genDaughter_eta.clear();
	m_genDaughter_phi.clear();
	m_genDaughter_M.clear();
	m_genMother_pdgId.clear();
	m_genMother_status.clear();
	m_genMother_pt.clear();
	m_genMother_eta.clear();
	m_genMother_phi.clear();
	m_genMother_M.clear();


  for(std::size_t g = 0; g < m_genVec.size(); ++g)
  {
  
    NtupleGenParticle GEN = m_genVec[g];  
    
    m_genParticle_pdgId.push_back(std::make_pair(g,  GEN.gen_pdgId()));
    m_genParticle_status.push_back(std::make_pair(g, GEN.gen_status())); 


	m_genParticle_isPrompt.push_back(std::make_pair(g, GEN.gen_isPrompt())); 
	m_genParticle_isPromptFinalState.push_back(std::make_pair(g, GEN.gen_isPromptFinalState())); 
	m_genParticle_isDirectPromptTauDecayProduct.push_back(std::make_pair(g, GEN.gen_isDirectPromptTauDecayProduct())); 
	m_genParticle_isDirectPromptTauDecayProductFinalState.push_back(std::make_pair(g, GEN.gen_isDirectPromptTauDecayProductFinalState())); 



    m_genParticle_pt.push_back(std::make_pair(g, GEN.gen_p4().pt()));
    m_genParticle_eta.push_back(std::make_pair(g, GEN.gen_p4().eta()));
    m_genParticle_phi.push_back(std::make_pair(g, GEN.gen_p4().phi()));
    m_genParticle_M.push_back(std::make_pair(g, GEN.gen_p4().M()));


    /* nested loop on daughters */
    for(std::size_t gg = 0; gg < GEN.daughters_pdgId().size(); ++gg)
    {
      m_genDaughter_pdgId.push_back(std::make_pair(g, GEN.daughters_pdgId()[gg]));
      m_genDaughter_status.push_back(std::make_pair(g, GEN.daughters_status()[gg]));
      m_genDaughter_pt.push_back(std::make_pair(g, GEN.daughters_gen_p4()[gg].pt()));
      m_genDaughter_eta.push_back(std::make_pair(g, GEN.daughters_gen_p4()[gg].eta()));
      m_genDaughter_phi.push_back(std::make_pair(g, GEN.daughters_gen_p4()[gg].phi()));
      m_genDaughter_M.push_back(std::make_pair(g, GEN.daughters_gen_p4()[gg].M()));
    }


    /* nested loop on mothers */
    for(std::size_t gg = 0; gg < GEN.mothers_pdgId().size(); ++gg)
    { 


      m_genMother_pdgId.push_back(std::make_pair(g, GEN.mothers_pdgId()[gg]));
      m_genMother_status.push_back(std::make_pair(g, GEN.mothers_status()[gg]));
      m_genMother_pt.push_back(std::make_pair(g, GEN.mothers_gen_p4()[gg].pt()));
      m_genMother_eta.push_back(std::make_pair(g, GEN.mothers_gen_p4()[gg].eta()));
      m_genMother_phi.push_back(std::make_pair(g, GEN.mothers_gen_p4()[gg].phi()));
      m_genMother_M.push_back(std::make_pair(g, GEN.mothers_gen_p4()[gg].M()));
    }

  }

  /* now classify the event, only valid for DY MC */
  classifyTheEventForDY();


}


// helpers 

/* assign DY classification : ZTT, ZL, ZJ, ZLL */
/* see : https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorkingSummer2013#Backgrounds_Methods */

void GenHelper::classifyTheEventForDY()
{

	/* reset */

	m_EventHasZtoTauTau = 0;
	m_EventHasZtoEE = 0;
	m_EventHasZtoMM = 0;
	m_isDY_genZTTcase1 = 0;        
	m_isDY_genZTTcase2 = 0;        
	m_isDY_genZTTcaseEmbedded = 0; 
	m_isDY_genZL = 0;              
	m_isDY_genZJcase1 = 0;         
	m_isDY_genZJcase2 = 0;         
	m_isDY_genZTTcase3 = 0;        
	m_isDY_genZLL = 0;             
	m_isDY_genZJcase3 = 0;         



	/* classification depends on if the event is actually Z->TauTau at Gen Level */

	bool isZTT = isZXXatGenLevel(m_genVec,15);
	bool isZEE = isZXXatGenLevel(m_genVec,11);
	bool isZMM = isZXXatGenLevel(m_genVec,13);

	m_EventHasZtoTauTau = isZTT;
	m_EventHasZtoEE = isZEE;
	m_EventHasZtoMM = isZMM;


	/* for eTau and muTau */
	if(m_CandidateEventType==TupleCandidateEventTypes::EleTau || m_CandidateEventType==TupleCandidateEventTypes::MuonTau)
	{
		bool tauMatch = isRecoTauGenTauMatched(m_leg2);
		bool lepMatch = isRecoTauGenEorMuMatched(m_leg2, m_genVec);


		m_isDY_genZTTcase1 = (isZTT && !lepMatch && tauMatch);
		m_isDY_genZTTcase2 = (isZTT && lepMatch);
		m_isDY_genZTTcaseEmbedded = (tauMatch); 
		m_isDY_genZL = (!isZTT && lepMatch);
		m_isDY_genZJcase1 = (!isZTT && !lepMatch);
		m_isDY_genZJcase2 = (isZTT && !lepMatch && !tauMatch);

	}

	else if(m_CandidateEventType==TupleCandidateEventTypes::TauTau)
	{
		/* m_EventHasZtoTauTau is good enough for ZTT in this category 
		since does not require reco-gen matching */
		bool lepFromZmatch1 = isRecoTauGenEorMu_FROMZ_Matched(m_leg1, m_genVec);
		bool lepFromZmatch2 = isRecoTauGenEorMu_FROMZ_Matched(m_leg2, m_genVec);

		m_isDY_genZTTcase3 = isZTT;
		m_isDY_genZLL = (!isZTT && lepFromZmatch1 && lepFromZmatch2);
		m_isDY_genZJcase3 = (!isZTT && !m_isDY_genZLL);

	}


}


/* simple check for Z->Tau Tau at GenLevel */
bool GenHelper::isZXXatGenLevel(std::vector<NtupleGenParticle> genVec,int LEPPDGID)
{
	for(std::size_t g = 0; g < genVec.size(); ++g)
	{

		NtupleGenParticle GEN = genVec[g];  
		if(abs(GEN.gen_pdgId())==23 || abs(GEN.gen_pdgId())==25 \
			|| abs(GEN.gen_pdgId())==35 \
			|| abs(GEN.gen_pdgId())==36 || abs(GEN.gen_pdgId())==37)
		{
			bool genlegP = 0;
			bool genlegM = 0;
			for(std::size_t gg = 0; gg < GEN.daughters_pdgId().size(); ++gg)
		    { 
		    	if(GEN.daughters_pdgId()[gg]==LEPPDGID) genlegP = 1;
		    	if(GEN.daughters_pdgId()[gg]==-1*LEPPDGID) genlegM = 1;

		    }	
		    if(genlegP && genlegM) 
		    {
				return 1;
		    }

		}

	}
	return 0;
}

/* checks if the reco tau is matched by DR<0.5 to an embedded genJet with pT > 18 */
bool GenHelper::isRecoTauGenTauMatched(NtupleLepton legX)
{

	if(legX.leptonType()==TupleLeptonTypes::aTau)
	{
		if(legX.genJet_p4().pt()>18.0 && deltaR(legX.p4(), legX.genJet_p4())<0.5) 
		{
			return 1;
		}

	}

	return 0;
}

/* checks if the reco tau is matched by DR<0.5 to an embedded gen electron or muon with pT > 8 */
bool GenHelper::isRecoTauGenEorMuMatched(NtupleLepton legX,std::vector<NtupleGenParticle> genVec)
{
	for(std::size_t g = 0; g < genVec.size(); ++g)
	{

		NtupleGenParticle GEN = genVec[g];  
		if( abs(GEN.gen_pdgId())==11 || abs(GEN.gen_pdgId())==13)
		{
			if(GEN.gen_p4().pt()>18.0)
			{
				if(deltaR(GEN.gen_p4(),legX.p4())<0.5)
				{
					return 1;				
				}
			}

		}


	}	

	return 0;

}


/* checks if the reco tau is matched by DR<0.5 to an embedded gen electron or muon FROM A Z with pT > 8 */
bool GenHelper::isRecoTauGenEorMu_FROMZ_Matched(NtupleLepton legX,std::vector<NtupleGenParticle> genVec)
{
	for(std::size_t g = 0; g < genVec.size(); ++g)
	{

		NtupleGenParticle GEN = genVec[g];  
		if( abs(GEN.gen_pdgId())==11 || abs(GEN.gen_pdgId())==13)
		{
			if(GEN.gen_p4().pt()>18.0)
			{
				if(deltaR(GEN.gen_p4(),legX.p4())<0.5)
				{
					/* now check mothers for a Z or H */
					for(std::size_t gg = 0; gg < GEN.mothers_pdgId().size(); ++gg)
			   		{ 

			    		if(GEN.mothers_pdgId()[gg]==23) return 1;
			    		if(GEN.mothers_pdgId()[gg]==25) return 1;
			    		if(GEN.mothers_pdgId()[gg]==35) return 1;
			    		if(GEN.mothers_pdgId()[gg]==36) return 1;
			    		if(GEN.mothers_pdgId()[gg]==37) return 1;


			    	}
				}
			}

		}


	}	

	return 0;

}

// getters 

	bool GenHelper::EventHasZtoTauTau() { return m_EventHasZtoTauTau; };
	bool GenHelper::EventHasZtoEE() { return m_EventHasZtoEE; };
	bool GenHelper::EventHasZtoMM() { return m_EventHasZtoMM; };
	bool GenHelper::isDY_genZTTcase1() { return m_isDY_genZTTcase1; };
	bool GenHelper::isDY_genZTTcase2() { return m_isDY_genZTTcase2; };
	bool GenHelper::isDY_genZTTcaseEmbedded() { return m_isDY_genZTTcaseEmbedded; };
	bool GenHelper::isDY_genZL() { return m_isDY_genZL; };
	bool GenHelper::isDY_genZJcase1() { return m_isDY_genZJcase1; };
	bool GenHelper::isDY_genZJcase2() { return m_isDY_genZJcase2; };
	bool GenHelper::isDY_genZTTcase3() { return m_isDY_genZTTcase3; };
	bool GenHelper::isDY_genZLL() { return m_isDY_genZLL; };
	bool GenHelper::isDY_genZJcase3() { return m_isDY_genZJcase3; };


	std::vector <std::pair< int, int>> GenHelper::genParticle_pdgId()  {return m_genParticle_pdgId; };
  	std::vector <std::pair< int, int>> GenHelper::genParticle_status() {return m_genParticle_status; };

  	std::vector <std::pair< int, int>> GenHelper::genParticle_isPrompt() {return m_genParticle_isPrompt; };
  	std::vector <std::pair< int, int>> GenHelper::genParticle_isPromptFinalState() {return m_genParticle_isPromptFinalState; };
  	std::vector <std::pair< int, int>> GenHelper::genParticle_isDirectPromptTauDecayProduct() {return m_genParticle_isDirectPromptTauDecayProduct; };
  	std::vector <std::pair< int, int>> GenHelper::genParticle_isDirectPromptTauDecayProductFinalState() {return m_genParticle_isDirectPromptTauDecayProductFinalState; };




  	std::vector <std::pair< int, double>> GenHelper::genParticle_pt()  {return m_genParticle_pt; };
  	std::vector <std::pair< int, double>> GenHelper::genParticle_eta() {return m_genParticle_eta; };
  	std::vector <std::pair< int, double>> GenHelper::genParticle_phi() {return m_genParticle_phi; };
  	std::vector <std::pair< int, double>> GenHelper::genParticle_M()   {return m_genParticle_M; }; 

  	std::vector <pair < int, int>> GenHelper::genDaughter_pdgId()      {return m_genDaughter_pdgId; };
  	std::vector <pair < int, int>> GenHelper::genDaughter_status()     {return m_genDaughter_status; }; 
  	std::vector <std::pair< int, double>> GenHelper::genDaughter_pt()  {return m_genDaughter_pt;}; 
  	std::vector <std::pair< int, double>> GenHelper::genDaughter_eta() {return m_genDaughter_eta;};
  	std::vector <std::pair< int, double>> GenHelper::genDaughter_phi() {return m_genDaughter_phi;};
  	std::vector <std::pair< int, double>> GenHelper::genDaughter_M()   {return m_genDaughter_M;};


  	std::vector <std::pair< int, int>> GenHelper::genMother_pdgId()    {return m_genMother_pdgId; };
  	std::vector <std::pair< int, int>> GenHelper::genMother_status()   {return m_genMother_status; };
  	std::vector <std::pair< int, double>> GenHelper::genMother_pt()    {return m_genMother_pt; };
  	std::vector <std::pair< int, double>> GenHelper::genMother_eta()   {return m_genMother_eta; }; 
  	std::vector <std::pair< int, double>> GenHelper::genMother_phi()   {return m_genMother_phi; }; 
  	std::vector <std::pair< int, double>> GenHelper::genMother_M()     {return m_genMother_M; };
