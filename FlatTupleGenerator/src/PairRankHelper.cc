/* class PairRankHelper :

contains function to take in rank criteria + a vector of NtupleEvent objects
and return a std::vector<std::pair<NtupleEvent,int>> where the int represents 
the pair's rank 

the idea is that in the TTree we can access the best pair using rank==0, the 2nd
best by rank == 1 etc. 

- Shalhout
*/


#include "DavisRunIITauTau/FlatTupleGenerator/interface/PairRankHelper.h"

/* ranking comparator */


bool NtupleRankCompare( const std::pair<double, NtupleEvent>& p1, const std::pair<double, NtupleEvent>& p2) 
{
	return p1.first > p2.first;	
}





/* constructor */

PairRankHelper::PairRankHelper(){}


/* helpers */



  double PairRankHelper::getSumPt(NtupleEvent pair)
  {
  	return pair.leg1().p4().pt()+pair.leg2().p4().pt();
  }

  double PairRankHelper::getIsolProduct(NtupleEvent pair,std::string eIsol, std::string muIsol, std::string tauID)
  {

  		double criterion = 1.0;

  		if(pair.leg1().leptonType()==TupleLeptonTypes::anElectron) criterion *= pair.leg1().relativeIsol(eIsol);
  		else if(pair.leg1().leptonType()==TupleLeptonTypes::aMuon) criterion *= pair.leg1().relativeIsol(muIsol);
  		else if(pair.leg1().leptonType()==TupleLeptonTypes::aTau)	 criterion *= pair.leg1().tauID(tauID);

  		if(pair.leg2().leptonType()==TupleLeptonTypes::anElectron) criterion *= pair.leg2().relativeIsol(eIsol);
  		else if(pair.leg2().leptonType()==TupleLeptonTypes::aMuon) criterion *= pair.leg2().relativeIsol(muIsol);
  		else if(pair.leg2().leptonType()==TupleLeptonTypes::aTau)  criterion *= pair.leg2().tauID(tauID);

  		return criterion;


  }





  /* for sumPt ranking */
  void PairRankHelper::init(std::vector<NtupleEvent> pairs)
  {

  	for(std::size_t i = 0; i<pairs.size(); ++i)
  	{
  		double criterion = getSumPt(pairs[i]);
  		std::pair<double, NtupleEvent> apair(criterion, pairs[i]);
	  	m_CriterionLepPair.push_back(apair);
	}
	std::cout<<m_CriterionLepPair.size()<<" = m_CriterionLepPair size \n";
	process_pairs();
	//print_ranking();

  }
  
  /* for isolation ranking note : the 3 strings are passed to 
  electron.relativeIsol(), muon.relativeIsol(), tau.tauID() in that order  */

  void PairRankHelper::init(std::vector<NtupleEvent> pairs,std::string eIsol, std::string muIsol, std::string tauID)
  {

  	for(std::size_t i = 0; i<pairs.size(); ++i)
  	{
  		double criterion = getIsolProduct(pairs[i],eIsol,muIsol,tauID);
  		std::pair<double, NtupleEvent> apair(criterion, pairs[i]);
	  	m_CriterionLepPair.push_back(apair);
	}

	process_pairs();
	//print_ranking();




  } 

void PairRankHelper::print_ranking()
{

	std::cout<<"------ new Event ------- \n";
	for(std::size_t x = 0; x<m_finalRanking.size();++x)
	{

	std::cout<<"RANK = "<<m_finalRanking[x].first<<" ";
	std::cout<<"CRITERION = "<<m_finalRankedCriterion[x].first<<" ";
	std::cout<<" isOS "<<m_finalRankedCriterion[x].second.isOsPair()<<" ";
	std::cout<<" pairType "<<m_finalRankedCriterion[x].second.CandidateEventType()<<"\n";


	}

}


std::vector<std::pair<std::size_t, NtupleEvent>> PairRankHelper::returnRankedPairVec()
{
	return m_finalRanking;

}

void PairRankHelper::process_pairs()
{

	/* Ranking : fills m_finalRanking with std::size RANK, and NtupleEvent
		repeat separately 
		for OS and SS (prefer OS to SS)

	*/



	

		for(std::size_t p = 0; p<m_CriterionLepPair.size(); ++p)
		{		
			/* note this all breaks if mix tauEs variants in same TTree */
			/* start by 1st splitting up pairs into OS and SS */


			if(m_CriterionLepPair[p].second.isOsPair()==1) m_OSRanking.push_back(m_CriterionLepPair[p]);
			else m_SSRanking.push_back(m_CriterionLepPair[p]);

		}	

		/* sort OS and SS separately */
		std::sort(m_OSRanking.begin(), m_OSRanking.end(), NtupleRankCompare);
		std::sort(m_SSRanking.begin(), m_SSRanking.end(), NtupleRankCompare);



		/* append OS and the SSranked to finalRanking */
		
		for(std::size_t t = 0; t<m_OSRanking.size(); ++t) 
		{
			std::pair<std::size_t, NtupleEvent> toPush(m_finalRanking.size(),m_OSRanking[t].second);
			m_finalRanking.push_back(toPush);

			m_finalRankedCriterion.push_back(m_OSRanking[t]);
		}


		for(std::size_t t = 0; t<m_SSRanking.size(); ++t) 
		{
			std::pair<std::size_t, NtupleEvent> toPush(m_finalRanking.size(),m_SSRanking[t].second);
			m_finalRanking.push_back(toPush);
			m_finalRankedCriterion.push_back(m_SSRanking[t]);

		}


		/* clear them */
		m_OSRanking.clear();
		m_SSRanking.clear();		
		

}


