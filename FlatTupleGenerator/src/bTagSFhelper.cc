#include "DavisRunIITauTau/FlatTupleGenerator/interface/bTagSFhelper.h"


/* constructor */

bTagSFhelper::bTagSFhelper(edm::FileInPath csvFileName)
{
	/* hard-coded jet pT maxima */

	m_MaxBJetPt = 670.0; /* see https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration#Code_example_in_C */
	m_MaxCJetPt = 670.0;
	m_MaxLJetPt = 1000.0; 

	/* init the BTagCalibration with the csv file */

	m_calib = new BTagCalibration("csvv2", csvFileName.fullPath());

    /* create the readers (one for each WP, and one for each systematic) */
	/* note b and c jets use "mujets" measurment, while udsg use "incl" */

	m_LooseWpReaderCentral_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_LOOSE,"mujets","central");
	m_LooseWpReaderUp_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_LOOSE,"mujets","up");
	m_LooseWpReaderDown_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_LOOSE,"mujets","down");

	m_MediumWpReaderCentral_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_MEDIUM,"mujets","central");
	m_MediumWpReaderUp_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_MEDIUM,"mujets","up");
	m_MediumWpReaderDown_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_MEDIUM,"mujets","down");

	m_TightWpReaderCentral_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_TIGHT,"mujets","central");
	m_TightWpReaderUp_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_TIGHT,"mujets","up");
	m_TightWpReaderDown_forBorC = new BTagCalibrationReader(m_calib, BTagEntry::OP_TIGHT,"mujets","down");


	m_LooseWpReaderCentral_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_LOOSE,"incl","central");
	m_LooseWpReaderUp_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_LOOSE,"incl","up");
	m_LooseWpReaderDown_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_LOOSE,"incl","down");

	m_MediumWpReaderCentral_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_MEDIUM,"incl","central");
	m_MediumWpReaderUp_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_MEDIUM,"incl","up");
	m_MediumWpReaderDown_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_MEDIUM,"incl","down");

	m_TightWpReaderCentral_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_TIGHT,"incl","central");
	m_TightWpReaderUp_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_TIGHT,"incl","up");
	m_TightWpReaderDown_forUDSG = new BTagCalibrationReader(m_calib, BTagEntry::OP_TIGHT,"incl","down");



}


/* InitForJet called once per jet. Args are :

[b-tag loose working point cut],  [b-tag medium working point cut], [b-tag tight working point cut],
[jet Pt], [jet Eta], [raw b-tag score], [hadronFlavour], and [isRealData] */

