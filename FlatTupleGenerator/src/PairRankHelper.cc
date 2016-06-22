/* class PairRankHelper :

contains function to take in rank criteria + a vector of NtupleEvent objects
and return a std::vector<std::pair<NtupleEvent,int>> where the int represents 
the pair's rank 

the idea is that in the TTree we can access the best pair using rank==0, the 2nd
best by rank == 1 etc. 

- Shalhout
*/


#include "DavisRunIITauTau/FlatTupleGenerator/interface/PairRankHelper.h"

/* ranking comparators */


IsolThenPtComparator::IsolThenPtComparator(bool leg1_isSmallerValueMoreIsolated, bool leg2_isSmallerValueMoreIsolated)
{
   m_leg1_isSmallerMoreIsolated = leg1_isSmallerValueMoreIsolated;
   m_leg2_isSmallerMoreIsolated = leg2_isSmallerValueMoreIsolated;
}



bool NtupleRankCompare_SumPt( const std::pair<double, NtupleEvent>& p1, const std::pair<double, NtupleEvent>& p2) 
{
  // simple pt sum comparison
   if(p1.first != p2.first)  return p1.first > p2.first;	
   else return 1;  
}

/* constructor */

PairRankHelper::PairRankHelper(){}


/* init for sumPt ranking */
void PairRankHelper::init(std::vector<NtupleEvent> pairs)
{



  for(std::size_t i = 0; i<pairs.size(); ++i)
  {
    double criterion = getSumPt(pairs[i]);
    std::pair<double, NtupleEvent> apair(criterion, pairs[i]);
    m_CriterionLepPair_SumPt.push_back(apair);
   }

   std::sort(m_CriterionLepPair_SumPt.begin(), m_CriterionLepPair_SumPt.end(), NtupleRankCompare_SumPt);
   
   m_finalRanking.clear();

   for(std::size_t x = 0; x<m_CriterionLepPair_SumPt.size(); ++x)
   {
      m_finalRanking.push_back( std::make_pair(x, m_CriterionLepPair_SumPt[x].second ) );

   }

}

/* init for isolation based ranking: 1st take pair with most isolated leg1, if leg1 is tied in isoaltion
prefer pair with higher leg1 pt, then if tied, compare leg2 isolation, then if still tied leg2 pt  */

void PairRankHelper::init(std::vector<NtupleEvent> pairs,std::string eIsol, std::string muIsol, std::string tauID,
bool leg1_isSmallerValueMoreIsolated, bool leg2_isSmallerValueMoreIsolated)
{

  bool verbose = 0;

  eIsol_ = eIsol;
  muIsol_ = muIsol;
  tauID_ = tauID;

  for(std::size_t i = 0; i<pairs.size(); ++i)
  {
    std::vector<double> criterion = getIsolOfLeg1andLeg2(pairs[i],eIsol,muIsol,tauID);
    std::pair<std::vector<double>, NtupleEvent> apair(criterion, pairs[i]);
    m_CriterionLepPair_Isol.push_back(apair);
  }

   //std::cout<<" TOTAL m_CriterionLepPair_Isol "<<m_CriterionLepPair_Isol.size()<<"\n";



  if(verbose)
  { 
    std::cout<<" ----- new ranking by isolation -------- \n";

     for(std::size_t x = 0; x<m_CriterionLepPair_Isol.size(); ++x)
     {
        if(verbose)
        {
           std::cout<<" PRE-SORTED RANK "<<x<<" has (l1_isol, l1_pt, l2_isol, l2_pt) = ( ";
           std::cout<<m_CriterionLepPair_Isol[x].first[0]<<" , "; 
           std::cout<<m_CriterionLepPair_Isol[x].second.leg1().pt()<<" , "; 
           std::cout<<m_CriterionLepPair_Isol[x].first[1]<<" , "; 
           std::cout<<m_CriterionLepPair_Isol[x].second.leg2().pt()<<" ) \n "; 
        }

      }
  }

   IsolThenPtComparator TheComparator(leg1_isSmallerValueMoreIsolated,leg2_isSmallerValueMoreIsolated);

   std::sort(m_CriterionLepPair_Isol.begin(), m_CriterionLepPair_Isol.end(), TheComparator);

   m_finalRanking.clear();




   for(std::size_t x = 0; x<m_CriterionLepPair_Isol.size(); ++x)
   {
      if(verbose)
      {
         std::cout<<" SORTED RANK "<<x<<" has (l1_isol, l1_pt, l2_isol, l2_pt) = ( ";
         std::cout<<m_CriterionLepPair_Isol[x].first[0]<<" , "; 
         std::cout<<m_CriterionLepPair_Isol[x].second.leg1().pt()<<" , "; 
         std::cout<<m_CriterionLepPair_Isol[x].first[1]<<" , "; 
         std::cout<<m_CriterionLepPair_Isol[x].second.leg2().pt()<<" ) \n "; 
      }


      m_finalRanking.push_back( std::make_pair(x, m_CriterionLepPair_Isol[x].second ) );

   }




} 




/* helpers */



  double PairRankHelper::getSumPt(NtupleEvent pair)
  {
  	return pair.leg1().p4().pt()+pair.leg2().p4().pt();
  }

  std::vector<double> PairRankHelper::getIsolOfLeg1andLeg2(NtupleEvent pair,std::string eIsol, std::string muIsol, std::string tauID)
  {

  		double criterion1 = 1.0;
      double criterion2 = 1.0;
      std::vector<double> criterion;

  		if(pair.leg1().leptonType()==TupleLeptonTypes::anElectron) criterion1 *= pair.leg1().relativeIsol(eIsol);
  		else if(pair.leg1().leptonType()==TupleLeptonTypes::aMuon) criterion1 *= pair.leg1().relativeIsol(muIsol);
  		else if(pair.leg1().leptonType()==TupleLeptonTypes::aTau)	 criterion1 *= pair.leg1().tauID(tauID);

  		if(pair.leg2().leptonType()==TupleLeptonTypes::anElectron) criterion2 *= pair.leg2().relativeIsol(eIsol);
  		else if(pair.leg2().leptonType()==TupleLeptonTypes::aMuon) criterion2 *= pair.leg2().relativeIsol(muIsol);
  		else if(pair.leg2().leptonType()==TupleLeptonTypes::aTau)  criterion2 *= pair.leg2().tauID(tauID);

      criterion.clear();      
      criterion.push_back(criterion1);
      criterion.push_back(criterion2);

  		return criterion;


  }

std::vector<std::pair<std::size_t, NtupleEvent>> PairRankHelper::returnRankedPairVec()
{
	return m_finalRanking;

}






