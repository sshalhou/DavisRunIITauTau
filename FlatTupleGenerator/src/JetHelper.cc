#include "DavisRunIITauTau/FlatTupleGenerator/interface/JetHelper.h"



bool NtupleJetOrderCompare( const std::pair<double, NtupleJet>& p1, const std::pair<double, NtupleJet>& p2) 
{
	return p1.first > p2.first;	
}


/* constructor */

JetHelper::JetHelper(){}

/* initialization function for eff lepton vector */
/* no DR lep-jet cuts are applied here */

void JetHelper::init(std::vector<NtupleJet> jetVec, std::string jetCut, bTagSFhelper * m_BtagSFTool, bool isRealData)
{

	/* reset the jet vectors */

	m_PtJetPairs_fullyCorrected.clear();
	m_PtJetPairs_JECshiftedUp.clear();
	m_PtJetPairs_JECshiftedDown.clear();
	m_PtJetPairs_JERnomianl.clear();
	m_PtJetPairs_JERup.clear();
	m_PtJetPairs_JERdown.clear();

	/* reset the b-tag SF vectors */
	SF_fullyCorrected.clear();
	SFup_fullyCorrected.clear();
	SFdown_fullyCorrected.clear();
	
	SF_JECshiftedUp.clear();
	SFup_JECshiftedUp.clear();
	SFdown_JECshiftedUp.clear();
	
	SF_JECshiftedDown.clear();
	SFup_JECshiftedDown.clear();
	SFdown_JECshiftedDown.clear();
	
	SF_JERnomianl.clear();
	SFup_JERnomianl.clear();
	SFdown_JERnomianl.clear();
	
	SF_JERup.clear();
	SFup_JERup.clear();
	SFdown_JERup.clear();
	
	SF_JERdown.clear();
	SFup_JERdown.clear();
	SFdown_JERdown.clear();



	LOOSE_SF_fullyCorrected.clear();
	LOOSE_SFup_fullyCorrected.clear();
	LOOSE_SFdown_fullyCorrected.clear();
	
	LOOSE_SF_JECshiftedUp.clear();
	LOOSE_SFup_JECshiftedUp.clear();
	LOOSE_SFdown_JECshiftedUp.clear();
	
	LOOSE_SF_JECshiftedDown.clear();
	LOOSE_SFup_JECshiftedDown.clear();
	LOOSE_SFdown_JECshiftedDown.clear();
	
	LOOSE_SF_JERnomianl.clear();
	LOOSE_SFup_JERnomianl.clear();
	LOOSE_SFdown_JERnomianl.clear();
	
	LOOSE_SF_JERup.clear();
	LOOSE_SFup_JERup.clear();
	LOOSE_SFdown_JERup.clear();
	
	LOOSE_SF_JERdown.clear();
	LOOSE_SFup_JERdown.clear();
	LOOSE_SFdown_JERdown.clear();

	/* create container to hold all jet systematic levels */
	std::string jetSysArray[6] = {"fullyCorrected","JECshiftedUp","JECshiftedDown","JERnomianl","JERup","JERdown"};

	/* create the cut selector */
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

		
		/* looping through the different jet systematics */	
		for(int sys=0; sys<6; sys++)	   
		{

			/* switch to the sys 4-vector */
			jetVec[j].Use4VectorVariant(jetSysArray[sys]);		

			/* check b-tags */
			if(jetVec[j].pt() >= 20.0 && fabs(jetVec[j].eta()) <= 2.4) /* btagging does not apply out of this range */
			{


				m_BtagSFTool->InitForJet(jetVec[j].pt(), 
				 					jetVec[j].eta(), 
									jetVec[j].defaultBtagAlgorithm_RawScore(),
									jetVec[j].PARTON_flavour(), isRealData);
									/* wisconsin uses PARTON_flavour we used to use HADRON_flavour */


				/* set the Btag SFs for the current jet */

				jetVec[j].set_defaultBtagAlgorithmSF_LooseWpCentral(m_BtagSFTool->SF_LooseWpCentral());
				jetVec[j].set_defaultBtagAlgorithmSF_LooseWpUp(m_BtagSFTool->SF_LooseWpUp());
				jetVec[j].set_defaultBtagAlgorithmSF_LooseWpDown(m_BtagSFTool->SF_LooseWpDown());

				jetVec[j].set_defaultBtagAlgorithmSF_MediumWpCentral(m_BtagSFTool->SF_MediumWpCentral());
				jetVec[j].set_defaultBtagAlgorithmSF_MediumWpUp(m_BtagSFTool->SF_MediumWpUp());
				jetVec[j].set_defaultBtagAlgorithmSF_MediumWpDown(m_BtagSFTool->SF_MediumWpDown());

				jetVec[j].set_defaultBtagAlgorithmSF_TightWpCentral(m_BtagSFTool->SF_TightWpCentral());
				jetVec[j].set_defaultBtagAlgorithmSF_TightWpUp(m_BtagSFTool->SF_TightWpUp());
				jetVec[j].set_defaultBtagAlgorithmSF_TightWpDown(m_BtagSFTool->SF_TightWpDown());


				/* for b-tag SF wisconsin seems to cut at 30 instead of 20 */
				if(jetSelector(jetVec[j]) && jetVec[j].pt() >= 30.0 && fabs(jetVec[j].eta()) <= 2.4 && jetVec[j].defaultBtagAlgorithm_RawScore()>m_BtagSFTool->getCutPointMedium())
				{
					/* store the medium WP scale factors for the correct jet variant */
					if(	jetSysArray[sys]=="fullyCorrected") 			
					{		
						SF_fullyCorrected.push_back(m_BtagSFTool->SF_MediumWpCentral());
						SFup_fullyCorrected.push_back(m_BtagSFTool->SF_MediumWpUp());
						SFdown_fullyCorrected.push_back(m_BtagSFTool->SF_MediumWpDown());
					}	
					if(	jetSysArray[sys]=="JECshiftedUp" ) 
					{		
						SF_JECshiftedUp.push_back(m_BtagSFTool->SF_MediumWpCentral());
						SFup_JECshiftedUp.push_back(m_BtagSFTool->SF_MediumWpUp());
						SFdown_JECshiftedUp.push_back(m_BtagSFTool->SF_MediumWpDown());
					}				
					if(	jetSysArray[sys]=="JECshiftedDown" ) 
					{		
						SF_JECshiftedDown.push_back(m_BtagSFTool->SF_MediumWpCentral());
						SFup_JECshiftedDown.push_back(m_BtagSFTool->SF_MediumWpUp());
						SFdown_JECshiftedDown.push_back(m_BtagSFTool->SF_MediumWpDown());
					}				
					if(	jetSysArray[sys]=="JERnomianl" ) 
					{		
						SF_JERnomianl.push_back(m_BtagSFTool->SF_MediumWpCentral());
						SFup_JERnomianl.push_back(m_BtagSFTool->SF_MediumWpUp());
						SFdown_JERnomianl.push_back(m_BtagSFTool->SF_MediumWpDown());
					}			
					if(	jetSysArray[sys]=="JERup" ) 
					{		
						SF_JERup.push_back(m_BtagSFTool->SF_MediumWpCentral());
						SFup_JERup.push_back(m_BtagSFTool->SF_MediumWpUp());
						SFdown_JERup.push_back(m_BtagSFTool->SF_MediumWpDown());
					}				
					if(	jetSysArray[sys]=="JERdown" ) 
					{		
						SF_JERdown.push_back(m_BtagSFTool->SF_MediumWpCentral());
						SFup_JERdown.push_back(m_BtagSFTool->SF_MediumWpUp());
						SFdown_JERdown.push_back(m_BtagSFTool->SF_MediumWpDown());
					}	
				}


				/* for b-tag SF wisconsin seems to cut at 30 instead of 20 */
				if(jetSelector(jetVec[j]) && jetVec[j].pt() >= 30.0 && fabs(jetVec[j].eta()) <= 2.4 && jetVec[j].defaultBtagAlgorithm_RawScore()>m_BtagSFTool->getCutPointLoose())
				{
					/* store the Loose WP scale factors for the correct jet variant */
					if(	jetSysArray[sys]=="fullyCorrected") 			
					{		
						LOOSE_SF_fullyCorrected.push_back(m_BtagSFTool->SF_LooseWpCentral());
						LOOSE_SFup_fullyCorrected.push_back(m_BtagSFTool->SF_LooseWpUp());
						LOOSE_SFdown_fullyCorrected.push_back(m_BtagSFTool->SF_LooseWpDown());
					}	
					if(	jetSysArray[sys]=="JECshiftedUp" ) 
					{		
						LOOSE_SF_JECshiftedUp.push_back(m_BtagSFTool->SF_LooseWpCentral());
						LOOSE_SFup_JECshiftedUp.push_back(m_BtagSFTool->SF_LooseWpUp());
						LOOSE_SFdown_JECshiftedUp.push_back(m_BtagSFTool->SF_LooseWpDown());
					}				
					if(	jetSysArray[sys]=="JECshiftedDown" ) 
					{		
						LOOSE_SF_JECshiftedDown.push_back(m_BtagSFTool->SF_LooseWpCentral());
						LOOSE_SFup_JECshiftedDown.push_back(m_BtagSFTool->SF_LooseWpUp());
						LOOSE_SFdown_JECshiftedDown.push_back(m_BtagSFTool->SF_LooseWpDown());
					}				
					if(	jetSysArray[sys]=="JERnomianl" ) 
					{		
						LOOSE_SF_JERnomianl.push_back(m_BtagSFTool->SF_LooseWpCentral());
						LOOSE_SFup_JERnomianl.push_back(m_BtagSFTool->SF_LooseWpUp());
						LOOSE_SFdown_JERnomianl.push_back(m_BtagSFTool->SF_LooseWpDown());
					}			
					if(	jetSysArray[sys]=="JERup" ) 
					{		
						LOOSE_SF_JERup.push_back(m_BtagSFTool->SF_LooseWpCentral());
						LOOSE_SFup_JERup.push_back(m_BtagSFTool->SF_LooseWpUp());
						LOOSE_SFdown_JERup.push_back(m_BtagSFTool->SF_LooseWpDown());
					}				
					if(	jetSysArray[sys]=="JERdown" ) 
					{		
						LOOSE_SF_JERdown.push_back(m_BtagSFTool->SF_LooseWpCentral());
						LOOSE_SFup_JERdown.push_back(m_BtagSFTool->SF_LooseWpUp());
						LOOSE_SFdown_JERdown.push_back(m_BtagSFTool->SF_LooseWpDown());
					}	
				}



				/* set the b-tag eff. for the current jet */

				jetVec[j].set_defaultBtagAlgorithmEff_LooseWp(m_BtagSFTool->EFF_LooseWp());
				jetVec[j].set_defaultBtagAlgorithmEff_MediumWp(m_BtagSFTool->EFF_MediumWp());
				jetVec[j].set_defaultBtagAlgorithmEff_TightWp(m_BtagSFTool->EFF_TightWp());


				/* set the Btag Pass/Fail tags (after SFs) for the current jet */
			

				jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpCentral(m_BtagSFTool->IsTagged_LooseWpCentral());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpUp(m_BtagSFTool->IsTagged_LooseWpUp());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpDown(m_BtagSFTool->IsTagged_LooseWpDown());

				jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpCentral(m_BtagSFTool->IsTagged_MediumWpCentral());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpUp(m_BtagSFTool->IsTagged_MediumWpUp());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpDown(m_BtagSFTool->IsTagged_MediumWpDown());

				jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpCentral(m_BtagSFTool->IsTagged_TightWpCentral());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpUp(m_BtagSFTool->IsTagged_TightWpUp());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpDown(m_BtagSFTool->IsTagged_TightWpDown());




				// std::cout<<" Jet b-tag Eff [l, m, t] = [ ";
				// std::cout<<jetVec[j].defaultBtagAlgorithmEff_LooseWp()<<" , ";
				// std::cout<<jetVec[j].defaultBtagAlgorithmEff_MediumWp()<<" , ";
				// std::cout<<jetVec[j].defaultBtagAlgorithmEff_TightWp()<<" ] \n ";


				// std::cout<<" Jet B-tag SFs [loose, looseUp, looseDn, med, medUp, medDn, tight, tightUp, tightDn] =  [ ";

				// std::cout<<m_BtagSFTool->SF_LooseWpCentral()<<" , ";
				// std::cout<<m_BtagSFTool->SF_LooseWpUp()<<" , ";
				// std::cout<<m_BtagSFTool->SF_LooseWpDown()<<" , ";
				// std::cout<<m_BtagSFTool->SF_MediumWpCentral()<<" , ";
				// std::cout<<m_BtagSFTool->SF_MediumWpUp()<<" , ";
				// std::cout<<m_BtagSFTool->SF_MediumWpDown()<<" , ";
				// std::cout<<m_BtagSFTool->SF_TightWpCentral()<<" , ";
				// std::cout<<m_BtagSFTool->SF_TightWpUp()<<" , ";
				// std::cout<<m_BtagSFTool->SF_TightWpDown()<<" ] ";

				// std::cout<<" init args were [pt, eta, rawScore, hadronFlav  ] = [ ";
				// std::cout<<jetVec[j].pt()<<" , "<<jetVec[j].eta()<<" , "<<jetVec[j].defaultBtagAlgorithm_RawScore()<<" , "<<jetVec[j].HADRON_flavour()<<" ] \n";

			} // b-tagging
			
			/* next check the jet ID  */


			if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="fullyCorrected") m_PtJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		
			if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JECshiftedUp" ) m_PtJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		
			if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JECshiftedDown" ) m_PtJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		
			if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JERnomianl" ) m_PtJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		
			if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JERup" ) m_PtJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
		
			if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JERdown" ) m_PtJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );

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



		} // loop on systematics 

	} // loop on jets 


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
					double minDR, NtupleLepton leg1, NtupleLepton leg2, bTagSFhelper *  m_BtagSFTool, bool isRealData)
{

	/* reset the jet vectors */

	m_PtJetPairs_fullyCorrected.clear();
	m_PtJetPairs_JECshiftedUp.clear();
	m_PtJetPairs_JECshiftedDown.clear();
	m_PtJetPairs_JERnomianl.clear();
	m_PtJetPairs_JERup.clear();
	m_PtJetPairs_JERdown.clear();

	/* reset the b-tag SF vectors */
	
	SF_fullyCorrected.clear();
	SFup_fullyCorrected.clear();
	SFdown_fullyCorrected.clear();
	
	SF_JECshiftedUp.clear();
	SFup_JECshiftedUp.clear();
	SFdown_JECshiftedUp.clear();
	
	SF_JECshiftedDown.clear();
	SFup_JECshiftedDown.clear();
	SFdown_JECshiftedDown.clear();
	
	SF_JERnomianl.clear();
	SFup_JERnomianl.clear();
	SFdown_JERnomianl.clear();
	
	SF_JERup.clear();
	SFup_JERup.clear();
	SFdown_JERup.clear();
	
	SF_JERdown.clear();
	SFup_JERdown.clear();
	SFdown_JERdown.clear();


	LOOSE_SF_fullyCorrected.clear();
	LOOSE_SFup_fullyCorrected.clear();
	LOOSE_SFdown_fullyCorrected.clear();
	
	LOOSE_SF_JECshiftedUp.clear();
	LOOSE_SFup_JECshiftedUp.clear();
	LOOSE_SFdown_JECshiftedUp.clear();
	
	LOOSE_SF_JECshiftedDown.clear();
	LOOSE_SFup_JECshiftedDown.clear();
	LOOSE_SFdown_JECshiftedDown.clear();
	
	LOOSE_SF_JERnomianl.clear();
	LOOSE_SFup_JERnomianl.clear();
	LOOSE_SFdown_JERnomianl.clear();
	
	LOOSE_SF_JERup.clear();
	LOOSE_SFup_JERup.clear();
	LOOSE_SFdown_JERup.clear();
	
	LOOSE_SF_JERdown.clear();
	LOOSE_SFup_JERdown.clear();
	LOOSE_SFdown_JERdown.clear();


	/* create container to hold all jet systematic levels */
	std::string jetSysArray[6] = {"fullyCorrected","JECshiftedUp","JECshiftedDown","JERnomianl","JERup","JERdown"};

	/* create the cut selector */
	StringCutObjectSelector<NtupleJet> jetSelector(jetCut);

	/* begin loop over jets, and fill the unordered pt:jet vector of pair*/
	for(std::size_t j = 0; j < jetVec.size(); ++j) 
	{
		
		/* looping through the different jet systematics */	
		for(int sys=0; sys<6; sys++)	   
		{
			/* switch to the sys 4-vector */
			jetVec[j].Use4VectorVariant(jetSysArray[sys]);		

			/* check b-tags */
			if(jetVec[j].pt() >= 20.0 && fabs(jetVec[j].eta()) <= 2.4) /* btagging does not apply out of this range */
			{


				m_BtagSFTool->InitForJet(jetVec[j].pt(), 
				 					jetVec[j].eta(), 
									jetVec[j].defaultBtagAlgorithm_RawScore(),
									jetVec[j].PARTON_flavour(), isRealData);
									/* wisconsin uses PARTON_flavour we used to use HADRON_flavour */

				// if(jetSysArray[sys]=="fullyCorrected")
				// {
				// 	std::cout<<" sf sf sf "<<m_BtagSFTool->SF_MediumWpCentral()<<" pt "<<jetVec[j].pt()<<" eta "<<jetVec[j].eta()<<" raw "<<jetVec[j].defaultBtagAlgorithm_RawScore()<<" ";
				// 	std::cout<<" parton flavour "<<jetVec[j].PARTON_flavour()<<" ";
				// 	std::cout<<" hadron flavour "<<jetVec[j].HADRON_flavour()<<" ";
				// 	std::cout<<" jetSelector "<<jetSelector(jetVec[j])<<"\n";
				// }

				/* set the Btag SFs for the current jet */
					
				jetVec[j].set_defaultBtagAlgorithmSF_LooseWpCentral(m_BtagSFTool->SF_LooseWpCentral());
				jetVec[j].set_defaultBtagAlgorithmSF_LooseWpUp(m_BtagSFTool->SF_LooseWpUp());
				jetVec[j].set_defaultBtagAlgorithmSF_LooseWpDown(m_BtagSFTool->SF_LooseWpDown());

				jetVec[j].set_defaultBtagAlgorithmSF_MediumWpCentral(m_BtagSFTool->SF_MediumWpCentral());
				jetVec[j].set_defaultBtagAlgorithmSF_MediumWpUp(m_BtagSFTool->SF_MediumWpUp());
				jetVec[j].set_defaultBtagAlgorithmSF_MediumWpDown(m_BtagSFTool->SF_MediumWpDown());

				jetVec[j].set_defaultBtagAlgorithmSF_TightWpCentral(m_BtagSFTool->SF_TightWpCentral());
				jetVec[j].set_defaultBtagAlgorithmSF_TightWpUp(m_BtagSFTool->SF_TightWpUp());
				jetVec[j].set_defaultBtagAlgorithmSF_TightWpDown(m_BtagSFTool->SF_TightWpDown());


				/* for b-tag SF wisconsin seems to cut at 30 instead of 20 */
				if(jetSelector(jetVec[j]) && jetVec[j].pt() >= 30.0 && fabs(jetVec[j].eta()) <= 2.4 && jetVec[j].defaultBtagAlgorithm_RawScore()>m_BtagSFTool->getCutPointMedium())
				{
					if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
					{

						/* store the medium WP scale factors for the correct jet variant */
						if(	jetSysArray[sys]=="fullyCorrected") 			
						{		
							SF_fullyCorrected.push_back(m_BtagSFTool->SF_MediumWpCentral());
							SFup_fullyCorrected.push_back(m_BtagSFTool->SF_MediumWpUp());
							SFdown_fullyCorrected.push_back(m_BtagSFTool->SF_MediumWpDown());
						}	
						if(	jetSysArray[sys]=="JECshiftedUp" ) 
						{		
							SF_JECshiftedUp.push_back(m_BtagSFTool->SF_MediumWpCentral());
							SFup_JECshiftedUp.push_back(m_BtagSFTool->SF_MediumWpUp());
							SFdown_JECshiftedUp.push_back(m_BtagSFTool->SF_MediumWpDown());
						}				
						if(	jetSysArray[sys]=="JECshiftedDown" ) 
						{		
							SF_JECshiftedDown.push_back(m_BtagSFTool->SF_MediumWpCentral());
							SFup_JECshiftedDown.push_back(m_BtagSFTool->SF_MediumWpUp());
							SFdown_JECshiftedDown.push_back(m_BtagSFTool->SF_MediumWpDown());
						}				
						if(	jetSysArray[sys]=="JERnomianl" ) 
						{		
							SF_JERnomianl.push_back(m_BtagSFTool->SF_MediumWpCentral());
							SFup_JERnomianl.push_back(m_BtagSFTool->SF_MediumWpUp());
							SFdown_JERnomianl.push_back(m_BtagSFTool->SF_MediumWpDown());
						}			
						if(	jetSysArray[sys]=="JERup" ) 
						{		
							SF_JERup.push_back(m_BtagSFTool->SF_MediumWpCentral());
							SFup_JERup.push_back(m_BtagSFTool->SF_MediumWpUp());
							SFdown_JERup.push_back(m_BtagSFTool->SF_MediumWpDown());
						}				
						if(	jetSysArray[sys]=="JERdown" ) 
						{		
							SF_JERdown.push_back(m_BtagSFTool->SF_MediumWpCentral());
							SFup_JERdown.push_back(m_BtagSFTool->SF_MediumWpUp());
							SFdown_JERdown.push_back(m_BtagSFTool->SF_MediumWpDown());
						}	
					}	
				}

				/* for b-tag SF wisconsin seems to cut at 30 instead of 20 */
				if(jetSelector(jetVec[j]) && jetVec[j].pt() >= 30.0 && fabs(jetVec[j].eta()) <= 2.4 && jetVec[j].defaultBtagAlgorithm_RawScore()>m_BtagSFTool->getCutPointLoose())
				{
					if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
					{

						/* store the medium WP scale factors for the correct jet variant */
						if(	jetSysArray[sys]=="fullyCorrected") 			
						{		
							LOOSE_SF_fullyCorrected.push_back(m_BtagSFTool->SF_LooseWpCentral());
							LOOSE_SFup_fullyCorrected.push_back(m_BtagSFTool->SF_LooseWpUp());
							LOOSE_SFdown_fullyCorrected.push_back(m_BtagSFTool->SF_LooseWpDown());
						}	
						if(	jetSysArray[sys]=="JECshiftedUp" ) 
						{		
							LOOSE_SF_JECshiftedUp.push_back(m_BtagSFTool->SF_LooseWpCentral());
							LOOSE_SFup_JECshiftedUp.push_back(m_BtagSFTool->SF_LooseWpUp());
							LOOSE_SFdown_JECshiftedUp.push_back(m_BtagSFTool->SF_LooseWpDown());
						}				
						if(	jetSysArray[sys]=="JECshiftedDown" ) 
						{		
							LOOSE_SF_JECshiftedDown.push_back(m_BtagSFTool->SF_LooseWpCentral());
							LOOSE_SFup_JECshiftedDown.push_back(m_BtagSFTool->SF_LooseWpUp());
							LOOSE_SFdown_JECshiftedDown.push_back(m_BtagSFTool->SF_LooseWpDown());
						}				
						if(	jetSysArray[sys]=="JERnomianl" ) 
						{		
							LOOSE_SF_JERnomianl.push_back(m_BtagSFTool->SF_LooseWpCentral());
							LOOSE_SFup_JERnomianl.push_back(m_BtagSFTool->SF_LooseWpUp());
							LOOSE_SFdown_JERnomianl.push_back(m_BtagSFTool->SF_LooseWpDown());
						}			
						if(	jetSysArray[sys]=="JERup" ) 
						{		
							LOOSE_SF_JERup.push_back(m_BtagSFTool->SF_LooseWpCentral());
							LOOSE_SFup_JERup.push_back(m_BtagSFTool->SF_LooseWpUp());
							LOOSE_SFdown_JERup.push_back(m_BtagSFTool->SF_LooseWpDown());
						}				
						if(	jetSysArray[sys]=="JERdown" ) 
						{		
							LOOSE_SF_JERdown.push_back(m_BtagSFTool->SF_LooseWpCentral());
							LOOSE_SFup_JERdown.push_back(m_BtagSFTool->SF_LooseWpUp());
							LOOSE_SFdown_JERdown.push_back(m_BtagSFTool->SF_LooseWpDown());
						}	
					}	
				}



				/* set the b-tag eff. for the current jet */

				jetVec[j].set_defaultBtagAlgorithmEff_LooseWp(m_BtagSFTool->EFF_LooseWp());
				jetVec[j].set_defaultBtagAlgorithmEff_MediumWp(m_BtagSFTool->EFF_MediumWp());
				jetVec[j].set_defaultBtagAlgorithmEff_TightWp(m_BtagSFTool->EFF_TightWp());


				/* set the Btag Pass/Fail tags (after SFs) for the current jet */
			

				jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpCentral(m_BtagSFTool->IsTagged_LooseWpCentral());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpUp(m_BtagSFTool->IsTagged_LooseWpUp());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_LooseWpDown(m_BtagSFTool->IsTagged_LooseWpDown());

				jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpCentral(m_BtagSFTool->IsTagged_MediumWpCentral());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpUp(m_BtagSFTool->IsTagged_MediumWpUp());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_MediumWpDown(m_BtagSFTool->IsTagged_MediumWpDown());

				jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpCentral(m_BtagSFTool->IsTagged_TightWpCentral());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpUp(m_BtagSFTool->IsTagged_TightWpUp());
				jetVec[j].set_defaultBtagAlgorithmIsTagged_TightWpDown(m_BtagSFTool->IsTagged_TightWpDown());

			} // b-tagging
			
			/* next check the DR && jet ID  */

			if(deltaR(leg1.p4(), jetVec[j].jet_p4()) >= minDR && deltaR(leg2.p4(), jetVec[j].jet_p4()) >= minDR)
			{

				if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="fullyCorrected") m_PtJetPairs_fullyCorrected.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			
				if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JECshiftedUp" ) m_PtJetPairs_JECshiftedUp.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			
				if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JECshiftedDown" ) m_PtJetPairs_JECshiftedDown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			
				if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JERnomianl" ) m_PtJetPairs_JERnomianl.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			
				if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JERup" ) m_PtJetPairs_JERup.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );
			
				if(	jetSelector(jetVec[j]) && jetSysArray[sys]=="JERdown" ) m_PtJetPairs_JERdown.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );

			} // deltaR

			// reset back to fullyCorrected just in case
			jetVec[j].Use4VectorVariant("fullyCorrected");

		} // loop on systematics 

	} // loop on jets 

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




 double JetHelper::getZeroBtagEventSF(std::string variant_, std::string shift_, unsigned int event_)
 {

	std::string jetSysArray[6] = {"fullyCorrected","JECshiftedUp","JECshiftedDown","JERnomianl","JERup","JERdown"};


	    assert(variant_ == "fullyCorrected" ||\
	           variant_ == "JECshiftedUp" ||\
	           variant_ == "JECshiftedDown" ||\
	           variant_ == "JERnomianl" ||\
	           variant_ == "JERup" ||\
	           variant_ == "JERdown");


	    assert(shift_ == "central" ||\
	           shift_ == "up" ||\
	           shift_ == "down");


	    std::vector <double> temp_sf_vector;
	    temp_sf_vector.clear();


	    if(variant_=="fullyCorrected")
    	{
	    	if(	shift_=="central") temp_sf_vector = SF_fullyCorrected;
    		if(	shift_=="up")      temp_sf_vector = SFup_fullyCorrected;
    		if(	shift_=="down")    temp_sf_vector = SFdown_fullyCorrected;
		}	

	    if(variant_=="JECshiftedUp")
    	{
	    	if(	shift_=="central") temp_sf_vector = SF_JECshiftedUp;
    		if(	shift_=="up")      temp_sf_vector = SFup_JECshiftedUp;
    		if(	shift_=="down")    temp_sf_vector = SFdown_JECshiftedUp;
		}	

	    if(variant_=="JECshiftedDown")
    	{
	    	if(	shift_=="central") temp_sf_vector = SF_JECshiftedDown;
    		if(	shift_=="up")      temp_sf_vector = SFup_JECshiftedDown;
    		if(	shift_=="down")    temp_sf_vector = SFdown_JECshiftedDown;
		}			

	    if(variant_=="JERnomianl")
    	{
	    	if(	shift_=="central") temp_sf_vector = SF_JERnomianl;
    		if(	shift_=="up")      temp_sf_vector = SFup_JERnomianl;
    		if(	shift_=="down")    temp_sf_vector = SFdown_JERnomianl;
		}	

	    if(variant_=="JERup")
    	{
	    	if(	shift_=="central") temp_sf_vector = SF_JERup;
    		if(	shift_=="up")      temp_sf_vector = SFup_JERup;
    		if(	shift_=="down")    temp_sf_vector = SFdown_JERup;
		}	
	  
	    if(variant_=="JERdown")
    	{
	    	if(	shift_=="central") temp_sf_vector = SF_JERdown;
    		if(	shift_=="up")      temp_sf_vector = SFup_JERdown;
    		if(	shift_=="down")    temp_sf_vector = SFdown_JERdown;
		}	
 

		/* compute the SF */
		double return_weight = 1.0;


		// std::cout<<event_<<" EVENT_XXX temp_sf_vector size "<<temp_sf_vector.size()<<"\n";
		// for(std::size_t j = 0; j<temp_sf_vector.size(); ++j)
		// {
		// 	std::cout<<event_<<" EVENT_XXX temp_sf_vector @ "<<j<<" "<<temp_sf_vector[j]<<"\n";
		// }


		if(temp_sf_vector.size() == 0) {temp_sf_vector.clear();  return 1.0; }


		for(std::size_t j = 0; j<temp_sf_vector.size(); ++j)
		{
			return_weight *= (1 - temp_sf_vector[j]);
		}

		temp_sf_vector.clear(); 
		return return_weight;

 }



 double JetHelper::getZeroBtagEventSF_LOOSE(std::string variant_, std::string shift_, unsigned int event_)
 {

	std::string jetSysArray[6] = {"fullyCorrected","JECshiftedUp","JECshiftedDown","JERnomianl","JERup","JERdown"};


	    assert(variant_ == "fullyCorrected" ||\
	           variant_ == "JECshiftedUp" ||\
	           variant_ == "JECshiftedDown" ||\
	           variant_ == "JERnomianl" ||\
	           variant_ == "JERup" ||\
	           variant_ == "JERdown");


	    assert(shift_ == "central" ||\
	           shift_ == "up" ||\
	           shift_ == "down");


	    std::vector <double> temp_sf_vector;
	    temp_sf_vector.clear();


	    if(variant_=="fullyCorrected")
    	{
	    	if(	shift_=="central") temp_sf_vector = LOOSE_SF_fullyCorrected;
    		if(	shift_=="up")      temp_sf_vector = LOOSE_SFup_fullyCorrected;
    		if(	shift_=="down")    temp_sf_vector = LOOSE_SFdown_fullyCorrected;
		}	

	    if(variant_=="JECshiftedUp")
    	{
	    	if(	shift_=="central") temp_sf_vector = LOOSE_SF_JECshiftedUp;
    		if(	shift_=="up")      temp_sf_vector = LOOSE_SFup_JECshiftedUp;
    		if(	shift_=="down")    temp_sf_vector = LOOSE_SFdown_JECshiftedUp;
		}	

	    if(variant_=="JECshiftedDown")
    	{
	    	if(	shift_=="central") temp_sf_vector = LOOSE_SF_JECshiftedDown;
    		if(	shift_=="up")      temp_sf_vector = LOOSE_SFup_JECshiftedDown;
    		if(	shift_=="down")    temp_sf_vector = LOOSE_SFdown_JECshiftedDown;
		}			

	    if(variant_=="JERnomianl")
    	{
	    	if(	shift_=="central") temp_sf_vector = LOOSE_SF_JERnomianl;
    		if(	shift_=="up")      temp_sf_vector = LOOSE_SFup_JERnomianl;
    		if(	shift_=="down")    temp_sf_vector = LOOSE_SFdown_JERnomianl;
		}	

	    if(variant_=="JERup")
    	{
	    	if(	shift_=="central") temp_sf_vector = LOOSE_SF_JERup;
    		if(	shift_=="up")      temp_sf_vector = LOOSE_SFup_JERup;
    		if(	shift_=="down")    temp_sf_vector = LOOSE_SFdown_JERup;
		}	
	  
	    if(variant_=="JERdown")
    	{
	    	if(	shift_=="central") temp_sf_vector = LOOSE_SF_JERdown;
    		if(	shift_=="up")      temp_sf_vector = LOOSE_SFup_JERdown;
    		if(	shift_=="down")    temp_sf_vector = LOOSE_SFdown_JERdown;
		}	
 

		/* compute the SF */
		double return_weight = 1.0;


		// std::cout<<event_<<" EVENT_XXX temp_sf_vector size "<<temp_sf_vector.size()<<"\n";
		// for(std::size_t j = 0; j<temp_sf_vector.size(); ++j)
		// {
		// 	std::cout<<event_<<" EVENT_XXX temp_sf_vector @ "<<j<<" "<<temp_sf_vector[j]<<"\n";
		// }


		if(temp_sf_vector.size() == 0) {temp_sf_vector.clear();  return 1.0; }


		for(std::size_t j = 0; j<temp_sf_vector.size(); ++j)
		{
			return_weight *= (1 - temp_sf_vector[j]);
		}

		temp_sf_vector.clear(); 
		return return_weight;

 }



