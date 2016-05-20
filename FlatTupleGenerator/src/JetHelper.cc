#include "DavisRunIITauTau/FlatTupleGenerator/interface/JetHelper.h"



bool NtupleJetOrderCompare( const std::pair<double, NtupleJet>& p1, const std::pair<double, NtupleJet>& p2) 
{
	return p1.first > p2.first;	
}


/* constructor */

JetHelper::JetHelper(){}

/* initialization function for eff lepton vector */
/* no DR lep-jet cuts are applied here */

void JetHelper::init(std::vector<NtupleJet> jetVec, std::string jetCut, bTagSFhelper  m_BtagSFTool, bool isRealData)
{



	m_PtJetPairs_fullyCorrected.clear();

	m_PtJetPairs_JECshiftedUp.clear();

	m_PtJetPairs_JECshiftedDown.clear();

	m_PtJetPairs_JERnomianl.clear();

	m_PtJetPairs_JERup.clear();

	m_PtJetPairs_JERdown.clear();


	/* create the cut selectors */

	StringCutObjectSelector<NtupleJet> jetSelector(jetCut);

	/* begin loop over jets, and fill the unordered pt:jet vector of pair*/

	for(std::size_t j = 0; j < jetVec.size(); ++j) 
	{


		/* test eval and print the various b-tag SFs for this jet */
		/* see https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X */
		/* these all need to become python args (also the CSV file!)
		   sf will be stored for data, mc, and embedded samples
		   but should only be used in mc and embedded samples where the b-jets are MC (like top)	
		*/

	

		jetVec[j].Use4VectorVariant("fullyCorrected");		
		if(jetVec[j].pt() >= 20.0 && fabs(jetVec[j].eta()) <= 2.4) /* btagging does not apply out of this range */
		{
			m_BtagSFTool.InitForJet(jetVec[j].pt(), 
			 					jetVec[j].eta(), 
								jetVec[j].defaultBtagAlgorithm_RawScore(),
								jetVec[j].HADRON_flavour(), isRealData);


			/* set the Btag SFs for the current jet */
				
			jetVec[j].set_defaultBtagAlgorithmSF_LooseWpCentral(m_BtagSFTool.SF_LooseWpCentral());
			jetVec[j].set_defaultBtagAlgorithmSF_LooseWpUp(m_BtagSFTool.SF_LooseWpUp());
			jetVec[j].set_defaultBtagAlgorithmSF_LooseWpDown(m_BtagSFTool.SF_LooseWpDown());

			jetVec[j].set_defaultBtagAlgorithmSF_MediumWpCentral(m_BtagSFTool.SF_MediumWpCentral());
			jetVec[j].set_defaultBtagAlgorithmSF_MediumWpUp(m_BtagSFTool.SF_MediumWpUp());
			jetVec[j].set_defaultBtagAlgorithmSF_MediumWpDown(m_BtagSFTool.SF_MediumWpDown());

			jetVec[j].set_defaultBtagAlgorithmSF_TightWpCentral(m_BtagSFTool.SF_TightWpCentral());
			jetVec[j].set_defaultBtagAlgorithmSF_TightWpUp(m_BtagSFTool.SF_TightWpUp());
			jetVec[j].set_defaultBtagAlgorithmSF_TightWpDown(m_BtagSFTool.SF_TightWpDown());


			/* set the b-tag eff. for the current jet */

			jetVec[j].set_defaultBtagAlgorithmEff_LooseWp(m_BtagSFTool.EFF_LooseWp());
			jetVec[j].set_defaultBtagAlgorithmEff_MediumWp(m_BtagSFTool.EFF_MediumWp());
			jetVec[j].set_defaultBtagAlgorithmEff_TightWp(m_BtagSFTool.EFF_TightWp());


			/* set the Btag Pass/Fail tags (after SFs) for the current jet */
		

			jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpCentral(m_BtagSFTool.IsTagged_LooseWpCentral());
			jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpUp(m_BtagSFTool.IsTagged_LooseWpUp());
			jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpDown(m_BtagSFTool.IsTagged_LooseWpDown());

			jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpCentral(m_BtagSFTool.IsTagged_MediumWpCentral());
			jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpUp(m_BtagSFTool.IsTagged_MediumWpUp());
			jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpDown(m_BtagSFTool.IsTagged_MediumWpDown());

			jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpCentral(m_BtagSFTool.IsTagged_TightWpCentral());
			jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpUp(m_BtagSFTool.IsTagged_TightWpUp());
			jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpDown(m_BtagSFTool.IsTagged_TightWpDown());




			// std::cout<<" Jet b-tag Eff [l, m, t] = [ ";
			// std::cout<<jetVec[j].defaultBtagAlgorithmEff_LooseWp()<<" , ";
			// std::cout<<jetVec[j].defaultBtagAlgorithmEff_MediumWp()<<" , ";
			// std::cout<<jetVec[j].defaultBtagAlgorithmEff_TightWp()<<" ] \n ";







			std::cout<<" Jet B-tag SFs [loose, looseUp, looseDn, med, medUp, medDn, tight, tightUp, tightDn] =  [ ";

			std::cout<<m_BtagSFTool.SF_LooseWpCentral()<<" , ";
			std::cout<<m_BtagSFTool.SF_LooseWpUp()<<" , ";
			std::cout<<m_BtagSFTool.SF_LooseWpDown()<<" , ";
			std::cout<<m_BtagSFTool.SF_MediumWpCentral()<<" , ";
			std::cout<<m_BtagSFTool.SF_MediumWpUp()<<" , ";
			std::cout<<m_BtagSFTool.SF_MediumWpDown()<<" , ";
			std::cout<<m_BtagSFTool.SF_TightWpCentral()<<" , ";
			std::cout<<m_BtagSFTool.SF_TightWpUp()<<" , ";
			std::cout<<m_BtagSFTool.SF_TightWpDown()<<" ] ";

			std::cout<<" init args were [pt, eta, rawScore, hadronFlav  ] = [ ";
			std::cout<<jetVec[j].pt()<<" , "<<jetVec[j].eta()<<" , "<<jetVec[j].defaultBtagAlgorithm_RawScore()<<" , "<<jetVec[j].HADRON_flavour()<<" ] \n";

		}
		
		/* next check the jet ID & B jet ID, & if passes add to the pair vectors,
		allowing jets to enter both vectors - cause that is what H2Tau Does */

		jetVec[j].Use4VectorVariant("fullyCorrected");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JECshiftedUp");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JECshiftedDown");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JERnomianl");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JERup");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JERdown");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );

		// reset back to fullyCorrected just in case
		jetVec[j].Use4VectorVariant("fullyCorrected");



		// std::cout<<" ----> in FlatTuple jethelper jet @ index "<<j;
		// std::cout<<" fullyCorrected pT= "<<jetVec[j].pt()<<" with variants ... ";
		// std::cout<<" RES_smeared= "<<jetVec[j].jet_p4_JERnomianl().pt();
		// std::cout<<" RES_smearedUP= "<<jetVec[j].jet_p4_JERup().pt();
		// std::cout<<" RES_smearedDN= "<<jetVec[j].jet_p4_JERdown().pt();
		// std::cout<<" JECunc_UP= "<<jetVec[j].jet_p4_JECshiftedUp().pt();
		// std::cout<<" JECunc_DN= "<<jetVec[j].jet_p4_JECshiftedDown().pt();
		// std::cout<<" cycling through the variants now using  Use4VectorVariant ... ";

		// jetVec[j].Use4VectorVariant("JERnomianl");  std::cout<<" "<<jetVec[j].pt();
		// jetVec[j].Use4VectorVariant("JERup");  std::cout<<" "<<jetVec[j].pt();
		// jetVec[j].Use4VectorVariant("JERdown");  std::cout<<" "<<jetVec[j].pt();
		// jetVec[j].Use4VectorVariant("JECshiftedUp");  std::cout<<" "<<jetVec[j].pt();
		// jetVec[j].Use4VectorVariant("JECshiftedDown");  std::cout<<" "<<jetVec[j].pt();

		// std::cout<<" back to nominal ...";

		// jetVec[j].Use4VectorVariant("fullyCorrected");  std::cout<<" "<<jetVec[j].pt()<<"\n";

	}

	// std::cout<<" check size of different jet variant collections ";
	// std::cout<<" fullyCorrected pT= "<<m_PtJetPairs_fullyCorrected.size();
	// std::cout<<" RES_smeared= "<<m_PtJetPairs_JECshiftedUp.size();
	// std::cout<<" RES_smearedUP= "<<m_PtJetPairs_JECshiftedDown.size();
	// std::cout<<" RES_smearedDN= "<<m_PtJetPairs_JERnomianl.size();
	// std::cout<<" JECunc_UP= "<<m_PtJetPairs_JERup.size();
	// std::cout<<" JECunc_DN= "<<m_PtJetPairs_JERdown.size()<<"\n";


} 



