#include "DavisRunIITauTau/FlatTupleGenerator/interface/JetHelper.h"



bool NtupleJetOrderCompare( const std::pair<double, NtupleJet>& p1, const std::pair<double, NtupleJet>& p2) 
{
	return p1.first > p2.first;	
}


/* constructor */

JetHelper::JetHelper(){}

/* initialization function for eff lepton vector */
/* no DR lep-jet cuts are applied here */

void JetHelper::init(std::vector<NtupleJet> jetVec, std::string jetCut, std::string bjetCut)
{

	/* setup the btag sf helper tool */

	edm::FileInPath sf_file = edm::FileInPath("DavisRunIITauTau/RunTimeDataInput/data/BTAGSF/CSVv2.csv");
	m_BtagSFTool = new bTagSFhelper(sf_file);


	m_PtJetPairs_fullyCorrected.clear();
	m_PtBJetPairs_fullyCorrected.clear();

	m_PtJetPairs_JECshiftedUp.clear();
	m_PtBJetPairs_JECshiftedUp.clear();

	m_PtJetPairs_JECshiftedDown.clear();
	m_PtBJetPairs_JECshiftedDown.clear();

	m_PtJetPairs_JERnomianl.clear();
	m_PtBJetPairs_JERnomianl.clear();

	m_PtJetPairs_JERup.clear();
	m_PtBJetPairs_JERup.clear();

	m_PtJetPairs_JERdown.clear();
	m_PtBJetPairs_JERdown.clear();


	/* create the cut selectors */

	StringCutObjectSelector<NtupleJet> jetSelector(jetCut);
	StringCutObjectSelector<NtupleJet> BjetSelector(bjetCut);

	/* begin loop over jets, and fill the unordered pt:jet vector of pair*/

	for(std::size_t j = 0; j < jetVec.size(); ++j) 
	{


		/* test eval and print the various b-tag SFs for this jet */
		/* see https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation76X */
		/* these all need to become python args (also the CSV file, isRealData too!)*/

		std::cout<<" ***** JetHelper.cc (m_BtagSFTool)  ... \n";
		std::cout<<"	these all need to become python args: \n";
		std::cout<<"	[b-tag Loose working point cut]  \n";
		std::cout<<"	[b-tag Medium working point cut] \n";
		std::cout<<"	[b-tag Tight working point cut]	\n";
		std::cout<<"	[isRealData] \n";
		std::cout<<"	(also the CSV file) ****** \n";

		jetVec[j].Use4VectorVariant("fullyCorrected");		
		if(jetVec[j].pt() >= 20.0 && fabs(jetVec[j].eta()) <= 2.4) /* btagging does not apply out of this range */
		{
			m_BtagSFTool->InitForJet(0.460, 0.800, 0.935, 
			 					jetVec[j].pt(), 
			 					jetVec[j].eta(), 
								jetVec[j].defaultBtagAlgorithm_RawScore(),
								jetVec[j].HADRON_flavour(),
								0);


			std::cout<<" Jet B-tag SFs [loose, looseUp, looseDn, med, medUp, medDn, tight, tightUp, tightDn] =  [ ";

			std::cout<<m_BtagSFTool->SF_LooseWpCentral()<<" , ";
			std::cout<<m_BtagSFTool->SF_LooseWpUp()<<" , ";
			std::cout<<m_BtagSFTool->SF_LooseWpDown()<<" , ";
			std::cout<<m_BtagSFTool->SF_MediumWpCentral()<<" , ";
			std::cout<<m_BtagSFTool->SF_MediumWpUp()<<" , ";
			std::cout<<m_BtagSFTool->SF_MediumWpDown()<<" , ";
			std::cout<<m_BtagSFTool->SF_TightWpCentral()<<" , ";
			std::cout<<m_BtagSFTool->SF_TightWpUp()<<" , ";
			std::cout<<m_BtagSFTool->SF_TightWpDown()<<" ] ";

			std::cout<<" init args were [pt, eta, rawScore, hadronFlav, isData ] = [ ";
			std::cout<<jetVec[j].pt()<<" , "<<jetVec[j].eta()<<" , "<<jetVec[j].defaultBtagAlgorithm_RawScore()<<" , "<<jetVec[j].HADRON_flavour()<<" , "<<0<<"] \n";

		}
		
		/* next check the jet ID & B jet ID, & if passes add to the pair vectors,
		allowing jets to enter both vectors - cause that is what H2Tau Does */

		jetVec[j].Use4VectorVariant("fullyCorrected");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JECshiftedUp");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JECshiftedDown");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JERnomianl");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JERup");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
	
		jetVec[j].Use4VectorVariant("JERdown");
		if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );

		// reset back to fullyCorrected just in case
		jetVec[j].Use4VectorVariant("fullyCorrected");



		std::cout<<" ----> in FlatTuple jethelper jet @ index "<<j;
		std::cout<<" fullyCorrected pT= "<<jetVec[j].pt()<<" with variants ... ";
		std::cout<<" RES_smeared= "<<jetVec[j].jet_p4_JERnomianl().pt();
		std::cout<<" RES_smearedUP= "<<jetVec[j].jet_p4_JERup().pt();
		std::cout<<" RES_smearedDN= "<<jetVec[j].jet_p4_JERdown().pt();
		std::cout<<" JECunc_UP= "<<jetVec[j].jet_p4_JECshiftedUp().pt();
		std::cout<<" JECunc_DN= "<<jetVec[j].jet_p4_JECshiftedDown().pt();
		std::cout<<" cycling through the variants now using  Use4VectorVariant ... ";

		jetVec[j].Use4VectorVariant("JERnomianl");  std::cout<<" "<<jetVec[j].pt();
		jetVec[j].Use4VectorVariant("JERup");  std::cout<<" "<<jetVec[j].pt();
		jetVec[j].Use4VectorVariant("JERdown");  std::cout<<" "<<jetVec[j].pt();
		jetVec[j].Use4VectorVariant("JECshiftedUp");  std::cout<<" "<<jetVec[j].pt();
		jetVec[j].Use4VectorVariant("JECshiftedDown");  std::cout<<" "<<jetVec[j].pt();

		std::cout<<" back to nominal ...";

		jetVec[j].Use4VectorVariant("fullyCorrected");  std::cout<<" "<<jetVec[j].pt()<<"\n";

	}

	std::cout<<" check size of different jet variant collections ";
	std::cout<<" fullyCorrected pT= "<<m_PtJetPairs_fullyCorrected.size();
	std::cout<<" RES_smeared= "<<m_PtJetPairs_JECshiftedUp.size();
	std::cout<<" RES_smearedUP= "<<m_PtJetPairs_JECshiftedDown.size();
	std::cout<<" RES_smearedDN= "<<m_PtJetPairs_JERnomianl.size();
	std::cout<<" JECunc_UP= "<<m_PtJetPairs_JERup.size();
	std::cout<<" JECunc_DN= "<<m_PtJetPairs_JERdown.size()<<"\n";


} 



