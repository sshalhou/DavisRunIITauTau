#include "DavisRunIITauTau/FlatTupleGenerator/interface/GenHelper.h"


/* constructor */

GenHelper::GenHelper(){}


/* fill reco-independent info */

void GenHelper::fillRecoIndependentInfo()
{

  for(std::size_t g = 0; g < m_genVec.size(); ++g)
  {
  
    NtupleGenParticle GEN = m_genVec[g];  
    
    m_genParticle_pdgId.push_back(std::make_pair(g,  GEN.gen_pdgId()));
    m_genParticle_status.push_back(std::make_pair(g, GEN.gen_status())); 


	m_genParticle_isPrompt.push_back(std::make_pair(g, GEN.gen_isPrompt())); 
	m_genParticle_isPromptFinalState.push_back(std::make_pair(g, GEN.gen_isPromptFinalState())); 
	m_genParticle_isDirectPromptTauDecayProduct.push_back(std::make_pair(g, GEN.gen_isDirectPromptTauDecayProduct())); 
	m_genParticle_isDirectPromptTauDecayProductFinalState.push_back(std::make_pair(g, GEN.gen_isDirectPromptTauDecayProductFinalState())); 
    m_genParticle_fromHardProcess.push_back(std::make_pair(g, GEN.gen_FromHardProcess())); 
    m_genParticle_isLastCopy.push_back(std::make_pair(g, GEN.gen_IsLastCopy())); 



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

}


std::vector <double> GenHelper::getTopPts()
{
	/* loop through genPartciles and find all particles with
	abs(m_genMother_pdgId) == 6 and gen_FromHardProcess() and m_genParticle_isLastCopy
	*/

	std::vector <double> retVec_;
	retVec_.clear();

	for(std::size_t g = 0; g < m_genParticle_pdgId.size(); ++g)
  	{
		if(abs(m_genParticle_pdgId[g].second) == 6)
		{
			if( m_genParticle_fromHardProcess[g].second == 1 && m_genParticle_isLastCopy[g].second == 1)
			{
				if(retVec_.size() <= 2)
				{
					retVec_.push_back(m_genParticle_pt[g].second);
				}

			}


		}


	}

	return retVec_;

}


/* reset variables to zero/empty vectors */
void GenHelper::resetVars()
{
	/* DR match max */

	MCdrMatchRun2 = 0.2;

	/* member data set to arguments */
	m_genVec.clear();
	m_effLep.clear();
	m_CandidateEventType = -999;	

	/* init member data */
	
	m_leg1_MCMatchType = -999;
    m_leg1_genMCmatch_pt = NAN;
    m_leg1_genMCmatch_eta = NAN; 
    m_leg1_genMCmatch_phi = NAN;
    m_leg1_genMCmatch_M = NAN;
    m_leg1_MCMatchPdgId = -999;

    m_leg2_MCMatchType = -999;
    m_leg2_genMCmatch_pt = NAN;
    m_leg2_genMCmatch_eta = NAN;
    m_leg2_genMCmatch_phi = NAN;
    m_leg2_genMCmatch_M = NAN;
    m_leg2_MCMatchPdgId = -999;

	m_effLep_MCMatchType.clear();
    m_effLep_genMCmatch_pt.clear();
    m_effLep_genMCmatch_eta.clear();
    m_effLep_genMCmatch_phi.clear();
    m_effLep_genMCmatch_M.clear();
    m_effLep_MCMatchPdgId.clear();


	temp_effLep_MCMatchType = -999;
    temp_effLep_genMCmatch_pt = NAN;
    temp_effLep_genMCmatch_eta = NAN;
    temp_effLep_genMCmatch_phi = NAN;
    temp_effLep_genMCmatch_M = NAN;
    temp_effLep_MCMatchPdgId = -999;

    m_top_pt_1 = NAN;
    m_top_pt_2 = NAN;


    m_IsZTT = -999;
    m_IsZL = -999;
    m_IsZJ = -999;
    m_IsZLL = -999;



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
    m_genParticle_fromHardProcess.clear();
    m_genParticle_isLastCopy.clear();

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


}

/* initialization function for EffCand Pairs (i.e. not EleMu, EleTau, etc.)*/

void GenHelper::init(std::vector<NtupleGenParticle> genVec, std::vector<NtupleLepton> effLep, int CandidateEventType )
{

	/* make sure not called for incorrect type */
	assert( CandidateEventType == TupleCandidateEventTypes::EffCand);

	/* reset variables */	
	resetVars();

	/* set some data members */

	m_genVec = genVec;
	m_effLep = effLep;
	m_CandidateEventType = CandidateEventType;	

	/* set some other info - need m_genVec to be set before this call */

	fillRecoIndependentInfo();

	/* perform the Run II MC Matching and classification of the two legs
	based on Run II guidelines */
	// see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorking2015#MC_Matching	

	for(std::size_t e = 0; e<m_effLep.size(); ++e)
	{
		temp_effLep = effLep.at(e);
		// std::cout<<" checking MC matches for an EffLep at index "<<e<<" with ";
		// std::cout<<"pt = "<<temp_effLep.p4().pt()<<" and type "<<temp_effLep.leptonType()<<"\n";
		checkLegsForEorMuorGenJetMatches(3);
	}

}


/* initialization function for regular H2TauTau Pairs (i.e. not EffCand)*/

void GenHelper::init(std::vector<NtupleGenParticle> genVec, NtupleLepton leg1, NtupleLepton leg2, int CandidateEventType )
{

	/* make sure not called for incorrect type */
	assert( CandidateEventType != TupleCandidateEventTypes::EffCand);

	/* reset variables */	
	resetVars();

	/* set some data members */

	m_genVec = genVec;
	m_leg1 = leg1;
	m_leg2 = leg2;
	m_CandidateEventType = CandidateEventType;	


	/* set some other info - need m_genVec to be set before this call */

	fillRecoIndependentInfo();


	/* perform the Run II MC Matching and classification of the two legs
	based on Run II guidelines */
	// see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HiggsToTauTauWorking2015#MC_Matching

	
	checkLegsForEorMuorGenJetMatches(1);
	checkLegsForEorMuorGenJetMatches(2);

	// std::cout<<" leg 1 mc match is type "<<m_leg1_MCMatchType<<" pdgId "<<m_leg1_MCMatchPdgId<<" pt "<<m_leg1_genMCmatch_pt<<"\n";
	// std::cout<<" leg 2 mc match is type "<<m_leg2_MCMatchType<<" pdgId "<<m_leg2_MCMatchPdgId<<" pt "<<m_leg2_genMCmatch_pt<<"\n";

	/* now classify the event, only valid for DY MC */
	classifyTheEventForRun2_DY();	


}


// helpers 

/* set the Run II leg matches to gen E or Mu or genJet */
/* this function fills member data if matches are found */
/* the argument legIndex = 1 for leg1, 2 for leg2, 3 for EffCand */

void GenHelper::checkLegsForEorMuorGenJetMatches(int legIndex) 
{
	/* only 1 or 2 are valid values for arg legIndex */
	assert(legIndex==1 || legIndex==2 || legIndex==3);

	if(legIndex==3)
	{
		temp_effLep_MCMatchType = -999;
	    temp_effLep_genMCmatch_pt = NAN;
    	temp_effLep_genMCmatch_eta = NAN;
	    temp_effLep_genMCmatch_phi = NAN;
    	temp_effLep_genMCmatch_M = NAN;
	    temp_effLep_MCMatchPdgId = -999;
	}


	TLorentzVector leg, genTemp, genTauJet;

	if(legIndex==1) leg.SetPtEtaPhiM(m_leg1.p4().pt(), m_leg1.p4().eta(), m_leg1.p4().phi(), m_leg1.p4().M());
	else if(legIndex==2) leg.SetPtEtaPhiM(m_leg2.p4().pt(), m_leg2.p4().eta(), m_leg2.p4().phi(), m_leg2.p4().M());
	else if(legIndex==3) leg.SetPtEtaPhiM(temp_effLep.p4().pt(), temp_effLep.p4().eta(), temp_effLep.p4().phi(), temp_effLep.p4().M());

		// std::cout<<" check--> lepton pt "<<leg.Pt()<<"\n";
		// std::cout<<"check--> gen particle size "<<m_genParticle_pdgId.size()<<"\n";

	for(std::size_t g = 0; g < m_genParticle_pdgId.size(); ++g)
	{

		/* zero 4-vector */
		genTemp.SetPtEtaPhiM(0,0,0,0);

		// std::cout<<" check-->  genTemp pt "<<genTemp.Pt()<<"\n";


		/* check for promptElectron/promptMuon/tauToElectronDecay/tauToMuonDecay */
		if(abs(m_genParticle_pdgId[g].second) == 11 ||  abs(m_genParticle_pdgId[g].second) == 13)
		{

			if(m_genParticle_pt[g].second > 8)
			{

				genTemp.SetPtEtaPhiM(m_genParticle_pt[g].second, m_genParticle_eta[g].second, 
									 m_genParticle_phi[g].second, m_genParticle_M[g].second);

				if(leg.DeltaR(genTemp) < MCdrMatchRun2)
				{

					if(m_genParticle_isPrompt[g].second == 1 || m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
					{
						if(legIndex==1)
						{
							m_leg1_genMCmatch_pt = m_genParticle_pt[g].second;
							m_leg1_genMCmatch_eta = m_genParticle_eta[g].second;
							m_leg1_genMCmatch_phi = m_genParticle_phi[g].second;
							m_leg1_genMCmatch_M = m_genParticle_M[g].second;
							m_leg1_MCMatchPdgId = m_genParticle_pdgId[g].second;
							
							if(abs(m_genParticle_pdgId[g].second) == 11 && m_genParticle_isPrompt[g].second == 1)
							{
								m_leg1_MCMatchType = GenMcMatchTypes::promptElectron;
							}
							else if(abs(m_genParticle_pdgId[g].second) == 11 && m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
							{
								m_leg1_MCMatchType = GenMcMatchTypes::tauToElectronDecay;
							}

							else if(abs(m_genParticle_pdgId[g].second) == 13 && m_genParticle_isPrompt[g].second == 1)
							{
								m_leg1_MCMatchType = GenMcMatchTypes::promptMuon;
							}
							else if(abs(m_genParticle_pdgId[g].second) == 13 && m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
							{
								m_leg1_MCMatchType = GenMcMatchTypes::tauToMuonDecay;
							}


						}
						else if(legIndex==2)
						{
							m_leg2_genMCmatch_pt = m_genParticle_pt[g].second;
							m_leg2_genMCmatch_eta = m_genParticle_eta[g].second;
							m_leg2_genMCmatch_phi = m_genParticle_phi[g].second;
							m_leg2_genMCmatch_M = m_genParticle_M[g].second;
							m_leg2_MCMatchPdgId = m_genParticle_pdgId[g].second;

							if(abs(m_genParticle_pdgId[g].second) == 11 && m_genParticle_isPrompt[g].second == 1)
							{
								m_leg2_MCMatchType = GenMcMatchTypes::promptElectron;
							}
							else if(abs(m_genParticle_pdgId[g].second) == 11 && m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
							{
								m_leg2_MCMatchType = GenMcMatchTypes::tauToElectronDecay;
							}

							else if(abs(m_genParticle_pdgId[g].second) == 13 && m_genParticle_isPrompt[g].second == 1)
							{
								m_leg2_MCMatchType = GenMcMatchTypes::promptMuon;
							}
							else if(abs(m_genParticle_pdgId[g].second) == 13 && m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
							{
								m_leg2_MCMatchType = GenMcMatchTypes::tauToMuonDecay;
							}
						}

						else if(legIndex==3)
						{							
							temp_effLep_genMCmatch_pt = m_genParticle_pt[g].second;
							temp_effLep_genMCmatch_eta = m_genParticle_eta[g].second;
							temp_effLep_genMCmatch_phi = m_genParticle_phi[g].second;
							temp_effLep_genMCmatch_M = m_genParticle_M[g].second;
							temp_effLep_MCMatchPdgId = m_genParticle_pdgId[g].second;

							if(abs(m_genParticle_pdgId[g].second) == 11 && m_genParticle_isPrompt[g].second == 1)
							{
								temp_effLep_MCMatchType = GenMcMatchTypes::promptElectron;
							}
							else if(abs(m_genParticle_pdgId[g].second) == 11 && m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
							{
								temp_effLep_MCMatchType = GenMcMatchTypes::tauToElectronDecay;
							}

							else if(abs(m_genParticle_pdgId[g].second) == 13 && m_genParticle_isPrompt[g].second == 1)
							{
								temp_effLep_MCMatchType = GenMcMatchTypes::promptMuon;
							}
							else if(abs(m_genParticle_pdgId[g].second) == 13 && m_genParticle_isDirectPromptTauDecayProduct[g].second == 1)
							{
								temp_effLep_MCMatchType = GenMcMatchTypes::tauToMuonDecay;
							}
						}

					}
				}

			}

		}

		/* check for hadronicTau */
		else if(abs(m_genParticle_pdgId[g].second) == 15 && m_genParticle_isPrompt[g].second == 1)
		{

			/* zero 4-vector */
			genTauJet.SetPtEtaPhiM(0,0,0,0);


			/* Build a Gen-tau jet, rebuilt by summing 4-momenta of visible gen tau decay products, 
			excluding electrons and muons. The pT of the gen tau jet should be >15 GeV. 
			Only consider the decay products of those gen taus that fulfill status flag IsPrompt. */


		    /* nested loop on daughters */
		    for(std::size_t gg = 0; gg < m_genDaughter_pdgId.size(); ++gg)
		    {

		    	TLorentzVector GenVecToSum(0,0,0,0);

		    
		      /* all daugthers of the current gen tau have first element == g	 */
		     
		    	if( m_genDaughter_pdgId[gg].first == (int)g ) 
		    	{
		    		/* should veto electrons, muons, and neutrinos */

		    		if( abs(m_genDaughter_pdgId[gg].second) != 11 &&\
		    			abs(m_genDaughter_pdgId[gg].second) != 12 &&\
		    			abs(m_genDaughter_pdgId[gg].second) != 13 &&\
		    			abs(m_genDaughter_pdgId[gg].second) != 14 &&\
		    			abs(m_genDaughter_pdgId[gg].second) != 15 &&\
		    			abs(m_genDaughter_pdgId[gg].second) != 16)
						{
		    				GenVecToSum.SetPtEtaPhiM(m_genDaughter_pt[gg].second, m_genDaughter_eta[gg].second,
											 m_genDaughter_phi[gg].second, m_genDaughter_M[gg].second);		    		 

			    			genTauJet += GenVecToSum;
			    		}	

		    	}	

		    }

		   // std::cout<<" check-->  genTauJet pt "<<genTauJet.Pt()<<"\n";


			if(leg.DeltaR(genTauJet) < MCdrMatchRun2 && genTauJet.Pt()>15)
			{

				if(legIndex==1 && m_leg1_MCMatchType==-999)
				{
					m_leg1_genMCmatch_pt = genTauJet.Pt();
					m_leg1_genMCmatch_eta = genTauJet.Eta();
					m_leg1_genMCmatch_phi = genTauJet.Phi();
					m_leg1_genMCmatch_M = genTauJet.M();
					m_leg1_MCMatchPdgId = m_genParticle_pdgId[g].second;
					m_leg1_MCMatchType = GenMcMatchTypes::hadronicTau;							
				}	

				else if(legIndex==2 && m_leg2_MCMatchType==-999)
				{
					m_leg2_genMCmatch_pt = genTauJet.Pt();
					m_leg2_genMCmatch_eta = genTauJet.Eta();
					m_leg2_genMCmatch_phi = genTauJet.Phi();
					m_leg2_genMCmatch_M = genTauJet.M();
					m_leg2_MCMatchPdgId = m_genParticle_pdgId[g].second;
					m_leg2_MCMatchType = GenMcMatchTypes::hadronicTau;							
				}	


				else if(legIndex==3 && temp_effLep_MCMatchType==-999)
				{
					temp_effLep_genMCmatch_pt = genTauJet.Pt();
					temp_effLep_genMCmatch_eta = genTauJet.Eta();
					temp_effLep_genMCmatch_phi = genTauJet.Phi();
					temp_effLep_genMCmatch_M = genTauJet.M();
					temp_effLep_MCMatchPdgId = m_genParticle_pdgId[g].second;
					temp_effLep_MCMatchType = GenMcMatchTypes::hadronicTau;							
				}	


		    	// std::cout<<" test : reco Pt "<<leg.Pt()<<" genJet Pt "<<genTauJet.Pt()<<" ";
		    	// if(legIndex==1 && m_leg1.leptonType()==TupleLeptonTypes::aTau ) std::cout<<" pat tau embedded gen jet pt = "<<m_leg1.genJet_p4().pt()<<"\n";
		    	// else if(legIndex==2 && m_leg2.leptonType()==TupleLeptonTypes::aTau )std::cout<<" pat tau embedded gen jet pt = "<<m_leg2.genJet_p4().pt()<<" ";
		    	// std::cout<<"\n";
		    }
		}

	}

	/* if reached here, and still no MC match, then likely a fake */
	if(legIndex==1 && m_leg1_MCMatchType==-999)
	{
					m_leg1_genMCmatch_pt = 0;
					m_leg1_genMCmatch_eta = 0;
					m_leg1_genMCmatch_phi = 0;
					m_leg1_genMCmatch_M = 0;
					m_leg1_MCMatchPdgId = 0;
					m_leg1_MCMatchType = GenMcMatchTypes::jetOrPuFake;
	}
	else if(legIndex==2 && m_leg2_MCMatchType==-999)
	{
					m_leg2_genMCmatch_pt = 0;
					m_leg2_genMCmatch_eta = 0;
					m_leg2_genMCmatch_phi = 0;
					m_leg2_genMCmatch_M = 0;
					m_leg2_MCMatchPdgId = 0;
					m_leg2_MCMatchType = GenMcMatchTypes::jetOrPuFake;
	}
	else if(legIndex==3 && temp_effLep_MCMatchType==-999)
	{
					temp_effLep_genMCmatch_pt = 0;
					temp_effLep_genMCmatch_eta = 0;
					temp_effLep_genMCmatch_phi = 0;
					temp_effLep_genMCmatch_M = 0;
					temp_effLep_MCMatchPdgId = 0;
					temp_effLep_MCMatchType = GenMcMatchTypes::jetOrPuFake;
	}


	if(legIndex==3)
	{
		m_effLep_MCMatchType.push_back(temp_effLep_MCMatchType);
		m_effLep_genMCmatch_pt.push_back(temp_effLep_genMCmatch_pt);
		m_effLep_genMCmatch_eta.push_back(temp_effLep_genMCmatch_eta);
		m_effLep_genMCmatch_phi.push_back(temp_effLep_genMCmatch_phi);
		m_effLep_genMCmatch_M.push_back(temp_effLep_genMCmatch_M);
		m_effLep_MCMatchPdgId.push_back(temp_effLep_MCMatchPdgId);

		// std::cout<<" have effLepton MC matches with type, genPt, recoPt, pdgID = "<<temp_effLep_MCMatchType<<" , "<<temp_effLep_genMCmatch_pt<<" , "<<temp_effLep.p4().pt()<<"  , "<<temp_effLep_MCMatchPdgId<<"\n";

	}


}


/* updated Run II DY classification (sets vals to IsZTT, IsZL, IsZJ,and IsZLL) */
void GenHelper::classifyTheEventForRun2_DY()
{

	 // code only valid if GenMcMatchTypes looks like this
     // promptElectron = 1,
     // promptMuon = 2,
     // tauToElectronDecay = 3,
     // tauToMuonDecay = 4,
     // hadronicTau = 5,
     // jetOrPuFake = 6

	/* reset */
	m_IsZTT = 0;
	m_IsZL = 0;
	m_IsZJ = 0;
	m_IsZLL = 0;

	int m1 = m_leg1_MCMatchType;
	int m2 = m_leg2_MCMatchType;
	int c12 = m_CandidateEventType;

	if(c12 == TupleCandidateEventTypes::EleTau || c12 == TupleCandidateEventTypes::MuonTau)
	{
		/* defined as : 
		ZTT : For etau and mutau channels: gen_match_2==5
		ZL :  For etau and mutau channels: gen_match_2<5
		ZJ :  For etau and mutau: gen_match_2==6
		ZLL : For etau, mutau and tautau channels = ZL+ZJ
		*/

		if(m2 == 5)    		 { m_IsZTT = 1; }
		else if(m2 < 5) 	 { m_IsZL = 1;  }
		else if(m2 == 6)	 { m_IsZJ = 1;  }
		if(m_IsZL || m_IsZJ) { m_IsZLL = 1; }


	}
	else if(c12 == TupleCandidateEventTypes::TauTau)
	{

		/* defined as : 
		ZTT : For tautau channel: gen_match_1==5 && gen_match_2==5;
		ZL :  For tautau channel: gen_match_1<6&&gen_match_2<6&&!(gen_match_1==5&&gen_match_2==5).
		ZJ :  For tautau channel: gen_match_2==6 or gen_match_1==6.
		ZLL : For etau, mutau and tautau channels = ZL+ZJ
		*/

		if(m1==5 && m2==5)       { m_IsZTT = 1; }
		else if(m1<6 && m2<6) 	 { m_IsZL = 1;  }
		else if(m1==6 || m2==6)	 { m_IsZJ = 1;  }
		if(m_IsZL || m_IsZJ)     { m_IsZLL = 1; }



	}
	else if(c12 == TupleCandidateEventTypes::EleMuon)
	{
		/* defined as : 
		ZTT : For emu channel: gen_match_1>2 && gen_match_2>3 
		ZL :  Not present in emu 
		ZJ :  Not present in emu 
		ZLL : For emu channel: gen_match_1< 3 or gen_match_2<4" 
		*/


		if(m1>2 && m2>3)  { m_IsZTT = 1; }
		else if(m1<3 || m2<4)     { m_IsZLL = 1; }
		m_IsZL = 0;
		m_IsZJ = 0;
	}


	// std::cout<<" PAIR IS ";
	// if(m_IsZTT) std::cout<<" ZTT ";
	// if(m_IsZL) std::cout<<" ZL ";
	// if(m_IsZJ) std::cout<<" ZJ ";
	// if(m_IsZLL) std::cout<<" ZLL ";
	// std::cout<<"\n";
}


/* OLD RUN I : assign DY classification : ZTT, ZL, ZJ, ZLL */
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


	int GenHelper::leg1_MCMatchType() { return m_leg1_MCMatchType; };
    double GenHelper::leg1_genMCmatch_pt() { return m_leg1_genMCmatch_pt; };
    double GenHelper::leg1_genMCmatch_eta() { return m_leg1_genMCmatch_eta; };
    double GenHelper::leg1_genMCmatch_phi() { return m_leg1_genMCmatch_phi; };
    double GenHelper::leg1_genMCmatch_M() { return m_leg1_genMCmatch_M; };
    int GenHelper::leg1_MCMatchPdgId() { return m_leg1_MCMatchPdgId; };

    int GenHelper::leg2_MCMatchType() { return m_leg2_MCMatchType; };
    double GenHelper::leg2_genMCmatch_pt() { return m_leg2_genMCmatch_pt; };
    double GenHelper::leg2_genMCmatch_eta() { return m_leg2_genMCmatch_eta; };
    double GenHelper::leg2_genMCmatch_phi() { return m_leg2_genMCmatch_phi; };
    double GenHelper::leg2_genMCmatch_M() { return m_leg2_genMCmatch_M; };
    int GenHelper::leg2_MCMatchPdgId() { return m_leg2_MCMatchPdgId; };



    std::vector<int> GenHelper::effLep_MCMatchType()  { return m_effLep_MCMatchType; };
    std::vector<double> GenHelper::effLep_genMCmatch_pt()  { return m_effLep_genMCmatch_pt; };
    std::vector<double> GenHelper::effLep_genMCmatch_eta()  { return m_effLep_genMCmatch_eta; };
    std::vector<double> GenHelper::effLep_genMCmatch_phi()  { return m_effLep_genMCmatch_phi; };
    std::vector<double> GenHelper::effLep_genMCmatch_M() { return m_effLep_genMCmatch_M; };
    std::vector<int> GenHelper::effLep_MCMatchPdgId() { return m_effLep_MCMatchPdgId; };



    int GenHelper::IsZTT() { return m_IsZTT; };
    int GenHelper::IsZL()  { return m_IsZL; };
    int GenHelper::IsZJ()  { return m_IsZJ; };
    int GenHelper::IsZLL() { return m_IsZLL; };


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
    std::vector<std::pair< int, int>> GenHelper::genParticle_fromHardProcess() {return m_genParticle_fromHardProcess;};
    std::vector<std::pair< int, int>> GenHelper::genParticle_isLastCopy() {return m_genParticle_isLastCopy;};


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
