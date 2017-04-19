/* helper class to help in decoding PU and PF jet ID working points */
/*  - S.Z. Shalhout 										 */

#ifndef DavisRunIITauTau_External_PUPFjetIdHelper_hh
#define DavisRunIITauTau_External_PUPFjetIdHelper_hh

#include <TMath.h>
#include <iostream>
#include "DavisRunIITauTau/NtupleObjects/interface/NtupleJet.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"


class PUPFjetIdHelper{

 public:

  PUPFjetIdHelper();
  ~PUPFjetIdHelper();

  /* returns the string for the cut bound pSet component of the PU ID working point PSet */
  /* args are prefix, ptBounds, absEtaBounds, jetPt, jetAbsEta */

  std::pair <std::string, unsigned int> getPtRangeStringAndEtaIndex(
  						std::string, std::vector<double>, std::vector<double>, double, double);


  /* return a pass fail for the PF jet ID given parameterSet and jet quantities */
  /* args are PFjetIDworkingPoint, ETA, NHF, NEMF, NumConst, MUF, CHF, CHM,CEMF,NumNeutralParticle  */
  bool passPfId(edm::ParameterSet, double, double, double, double, double, double, double, double, double );

  /* helper to parse PFid vectors and apply cuts */
  /* returns 1 if cut passes */
  /* args are ETA, PARvalue, CONFIGvec */
  int processPfIdCut(double,double, std::vector<double>);

  					};



PUPFjetIdHelper::PUPFjetIdHelper() {}
PUPFjetIdHelper::~PUPFjetIdHelper() {}

  int PUPFjetIdHelper::processPfIdCut(double ETA,double PARvalue, std::vector<double> CONFIGvec)
  {
  	int retvalue = 0;


  	if(ETA>=CONFIGvec[0] && ETA<=CONFIGvec[1])
    {
    	if(PARvalue>CONFIGvec[2] && CONFIGvec[3]==0) retvalue++;
    	else if(PARvalue<CONFIGvec[2] && CONFIGvec[3]==1) retvalue++;

    } else retvalue++;

  	return retvalue;

  }
	


  /* args are PFjetIDworkingPoint, NHF, NEMF, NumConst, MUF, CHF, CHM,CEMF */
  bool PUPFjetIdHelper::passPfId(edm::ParameterSet PFjetIDworkingPointSrc_, double ETA,
  	 						double NHF, double NEMF, double NumConst, double MUF, double CHF, double CHM, double CEMF, double NumNeutralParticle)

  {

  	/* for each passed cut increment the score */
  	int score = 0;

    /* NHF */
    if(PFjetIDworkingPointSrc_.exists("NHF"))
    {
      std::vector<double> NHF_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NHF");
      score += processPfIdCut(ETA, NHF, NHF_vec);
    } else score++;


  	/* NEMF */
    if(PFjetIDworkingPointSrc_.exists("NEMF"))
    {    
      std::vector<double> NEMF_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NEMF");
      score += processPfIdCut(ETA, NEMF, NEMF_vec);
    } else score++;

  	/* NumConst */
    if(PFjetIDworkingPointSrc_.exists("NumConst"))
    {        
      std::vector<double> NumConst_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NumConst");
      score += processPfIdCut(ETA, NumConst, NumConst_vec);
    } else score++;


  	/* MUF */
    if(PFjetIDworkingPointSrc_.exists("MUF"))
    {        
      std::vector<double> MUF_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("MUF");
      score += processPfIdCut(ETA, MUF, MUF_vec);
    } else score++;



  	/* CHF */
    if(PFjetIDworkingPointSrc_.exists("CHF"))
    {        
      std::vector<double> CHF_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("CHF");
      score += processPfIdCut(ETA, CHF, CHF_vec);
    } else score++;

  	/* CHM */
    if(PFjetIDworkingPointSrc_.exists("CHM"))
    {        
      std::vector<double> CHM_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("CHM");
      score += processPfIdCut(ETA, CHM, CHM_vec);
    } else score++;

  	/* CEMF */
    if(PFjetIDworkingPointSrc_.exists("CEMF"))
    {        
      std::vector<double> CEMF_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("CEMF");
      score += processPfIdCut(ETA, CEMF, CEMF_vec);
    } else score++;


    /* NEMF_HIGH */
    if(PFjetIDworkingPointSrc_.exists("NEMF_HIGH"))
    {        
      std::vector<double> NEMF_HIGH_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NEMF_HIGH");
      score += processPfIdCut(ETA, NEMF, NEMF_HIGH_vec);
    } else score++;

    /* NumNeutralParticle_HIGH */
    if(PFjetIDworkingPointSrc_.exists("NumNeutralParticle_HIGH"))
    {        
      std::vector<double> NumNeutralParticle_HIGH_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NumNeutralParticle_HIGH");
      score += processPfIdCut(ETA, NumNeutralParticle, NumNeutralParticle_HIGH_vec);
    } else score++;


    /* NEMF_LOW */
    if(PFjetIDworkingPointSrc_.exists("NEMF_LOW"))
    {        
      std::vector<double> NEMF_LOW_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NEMF_LOW");
      score += processPfIdCut(ETA, NEMF, NEMF_LOW_vec);
    } else score++;

    /* NumNeutralParticle_LOW */
    if(PFjetIDworkingPointSrc_.exists("NumNeutralParticle_LOW"))
    {        
      std::vector<double> NumNeutralParticle_LOW_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NumNeutralParticle_LOW");
      score += processPfIdCut(ETA, NumNeutralParticle, NumNeutralParticle_LOW_vec);
    } else score++;




    /* NEMF_27_30 */
    if(PFjetIDworkingPointSrc_.exists("NEMF_27_30"))
    {        
      std::vector<double> NEMF_27_30_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NEMF_27_30");
      score += processPfIdCut(ETA, NEMF, NEMF_27_30_vec);
    } else score++;


    /* NHF_27_30 */
    if(PFjetIDworkingPointSrc_.exists("NHF_27_30"))
    {        
      std::vector<double> NHF_27_30_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NHF_27_30");
      score += processPfIdCut(ETA, NHF, NHF_27_30_vec);
    } else score++;


    /* NumNeutralParticle_27_30 */
    if(PFjetIDworkingPointSrc_.exists("NumNeutralParticle_27_30"))
    {        
      std::vector<double> NumNeutralParticle_27_30_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NumNeutralParticle_27_30");
      score += processPfIdCut(ETA, NumNeutralParticle, NumNeutralParticle_27_30_vec);
    } else score++;


    /* NEMF_NEG_30_27 */
    if(PFjetIDworkingPointSrc_.exists("NEMF_NEG_30_27"))
    {        
      std::vector<double> NEMF_NEG_30_27_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NEMF_NEG_30_27");
      score += processPfIdCut(ETA, NEMF, NEMF_NEG_30_27_vec);
    } else score++;


    /* NHF_NEG_30_27 */
    if(PFjetIDworkingPointSrc_.exists("NHF_NEG_30_27"))
    {        
      std::vector<double> NHF_NEG_30_27_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NHF_NEG_30_27");
      score += processPfIdCut(ETA, NHF, NHF_NEG_30_27_vec);
    } else score++;


    /* NumNeutralParticle_NEG_30_27 */
    if(PFjetIDworkingPointSrc_.exists("NumNeutralParticle_NEG_30_27"))
    {        
      std::vector<double> NumNeutralParticle_NEG_30_27_vec =  PFjetIDworkingPointSrc_.getParameter<std::vector<double> >("NumNeutralParticle_NEG_30_27");
      score += processPfIdCut(ETA, NumNeutralParticle, NumNeutralParticle_NEG_30_27_vec);
    } else score++;



	if (score == 17) return 1;
	return 0;
  }