/* initialization function for regular leg1 + leg2 candidate pair */

void JetHelper::init(std::vector<NtupleJet> jetVec, std::string jetCut, std::string bjetCut,
					double minDR, NtupleLepton leg1, NtupleLepton leg2)
{

	m_PtJetPairs_fullyCorrected.clear();
	m_PtBJetPairs_fullyCorrected.clear();

	m_PtJetPairs_JECshiftedUp.clear();
	m_PtBJetPairs_JECshiftedUp.clear();

	m_PtJetPairs_JECshiftedDown.clear();
	m_PtBJetPairs_JECshiftedDown.clear();

	m_PtJetPairs_JERnomianl.clear();
	m_PtBJetPairs_JERnomianl.clear();

	m_PtJetPairs_JERup.clear();
	m_PtBJetPairs_JERup.clear();

	m_PtJetPairs_JERdown.clear();
	m_PtBJetPairs_JERdown.clear();



	/* create the cut selectors */

	StringCutObjectSelector<NtupleJet> jetSelector(jetCut);
	StringCutObjectSelector<NtupleJet> BjetSelector(bjetCut);

	/* begin loop over jets, and fill the unordered pt:jet vector of pair*/

	for(std::size_t j = 0; j < jetVec.size(); ++j) 
	{


		/*  check the DR, jet ID & B jet ID, & if passes add to the pair vectors,
		allowing jets to enter both vectors - cause that is what H2Tau Does */

		jetVec[j].Use4VectorVariant("fullyCorrected");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JECshiftedUp");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JECshiftedDown");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}			

		jetVec[j].Use4VectorVariant("JERnomianl");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JERup");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		}	

		jetVec[j].Use4VectorVariant("JERdown");
		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
		{
			if(	jetSelector(jetVec[j]) ) m_PtJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
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


	std::vector<NtupleJet> JetHelper::PtOrderedPassingBJets(std::string variant_)
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
	      std::sort(m_PtBJetPairs_fullyCorrected.begin(), m_PtBJetPairs_fullyCorrected.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtBJetPairs_fullyCorrected;
        }
    	else if(variant_ == "JECshiftedUp")
    	{
	      std::sort(m_PtBJetPairs_JECshiftedUp.begin(), m_PtBJetPairs_JECshiftedUp.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtBJetPairs_JECshiftedUp;
        }
    	else if(variant_ == "JECshiftedDown")
    	{
	      std::sort(m_PtBJetPairs_JECshiftedDown.begin(), m_PtBJetPairs_JECshiftedDown.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtBJetPairs_JECshiftedDown;
        }
    	else if(variant_ == "JERnomianl")
    	{
	      std::sort(m_PtBJetPairs_JERnomianl.begin(), m_PtBJetPairs_JERnomianl.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtBJetPairs_JERnomianl;
        }
    	else if(variant_ == "JERup")
    	{
	      std::sort(m_PtBJetPairs_JERup.begin(), m_PtBJetPairs_JERup.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtBJetPairs_JERup;
        }                
    	else if(variant_ == "JERdown")
    	{
	      std::sort(m_PtBJetPairs_JERdown.begin(), m_PtBJetPairs_JERdown.end(), NtupleJetOrderCompare);
     	  temp_pair = m_PtBJetPairs_JERdown;
        }


		for(std::size_t k = 0; k<temp_pair.size(); ++k)
		{
			returnVec.push_back(temp_pair[k].second);	
		}

		return returnVec;

  	}
