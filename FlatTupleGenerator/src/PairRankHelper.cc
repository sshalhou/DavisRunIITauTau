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
	/* rank by provided doubles, in the case of equal criteria use the CandidateEventTypes
	to rank  */
	if(p1.first != p2.first) return p1.first > p2.first;
	else { return p1.second.CandidateEventType() > p2.second.CandidateEventType();}

}




/* constructor */

PairRankHelper::PairRankHelper(){}


/* helpers */



/* return a ranked pair <rank, NtupleEvent> */

std::vector<std::pair <std::size_t, NtupleEvent>> PairRankHelper::rank_pairs_BySumPt(std::vector<NtupleEvent> Input)
{
	std::vector<std::pair <double, NtupleEvent>> theVectorToRank;
	for (std::size_t x = 0;  x<Input.size(); ++x )
	{

		std::pair <double, NtupleEvent> thepair(Input[x].leg1().p4().pt()+Input[x].leg2().p4().pt(),Input[x]);
		theVectorToRank.push_back(thepair);

	}




	std::sort(theVectorToRank.begin(), theVectorToRank.end(), NtupleRankCompare);




	std::vector<std::pair <std::size_t, NtupleEvent>> r;
	r.clear();
	for(std::size_t y=0; y<theVectorToRank.size();++y)
	{

		std::pair <std::size_t, NtupleEvent> theRankedPair(y,theVectorToRank[y].second);

		r.push_back(theRankedPair);

	}
	return r;
}



/* fillers */

void PairRankHelper::process_pairs(std::vector<NtupleEvent> PAIRS)
{

}

void PairRankHelper::process_pairs_RANKDEMO(std::vector<NtupleEvent> PAIRS)
{
	m_InputPairs = PAIRS;
	std::vector<std::pair <std::size_t, NtupleEvent>> finalRanking;

	/* Ranking :
		repeat separately for each TauEsVariant then 
		for OS and SS (prefer OS to SS)

	*/
	
	for (float shift = -1.0; shift <= +1.0; shift+=1.0)
	{


		/* vecs to hold ordered pairs each shift */
		std::vector<std::pair <std::size_t, NtupleEvent>> OSranked;
		OSranked.clear();
		std::vector<std::pair <std::size_t, NtupleEvent>> SSranked;
		SSranked.clear();

		std::cout<<" size "<<OSranked.size()<<" shift "<<shift<<"\n";

		for(std::size_t p = 0; p<PAIRS.size(); ++p)
		{		
			/* consider one Tau Es Variant at a time unless it pair does not involve tau_h 
			in which case treat under tauEsNominal */

			if (isnan(PAIRS[p].TauEsNumberSigmasShifted())==1 && shift != 0.0 )  continue;
			else if(PAIRS[p].TauEsNumberSigmasShifted()!=shift) continue;

			std::cout<<" shift comp "<<PAIRS[p].TauEsNumberSigmasShifted()<<" "<<shift<<" bool "<<(PAIRS[p].TauEsNumberSigmasShifted()==shift)<<"\n";

			/* start by 1st splitting up pairs into OS and SS */

			if(PAIRS[p].isOsPair()==1) m_OSpairsNoRank.push_back(PAIRS[p]);
			else m_SSpairsNoRank.push_back(PAIRS[p]);

		}	

			/* next generate std::pairs <double, NtupleEvent> in which the double
			represents the pair-ordering critera (either sumPt or isolation based) */


			OSranked = rank_pairs_BySumPt(m_OSpairsNoRank);
			SSranked = rank_pairs_BySumPt(m_SSpairsNoRank);			

			std::cout<<" OS size "<<OSranked.size()<<" ES shift = "<<shift<<"\n";
			std::cout<<" SS size "<<SSranked.size()<<" ES shift = "<<shift<<"\n";

			/* append OS and the SSranked to finalRanking */
			for(std::size_t i = 0; i<OSranked.size(); ++i) finalRanking.push_back(OSranked[i]);
			for(std::size_t i = 0; i<SSranked.size(); ++i) finalRanking.push_back(SSranked[i]);

			m_OSpairsNoRank.clear();
			m_SSpairsNoRank.clear();		


	}

	/* CHECK -- temp START */

	
	std::cout<<" ------------------------------- NEW EVENT -------------------------------\n";
	std::cout<<" input order : \n";

	for(std::size_t i = 0; i<PAIRS.size(); ++i) 
	{

		double sumPt = PAIRS[i].leg1().p4().pt()+PAIRS[i].leg2().p4().pt();
		double isOsPair = PAIRS[i].isOsPair();
		double TauEsShift = PAIRS[i].TauEsNumberSigmasShifted();
		int type = PAIRS[i].CandidateEventType();

		std::cout<<"Original Rank = "<<i<<" sumPt = "<<sumPt<<" isOS? = "<<isOsPair<<" type = "<<type<<" TauEsShift = "<<TauEsShift<<"\n";


	}


	std::cout<<" ranked order : \n";

	for(std::size_t i = 0; i<finalRanking.size(); ++i) 
	{

		double sumPt = finalRanking[i].second.leg1().p4().pt()+finalRanking[i].second.leg2().p4().pt();
		double isOsPair = finalRanking[i].second.isOsPair();
		double TauEsShift = finalRanking[i].second.TauEsNumberSigmasShifted();
		int type = finalRanking[i].second.CandidateEventType();

		std::cout<<"Final Rank = "<<finalRanking[i].first<<" sumPt = "<<sumPt<<" isOS? = "<<isOsPair<<" type = "<<type<<" TauEsShift = "<<TauEsShift<<"\n";


	}


	/* CHECK -- temp END */


}