void bTagSFhelper::InitForJet(double LOOSEcut_, double MEDIUMcut_, double TIGHTcut_,
								   double pt_, double eta_, double rawScore_, 
								   int flavour_, bool isData_)
{

	/* crash all this if sf tool is invoked for data (should only every apply to MC) */
	assert(!isData_);

	/* reset the scale factors */
	m_SF_LooseWpCentral = 1.0;
	m_SF_LooseWpUp = 1.0;
	m_SF_LooseWpDown = 1.0;
	m_SF_MediumWpCentral = 1.0;
	m_SF_MediumWpUp = 1.0;
	m_SF_MediumWpDown = 1.0;
	m_SF_TightWpCentral = 1.0;
	m_SF_TightWpUp = 1.0;
	m_SF_TightWpDown = 1.0;

	/* set the double uncertainty option to False by default, 
	only set to true if jet pt is out of range */
	m_DoubleUncertainty = 0; 


	/* init some member data */

	m_btag_workingPointLooseCut = LOOSEcut_;
 	m_btag_workingPointMediumCut = MEDIUMcut_; 
	m_btag_workingPointTightCut  = TIGHTcut_;
	m_jetEta = eta_;
    m_jetRawScore = rawScore_;
    m_isRealData = isData_;


    /* set the flavour, adjusting to codes needed for the SF reader */

    if(flavour_==5)  m_jetHadronFlavour = BTagEntry::FLAV_B;
    else if(flavour_==4)  m_jetHadronFlavour = BTagEntry::FLAV_C;
    else  flavour_ = BTagEntry::FLAV_UDSG;

    /* set the jetPt, use max values if exceeded and double the uncertainty */

    m_jetPt = pt_;

	/* set the double uncertainty option to False by default, 
	only set to true if jet pt is out of range */
	
	m_DoubleUncertainty = 0; 


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

    /* init the random gen. seed - done once per jet, seed is chosen by H2Tau group convention */

    m_Rand3.SetSeed((int)((m_jetEta+5)*100000));

    /* read the scale factors from the CSV file */

    // for B 
    if(m_jetHadronFlavour == BTagEntry::FLAV_B)
    {

		m_SF_LooseWpCentral = m_LooseWpReaderCentral_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_LooseWpUp = m_LooseWpReaderUp_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_LooseWpDown = m_LooseWpReaderDown_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);

		m_SF_MediumWpCentral = m_MediumWpReaderCentral_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_MediumWpUp = m_MediumWpReaderUp_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_MediumWpDown = m_MediumWpReaderDown_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
	
		m_SF_TightWpCentral = m_TightWpReaderCentral_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_TightWpUp = m_TightWpReaderUp_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
		m_SF_TightWpDown = m_TightWpReaderDown_forBorC->eval(BTagEntry::FLAV_B, m_jetEta, m_jetPt);
    
    }

    // for C
    else if(m_jetHadronFlavour == BTagEntry::FLAV_C)
    {

		m_SF_LooseWpCentral = m_LooseWpReaderCentral_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_LooseWpUp = m_LooseWpReaderUp_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_LooseWpDown = m_LooseWpReaderDown_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);

		m_SF_MediumWpCentral = m_MediumWpReaderCentral_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_MediumWpUp = m_MediumWpReaderUp_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_MediumWpDown = m_MediumWpReaderDown_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
	
		m_SF_TightWpCentral = m_TightWpReaderCentral_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_TightWpUp = m_TightWpReaderUp_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);
		m_SF_TightWpDown = m_TightWpReaderDown_forBorC->eval(BTagEntry::FLAV_C, m_jetEta, m_jetPt);

    }


    // for UDSG
    else if(m_jetHadronFlavour == BTagEntry::FLAV_UDSG)
    {



		m_SF_LooseWpCentral = m_LooseWpReaderCentral_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_LooseWpUp = m_LooseWpReaderUp_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_LooseWpDown = m_LooseWpReaderDown_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);

		m_SF_MediumWpCentral = m_MediumWpReaderCentral_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_MediumWpUp = m_MediumWpReaderUp_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_MediumWpDown = m_MediumWpReaderDown_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
	
		m_SF_TightWpCentral = m_TightWpReaderCentral_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_TightWpUp = m_TightWpReaderUp_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);
		m_SF_TightWpDown = m_TightWpReaderDown_forUDSG->eval(BTagEntry::FLAV_UDSG, m_jetEta, m_jetPt);

    }


    if(m_DoubleUncertainty)
    {

		m_SF_LooseWpUp     =  2.0 * (m_SF_LooseWpUp   - m_SF_LooseWpCentral) +  m_SF_LooseWpCentral;
		m_SF_LooseWpDown   =  2.0 * (m_SF_LooseWpDown - m_SF_LooseWpCentral) +  m_SF_LooseWpCentral;
	
		m_SF_MediumWpUp     =  2.0 * (m_SF_MediumWpUp   - m_SF_MediumWpCentral) +  m_SF_MediumWpCentral;
		m_SF_MediumWpDown   =  2.0 * (m_SF_MediumWpDown - m_SF_MediumWpCentral) +  m_SF_MediumWpCentral;
	
		m_SF_TightWpUp     =  2.0 * (m_SF_TightWpUp   - m_SF_TightWpCentral) +  m_SF_TightWpCentral;
		m_SF_TightWpDown   =  2.0 * (m_SF_TightWpDown - m_SF_TightWpCentral) +  m_SF_TightWpCentral;
	

    }


}


// functions to return scale factors 

double bTagSFhelper::SF_LooseWpCentral() const { return m_SF_LooseWpCentral; }
double bTagSFhelper::SF_LooseWpUp() const { return m_SF_LooseWpUp; }
double bTagSFhelper::SF_LooseWpDown() const { return m_SF_LooseWpDown; }
double bTagSFhelper::SF_MediumWpCentral() const { return m_SF_MediumWpCentral; }
double bTagSFhelper::SF_MediumWpUp() const { return m_SF_MediumWpUp; }
double bTagSFhelper::SF_MediumWpDown() const { return m_SF_MediumWpDown; }
double bTagSFhelper::SF_TightWpCentral() const { return m_SF_TightWpCentral; }
double bTagSFhelper::SF_TightWpUp() const { return m_SF_TightWpUp; }
double bTagSFhelper::SF_TightWpDown() const { return m_SF_TightWpDown; }