/* initialization function for regular leg1 + leg2 candidate pair */


void JetHelper::init(std::vector<NtupleJet> jetVec, std::string jetCut,
					double minDR, NtupleLepton leg1, NtupleLepton leg2, bTagSFhelper  m_BtagSFTool, bool isRealData)
{

	m_PtJetPairs_fullyCorrected.clear();

	m_PtJetPairs_JECshiftedUp.clear();

	m_PtJetPairs_JECshiftedDown.clear();

	m_PtJetPairs_JERnomianl.clear();

	m_PtJetPairs_JERup.clear();

	m_PtJetPairs_JERdown.clear();



	/* create the cut selectors */

	StringCutObjectSelector<NtupleJet> jetSelector(jetCut);

	/* begin loop over jets, and fill the unordered pt:jet vector of pair*/

	for(std::size_t j = 0; j < jetVec.size(); ++j) 
	{


		/*  check the DR, jet ID & B jet ID, & if passes add to the pair vectors,
		allowing jets to enter both vectors - cause that is what H2Tau Does */

		jetVec[j].Use4VectorVariant("fullyCorrected");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JECshiftedUp");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JECshiftedDown");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}			

		jetVec[j].Use4VectorVariant("JERnomianl");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JERup");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JERdown");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}					

		// reset back to fullyCorrected just in case
		jetVec[j].Use4VectorVariant("fullyCorrected");


	}

} 

