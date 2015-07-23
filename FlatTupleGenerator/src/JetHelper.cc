#include "DavisRunIITauTau/FlatTupleGenerator/interface/JetHelper.h"



bool NtupleJetOrderCompare( const std::pair<double, NtupleJet>& p1, const std::pair<double, NtupleJet>& p2) 
{
	return p1.first > p2.first;	
}


/* constructor */

JetHelper::JetHelper(){}


/* initialization function */

void JetHelper::init(std::vector<NtupleJet> jetVec, std::string jetCut, std::string bjetCut,
					double minDR, NtupleLepton leg1, NtupleLepton leg2)
{

	m_PtJetPairs.clear();
	m_PtBJetPairs.clear();

	/* create the cut selectors */

	StringCutObjectSelector<NtupleJet> jetSelector(jetCut);
	StringCutObjectSelector<NtupleJet> BjetSelector(bjetCut);

	/* begin loop over jets, and fill the unordered pt:jet vector of pair*/

	for(std::size_t j = 0; j < jetVec.size(); ++j) 
	{

		/* first check the DR between the jet and each leg */

		if(deltaR(leg1.p4(), jetVec[j].jet_p4()) < minDR) continue;
		if(deltaR(leg2.p4(), jetVec[j].jet_p4()) < minDR) continue;

		/* next check the jet ID & B jet ID, & if passes add to the pair vectors,
		allowing jets to enter both vectors - cause that is what H2Tau Does */

		if(	jetSelector(jetVec[j]) ) m_PtJetPairs.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );

		if(	BjetSelector(jetVec[j]) ) m_PtBJetPairs.push_back( std::make_pair(jetVec[j].pt(), jetVec[j]) );

	}

} 

// getters

	std::vector<NtupleJet> JetHelper::PtOrderedPassingJets()
 	{

 		std::vector <NtupleJet> returnVec;

 		/* seems jets are already ranked in mini-AOD, but just to be safe under future JEC variants */
		std::sort(m_PtJetPairs.begin(), m_PtJetPairs.end(), NtupleJetOrderCompare);

		for(std::size_t k = 0; k<m_PtJetPairs.size(); ++k)
		{
			returnVec.push_back(m_PtJetPairs[k].second);	
		}

		return returnVec;

  	}


	std::vector<NtupleJet> JetHelper::PtOrderedPassingBJets()
 	{

 		std::vector <NtupleJet> returnVec;

 		/* seems jets are already ranked in mini-AOD, but just to be safe under future JEC variants */
		std::sort(m_PtBJetPairs.begin(), m_PtBJetPairs.end(), NtupleJetOrderCompare);

		for(std::size_t k = 0; k<m_PtBJetPairs.size(); ++k)
		{
			returnVec.push_back(m_PtBJetPairs[k].second);	
		}

		return returnVec;

  	}
