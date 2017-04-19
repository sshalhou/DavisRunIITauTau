#include "DavisRunIITauTau/FlatTupleGenerator/interface/bTagSFhelper.h"


/* constructor */

bTagSFhelper::bTagSFhelper(BTagCalibration calibTool, edm::FileInPath looseEffRootFile, 
   edm::FileInPath mediumEffRootFile, edm::FileInPath tightEffRootFile,
   double cutL_, double cutM_, double cutT_,
    TH2F hist_LooseEff_b, TH2F hist_LooseEff_c, TH2F hist_LooseEff_usdg, 
	TH2F hist_MediumEff_b, TH2F hist_MediumEff_c, TH2F hist_MediumEff_usdg, 
	TH2F hist_TightEff_b, TH2F hist_TightEff_c, TH2F hist_TightEff_usdg,							
	BTagCalibrationReader reader_LooseWpReaderAllVariants_forB,
	BTagCalibrationReader reader_MediumWpReaderAllVariants_forB, 
	BTagCalibrationReader reader_TightWpReaderAllVariants_forB, 
	BTagCalibrationReader reader_LooseWpReaderAllVariants_forC,
	BTagCalibrationReader reader_MediumWpReaderAllVariants_forC, 
	BTagCalibrationReader reader_TightWpReaderAllVariants_forC, 
	BTagCalibrationReader reader_LooseWpReaderAllVariants_forUDSG, 
	BTagCalibrationReader reader_MediumWpReaderAllVariants_forUDSG, 
	BTagCalibrationReader reader_TightWpReaderAllVariants_forUDSG)
{

	/* setup the Btag SF tool */

	m_calib = calibTool;

	/* setup the Btag SF readers */

	m_LooseWpReaderAllVariants_forB  = reader_LooseWpReaderAllVariants_forB;
	m_MediumWpReaderAllVariants_forB  = reader_MediumWpReaderAllVariants_forB;
	m_TightWpReaderAllVariants_forB  = reader_TightWpReaderAllVariants_forB;

	m_LooseWpReaderAllVariants_forC  = reader_LooseWpReaderAllVariants_forC;
	m_MediumWpReaderAllVariants_forC  = reader_MediumWpReaderAllVariants_forC;
	m_TightWpReaderAllVariants_forC  = reader_TightWpReaderAllVariants_forC;

	m_LooseWpReaderAllVariants_forUDSG  = reader_LooseWpReaderAllVariants_forUDSG;
	m_MediumWpReaderAllVariants_forUDSG  = reader_MediumWpReaderAllVariants_forUDSG;
	m_TightWpReaderAllVariants_forUDSG  = reader_TightWpReaderAllVariants_forUDSG;

	/* set the b-tag eff histograms */

	m_LooseEff_b = hist_LooseEff_b;
	m_LooseEff_c = hist_LooseEff_c;
	m_LooseEff_usdg = hist_LooseEff_usdg;
	m_MediumEff_b = hist_MediumEff_b;
	m_MediumEff_c = hist_MediumEff_c;
	m_MediumEff_usdg = hist_MediumEff_usdg;
	m_TightEff_b = hist_TightEff_b;
	m_TightEff_c = hist_TightEff_c;
	m_TightEff_usdg = hist_TightEff_usdg;

	/* set the files */

	m_looseEffRootFile = looseEffRootFile;
	m_mediumEffRootFile = mediumEffRootFile;
	m_tightEffRootFile = tightEffRootFile;

	/* set the cuts */

	m_cutLoose = cutL_;
	m_cutMedium = cutM_;
	m_cutTight = cutT_;


	

	/* hard-coded jet pT maxima & minima */

	m_MaxBJetPt = 670.0; /* see https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration#Code_example_in_C */
	m_MaxCJetPt = 670.0;
	m_MaxLJetPt = 1000.0; 

	m_MinBJetPt = 30.0;
	m_MinCJetPt = 30.0;
	m_MinLJetPt = 20.0;

	std::cout<<" JET PT MIN AND MAX (for valid b-tag SF range) = \n";
	std::cout<<" **** b-jets ["<<m_MinBJetPt<<","<<m_MaxBJetPt<<"] \n";
	std::cout<<" **** c-jets ["<<m_MinCJetPt<<","<<m_MaxCJetPt<<"] \n";
	std::cout<<" **** usgd-jets ["<<m_MinLJetPt<<","<<m_MaxLJetPt<<"] \n";
	std::cout<<" CHANGE IN bTagSFhelper.cc if not correct \n";

}


