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

  /* always prefer OS to SS */
  
  if ( p1.second.isOsPair()==1 && p2.second.isOsPair()!=1) return true;
  if ( p1.second.isOsPair()!=1 && p2.second.isOsPair()==1) return false;

  /* if both OS or both SS, rank by the provided criterion if it differes */

  if(p1.first != p2.first)  return p1.first > p2.first;	

  /* otherwise rank by pair types 
	adapted from code by LLR
  */

  int p1Type=0;
  int p2Type=0;
  
  if(p1.second.leg1().leptonType()==TupleLeptonTypes::anElectron) p1Type+=0;
  else if(p1.second.leg1().leptonType()==TupleLeptonTypes::aMuon) p1Type+=1;
  else if(p1.second.leg1().leptonType()==TupleLeptonTypes::aTau) p1Type+=2;

  if(p1.second.leg2().leptonType()==TupleLeptonTypes::anElectron) p1Type+=0;
  else if(p1.second.leg2().leptonType()==TupleLeptonTypes::aMuon) p1Type+=1;
  else if(p1.second.leg2().leptonType()==TupleLeptonTypes::aTau) p1Type+=2;

  if(p2.second.leg1().leptonType()==TupleLeptonTypes::anElectron) p2Type+=0;
  else if(p2.second.leg1().leptonType()==TupleLeptonTypes::aMuon) p2Type+=1;
  else if(p2.second.leg1().leptonType()==TupleLeptonTypes::aTau) p2Type+=2;

  if(p2.second.leg2().leptonType()==TupleLeptonTypes::anElectron) p2Type+=0;
  else if(p2.second.leg2().leptonType()==TupleLeptonTypes::aMuon) p2Type+=1;
  else if(p2.second.leg2().leptonType()==TupleLeptonTypes::aTau) p2Type+=2;


  return (p1Type<p2Type);

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
	print_ranking();

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
	print_ranking();




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
			
	*/



	

		for(std::size_t p = 0; p<m_CriterionLepPair.size(); ++p)
		{		
			/* note this all breaks if mix tauEs variants in same TTree */
			

			m_Ranking.push_back(m_CriterionLepPair[p]);

		}	

		std::sort(m_Ranking.begin(), m_Ranking.end(), NtupleRankCompare);



		/* append to finalRanking */
		
		for(std::size_t t = 0; t<m_Ranking.size(); ++t) 
		{
			std::pair<std::size_t, NtupleEvent> toPush(m_finalRanking.size(),m_Ranking[t].second);
			m_finalRanking.push_back(toPush);

			m_finalRankedCriterion.push_back(m_Ranking[t]);
		}


	


		/* clear them */
		m_Ranking.clear();
		

}