std::pair <std::string, unsigned int> PUPFjetIdHelper::getPtRangeStringAndEtaIndex(
  						std::string prefix, std::vector<double> ptBounds, 
  						std::vector<double> absEtaBounds, double jetPt, double jetAbsEta)
	{
		std::string returnName;
		unsigned int returnIndex = 0;
		double ptLowerBound = 0;
		double ptHigherBound = 10;

		/* note not using <= or >= here since default jet ID code does not have them */


		// eta range
		for(unsigned int i = 0; i < absEtaBounds.size(); ++i)
		{

			if( fabs(jetAbsEta) > absEtaBounds[i] && fabs(jetAbsEta) < absEtaBounds[i+1] ) 
				{
					returnIndex = i;
				}		
		}			

		// pt range
		for(unsigned int i = 0; i < ptBounds.size(); ++i)
		{

			if( jetPt > ptBounds[i] && jetPt < ptBounds[i+1] ) 
				{
					ptLowerBound = ptBounds[i];
					ptHigherBound = ptBounds[i+1];
				}				

		}			

		// last bin might be something like 30 to 50 but it means > 30 :

		if(jetPt > ptBounds[ptBounds.size()-1] && ptBounds.size()>=2) 
		{
			 ptLowerBound = ptBounds[ptBounds.size()-2];
		     ptHigherBound = ptBounds[ptBounds.size()-1];

		}



		returnName = prefix+std::to_string(int(ptLowerBound))+std::to_string(int(ptHigherBound));

		std::pair <std::string, unsigned int> returnPair(returnName,returnIndex);

		return returnPair;
	}



#endif