/* InitForJet called once per jet. Args are :
[jet Pt], [jet Eta], [raw b-tag score], [hadronFlavour] */

void bTagSFhelper::InitForJet(double pt_, double eta_, double rawScore_, 
								   int flavour_, bool isRealData_)
{



	/* reset the scale factors and eff. */
	m_SF_LooseWpCentral = 1.0;
	m_SF_LooseWpUp = 1.0;
	m_SF_LooseWpDown = 1.0;
	m_SF_MediumWpCentral = 1.0;
	m_SF_MediumWpUp = 1.0;
	m_SF_MediumWpDown = 1.0;
	m_SF_TightWpCentral = 1.0;
	m_SF_TightWpUp = 1.0;
	m_SF_TightWpDown = 1.0;

	m_EFF_LooseWp = 1.0;
	m_EFF_MediumWp = 1.0;
	m_EFF_TightWp = 1.0;

	/* reset the btags */

	m_IsTagged_LooseWpCentral= 0;
	m_IsTagged_LooseWpUp= 0;
	m_IsTagged_LooseWpDown= 0;
	m_IsTagged_MediumWpCentral= 0;
	m_IsTagged_MediumWpUp= 0;
	m_IsTagged_MediumWpDown= 0;
	m_IsTagged_TightWpCentral= 0;
	m_IsTagged_TightWpUp= 0;
	m_IsTagged_TightWpDown= 0;



	/* set the double uncertainty option to False by default, 
	only set to true if jet pt is out of range */
	m_DoubleUncertainty = 0; 


	/* init some member data */


	m_jetEta = eta_;
    m_jetRawScore = rawScore_;


    /* set the flavour, adjusting to codes needed for the SF reader */

    if(flavour_==5)  m_jetHadronFlavour = BTagEntry::FLAV_B;
    else if(flavour_==4)  m_jetHadronFlavour = BTagEntry::FLAV_C;
    else  m_jetHadronFlavour = BTagEntry::FLAV_UDSG;

    /* set the jetPt, use max values if exceeded and double the uncertainty */

    m_jetPt = pt_;

	/* set the double uncertainty option to False by default, 
	only set to true if jet pt is out of range */
	
	m_DoubleUncertainty = 0; 


	// pt over limit 
    if(m_jetHadronFlavour == BTagEntry::FLAV_B && m_jetPt>m_MaxBJetPt) 
	{
		m_jetPt = m_MaxBJetPt * 0.99999;
		m_DoubleUncertainty = 1;
	}	
    else if(m_jetHadronFlavour == BTagEntry::FLAV_C && m_jetPt>m_MaxCJetPt) 
    { 
    	m_jetPt = m_MaxCJetPt * 0.99999;
		m_DoubleUncertainty = 1;
	}	    
    else if(m_jetHadronFlavour == BTagEntry::FLAV_UDSG && m_jetPt>m_MaxLJetPt)
    { 
    	m_jetPt = m_MaxLJetPt * 0.99999;
		m_DoubleUncertainty = 1;
	}	

	// pt too small 


    if(m_jetHadronFlavour == BTagEntry::FLAV_B && m_jetPt<=m_MinBJetPt) 
	{
		m_jetPt = m_MinBJetPt * 1.00001;
		m_DoubleUncertainty = 1;
	}	
    else if(m_jetHadronFlavour == BTagEntry::FLAV_C && m_jetPt<=m_MinCJetPt) 
    { 
    	m_jetPt = m_MinCJetPt * 1.00001;
		m_DoubleUncertainty = 1;
	}	    
    else if(m_jetHadronFlavour == BTagEntry::FLAV_UDSG && m_jetPt<=m_MinLJetPt)
    { 
    	m_jetPt = m_MinLJetPt * 1.00001;
		m_DoubleUncertainty = 1;
	}	

    /* read the scale factors from the CSV file */

    // for B 
    if(m_jetHadronFlavour == BTagEntry::FLAV_B)
    {
    	//std::cout<<" have *** a B with m_jetHadronFlavour = "<<m_jetHadronFlavour<<"\n";
		m_SF_MediumWpCentral = m_MediumWpReaderAllVariants_forB.eval_auto_bounds("central",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_MediumWpUp = m_MediumWpReaderAllVariants_forB.eval_auto_bounds("up",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_MediumWpDown = m_MediumWpReaderAllVariants_forB.eval_auto_bounds("down",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
	
		m_SF_LooseWpCentral = m_LooseWpReaderAllVariants_forB.eval_auto_bounds("central",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_LooseWpUp = m_LooseWpReaderAllVariants_forB.eval_auto_bounds("up",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_LooseWpDown = m_LooseWpReaderAllVariants_forB.eval_auto_bounds("down",BTagEntry::FLAV_B, m_jetEta, m_jetPt);

		m_SF_TightWpCentral = m_TightWpReaderAllVariants_forB.eval_auto_bounds("central",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_TightWpUp = m_TightWpReaderAllVariants_forB.eval_auto_bounds("up",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_TightWpDown = m_TightWpReaderAllVariants_forB.eval_auto_bounds("down",BTagEntry::FLAV_B, m_jetEta, m_jetPt);
    
		/* extract the b-tag eff. from TFiles and TH2D histograms */

		int BINx_ = 0;
		int BINy_ = 0;


		/* Loose eff. */
	    BINx_ = m_LooseEff_b.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_LooseEff_b.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_LooseWp = m_LooseEff_b.GetBinContent(BINx_,BINy_);

		/* Medium eff. */
	    BINx_ = m_MediumEff_b.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_MediumEff_b.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_MediumWp = m_MediumEff_b.GetBinContent(BINx_,BINy_);
	
		/* Tight eff. */
	    BINx_ = m_TightEff_b.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_TightEff_b.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_TightWp = m_TightEff_b.GetBinContent(BINx_,BINy_);

    	//std::cout<<" _b jet eff are "<<m_EFF_LooseWp<<" , "<<m_EFF_MediumWp<<" , "<<m_EFF_TightWp<<"\n";


    }

    // for C
    else if(m_jetHadronFlavour == BTagEntry::FLAV_C)
    {

    	//std::cout<<" have *** a C with m_jetHadronFlavour = "<<m_jetHadronFlavour<<"\n";

		m_SF_MediumWpCentral = m_MediumWpReaderAllVariants_forC.eval_auto_bounds("central",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_MediumWpUp = m_MediumWpReaderAllVariants_forC.eval_auto_bounds("up",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_MediumWpDown = m_MediumWpReaderAllVariants_forC.eval_auto_bounds("down",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
	
		m_SF_LooseWpCentral = m_LooseWpReaderAllVariants_forC.eval_auto_bounds("central",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_LooseWpUp = m_LooseWpReaderAllVariants_forC.eval_auto_bounds("up",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_LooseWpDown = m_LooseWpReaderAllVariants_forC.eval_auto_bounds("down",BTagEntry::FLAV_C, m_jetEta, m_jetPt);


		m_SF_TightWpCentral = m_TightWpReaderAllVariants_forC.eval_auto_bounds("central",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_TightWpUp = m_TightWpReaderAllVariants_forC.eval_auto_bounds("up",BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_TightWpDown = m_TightWpReaderAllVariants_forC.eval_auto_bounds("down",BTagEntry::FLAV_C, m_jetEta, m_jetPt);

		/* extract the b-tag eff. from TFiles and TH2D histograms */

		int BINx_ = 0;
		int BINy_ = 0;

		/* Loose eff. */
	    BINx_ = m_LooseEff_c.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_LooseEff_c.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_LooseWp = m_LooseEff_c.GetBinContent(BINx_,BINy_);

		/* Medium eff. */
	    BINx_ = m_MediumEff_c.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_MediumEff_c.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_MediumWp = m_MediumEff_c.GetBinContent(BINx_,BINy_);
	
		/* Tight eff. */
	    BINx_ = m_TightEff_c.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_TightEff_c.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_TightWp = m_TightEff_c.GetBinContent(BINx_,BINy_);

    	// std::cout<<" _c jet eff are "<<m_EFF_LooseWp<<" , "<<m_EFF_MediumWp<<" , "<<m_EFF_TightWp<<"\n";



    }


    // for UDSG
    else if(m_jetHadronFlavour == BTagEntry::FLAV_UDSG)
    {

    	 // std::cout<<" have *** a UDSG with m_jetHadronFlavour = "<<m_jetHadronFlavour<<"\n";

		m_SF_MediumWpCentral = m_MediumWpReaderAllVariants_forUDSG.eval_auto_bounds("central",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_MediumWpUp = m_MediumWpReaderAllVariants_forUDSG.eval_auto_bounds("up",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_MediumWpDown = m_MediumWpReaderAllVariants_forUDSG.eval_auto_bounds("down",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
	
		m_SF_LooseWpCentral = m_LooseWpReaderAllVariants_forUDSG.eval_auto_bounds("central",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_LooseWpUp = m_LooseWpReaderAllVariants_forUDSG.eval_auto_bounds("up",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_LooseWpDown = m_LooseWpReaderAllVariants_forUDSG.eval_auto_bounds("down",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);

		m_SF_TightWpCentral = m_TightWpReaderAllVariants_forUDSG.eval_auto_bounds("central",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_TightWpUp = m_TightWpReaderAllVariants_forUDSG.eval_auto_bounds("up",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_TightWpDown = m_TightWpReaderAllVariants_forUDSG.eval_auto_bounds("down",BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);


		/* extract the b-tag eff. from TFiles and TH2D histograms */

		int BINx_ = 0;
		int BINy_ = 0;

		/* Loose eff. */
	    BINx_ = m_LooseEff_usdg.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_LooseEff_usdg.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_LooseWp = m_LooseEff_usdg.GetBinContent(BINx_,BINy_);

		/* Medium eff. */
	    BINx_ = m_MediumEff_usdg.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_MediumEff_usdg.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_MediumWp = m_MediumEff_usdg.GetBinContent(BINx_,BINy_);
	
		/* Tight eff. */
	    BINx_ = m_TightEff_usdg.GetXaxis()->FindBin(m_jetPt);
    	BINy_ = m_TightEff_usdg.GetYaxis()->FindBin(m_jetEta);
    	m_EFF_TightWp = m_TightEff_usdg.GetBinContent(BINx_,BINy_);

    	// std::cout<<" _usdg jet eff are "<<m_EFF_LooseWp<<" , "<<m_EFF_MediumWp<<" , "<<m_EFF_TightWp<<"\n";




    }

    else  { std::cout<<" have *** a NOTHING with m_jetHadronFlavour = "<<m_jetHadronFlavour<<"\n"; }


    if(m_DoubleUncertainty)
    {

		m_SF_LooseWpUp     =  2.0 * (m_SF_LooseWpUp   - m_SF_LooseWpCentral) +  m_SF_LooseWpCentral;
		m_SF_LooseWpDown   =  2.0 * (m_SF_LooseWpDown - m_SF_LooseWpCentral) +  m_SF_LooseWpCentral;
	
		m_SF_MediumWpUp     =  2.0 * (m_SF_MediumWpUp   - m_SF_MediumWpCentral) +  m_SF_MediumWpCentral;
		m_SF_MediumWpDown   =  2.0 * (m_SF_MediumWpDown - m_SF_MediumWpCentral) +  m_SF_MediumWpCentral;
	
		m_SF_TightWpUp     =  2.0 * (m_SF_TightWpUp   - m_SF_TightWpCentral) +  m_SF_TightWpCentral;
		m_SF_TightWpDown   =  2.0 * (m_SF_TightWpDown - m_SF_TightWpCentral) +  m_SF_TightWpCentral;
	

    }

    PromoteDemoteBtags(rawScore_, m_cutLoose, m_cutMedium, m_cutTight, isRealData_);


}

// function to apply promote-demote method of b-tag SFs


void bTagSFhelper::PromoteDemoteBtags(double raw_, double cutL_, double cutM_, double cutT_, bool isRealData_)
{

	// std::cout<<" Raw b-tags are L, M, T : "<<(raw_>cutL_)<<" , "<<(raw_>cutM_)<<" , "<<(raw_>cutT_)<<"\n";

	if(isRealData_)
	{
		/* for data evaluate the cuts, no systematics are applied */

		m_IsTagged_LooseWpCentral	= (raw_>cutL_);
		m_IsTagged_LooseWpUp	= m_IsTagged_LooseWpCentral;
		m_IsTagged_LooseWpDown	= m_IsTagged_LooseWpCentral;

		m_IsTagged_MediumWpCentral	= (raw_>cutM_);
		m_IsTagged_MediumWpUp	= m_IsTagged_MediumWpCentral;
		m_IsTagged_MediumWpDown	= m_IsTagged_MediumWpCentral;

		m_IsTagged_TightWpCentral	= (raw_>cutT_);
		m_IsTagged_TightWpUp	= m_IsTagged_TightWpCentral;
		m_IsTagged_TightWpDown	= m_IsTagged_TightWpCentral;

	}

	else
	{
		/* use unique random seed, and a single random draw for each jet */

		TRandom3 m_rand; 
		m_rand.SetSeed((int)((m_jetEta+5)*100000)); 
		float coin = m_rand.Uniform(1.);
			

		m_IsTagged_LooseWpCentral = applyBTagSF( (raw_>cutL_), m_SF_LooseWpCentral, m_EFF_LooseWp, coin);
		m_IsTagged_LooseWpUp = applyBTagSF( (raw_>cutL_), m_SF_LooseWpUp, m_EFF_LooseWp, coin);
		m_IsTagged_LooseWpDown = applyBTagSF( (raw_>cutL_), m_SF_LooseWpDown, m_EFF_LooseWp, coin);

		m_IsTagged_MediumWpCentral = applyBTagSF( (raw_>cutM_), m_SF_MediumWpCentral, m_EFF_MediumWp, coin);
		m_IsTagged_MediumWpUp = applyBTagSF( (raw_>cutM_), m_SF_MediumWpUp, m_EFF_MediumWp, coin);
		m_IsTagged_MediumWpDown = applyBTagSF( (raw_>cutM_), m_SF_MediumWpDown, m_EFF_MediumWp, coin);

		m_IsTagged_TightWpCentral = applyBTagSF( (raw_>cutT_), m_SF_TightWpCentral, m_EFF_TightWp, coin);
		m_IsTagged_TightWpUp = applyBTagSF( (raw_>cutT_), m_SF_TightWpUp, m_EFF_TightWp, coin);
		m_IsTagged_TightWpDown = applyBTagSF( (raw_>cutT_), m_SF_TightWpDown, m_EFF_TightWp, coin);
	}








}


// apply the b-tag SF 

bool bTagSFhelper::applyBTagSF(bool isBTagged, double Btag_SF, double Btag_eff, float coin)
{
  bool newBTag = isBTagged;

  if (Btag_SF == 1) 
  {
  	return newBTag; //no correction needed
  }
  	

  if(Btag_SF > 1)
  {  

    if( !isBTagged ) 
    {

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1.0/Btag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newBTag = true;}
    }

  }
  else
  {  

    //downgrade tagged to untagged
    if( isBTagged && coin > Btag_SF ) {newBTag = false;}

  }

  return newBTag;
}



// functions to return scale factors and eff. 

double bTagSFhelper::SF_LooseWpCentral() const { return m_SF_LooseWpCentral; }
double bTagSFhelper::SF_LooseWpUp() const { return m_SF_LooseWpUp; }
double bTagSFhelper::SF_LooseWpDown() const { return m_SF_LooseWpDown; }
double bTagSFhelper::SF_MediumWpCentral() const { return m_SF_MediumWpCentral; }
double bTagSFhelper::SF_MediumWpUp() const { return m_SF_MediumWpUp; }
double bTagSFhelper::SF_MediumWpDown() const { return m_SF_MediumWpDown; }
double bTagSFhelper::SF_TightWpCentral() const { return m_SF_TightWpCentral; }
double bTagSFhelper::SF_TightWpUp() const { return m_SF_TightWpUp; }
double bTagSFhelper::SF_TightWpDown() const { return m_SF_TightWpDown; }


double bTagSFhelper::getCutPointMedium() const { return m_cutMedium; }


double bTagSFhelper::EFF_LooseWp() const { return m_EFF_LooseWp; }
double bTagSFhelper::EFF_MediumWp() const { return m_EFF_MediumWp; }
double bTagSFhelper::EFF_TightWp() const { return m_EFF_TightWp; }

// return final tags after PromoteDemoteBtags is called


bool bTagSFhelper::IsTagged_LooseWpCentral() const { return m_IsTagged_LooseWpCentral; }
bool bTagSFhelper::IsTagged_LooseWpUp() const { return m_IsTagged_LooseWpUp; }
bool bTagSFhelper::IsTagged_LooseWpDown() const { return m_IsTagged_LooseWpDown; }
bool bTagSFhelper::IsTagged_MediumWpCentral() const { return m_IsTagged_MediumWpCentral; }
bool bTagSFhelper::IsTagged_MediumWpUp() const { return m_IsTagged_MediumWpUp; }
bool bTagSFhelper::IsTagged_MediumWpDown() const { return m_IsTagged_MediumWpDown; }
bool bTagSFhelper::IsTagged_TightWpCentral() const { return m_IsTagged_TightWpCentral; }
bool bTagSFhelper::IsTagged_TightWpUp() const { return m_IsTagged_TightWpUp; }
bool bTagSFhelper::IsTagged_TightWpDown() const { return m_IsTagged_TightWpDown; }