// getters

	std::vector<NtupleJet> JetHelper::PtOrderedPassingJets(std::string variant_)
 	{

	    assert(variant_ == "fullyCorrected" ||\
	           variant_ == "JECshiftedUp" ||\
	           variant_ == "JECshiftedDown" ||\
	           variant_ == "JERnomianl" ||\
	           variant_ == "JERup" ||\
	           variant_ == "JERdown");


 		std::vector <NtupleJet> returnVec;
 		std::vector<std::pair<double, NtupleJet>> temp_pair;

 		/* seems jets are already ranked in mini-AOD, but just to be safe under future JEC variants */
    	if(variant_ == "fullyCorrected")
    	{
	      std::sort(m_PtJetPairs_fullyCorrected.begin(), m_PtJetPairs_fullyCorrected.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtJetPairs_fullyCorrected;
        }
    	else if(variant_ == "JECshiftedUp")
    	{
	      std::sort(m_PtJetPairs_JECshiftedUp.begin(), m_PtJetPairs_JECshiftedUp.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtJetPairs_JECshiftedUp;
        }
    	else if(variant_ == "JECshiftedDown")
    	{
	      std::sort(m_PtJetPairs_JECshiftedDown.begin(), m_PtJetPairs_JECshiftedDown.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtJetPairs_JECshiftedDown;
        }
    	else if(variant_ == "JERnomianl")
    	{
	      std::sort(m_PtJetPairs_JERnomianl.begin(), m_PtJetPairs_JERnomianl.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtJetPairs_JERnomianl;
        }
    	else if(variant_ == "JERup")
    	{
	      std::sort(m_PtJetPairs_JERup.begin(), m_PtJetPairs_JERup.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtJetPairs_JERup;
        }                
    	else if(variant_ == "JERdown")
    	{
	      std::sort(m_PtJetPairs_JERdown.begin(), m_PtJetPairs_JERdown.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtJetPairs_JERdown;
        }


		for(std::size_t k = 0; k<temp_pair.size(); ++k)
		{
			returnVec.push_back(temp_pair[k].second);	
		}

		return returnVec;

  	}


