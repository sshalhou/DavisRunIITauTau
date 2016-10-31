/* to do -- add in signal curves with multiplyier option -- formatting needed */
/* to do -- add in option to not draw data on signal region plots */


///////////////////////////////////////////////////////////
// root -l
// .L miniAODv2_76X_analysisMacro.C+
// miniAODv2_76X_analysisMacro()
////////////////////////////////////////////////////////////

#include <iostream>
#include <map>
#include "TChain.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TVector2.h"
#include "TMath.h"
#include <fstream>

#include "TLine.h"
#include "TH1F.h"
#include "TCut.h"
#include <iomanip>
#include "TFile.h"
#include <stdio.h>
#include "TApplication.h"

#include "tdrstyle.C"
#include "loadTChains.C"

///////////////////////////////////////////////////////////
// global vars. & function decs. 
///////////////////////////////////////////////////////////

/* channel bools */

bool do_mTau = 0;
bool do_eTau = 0;
bool do_eMu = 0;
bool do_TauTau = 0;
bool do_All = 0;

/* DATA maximum factor on hists y-axis */

int DATA_MAX = 2;
float DATA_MIN = 1e-1;
int LOG_MAX = 1000;

/* set log y */
bool setLog  = 0;

/* plot signals */

bool shouldIplotSignals = 0;

/* for safety blind met (in data) above this value, and m_vis between these */
double met_blind = 100;

/* plotting region key requirement -- usually a cut on the met!
   for control region data usually choose met < 100
   if no cut is applied, make sure to set signalRegionMETonly to 1
   (no other dists. will be shown in that case)*/

std::map <int,std::string> drCutMap;
std::map <std::string,std::string> met_options;
std::map <std::string,TCut> jetCutMap;
std::map <std::string,TCut> wNorm_cut_options;

std::string metCutVal = "";
bool cRegion = 0;
bool signalRegionMETonly = 1;
bool evalBaselineSys = 0;
bool evalEnergyShiftSys = 0;
int drCut;

// TCut keyCut("met<100");

/* lumi sf (3.0/fb projection)*/ 

double lumi_sf = 1.0;

/* data marker style */

int dataMarker = 8;

/* some hist binnings */

float mtBinning[3] = {50.,0.,250.}; /* for mt in all regions */
float metBinning[3] = {50.,0.,1000.};  /* for met in all regions */
float m_visBinning[3] = {25.,0.,250.}; /* for m_vis in all regions */
float ptBinning[3] = {40.,0.,200.}; /* for pT in all regions */
float nbtagBinning[3] = {30.,0.,30.}; /* for nbtag in all regions */
float lptBinning[3] = {35.,0.,3500.};
float m_minBinning[3] = {20,0.,1000.};
float p_chiBinning[3] = {30,-150.,150.};


/* some hist x-axis labels */
std::map<std::string,std::string > x_axisLabels;

/* stack plot colors */

std::map<std::string,int> colors;

/* channel label */

std::string chan_label;

/* canvas dim */

int canDim[2] = {900,750};

/* lumi and sqrt(s) */

std::string lumiAndRtS = "[2.3/fb @ 13 TeV]";

/* sample weights (sample, weight) */

std::map<std::string,std::string> weights;

/* QCD OS to SS scale factor -- to be measured */

double qcdOStoSS = 1.06;


//txt file with sys
std::string saveNameValues = "baselineSys.txt";
ofstream out_data(saveNameValues.c_str());

/* string to hold main title for hists */

std::string global_title;

/* string for canvas save prefix */

std::string saveName;

/* given a TCut obtain a [data-(non-W)]/W scale factor */
/* args are cut, canvas name */

double wjetsNorm(TCut, std::string);
double wjetsNorm_NoPlots(TCut);

/* given a TCut and a w mc scale factor fill a TH1F with a qcd shape under the TCut */
/* args are cut, w sf, qcd hist to fill, string expression to fill (pt_1 m_vis etc.), binning array,
canvas name string */

void fillQCD_Shape(TCut, double, TH1F *, std::string, float[3], std::string, std::string);
void fillQCD_Shape_NoPlots(TCut, double, TH1F *, std::string, float[3]);

/* given a TCut and a w mc scale factor and a qcd shape draw string under float[3] binning */
/* args are cut, w sf, qcd hist to draw, string expression to fill (pt_1 m_vis etc.), 
binning array, canvas name */

void drawSignalRegion(TCut, double, TH1F *, std::string, float[3], std::string, std::string);

/*output vector of yields, no plots*/

std::vector<std::vector<double>> countSignalRegion(TCut, double, TH1F *, std::string, float[3]);

/* determine BKG fraction distribution */

void findBkgFractions(TCut, double, std::string, float[3]);

/* find systematic for baseline variations */

void evalSysBaseline(std::vector<std::vector<double>>, TCut, TCut, TCut, TCut, TCut, TCut, TCut, TCut, std::string, float[3], std::string);
//for  channels with negligable W contribution
void evalSysBaselineNoW(std::vector<std::vector<double>>, TCut, TCut, TCut, TCut, std::string, float[3], std::string);

double deltar_( double eta1, double phi1, double eta2, double phi2)
{
	double deta  = eta1 - eta2;
	double dphi = TVector2::Phi_mpi_pi(phi1-phi2);
	return TMath::Sqrt(deta*deta+dphi*dphi);
}

/* run channels */

void doMuTau();
void doEleTau();
void doEleMu();
void doTauTau();

/* draw a standard TCanvas and TLatex for this analysis */
/* as well as a ratio plot (canvas must have 2 dirs) */

void drawTcanvasAndLegendAndRatio(TCanvas *, TH1F*, TH1F*, bool); /* data, sumBkg ,  bool drawSignals?*/

///////////////////////////////////////////////////////////
// main function
///////////////////////////////////////////////////////////

int miniAODv2_76X_analysisMacro()
{
    
	/* interactive */
	int choice = -1;
	int choice2 = -1;
	int choice3 = -1;
	int choice4 = -1;

	while(choice <1 || choice >5)
	{
		std::cout<<" Please enter a channel choice \n";
		std::cout<<" 			enter 1 for muTau \n";
		std::cout<<" 			enter 2 for eTau \n";
		std::cout<<" 			enter 3 for eMu \n";
		std::cout<<" 			enter 4 for TauTau \n";
        std::cout<<" 			enter 5 for all channels \n";

	    cin>>choice;
	}

	/* string for canvas saving */
	saveName = "";

	if(choice==1) {do_mTau = 1; saveName += "MuTau_"; }
	if(choice==2) {do_eTau = 1; saveName += "EleTau_"; }
	if(choice==3) {do_eMu = 1; saveName += "EleMu_"; }
	if(choice==4) {do_TauTau = 1; saveName += "TauTau_"; }
    if(choice==5) {do_All = 1; saveName += "AllChanRun_"; }

	while(choice2!=1 && choice2!=2 && choice2!=3 && choice2!=4)
	{
		std::cout<<" Choose a plot set : \n";
		std::cout<<" 			enter 1 for signal region full MET dist. (above a cut) with blind tail \n";
		std::cout<<" 			enter 2 for many plots in MET<100 GeV control region \n";
        std::cout<<"                        enter 3 for baseline systematics \n";
        std::cout<<"                        enter 4 for ES shift systematics \n";
		cin>>choice2;
	}
    
	if(choice2==1)
	{
		signalRegionMETonly = 1;
		metBinning[0] = 50;
		metBinning[1] = 0;
		metBinning[2] = 1000;
		std::cout<<" enter a met cut value ";
		cin>>metCutVal;
		saveName += (("signalRegion_met_over_" + metCutVal + "_").c_str());
	}
	if(choice2==2)
	{
        cRegion = 1;
		signalRegionMETonly = 0;
		metBinning[0] = 25;
		metBinning[1] = 0;
		metBinning[2] = 150;
		saveName += ("lowMETRegion_");

	}
    if(choice2==3)
	{
        
        evalBaselineSys = 1;
		metBinning[0] = 50;
		metBinning[1] = 0;
		metBinning[2] = 1000;
        std::cout<<" enter a met cut value ";
		cin>>metCutVal;
	}
    if(choice2==4)
	{
        evalEnergyShiftSys = 1;
		metBinning[0] = 50;
		metBinning[1] = 0;
		metBinning[2] = 1000;
        std::cout<<" enter a met cut value ";
		cin>>metCutVal;

	}
	while(choice4!=1 && choice4!=2 && choice4!=3)
	{
		std::cout<<" enter DR range : \n";
		std::cout<<"	   enter 1 for low  [ dr(tau,tau)<1 ] \n";
		std::cout<<"	   enter 2 for medium  [ dr(tau,tau)>=1 && dr(tau,tau) < 2.0] \n";
        std::cout<<"	   enter 3 for all regions above minimum\n";
		cin>>choice4;

		if(choice4==1)
        {
         drCut = 1;
         saveName += "LowDR_";
        }
		if(choice4==2)
        {
         drCut = 2;
         saveName += "MidDR_";
        }
        if(choice4==3)
        {
         drCut = 3;
         saveName += "FullDR_";
        }
	}
	while(choice3!=1 && choice3!=2)
	{
		std::cout<<" Choose a plot style : \n";
		std::cout<<" 			enter 1 logarithmic \n";
		std::cout<<" 			enter 2 normal \n";

		cin>>choice3;
	}
	if(choice3==1) { setLog = 1; saveName += "log_"; }
	else { setLog = 0; saveName += "norm_";}

	if(choice2==1 /*&& choice3==1*/) { shouldIplotSignals = 1;  DATA_MIN = 1e-2; }

	/////////////////

	/* some formatting */
	setTDRStyle();
	/* int colors */
	colors["ZTT"] = 92;
    colors["ZL"] = 94;
    colors["ZJ"] = 96;
	colors["TT"] = 2;
    colors["VV"] = 8;
	colors["W"] = 634;
	colors["QCD"] = 606;
    colors["GluGluHTauTau"] = 7;
    colors["VBFHTauTau"] = 9;
    colors["ttHJetTT"] = 11;
	colors["ZHTauTau"] = 52;
    colors["WHTauTau"] = 5;
	colors["MONO"] = 4;

	/* x - axis labels */

	x_axisLabels["m_vis"] = "Visible di-#tau Mass [GeV]";
	x_axisLabels["nbtag"] = "Number of Jets";
	x_axisLabels["met"] = "Missing Transverse Energy (PF) [GeV]";
    x_axisLabels["LPT"] = "Likelihood Transverse Momentum of Pair Mother [GeV]";

	if(do_eTau)
	{
		x_axisLabels["mt_1"] = "Transverse Mass (e,MET) [GeV]";
		x_axisLabels["pt_1"] = "Transverse Momentum of Electron [GeV]";
		x_axisLabels["pt_2"] = "Transverse Momentum of #tau_{h} [GeV]";
        x_axisLabels["M_min"] = "Function M_min [GeV]";
        x_axisLabels["P_chi"] = "Function P_chi [GeV]";
	}

	if(do_eMu) 
	{
		x_axisLabels["mt_1"] = "Transverse Mass (e,MET) [GeV]";
		x_axisLabels["pt_1"] = "Transverse Momentum of Electron [GeV]";
		x_axisLabels["pt_2"] = "Transverse Momentum of Muon [GeV]";
	}

	if(do_mTau) 
	{
		x_axisLabels["mt_1"] = "Transverse Mass (#mu,MET) [GeV]";
		x_axisLabels["pt_1"] = "Transverse Momentum of Muon [GeV]";
		x_axisLabels["pt_2"] = "Transverse Momentum of #tau_{h} [GeV]";
        x_axisLabels["M_min"] = "Function M_min [GeV]";
        x_axisLabels["P_chi"] = "Function P_chi [GeV]";
	}

	if(do_TauTau) 
	{
		x_axisLabels["mt_1"] = "Transverse Mass (lead-#tau_{h},MET) [GeV]";
		x_axisLabels["pt_1"] = "Transverse Momentum of lead-#tau_{h} [GeV]";
		x_axisLabels["pt_2"] = "Transverse Momentum of 2nd-#tau_{h} [GeV]";
	}
    
    if(do_All)
	{
		x_axisLabels["mt_1"] = "Transverse Mass [GeV]";
		x_axisLabels["pt_1"] = "Transverse Momentum of Leg 1 [GeV]";
		x_axisLabels["pt_2"] = "Transverse Momentum of Leg 2 [GeV]";
	}

    ///CutMaps///
    drCutMap[1] = "DeltaR_leg1_leg2 < 1.";
    drCutMap[2] = "DeltaR_leg1_leg2 >= 1. && DeltaR_leg1_leg2 < 2.0";
    drCutMap[3] = "DeltaR_leg1_leg2 > 0.0";
    
    met_options["NOM"] = "met > " + metCutVal;
    met_options["MET_RESP_UP"] = "responseUP_mvaMET_1 > " + metCutVal;
    met_options["MET_RESP_DOWN"] = "responseDOWN_mvaMET_1 > " + metCutVal;
    met_options["MET_RESO_UP"] = "resolutionUP_mvaMET_1 > " + metCutVal;
    met_options["MET_RESO_DOWN"] = "resolutionDOWN_mvaMET_1 > " + metCutVal;
    
    jetCutMap["NOM"] = TCut("nbtag==0 && njets <= 2");
    jetCutMap["BUP"] = TCut("nbtag_oneSigmaUp==0 && njets <= 2");
    jetCutMap["BDOWN"] = TCut("nbtag_oneSigmaDown==0 && njets <= 2");
    jetCutMap["NJECUP"] = TCut("nbtag==0 && njets_JECshiftedUp <= 2");
    jetCutMap["NJECDOWN"] = TCut("nbtag==0 && njets_JECshiftedDown <= 2");
    jetCutMap["NJERUP"] = TCut("nbtag==0 && njets_JERshiftedUp <= 2");
    jetCutMap["NJERDOWN"] = TCut("nbtag==0 && njets_JERshiftedDown <= 2");

    wNorm_cut_options["NOM"] = TCut("mt_1 > 80");
    wNorm_cut_options["MET_RESP_UP"] = TCut("responseUP_MTmvaMET_1 > 80");
    wNorm_cut_options["MET_RESP_DOWN"] = TCut("responseDOWN_MTmvaMET_1 > 80");
    wNorm_cut_options["MET_RESO_UP"] = TCut("resolutionUP_MTmvaMET_1 > 80");
    wNorm_cut_options["MET_RESO_DOWN"] = TCut("resolutionDOWN_MTmvaMET_1 > 80");
    
	/* max */
	if(setLog == 1) DATA_MAX = LOG_MAX;

	/* mc sample */
    weights["DY"] = " (2.3 * final_weight) ";
    weights["ZTT"] = " (2.3 * final_weight) ";
    weights["ZL"] = " (2.3 * final_weight) ";
    weights["ZJ"] = " (2.3 * final_weight) ";
	weights["TT"] = " (2.3 * final_weight) ";
    weights["VV"] = " (2.3 * final_weight) ";
	weights["W"] = " (2.3 * final_weight) ";
	weights["QCD"] = " (2.3 * final_weight) ";
    weights["GluGluHTauTau"] = " (2.3 * final_weight) ";
    weights["VBFHTauTau"] = " (2.3 * final_weight) ";
    weights["ttHJetTT"] = " (2.3 * final_weight) ";
	weights["ZHTauTau"] = " (2.3 * final_weight) ";
    weights["WHTauTau"] = " (2.3 * final_weight) ";
	weights["MONO"] = " (2.3 * final_weight) ";

	std::cout<<" NOTE ************** mono-Higgs normalized to "<<weights["MONO"]<<"\n";
	std::cout<<" event yields shown with extra (lumi) factor of "<<lumi_sf<<"\n";

	/* do channels */

	//std::cout<<saveName<<"\n";

	if(do_mTau) doMuTau();
	if(do_eTau) doEleTau();
	if(do_eMu) doEleMu();
	if(do_TauTau) doTauTau();
    if(do_All)
    {
        doMuTau();
        doEleTau();
        doEleMu();
        doTauTau();
    }
	
	std::cout<<" press any key to exit root\n";
	std::string k_;
	cin>>k_;
	gApplication->Terminate();
    
	return 0;
}
////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
// function imps. 
///////////////////////////////////////////////////////////

void doTauTau()
{
	/* set channel label */

    TCut SScut_TauTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && againstElectronVLooseMVA6_1 > 0.5 && againstElectronVLooseMVA6_2 > 0.5 && againstMuonLoose3_1 > 0.5 && againstMuonLoose3_2 > 0.5 && byVTightIsolationMVArun2v1DBoldDMwLT_1 > 0.5 && byVTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && againstElectronVLooseMVA6_1 > 0.5 && againstElectronVLooseMVA6_2 > 0.5 && againstMuonLoose3_1 > 0.5 && againstMuonLoose3_2 > 0.5 && byVTightIsolationMVArun2v1DBoldDMwLT_1 > 0.5 && byVTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");

    std::string metCutTmp;
    if (cRegion) {metCutTmp = "met < 100";}
    else {metCutTmp = met_options["NOM"];}
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp).c_str());
    cut_options_nom += jetCutMap["NOM"];

	chan_label = "#tau_{h} + #tau_{h}";

	/* setup files for eleMu channel */

	setup_files_TauTau();

    if (evalEnergyShiftSys==0 && evalBaselineSys==0)
    {

        /* declare the TauTau qcd shapes for each binning */

        /* mt_1 */
        TH1F * qcd_TauTau_mt = new TH1F("qcd_TauTau_mt","qcd_TauTau_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
        qcd_TauTau_mt->Sumw2(); 
        qcd_TauTau_mt->SetFillColor(colors["QCD"]);	
        
        /* met */
        TH1F * qcd_TauTau_met = new TH1F("qcd_TauTau_met","qcd_TauTau_met",metBinning[0],metBinning[1],metBinning[2]); 
        qcd_TauTau_met->Sumw2(); 
        qcd_TauTau_met->SetFillColor(colors["QCD"]);	
        
        /* m_vis */
        TH1F * qcd_TauTau_m_vis = new TH1F("qcd_TauTau_m_vis","qcd_TauTau_m_vis",m_visBinning[0],m_visBinning[1],m_visBinning[2]); 
        qcd_TauTau_m_vis->Sumw2(); 
        qcd_TauTau_m_vis->SetFillColor(colors["QCD"]);	
        
        /* pt_1 */
        TH1F * qcd_TauTau_pt_1 = new TH1F("qcd_TauTau_pt_1","qcd_TauTau_pt_1",ptBinning[0],ptBinning[1],ptBinning[2]); 
        qcd_TauTau_pt_1->Sumw2(); 
        qcd_TauTau_pt_1->SetFillColor(colors["QCD"]);	
        
        /* pt_2 */
        TH1F * qcd_TauTau_pt_2 = new TH1F("qcd_TauTau_pt_2","qcd_TauTau_pt_2",ptBinning[0],ptBinning[1],ptBinning[2]); 
        qcd_TauTau_pt_2->Sumw2(); 
        qcd_TauTau_pt_2->SetFillColor(colors["QCD"]);	
        
        /* LPT */
        TH1F * qcd_TauTau_LPT = new TH1F("qcd_TauTau_LPT","qcd_TauTau_LPT",lptBinning[0],lptBinning[1],lptBinning[2]);
        qcd_TauTau_LPT->Sumw2();
        qcd_TauTau_LPT->SetFillColor(colors["QCD"]);
        
        /* nbtag */
        TH1F * qcd_TauTau_nbtag = new TH1F("qcd_TauTau_nbtag","qcd_TauTau_nbtag",nbtagBinning[0],nbtagBinning[1],nbtagBinning[2]); 
        qcd_TauTau_nbtag->Sumw2(); 
        qcd_TauTau_nbtag->SetFillColor(colors["QCD"]);

        /* need to make this function more general for any dist. */	

        //nbtag==0 && njets <= 2 && deltar_(eta_1,phi_1,eta_2,phi_2) < 1 &&

        global_title = "QCD (Same Sign) Estimate Region";

        double wSF_SS_TauTau = 1.0; /* temp */
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (TauTau)", "TauTau");
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (TauTau)", "TauTau");
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (TauTau)", "TauTau");
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (TauTau)", "TauTau");
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (TauTau)", "TauTau");
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (TauTau)", "TauTau");
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (TauTau)", "TauTau");

        /* now draw the signal region in mt */
        
        double wSF_OS_TauTau = 1.0; /* temp */

        global_title = "MET < 100 GeV Control Region";

        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_mt, "mt_1", mtBinning, "sig region (met<100) mt", "TauTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "TauTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "TauTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_met, "met", metBinning, "sig region (met<100) met", "TauTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "TauTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "TauTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "TauTau");
        
        reset_files();
    }
    else if (evalBaselineSys==1)
    {
        
        setup_files_TauTau();

        /* perform the OS W+jets normalization estimate (to be used in the signal region) */

        double wSF_OS_TauTau = 1.0;

        /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */

        double wSF_SS_TauTau = 1.0;
        
        /* declare the TauTau qcd shapes for each binning */
        
        /* met */
        TH1F * qcd_TauTau_met = new TH1F("qcd_TauTau_met","qcd_TauTau_met",metBinning[0],metBinning[1],metBinning[2]);
        qcd_TauTau_met->Sumw2();

        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_met, "met", metBinning);

        /* use nominal analysis cuts to find nominal yields*/

        std::vector<std::vector<double>> nomYieldsVect;

        nomYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_met, "met", metBinning);
        
        TCut cut_options_met_reso_up((drCutMap[drCut] + " && " + met_options["MET_RESO_UP"]).c_str());
        cut_options_met_reso_up += jetCutMap["NOM"];
        TCut cut_options_met_reso_down((drCutMap[drCut] + " && " + met_options["MET_RESO_DOWN"]).c_str());
        cut_options_met_reso_up += jetCutMap["NOM"];
        
        //evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_reso_up, signalCut_base * cut_options_met_reso_down, SScut_TauTau_base * cut_options_met_reso_up, SScut_TauTau_base * cut_options_met_reso_down, "met", metBinning, "MetResolution");
        
    }
    else if (evalEnergyShiftSys==1)
    {
    std::cout<<"Not Done Yet" << std::endl;
    }
}


void doEleMu()
{

	/* set channel label */

	chan_label = "e + #mu";

	/* setup files for eleMu channel */

	setup_files_eleMu();

    //TCut SScut_eleMu("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0  && iso_1<0.15 && iso_2<0.15");
    TCut SScut_eleMu_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0  && iso_1 < 0.15 && iso_2 < 0.15");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0  && iso_1 < 0.15 && iso_2 < 0.15");

    std::string metCutTmp;
    if (cRegion) {metCutTmp = "met < 100";}
    else {metCutTmp = met_options["NOM"];}
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp).c_str());
    cut_options_nom += jetCutMap["NOM"];

	/* declare the eleMu qcd shapes for each binning */		

    if (evalEnergyShiftSys==0 && evalBaselineSys==0)
    {

        /* mt_1 */
        TH1F * qcd_eleMu_mt = new TH1F("qcd_eleMu_mt","qcd_eleMu_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
        qcd_eleMu_mt->Sumw2(); 
        qcd_eleMu_mt->SetFillColor(colors["QCD"]);	
        
        /* met */
        TH1F * qcd_eleMu_met = new TH1F("qcd_eleMu_met","qcd_eleMu_met",metBinning[0],metBinning[1],metBinning[2]); 
        qcd_eleMu_met->Sumw2(); 
        qcd_eleMu_met->SetFillColor(colors["QCD"]);	
        
        /* m_vis */
        TH1F * qcd_eleMu_m_vis = new TH1F("qcd_eleMu_m_vis","qcd_eleMu_m_vis",m_visBinning[0],m_visBinning[1],m_visBinning[2]); 
        qcd_eleMu_m_vis->Sumw2(); 
        qcd_eleMu_m_vis->SetFillColor(colors["QCD"]);	
        
        /* pt_1 */
        TH1F * qcd_eleMu_pt_1 = new TH1F("qcd_eleMu_pt_1","qcd_eleMu_pt_1",ptBinning[0],ptBinning[1],ptBinning[2]); 
        qcd_eleMu_pt_1->Sumw2(); 
        qcd_eleMu_pt_1->SetFillColor(colors["QCD"]);	
        
        /* pt_2 */
        TH1F * qcd_eleMu_pt_2 = new TH1F("qcd_eleMu_pt_2","qcd_eleMu_pt_2",ptBinning[0],ptBinning[1],ptBinning[2]); 
        qcd_eleMu_pt_2->Sumw2(); 
        qcd_eleMu_pt_2->SetFillColor(colors["QCD"]);	

        /* LPT */
        TH1F * qcd_eleMu_LPT = new TH1F("qcd_eleMu_LPT","qcd_eleMu_LPT",lptBinning[0],lptBinning[1],lptBinning[2]);
        qcd_eleMu_LPT->Sumw2();
        qcd_eleMu_LPT->SetFillColor(colors["QCD"]);

        /* nbtag */
        TH1F * qcd_eleMu_nbtag = new TH1F("qcd_eleMu_nbtag","qcd_eleMu_nbtag",nbtagBinning[0],nbtagBinning[1],nbtagBinning[2]); 
        qcd_eleMu_nbtag->Sumw2(); 
        qcd_eleMu_nbtag->SetFillColor(colors["QCD"]);

        /* need to make this function more general for any dist. */
        
        double wSF_SS_eleMu = 1.0; /* in eMu case W bkg is negligible */

        global_title = "QCD (Same Sign) Estimate Region";

        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (eleMu)", "EleMu");
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (eleMu)", "EleMu");
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (eleMu)", "EleMu");
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_met, "met", metBinning,  "QCD met shape ext. in SS side band (eleMu)", "EleMu");
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (eleMu)", "EleMu");
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (eleMu)", "EleMu");
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (eleMu)", "EleMu");

        /* now draw the signal region in mt */
        
        double wSF_OS_eleMu = 1.0; /* in eMu case W bkg is negligible */

        global_title = "MET < 100 GeV Control Region";

        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_mt, "mt_1", mtBinning, "sig region (met<100) mt", "EleMu");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "EleMu");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "EleMu");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_met, "met", metBinning, "sig region (met<100) met", "EleMu");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "EleMu");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "EleMu");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "EleMu");
        
        reset_files();
    }
    else if (evalBaselineSys==1)
    {
    
        setup_files_eleMu();

        /* perform the OS W+jets normalization estimate (to be used in the signal region) */

        double wSF_OS_eleMu = 1.0;

        /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */

        double wSF_SS_eleMu = 1.0;
        
        /* declare the eleMu qcd shapes for each binning */
        
        /* met */
        TH1F * qcd_eleMu_met = new TH1F("qcd_eleMu_met","qcd_eleMu_met",metBinning[0],metBinning[1],metBinning[2]);
        qcd_eleMu_met->Sumw2();

        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_met, "met", metBinning);

        /* use nominal analysis cuts to find nominal yields*/

        std::vector<std::vector<double>> nomYieldsVect;

        nomYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_met, "met", metBinning);
        
        TCut cut_options_met_reso_up((drCutMap[drCut] + " && " + met_options["MET_RESO_UP"]).c_str());
        cut_options_met_reso_up += jetCutMap["NOM"];
        TCut cut_options_met_reso_down((drCutMap[drCut] + " && " + met_options["MET_RESO_DOWN"]).c_str());
        cut_options_met_reso_up += jetCutMap["NOM"];
        
        //evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_reso_up, signalCut_base * cut_options_met_reso_down, SScut_eleMu_base * cut_options_met_reso_up, SScut_eleMu_base * cut_options_met_reso_down, "met", metBinning, "MetResolution");
    }
    else if (evalEnergyShiftSys==1)
    {
    std::cout<<"Not Done Yet" << std::endl;
    }

}

void doEleTau()
{

    /* setup files for eleTau channel */
    setup_files_eleTau();

	/* No WNorm in 76X */
    TCut OS_wNorm_eleTau_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && iso_1<0.1 && againstMuonLoose3_2 > 0.5 && againstElectronTightMVA6_2 > 0.5 && byTightIsolationMVArun2v1DBoldDMwLT_2 < 0.5");
    TCut SS_wNorm_eleTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && iso_1<0.1 && againstMuonLoose3_2 > 0.5 && againstElectronTightMVA6_2 > 0.5 && byTightIsolationMVArun2v1DBoldDMwLT_2 < 0.5");
    
    TCut SScut_eleTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && iso_1 < 0.1 && againstMuonLoose3_2 > 0.5 && againstElectronTightMVA6_2 > 0.5 && byTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && iso_1 < 0.1 && againstMuonLoose3_2 > 0.5 && againstElectronTightMVA6_2 > 0.5 && byTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");

    std::string metCutTmp;
    if (cRegion) {metCutTmp = "met < 100";}
    else {metCutTmp = met_options["NOM"];}
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp).c_str());
    cut_options_nom += jetCutMap["NOM"];
    
	chan_label = "e + #tau_{h}";

    //add options based on input: plots, sys3, sys4

    if (evalEnergyShiftSys==0 && evalBaselineSys==0)
    {

        /* perform the OS W+jets normalization estimate (to be used in the signal region) */

        global_title = "Opp. Sign high M_{T} Control Region";

        double wSF_OS_eleTau = 1.0;
        //double wSF_OS_eleTau  = wjetsNorm(OS_wNorm_eleTau_base * wNorm_cut_options["NOM"], "wjetsOS");

        /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */

        global_title = "Same Sign high M_{T} Control Region";

        double wSF_SS_eleTau = 1.0;
        //double wSF_SS_eleTau = wjetsNorm(SS_wNorm_eleTau_base * wNorm_cut_options["NOM"], "wjetsSSforQCD");
        
        /* declare the eleTau qcd shapes for each binning */		

        /* mt_1 */
        TH1F * qcd_eleTau_mt = new TH1F("qcd_eleTau_mt","qcd_eleTau_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
        qcd_eleTau_mt->Sumw2(); 
        qcd_eleTau_mt->SetFillColor(colors["QCD"]);	
        
        /* met */
        TH1F * qcd_eleTau_met = new TH1F("qcd_eleTau_met","qcd_eleTau_met",metBinning[0],metBinning[1],metBinning[2]); 
        qcd_eleTau_met->Sumw2(); 
        qcd_eleTau_met->SetFillColor(colors["QCD"]);	
        
        /* m_vis */
        TH1F * qcd_eleTau_m_vis = new TH1F("qcd_eleTau_m_vis","qcd_eleTau_m_vis",m_visBinning[0],m_visBinning[1],m_visBinning[2]); 
        qcd_eleTau_m_vis->Sumw2(); 
        qcd_eleTau_m_vis->SetFillColor(colors["QCD"]);	
        
        /* pt_1 */
        TH1F * qcd_eleTau_pt_1 = new TH1F("qcd_eleTau_pt_1","qcd_eleTau_pt_1",ptBinning[0],ptBinning[1],ptBinning[2]); 
        qcd_eleTau_pt_1->Sumw2(); 
        qcd_eleTau_pt_1->SetFillColor(colors["QCD"]);	
        
        /* pt_2 */
        TH1F * qcd_eleTau_pt_2 = new TH1F("qcd_eleTau_pt_2","qcd_eleTau_pt_2",ptBinning[0],ptBinning[1],ptBinning[2]); 
        qcd_eleTau_pt_2->Sumw2(); 
        qcd_eleTau_pt_2->SetFillColor(colors["QCD"]);

        /* LPT */
        TH1F * qcd_eleTau_LPT = new TH1F("qcd_eleTau_LPT","qcd_eleTau_LPT",lptBinning[0],lptBinning[1],lptBinning[2]);
        qcd_eleTau_LPT->Sumw2();
        qcd_eleTau_LPT->SetFillColor(colors["QCD"]);

        /* M_min */
        TH1F * qcd_eleTau_m_min = new TH1F("qcd_eleTau_m_min","qcd_eleTau_m_min",m_minBinning[0],m_minBinning[1],m_minBinning[2]);
        qcd_eleTau_m_min->Sumw2();
        qcd_eleTau_m_min->SetFillColor(colors["QCD"]);

        /* P_chi */
        TH1F * qcd_eleTau_p_chi = new TH1F("qcd_eleTau_p_chi","qcd_eleTau_p_chi",p_chiBinning[0],p_chiBinning[1],p_chiBinning[2]);
        qcd_eleTau_p_chi->Sumw2();
        qcd_eleTau_p_chi->SetFillColor(colors["QCD"]);

        /* nbtag */
        TH1F * qcd_eleTau_nbtag = new TH1F("qcd_eleTau_nbtag","qcd_eleTau_nbtag",nbtagBinning[0],nbtagBinning[1],nbtagBinning[2]); 
        qcd_eleTau_nbtag->Sumw2(); 
        qcd_eleTau_nbtag->SetFillColor(colors["QCD"]);	
        
        global_title = "QCD (Same Sign) Estimate Region";
        
        /* need to make this function more general for any dist. */
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_LPT, "LPT", lptBinning, "QCD LPT shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_m_min, "M_min", m_minBinning, "QCD Function M_min shape ext. in SS side band (eleTau)", "EleTau");
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_p_chi, "P_chi", p_chiBinning, "QCD Function P_chi shape ext. in SS side band (eleTau)", "EleTau");

        /* now draw the signal region in mt */

        global_title = "MET < 100 GeV Control Region";

        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mt, "mt_1", mtBinning, "sig region (met<100) mt", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_met, "met", metBinning, "sig region (met<100) met", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_m_min, "M_min", m_minBinning, "sig region (met<100) Function M_min", "EleTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_p_chi, "P_chi", p_chiBinning, "sig region (met<100) Function P_chi", "EleTau");
        
        reset_files();
        
    }
    else if (evalBaselineSys==1)
    {
        
        setup_files_eleTau();

        /* perform the OS W+jets normalization estimate (to be used in the signal region) */

        double wSF_OS_eleTau =  wjetsNorm_NoPlots(OS_wNorm_eleTau_base * wNorm_cut_options["NOM"]);

        /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */

        double wSF_SS_eleTau = wjetsNorm_NoPlots(SS_wNorm_eleTau_base * wNorm_cut_options["NOM"]);
        
        /* declare the muTau qcd shapes for each binning */
        
        /* met */
        TH1F * qcd_eleTau_met = new TH1F("qcd_eleTau_met","qcd_eleTau_met",metBinning[0],metBinning[1],metBinning[2]);
        qcd_eleTau_met->Sumw2();

        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_met, "met", metBinning);

        /* use nominal analysis cuts to find nominal yields*/

        std::vector<std::vector<double>> nomYieldsVect;

        nomYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_met, "met", metBinning);
        
        TCut cut_options_met_reso_up((drCutMap[drCut] + " && " + met_options["MET_RESO_UP"]).c_str());
        cut_options_met_reso_up += jetCutMap["NOM"];
        TCut cut_options_met_reso_down((drCutMap[drCut] + " && " + met_options["MET_RESO_DOWN"]).c_str());
        cut_options_met_reso_up += jetCutMap["NOM"];
        
        //evalSysBaseline(nomYieldsVect, signalCut_base * cut_options_met_reso_up, signalCut_base * cut_options_met_reso_down, SS_wNorm_eleTau_base * wNorm_cut_options["MET_RESO_UP"], SS_wNorm_eleTau_base * wNorm_cut_options["MET_RESO_DOWN"], OS_wNorm_eleTau_base * wNorm_cut_options["MET_RESO_UP"], OS_wNorm_eleTau_base * wNorm_cut_options["MET_RESO_DOWN"], SScut_eleTau_base * cut_options_met_reso_up, SScut_eleTau_base * cut_options_met_reso_down, "met", metBinning, "MetResolution");
    }
    else if (evalEnergyShiftSys==1)
    {
    std::cout<<"Not Done Yet" << std::endl;
    }
}

void doMuTau()
{
	/* No WNorm in 76X */
    TCut OS_wNorm_muTau_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && againstMuonTight3_2>0.5 && againstElectronVLooseMVA6_2>0.5 && iso_1 < 0.1 && byTightIsolationMVArun2v1DBoldDMwLT_2 < 0.5");
    TCut SS_wNorm_muTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && againstMuonTight3_2>0.5 && againstElectronVLooseMVA6_2>0.5 && iso_1 < 0.1 && byTightIsolationMVArun2v1DBoldDMwLT_2 < 0.5");
    
    TCut SScut_muTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && againstMuonTight3_2>0.5 && againstElectronVLooseMVA6_2>0.5 && iso_1 < 0.1 && byTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && againstMuonTight3_2>0.5 && againstElectronVLooseMVA6_2>0.5 && iso_1 < 0.1 && byTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");

    std::string metCutTmp;
    if (cRegion) {metCutTmp = "met < 100";}
    else {metCutTmp = met_options["NOM"];}
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp).c_str());
    cut_options_nom += jetCutMap["NOM"];

	chan_label = "#mu+ #tau_{h}";
    
    if (evalBaselineSys==0 && evalEnergyShiftSys==0)
    {
        /* setup files for muTau channel */
        setup_files_muTau();

        /* perform the OS W+jets normalization estimate (to be used in the signal region) */

        global_title = "Opp. Sign high M_{T} Control Region";

        //double wSF_OS_muTau =  0.870714;//wjetsNorm(OS_wNorm_muTau, "wjetsOS");
        //double wSF_OS_muTau =  wjetsNorm(OS_wNorm_muTau_base * wNorm_cut_options["NOM"], "wjetsOS");
        double wSF_OS_muTau =  1.0;
        
        /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */
        //still has wjetsNorm calculation and plots...
        global_title = "Same Sign high M_{T} Control Region";

        //double wSF_SS_muTau = 0.967438;//wjetsNorm(SS_wNorm_muTau, "wjetsSSforQCD");

        //double wSF_SS_muTau = wjetsNorm(SS_wNorm_muTau_base * wNorm_cut_options["NOM"], "wjetsSSforQCD");
        double wSF_SS_muTau = 1.0;
        
        /* declare the muTau qcd shapes for each binning */		

        /* mt_1 */
        TH1F * qcd_muTau_mt = new TH1F("qcd_muTau_mt","qcd_muTau_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
        qcd_muTau_mt->Sumw2(); 
        qcd_muTau_mt->SetFillColor(colors["QCD"]);	
        
        /* met */
        TH1F * qcd_muTau_met = new TH1F("qcd_muTau_met","qcd_muTau_met",metBinning[0],metBinning[1],metBinning[2]); 
        qcd_muTau_met->Sumw2(); 
        qcd_muTau_met->SetFillColor(colors["QCD"]);	
        
        /* m_vis */
/*        TH1F * qcd_muTau_m_vis = new TH1F("qcd_muTau_m_vis","qcd_muTau_m_vis",m_visBinning[0],m_visBinning[1],m_visBinning[2]);
        qcd_muTau_m_vis->Sumw2(); 
        qcd_muTau_m_vis->SetFillColor(colors["QCD"]);	
*/
        /* pt_1 */
/*        TH1F * qcd_muTau_pt_1 = new TH1F("qcd_muTau_pt_1","qcd_muTau_pt_1",ptBinning[0],ptBinning[1],ptBinning[2]);
        qcd_muTau_pt_1->Sumw2(); 
        qcd_muTau_pt_1->SetFillColor(colors["QCD"]);	
*/
        /* pt_2 */
/*        TH1F * qcd_muTau_pt_2 = new TH1F("qcd_muTau_pt_2","qcd_muTau_pt_2",ptBinning[0],ptBinning[1],ptBinning[2]);
        qcd_muTau_pt_2->Sumw2(); 
        qcd_muTau_pt_2->SetFillColor(colors["QCD"]);	
*/
        /* LPT */
        TH1F * qcd_muTau_LPT = new TH1F("qcd_muTau_LPT","qcd_muTau_LPT",lptBinning[0],lptBinning[1],lptBinning[2]);
        qcd_muTau_LPT->Sumw2();
        qcd_muTau_LPT->SetFillColor(colors["QCD"]);
        
        /* M_min */
        
/*        TH1F * qcd_muTau_m_min = new TH1F("qcd_muTau_m_min","qcd_muTau_m_min",m_minBinning[0],m_minBinning[1],m_minBinning[2]);
        qcd_muTau_m_min->Sumw2();
        qcd_muTau_m_min->SetFillColor(colors["QCD"]);
*/
        /* P_chi */
        TH1F * qcd_muTau_p_chi = new TH1F("qcd_muTau_p_chi","qcd_muTau_p_chi",p_chiBinning[0],p_chiBinning[1],p_chiBinning[2]);
        qcd_muTau_p_chi->Sumw2();
        qcd_muTau_p_chi->SetFillColor(colors["QCD"]);

        /* nbtag */
/*        TH1F * qcd_muTau_nbtag = new TH1F("qcd_muTau_nbtag","qcd_muTau_nbtag",nbtagBinning[0],nbtagBinning[1],nbtagBinning[2]);
        qcd_muTau_nbtag->Sumw2(); 
        qcd_muTau_nbtag->SetFillColor(colors["QCD"]);
*/
        global_title = "QCD (Same Sign) Estimate Region";

        //SScut_muTau_base * cut_options_nom; /* needs to match whatever we draw the full model in*/
        
        fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (muTau)", "MuTau");
        //fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (muTau)", "MuTau");
        //fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (muTau)", "MuTau");
        fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (muTau)", "MuTau");
        //fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (muTau)", "MuTau");
        //fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (muTau)", "MuTau");
        fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (muTau)", "MuTau");
        //fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_m_min, "M_min", m_minBinning, "QCD Function M_min shape ext. in SS side band (muTau)", "MuTau");
        fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_p_chi, "P_chi", p_chiBinning, "QCD Function P_chi shape ext. in SS side band (muTau)", "MuTau");
        
        /* now draw the signal region in mt */
        
        global_title = "MET < 100 GeV Control Region";
        
        //findBkgFractions(signalCut_base * cut_options_nom, wSF_OS_muTau, "met", metBinning);
        
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mt, "mt_1", mtBinning, "sig region (met<100) mt", "MuTau");
        //drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "MuTau");
        //drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "MuTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning, "sig region (met<100) met", "MuTau");
        //drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "MuTau");
        //drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "MuTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "MuTau");
        //drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_m_min, "M_min", m_minBinning, "sig region (met<100) Function M_min", "MuTau");
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_p_chi, "P_chi", p_chiBinning, "sig region (met<100) Function P_chi", "MuTau");
        
        reset_files();
        
    }
    else if (evalBaselineSys==1)
    {
        
        setup_files_muTau();

        /* perform the OS W+jets normalization estimate (to be used in the signal region) */

        //double wSF_OS_muTau =  wjetsNorm_NoPlots(OS_wNorm_muTau_base * wNorm_cut_options["NOM"]);
        double wSF_OS_muTau =  1.0;
        /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */
        //double wSF_SS_muTau = wjetsNorm_NoPlots(SS_wNorm_muTau_base * wNorm_cut_options["NOM"]);
        double wSF_SS_muTau = 1.0;
        /* declare the muTau qcd shapes for each binning */
        /* met */
        TH1F * qcd_muTau_met = new TH1F("qcd_muTau_met","qcd_muTau_met",metBinning[0],metBinning[1],metBinning[2]);
        qcd_muTau_met->Sumw2();
        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning);

        /* use nominal analysis cuts to find nominal yields*/
        std::vector<std::vector<double>> nomYieldsVect;
        nomYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning);
        
        //metRESO
        TCut cut_options_met_reso_up((drCutMap[drCut] + " && " + met_options["MET_RESO_UP"]).c_str()); cut_options_met_reso_up += jetCutMap["NOM"];
        TCut cut_options_met_reso_down((drCutMap[drCut] + " && " + met_options["MET_RESO_DOWN"]).c_str()); cut_options_met_reso_down += jetCutMap["NOM"];
        evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_reso_up, signalCut_base * cut_options_met_reso_down, SScut_muTau_base * cut_options_met_reso_up, SScut_muTau_base * cut_options_met_reso_down, "met", metBinning, "MetResolution");
        
        //metRESP
        TCut cut_options_met_resp_up((drCutMap[drCut] + " && " + met_options["MET_RESP_UP"]).c_str()); cut_options_met_resp_up += jetCutMap["NOM"];
        TCut cut_options_met_resp_down((drCutMap[drCut] + " && " + met_options["MET_RESP_DOWN"]).c_str());cut_options_met_resp_down += jetCutMap["NOM"];
        evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_resp_up, signalCut_base * cut_options_met_resp_down, SScut_muTau_base * cut_options_met_resp_up, SScut_muTau_base * cut_options_met_resp_down, "met", metBinning, "MetResponse");

        //Btag
        TCut cut_options_met_b_up((drCutMap[drCut] + " && " + met_options["NOM"]).c_str());cut_options_met_b_up += jetCutMap["BUP"];
        TCut cut_options_met_b_down((drCutMap[drCut] + " && " + met_options["NOM"]).c_str());cut_options_met_b_down += jetCutMap["BDOWN"];
        evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_b_up, signalCut_base * cut_options_met_b_down, SScut_muTau_base * cut_options_met_b_up, SScut_muTau_base * cut_options_met_b_down, "met", metBinning, "Btag");
        
        //JEC
        TCut cut_options_met_njec_up((drCutMap[drCut] + " && " + met_options["NOM"]).c_str()); cut_options_met_njec_up += jetCutMap["NJECUP"];
        TCut cut_options_met_njec_down((drCutMap[drCut] + " && " + met_options["NOM"]).c_str());cut_options_met_njec_down += jetCutMap["NJECDOWN"];
        evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_njec_up, signalCut_base * cut_options_met_njec_down, SScut_muTau_base * cut_options_met_njec_up, SScut_muTau_base * cut_options_met_njec_down, "met", metBinning, "NjetJEC");
        
        //JER
        TCut cut_options_met_njer_up((drCutMap[drCut] + " && " + met_options["NOM"]).c_str()); cut_options_met_njer_up += jetCutMap["NJERUP"];
        TCut cut_options_met_njer_down((drCutMap[drCut] + " && " + met_options["NOM"]).c_str());cut_options_met_njer_down += jetCutMap["NJERDOWN"];
        evalSysBaselineNoW(nomYieldsVect, signalCut_base * cut_options_met_njer_up, signalCut_base * cut_options_met_njer_down, SScut_muTau_base * cut_options_met_njer_up, SScut_muTau_base * cut_options_met_njer_down, "met", metBinning, "NjetJER");
    
    }
    else if (evalEnergyShiftSys==1)
    {
        
        setup_files_muTau();
        double wSF_OS_muTau =  1.0;
        double wSF_SS_muTau = 1.0;
        /* met */
        TH1F * qcd_muTau_met = new TH1F("qcd_muTau_met","qcd_muTau_met",metBinning[0],metBinning[1],metBinning[2]);
        qcd_muTau_met->Sumw2();
        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning);
        /* use nominal analysis cuts to find nominal yields*/
        std::vector<std::vector<double>> nomYieldsVect;
        nomYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning);
        
        reset_files();
        std::cout << "number of entries VV: " << VV->GetEntries() << std::endl;
        setup_upTau_files_muTau();
        wSF_OS_muTau =  wjetsNorm_NoPlots(OS_wNorm_muTau_base * wNorm_cut_options["NOM"]);
        wSF_SS_muTau = wjetsNorm_NoPlots(SS_wNorm_muTau_base * wNorm_cut_options["NOM"]);
        /* met */
        qcd_muTau_met->Reset();
        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning);
        /* use nominal analysis cuts to find nominal yields*/
        std::vector<std::vector<double>> upTauYieldsVect;
        upTauYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning);
        
        reset_files();
        setup_downTau_files_muTau();
        wSF_OS_muTau =  wjetsNorm_NoPlots(OS_wNorm_muTau_base * wNorm_cut_options["NOM"]);
        wSF_SS_muTau = wjetsNorm_NoPlots(SS_wNorm_muTau_base * wNorm_cut_options["NOM"]);
        /* met */
        qcd_muTau_met->Reset();
        /* need to make this function more general for any dist. */
        fillQCD_Shape_NoPlots(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning);
        /* use nominal analysis cuts to find nominal yields*/
        std::vector<std::vector<double>> downTauYieldsVect;
        downTauYieldsVect = countSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning);
        
        out_data << "Tau ES Systematics";
        
        for (unsigned int i = 0; i < upTauYieldsVect.size(); i++)
        {
            for (int j = 0 ; j < 13; j++)
            {
                double diff = abs(upTauYieldsVect[i][j] - downTauYieldsVect[i][j]);
                double diffFrac = diff/(2.0 * nomYieldsVect[i][j]);
                out_data << diffFrac << "        ";
            }
            out_data << std::endl;
        }
    
    }
}

void findBkgFractions(TCut cut, double sf, std::string parameter, float bin[3])
{

    TH1F * DYinc_ = new TH1F("DYinc_","DYinc_",bin[0],bin[1],bin[2]);
	DYinc_->Sumw2();

	TH1F * DYhigh_ = new TH1F("DYhigh_","DYhigh_",bin[0],bin[1],bin[2]);
	DYhigh_->Sumw2();
    
	TH1F * DYlow_ = new TH1F("DYlow_","DYlow_",bin[0],bin[1],bin[2]);
	DYlow_->Sumw2();
    
    TH1F * DY1Jets_ = new TH1F("DY1Jets_","DY1Jets_",bin[0],bin[1],bin[2]);
	DY1Jets_->Sumw2();
    
    TH1F * DY2Jets_ = new TH1F("DY2Jets_","DY2Jets_",bin[0],bin[1],bin[2]);
	DY2Jets_->Sumw2();
    
    TH1F * DY3Jets_ = new TH1F("DY3Jets_","DY3Jets_",bin[0],bin[1],bin[2]);
	DY3Jets_->Sumw2();
    
    TH1F * DY4Jets_ = new TH1F("DY4Jets_","DY4Jets_",bin[0],bin[1],bin[2]);
	DY4Jets_->Sumw2();
    
	TH1F * WJetsToLNu_ = new TH1F("WJetsToLNu_","WJetsToLNu_",bin[0],bin[1],bin[2]);
	WJetsToLNu_->Sumw2();
    
    TH1F * W1JetsToLNu_ = new TH1F("W1JetsToLNu_","W1JetsToLNu_",bin[0],bin[1],bin[2]);
	W1JetsToLNu_->Sumw2();
    
    TH1F * W2JetsToLNu_ = new TH1F("W2JetsToLNu_","W2JetsToLNu_",bin[0],bin[1],bin[2]);
	W2JetsToLNu_->Sumw2();
    
    TH1F * W3JetsToLNu_ = new TH1F("W3JetsToLNu_","W3JetsToLNu_",bin[0],bin[1],bin[2]);
	W3JetsToLNu_->Sumw2();
    
    TH1F * W4JetsToLNu_ = new TH1F("W4JetsToLNu_","W4JetsToLNu_",bin[0],bin[1],bin[2]);
	W4JetsToLNu_->Sumw2();
    
    TH1F * TT_ = new TH1F("TT_","TT_",bin[0],bin[1],bin[2]);
	TT_->Sumw2();

    TH1F * ST_t_channel_antitop_4f_leptonDecays_ = new TH1F("ST_t_channel_antitop_4f_leptonDecays_","ST_t_channel_antitop_4f_leptonDecays_",bin[0],bin[1],bin[2]);
	ST_t_channel_antitop_4f_leptonDecays_->Sumw2();
    
	TH1F * ST_t_channel_top_4f_leptonDecays_ = new TH1F("ST_t_channel_top_4f_leptonDecays_","ST_t_channel_top_4f_leptonDecays_",bin[0],bin[1],bin[2]);
	ST_t_channel_top_4f_leptonDecays_->Sumw2();
    
	TH1F * ST_tW_antitop_5f_inclusiveDecays_ = new TH1F("ST_tW_antitop_5f_inclusiveDecays_","ST_tW_antitop_5f_inclusiveDecays_",bin[0],bin[1],bin[2]);
	ST_tW_antitop_5f_inclusiveDecays_->Sumw2();
    
	TH1F * ST_tW_top_5f_inclusiveDecays_ = new TH1F("ST_tW_top_5f_inclusiveDecays_","ST_tW_top_5f_inclusiveDecays_",bin[0],bin[1],bin[2]);
	ST_tW_top_5f_inclusiveDecays_->Sumw2();
    
	TH1F * VVTo2L2Nu_ = new TH1F("VVTo2L2Nu_","VVTo2L2Nu_",bin[0],bin[1],bin[2]);
	VVTo2L2Nu_->Sumw2();
    
    TH1F * WWTo1L1Nu2Q_ = new TH1F("WWTo1L1Nu2Q_","WWTo1L1Nu2Q_",bin[0],bin[1],bin[2]);
	WWTo1L1Nu2Q_->Sumw2();
    
    TH1F * WZJToLLLNu_ = new TH1F("WZJToLLLNu_","WZJToLLLNu_",bin[0],bin[1],bin[2]);
	WZJToLLLNu_->Sumw2();
    
    TH1F * WZTo1L1Nu2Q_ = new TH1F("WZTo1L1Nu2Q_","WZTo1L1Nu2Q_",bin[0],bin[1],bin[2]);
	WZTo1L1Nu2Q_->Sumw2();
    
    TH1F * WZTo1L3Nu_ = new TH1F("WZTo1L3Nu_","WZTo1L3Nu_",bin[0],bin[1],bin[2]);
	WZTo1L3Nu_->Sumw2();
    
    TH1F * WZTo2L2Q_ = new TH1F("WZTo2L2Q_","WZTo2L2Q_",bin[0],bin[1],bin[2]);
	WZTo2L2Q_->Sumw2();
    
	TH1F * ZZTo2L2Q_ = new TH1F("ZZTo2L2Q_","ZZTo2L2Q_",bin[0],bin[1],bin[2]);
	ZZTo2L2Q_->Sumw2();
    
	TH1F * ZZTo4L_ = new TH1F("ZZTo4L_","ZZTo4L_",bin[0],bin[1],bin[2]);
	ZZTo4L_->Sumw2();
    
	TH1F * GluGluHTauTau_ = new TH1F("GluGluHTauTau_","GluGluHTauTau_",bin[0],bin[1],bin[2]);
	GluGluHTauTau_->Sumw2();
    
	TH1F * VBFHTauTau_ = new TH1F("VBFHTauTau_","VBFHTauTau_",bin[0],bin[1],bin[2]);
	VBFHTauTau_->Sumw2();
    
	TH1F * WminusHToTauTau_M125_ = new TH1F("WminusHToTauTau_M125_","WminusHToTauTau_M125_",bin[0],bin[1],bin[2]);
	WminusHToTauTau_M125_->Sumw2();
    
    TH1F * WplusHToTauTau_M125_ = new TH1F("WplusHToTauTau_M125_","WplusHToTauTau_M125_",bin[0],bin[1],bin[2]);
	WplusHToTauTau_M125_->Sumw2();
    
    TH1F * ttHJetTT_ = new TH1F("ttHJetTT_","ttHJetTT_",bin[0],bin[1],bin[2]);
	ttHJetTT_->Sumw2();
    
    TH1F * ZHTauTau_ = new TH1F("ZHTauTau_","ZHTauTau_",bin[0],bin[1],bin[2]);
	ZHTauTau_->Sumw2();
    
    TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2();
    
    DYhigh->Draw((parameter+">>DYhigh_").c_str(),cut*weights["DY"].c_str());
    DYlow->Draw((parameter+">>DYlow_").c_str(),cut*weights["DY"].c_str());
    DYinc->Draw((parameter+">>DYinc_").c_str(),cut*weights["DY"].c_str());
    DY1Jets->Draw((parameter+">>DY1Jets_").c_str(),cut*weights["DY"].c_str());
    DY2Jets->Draw((parameter+">>DY2Jets_").c_str(),cut*weights["DY"].c_str());
    DY3Jets->Draw((parameter+">>DY3Jets_").c_str(),cut*weights["DY"].c_str());
    DY4Jets->Draw((parameter+">>DY4Jets_").c_str(),cut*weights["DY"].c_str());
    WJetsToLNu->Draw((parameter+">>WJetsToLNu_").c_str(),cut*weights["W"].c_str());
    W1JetsToLNu->Draw((parameter+">>W1JetsToLNu_").c_str(),cut*weights["W"].c_str());
    W2JetsToLNu->Draw((parameter+">>W2JetsToLNu_").c_str(),cut*weights["W"].c_str());
    W3JetsToLNu->Draw((parameter+">>W3JetsToLNu_").c_str(),cut*weights["W"].c_str());
    W4JetsToLNu->Draw((parameter+">>W4JetsToLNu_").c_str(),cut*weights["W"].c_str());
    TT->Draw((parameter+">>TT_").c_str(),cut*weights["TT"].c_str());
    GluGluHTauTau->Draw((parameter+">>GluGluHTauTau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>VBFHTauTau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    WminusHToTauTau_M125->Draw((parameter+">>WminusHToTauTau_M125_").c_str(),cut*weights["WHTauTau"].c_str());
    WplusHToTauTau_M125->Draw((parameter+">>WplusHToTauTau_M125_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>ttHJetTT_").c_str(),cut*weights["ttHJetTT"].c_str());
    ZHTauTau->Draw((parameter+">>ZHTauTau_").c_str(),cut*weights["ZHTauTau"].c_str());
    ST_t_channel_antitop_4f_leptonDecays->Draw((parameter+">>ST_t_channel_antitop_4f_leptonDecays_").c_str(),cut*weights["VV"].c_str());
    ST_t_channel_top_4f_leptonDecays->Draw((parameter+">>ST_t_channel_top_4f_leptonDecays_").c_str(),cut*weights["VV"].c_str());
    ST_tW_antitop_5f_inclusiveDecays->Draw((parameter+">>ST_tW_antitop_5f_inclusiveDecays_").c_str(),cut*weights["VV"].c_str());
    ST_tW_top_5f_inclusiveDecays->Draw((parameter+">>ST_tW_top_5f_inclusiveDecays_").c_str(),cut*weights["VV"].c_str());
    VVTo2L2Nu->Draw((parameter+">>VVTo2L2Nu_").c_str(),cut*weights["VV"].c_str());
    WWTo1L1Nu2Q->Draw((parameter+">>WWTo1L1Nu2Q_").c_str(),cut*weights["VV"].c_str());
    WZJToLLLNu->Draw((parameter+">>WZJToLLLNu_").c_str(),cut*weights["VV"].c_str());
    WZTo1L1Nu2Q->Draw((parameter+">>WZTo1L1Nu2Q_").c_str(),cut*weights["VV"].c_str());
    WZTo1L3Nu->Draw((parameter+">>WZTo1L3Nu_").c_str(),cut*weights["VV"].c_str());
    WZTo2L2Q->Draw((parameter+">>WZTo2L2Q_").c_str(),cut*weights["VV"].c_str());
    ZZTo2L2Q->Draw((parameter+">>ZZTo2L2Q_").c_str(),cut*weights["VV"].c_str());
    ZZTo4L->Draw((parameter+">>ZZTo4L_").c_str(),cut*weights["VV"].c_str());

    WJetsToLNu_->Scale(sf);
    W1JetsToLNu_->Scale(sf);
    W2JetsToLNu_->Scale(sf);
    W3JetsToLNu_->Scale(sf);
    W4JetsToLNu_->Scale(sf);
    
    WJetsToLNu_->Scale(lumi_sf);
    W1JetsToLNu_->Scale(lumi_sf);
    W2JetsToLNu_->Scale(lumi_sf);
    W3JetsToLNu_->Scale(lumi_sf);
    W4JetsToLNu_->Scale(lumi_sf);
    DYhigh_->Scale(lumi_sf);
    DYlow_->Scale(lumi_sf);
    DYinc_->Scale(lumi_sf);
    DY1Jets_->Scale(lumi_sf);
    DY2Jets_->Scale(lumi_sf);
    DY3Jets_->Scale(lumi_sf);
    DY4Jets_->Scale(lumi_sf);
    TT_->Scale(lumi_sf);
    GluGluHTauTau_->Scale(lumi_sf);
    VBFHTauTau_->Scale(lumi_sf);
    WminusHToTauTau_M125_->Scale(lumi_sf);
    WplusHToTauTau_M125_->Scale(lumi_sf);
    ttHJetTT_->Scale(lumi_sf);
    ZHTauTau_->Scale(lumi_sf);
    ST_t_channel_antitop_4f_leptonDecays_->Scale(lumi_sf);
    ST_t_channel_top_4f_leptonDecays_->Scale(lumi_sf);
    ST_tW_antitop_5f_inclusiveDecays_->Scale(lumi_sf);
    ST_tW_top_5f_inclusiveDecays_->Scale(lumi_sf);
    VVTo2L2Nu_->Scale(lumi_sf);
    WWTo1L1Nu2Q_->Scale(lumi_sf);
    WZJToLLLNu_->Scale(lumi_sf);
    WZTo1L1Nu2Q_->Scale(lumi_sf);
    WZTo1L3Nu_->Scale(lumi_sf);
    WZTo2L2Q_->Scale(lumi_sf);
    ZZTo2L2Q_->Scale(lumi_sf);
    ZZTo4L_->Scale(lumi_sf);
    
    comb_->Add(WJetsToLNu_);
    comb_->Add(W1JetsToLNu_);
    comb_->Add(W2JetsToLNu_);
    comb_->Add(W3JetsToLNu_);
    comb_->Add(W4JetsToLNu_);
    comb_->Add(DYhigh_);
    comb_->Add(DYlow_);
    comb_->Add(DYinc_);
    comb_->Add(DY1Jets_);
    comb_->Add(DY2Jets_);
    comb_->Add(DY3Jets_);
    comb_->Add(DY4Jets_);
    comb_->Add(TT_);
    comb_->Add(GluGluHTauTau_);
    comb_->Add(VBFHTauTau_);
    comb_->Add(WminusHToTauTau_M125_);
    comb_->Add(WplusHToTauTau_M125_);
    comb_->Add(ttHJetTT_);
    comb_->Add(ZHTauTau_);
    comb_->Add(ST_t_channel_antitop_4f_leptonDecays_);
    comb_->Add(ST_t_channel_top_4f_leptonDecays_);
    comb_->Add(ST_tW_antitop_5f_inclusiveDecays_);
    comb_->Add(ST_tW_top_5f_inclusiveDecays_);
    comb_->Add(VVTo2L2Nu_);
    comb_->Add(WWTo1L1Nu2Q_);
    comb_->Add(WZJToLLLNu_);
    comb_->Add(WZTo1L1Nu2Q_);
    comb_->Add(WZTo1L3Nu_);
    comb_->Add(WZTo2L2Q_);
    comb_->Add(ZZTo2L2Q_);
    comb_->Add(ZZTo4L_);

	double error = 0;
    
    double totalBKGIntegral = comb_->Integral();
    
    std::cout << "\n";
    std::cout << "BKG Totals and Fractions" << "\n";
    std::cout << "\n";

	error = 0;
	WJetsToLNu_->IntegralAndError(-1,1e3, error);
	std::cout<<" WJetsToLNu................................"<<WJetsToLNu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WJetsToLNu_->Integral()/totalBKGIntegral<< "\n";
	error = 0;
	W1JetsToLNu_->IntegralAndError(-1,1e3, error);
	std::cout<<" W1JetsToLNu..............................."<<W1JetsToLNu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  W1JetsToLNu_->Integral()/totalBKGIntegral<< "\n";
	error = 0;
	W2JetsToLNu_->IntegralAndError(-1,1e3, error);
	std::cout<<" W2JetsToLNu..............................."<<W2JetsToLNu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  W2JetsToLNu_->Integral()/totalBKGIntegral<< "\n";
	error = 0;
	W3JetsToLNu_->IntegralAndError(-1,1e3, error);
	std::cout<<" W3JetsToLNu..............................."<<W3JetsToLNu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  W3JetsToLNu_->Integral()/totalBKGIntegral<< "\n";
	error = 0;
	W4JetsToLNu_->IntegralAndError(-1,1e3, error);
	std::cout<<" W4JetsToLNu..............................."<<W4JetsToLNu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  W4JetsToLNu_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DYhigh_->IntegralAndError(-1,1e3, error);
    std::cout<<" DYhigh...................................."<< DYhigh_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  DYhigh_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DYlow_->IntegralAndError(-1,1e3, error);
    std::cout<<" DYlow....................................."<< DYlow_->Integral()<<" +/- "<<error<< "   Fraction: " <<  DYlow_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DYinc_->IntegralAndError(-1,1e3, error);
    std::cout<<" DYinc....................................."<< DYinc_->Integral()<<" +/- "<<error<< "   Fraction: " <<  DYinc_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DY1Jets_->IntegralAndError(-1,1e3, error);
    std::cout<<" DY1Jets..................................."<< DY1Jets_->Integral()<<" +/- "<<error<< "   Fraction: " <<  DY1Jets_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DY2Jets_->IntegralAndError(-1,1e3, error);
    std::cout<<" DY2Jets..................................."<< DY2Jets_->Integral()<<" +/- "<<error<< "   Fraction: " <<  DY2Jets_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DY3Jets_->IntegralAndError(-1,1e3, error);
    std::cout<<" DY3Jets..................................."<< DY3Jets_->Integral()<<" +/- "<<error<< "   Fraction: " <<  DY3Jets_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    DY4Jets_->IntegralAndError(-1,1e3, error);
    std::cout<<" DY4Jets..................................."<< DY4Jets_->Integral()<<" +/- "<<error<< "   Fraction: " <<  DY4Jets_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    TT_->IntegralAndError(-1,1e3, error);
    std::cout<<" TT........................................"<< TT_->Integral()<<" +/- "<<error<< "   Fraction: " <<  TT_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    GluGluHTauTau_->IntegralAndError(-1,1e3, error);
    std::cout<<" GluGluHTauTau............................."<< GluGluHTauTau_->Integral()<<" +/- "<<error<< "   Fraction: " <<  GluGluHTauTau_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    VBFHTauTau_->IntegralAndError(-1,1e3, error);
    std::cout<<" VBFHTauTau................................"<< VBFHTauTau_->Integral()<<" +/- "<<error<< "   Fraction: " <<  VBFHTauTau_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WminusHToTauTau_M125_->IntegralAndError(-1,1e3, error); 
    std::cout<<" WminusHToTauTau_M125......................"<< WminusHToTauTau_M125_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WminusHToTauTau_M125_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WplusHToTauTau_M125_->IntegralAndError(-1,1e3, error); 
    std::cout<<" WplusHToTauTau_M125......................."<< WplusHToTauTau_M125_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WplusHToTauTau_M125_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ttHJetTT_->IntegralAndError(-1,1e3, error);
    std::cout<<" ttHJetTT.................................."<< ttHJetTT_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ttHJetTT_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ZHTauTau_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZHTauTau.................................."<< ZHTauTau_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ZHTauTau_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ST_t_channel_antitop_4f_leptonDecays_->IntegralAndError(-1,1e3, error);
    std::cout<<" ST_t_channel_antitop_4f_leptonDecays......"<< ST_t_channel_antitop_4f_leptonDecays_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ST_t_channel_antitop_4f_leptonDecays_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ST_t_channel_top_4f_leptonDecays_->IntegralAndError(-1,1e3, error);
    std::cout<<" ST_t_channel_top_4f_leptonDecays.........."<< ST_t_channel_top_4f_leptonDecays_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ST_t_channel_top_4f_leptonDecays_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ST_tW_antitop_5f_inclusiveDecays_->IntegralAndError(-1,1e3, error);
    std::cout<<" ST_tW_antitop_5f_inclusiveDecays.........."<< ST_tW_antitop_5f_inclusiveDecays_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ST_tW_antitop_5f_inclusiveDecays_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ST_tW_top_5f_inclusiveDecays_->IntegralAndError(-1,1e3, error);
    std::cout<<" ST_tW_top_5f_inclusiveDecays.............."<< ST_tW_top_5f_inclusiveDecays_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ST_tW_top_5f_inclusiveDecays_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    VVTo2L2Nu_->IntegralAndError(-1,1e3, error);
    std::cout<<" VVTo2L2Nu................................."<< VVTo2L2Nu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  VVTo2L2Nu_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WWTo1L1Nu2Q_->IntegralAndError(-1,1e3, error);
    std::cout<<" WWTo1L1Nu2Q..............................."<< WWTo1L1Nu2Q_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WWTo1L1Nu2Q_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WZJToLLLNu_->IntegralAndError(-1,1e3, error);
    std::cout<<" WZJToLLLNu................................"<< WZJToLLLNu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WZJToLLLNu_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WZTo1L1Nu2Q_->IntegralAndError(-1,1e3, error);
    std::cout<<" WZTo1L1Nu2Q..............................."<< WZTo1L1Nu2Q_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WZTo1L1Nu2Q_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WZTo1L3Nu_->IntegralAndError(-1,1e3, error);
    std::cout<<" WZTo1L3Nu................................."<< WZTo1L3Nu_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WZTo1L3Nu_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    WZTo2L2Q_->IntegralAndError(-1,1e3, error);
    std::cout<<" WZTo2L2Q.................................."<< WZTo2L2Q_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  WZTo2L2Q_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ZZTo2L2Q_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZZTo2L2Q.................................."<< ZZTo2L2Q_->Integral()<<" +/- "<<error<<  "   Fraction: " <<  ZZTo2L2Q_->Integral()/totalBKGIntegral<< "\n";
    error = 0;
    ZZTo4L_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZZTo4L...................................."<< ZZTo4L_->Integral()<<" +/- "<<error<< "   Fraction: " <<  ZZTo4L_->Integral()/totalBKGIntegral<< "\n";
    
    error = 0;
    comb_->IntegralAndError(-1,1e3, error);
    std::cout<<" Combined Background Total................."<< comb_->Integral()<<" +/- "<<error<< "\n";
    
    delete WJetsToLNu_;
    delete W1JetsToLNu_;
    delete W2JetsToLNu_;
    delete W3JetsToLNu_;
    delete W4JetsToLNu_;
    delete DYhigh_;
    delete DYlow_;
    delete DYinc_;
    delete DY1Jets_;
    delete DY2Jets_;
    delete DY3Jets_;
    delete DY4Jets_;
    delete TT_;
    delete GluGluHTauTau_;
    delete VBFHTauTau_;
    delete WminusHToTauTau_M125_;
    delete WplusHToTauTau_M125_;
    delete ttHJetTT_;
    delete ZHTauTau_;
    delete ST_t_channel_antitop_4f_leptonDecays_;
    delete ST_t_channel_top_4f_leptonDecays_;
    delete ST_tW_antitop_5f_inclusiveDecays_;
    delete ST_tW_top_5f_inclusiveDecays_;
    delete VVTo2L2Nu_;
    delete WWTo1L1Nu2Q_;
    delete WZJToLLLNu_;
    delete WZTo1L1Nu2Q_;
    delete WZTo1L3Nu_;
    delete WZTo2L2Q_;
    delete ZZTo2L2Q_;
    delete ZZTo4L_;
    delete comb_;
}


void drawSignalRegion(TCut cut, double sf, TH1F * QCDshape, std::string parameter, float bin[3], std::string can_name, std::string chan)
{

	/* check if want blinded signal region met tail */

	if(signalRegionMETonly && parameter!="met") return;

	if(signalRegionMETonly && parameter=="met") 
	{
		global_title = "Signal Region with Blind MET Tail";
	}
    
	/* create a TCanvas */
	TCanvas * Signal_region = new TCanvas(can_name.c_str(),can_name.c_str(),canDim[0],canDim[1]);
	Signal_region->Divide(1,2);

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",bin[0],bin[1],bin[2]); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",bin[0],bin[1],bin[2]); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",bin[0],bin[1],bin[2]);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",bin[0],bin[1],bin[2]);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",bin[0],bin[1],bin[2]);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",bin[0],bin[1],bin[2]); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * tt_ = new TH1F("tt_","tt_",bin[0],bin[1],bin[2]); 
	tt_->Sumw2(); 
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",bin[0],bin[1],bin[2]);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",bin[0],bin[1],bin[2]);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",bin[0],bin[1],bin[2]);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",bin[0],bin[1],bin[2]);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",bin[0],bin[1],bin[2]);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);
    
	TH1F * zp600_ = new TH1F("zp600_","zp600_",bin[0],bin[1],bin[2]); 
	zp600_->Sumw2(); 

	TH1F * zp800_ = new TH1F("zp800_","zp800_",bin[0],bin[1],bin[2]); 
	zp800_->Sumw2(); 

	TH1F * zp1000_ = new TH1F("zp1000_","zp1000_",bin[0],bin[1],bin[2]); 
	zp1000_->Sumw2(); 

	TH1F * zp1200_ = new TH1F("zp1200_","zp1200_",bin[0],bin[1],bin[2]); 
	zp1200_->Sumw2(); 

	//TH1F * zp1400_ = new TH1F("zp1400_","zp1400_",bin[0],bin[1],bin[2]);
	//zp1400_->Sumw2();

	/* sum of all bks */
	TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2(); 

	/* fill the hists */
	Signal_region->cd(1);

	DATA->Draw((parameter+">>data_").c_str(),cut);

	/* apply blinding conditions */

	if(parameter=="met")
	{
		for(int i=0; i<data_->GetNbinsX()+1; ++i)
		{
			if(data_->GetBinLowEdge(i)>= met_blind) 
			{
				data_->SetBinContent(i,0);
				data_->SetBinError(i,0);
			}
		}

	}

	W->Draw((parameter+">>w_").c_str(),cut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),cut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),cut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),cut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),cut*weights["VV"].c_str());
	TT->Draw((parameter+">>tt_").c_str(),cut*weights["TT"].c_str());
	ZHTauTau->Draw((parameter+">>zh_").c_str(),cut*weights["ZH"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),cut*weights["ttHJetTT"].c_str());

	MZP600_MA0400->Draw((parameter+">>zp600_").c_str(),cut*weights["MONO"].c_str());
	MZP800_MA0400->Draw((parameter+">>zp800_").c_str(),cut*weights["MONO"].c_str());
	MZP1000_MA0400->Draw((parameter+">>zp1000_").c_str(),cut*weights["MONO"].c_str());
	MZP1200_MA0400->Draw((parameter+">>zp1200_").c_str(),cut*weights["MONO"].c_str());
	//MZP1400_MA0700->Draw((parameter+">>zp1400_").c_str(),cut*weights["MONO"].c_str());

	qcd_->Add(QCDshape);
	qcd_->Scale(qcdOStoSS);
	w_->Scale(sf);

	THStack * sigMTstack  = new THStack();

    sigMTstack->Add(zhtautau_);
    sigMTstack->Add(tthjettt_);
    sigMTstack->Add(whtautau_);
    sigMTstack->Add(vbfhtautau_);
    sigMTstack->Add(glugluhtautau_);
    sigMTstack->Add(vv_);
	sigMTstack->Add(tt_);
	sigMTstack->Add(w_);
	sigMTstack->Add(ztt_);
    sigMTstack->Add(zj_);
    sigMTstack->Add(zl_);
	sigMTstack->Add(qcd_);

	Signal_region->cd(1);

	data_->SetMaximum(DATA_MAX*data_->GetMaximum());
	data_->SetMinimum(DATA_MIN);

//	data_->SetTitle((can_name+";XXX;Events/Bin").c_str());
	data_->SetTitle(";XXX;Events/Bin");

	data_->GetXaxis()->SetTitle(x_axisLabels[parameter].c_str());

	data_->DrawCopy("PE");
	sigMTstack->Draw("histsames");

	zp1000_->SetLineStyle(1);
	//zp1400_->SetLineStyle(2);

	zp1000_->SetLineWidth(5);
	//zp1400_->SetLineWidth(5);

	zp1000_->SetLineColor(6);
	//zp1400_->SetLineColor(1);

	if(shouldIplotSignals) 	zp1000_->DrawCopy("hist sames");
	//if(shouldIplotSignals)	zp1400_->DrawCopy("hist sames");

	data_->DrawCopy("PEsames");

	/* update canvas */
	Signal_region->Update();

	/* get a sum of bks */

	comb_->Add(vv_);
	comb_->Add(tt_);
	comb_->Add(w_);
	comb_->Add(ztt_);
    comb_->Add(zj_);
    comb_->Add(zl_);
    comb_->Add(zhtautau_);
    comb_->Add(tthjettt_);
    comb_->Add(glugluhtautau_);
    comb_->Add(vbfhtautau_);
    comb_->Add(whtautau_);
	comb_->Add(qcd_);
    
	/* small fix for when blinded data is empty */

	if(data_->GetSumOfWeights()==0)
	{
		data_->SetMarkerColor(2);
		std::cout<<" **** EMPTY BLINDED DATA ****, setting eq to bkg total ****\n";
		data_->Add(comb_);

		data_->DrawCopy("PE");
		sigMTstack->Draw("histsames");
		if(shouldIplotSignals) 	zp1000_->DrawCopy("hist sames");
		//if(shouldIplotSignals)	zp1400_->DrawCopy(" hist sames");

		data_->DrawCopy("PEsames");
	}

	drawTcanvasAndLegendAndRatio(Signal_region, data_, comb_,1);

	Signal_region->DrawClone();

	std::string localSaveName = saveName + parameter + "_" + chan + ".png";
	Signal_region->cd()->SaveAs(localSaveName.c_str());

	Signal_region->Close();

	// scale things to the projected lumi
	vv_->Scale(lumi_sf);
	tt_->Scale(lumi_sf);
	ztt_->Scale(lumi_sf);
    zl_->Scale(lumi_sf);
    zj_->Scale(lumi_sf);
	w_->Scale(lumi_sf);
	qcd_->Scale(lumi_sf);
    zhtautau_->Scale(lumi_sf);
    glugluhtautau_->Scale(lumi_sf);
    vbfhtautau_->Scale(lumi_sf);
    whtautau_->Scale(lumi_sf);
    tthjettt_->Scale(lumi_sf);
    
	zp600_->Scale(lumi_sf);
	zp800_->Scale(lumi_sf);
	zp1000_->Scale(lumi_sf);
	zp1200_->Scale(lumi_sf);
	//zp1400_->Scale(lumi_sf);
	comb_->Scale();
    
	// print signal region bkg yields (under whatever cut is provided)

	std::cout<<" bkg totals under "<<can_name<<"\n";

	double error = 0;

	error = 0;
	vv_->IntegralAndError(-1,1e3, error);
	std::cout<<" VV ... "<<vv_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	tt_->IntegralAndError(-1,1e3, error);
	std::cout<<" TT ... "<<tt_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	ztt_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZTT ... "<<ztt_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
	zl_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZL ... "<<zl_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
	zj_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZJ ... "<<zj_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	w_->IntegralAndError(-1,1e3, error);
	std::cout<<" W ... "<<w_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
	zhtautau_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZHTauTau ... "<<zhtautau_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
	glugluhtautau_->IntegralAndError(-1,1e3, error);
	std::cout<<" GluGluHTauTau ... "<<glugluhtautau_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
	vbfhtautau_->IntegralAndError(-1,1e3, error);
	std::cout<<" VBFHTauTau ... "<<vbfhtautau_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
	whtautau_->IntegralAndError(-1,1e3, error);
	std::cout<<" WHTauTau ... "<<whtautau_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
	tthjettt_->IntegralAndError(-1,1e3, error);
	std::cout<<" ttHJetTT ... "<<tthjettt_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	qcd_->IntegralAndError(-1,1e3, error);
	error = sqrt(qcd_->GetEntries()); /* since it is a sum the error acts odd */
	std::cout<<" QCD ... "<<qcd_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	zp600_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZP600 ... "<<zp600_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	zp800_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZP800 ... "<<zp800_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	zp1000_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZP1000 ... "<<zp1000_->Integral()<<" +/- "<<error<<"\n";

	error = 0;
	zp1200_->IntegralAndError(-1,1e3, error);
	std::cout<<" ZP1200 ... "<<zp1200_->Integral()<<" +/- "<<error<<"\n";

	//error = 0;
	//zp1400_->IntegralAndError(-1,1e3, error);
	//std::cout<<" ZP1400 ... "<<zp1400_->Integral()<<" +/- "<<error<<"\n";

	/* the sum */

	error = 0;
	comb_->IntegralAndError(-1,1e3, error);
	std::cout<<" totalBkg ... "<<comb_->Integral()<<" +/- "<<error<<"\n";

	// test

    double wI, wE;
    double vvI, vvE;
    double zttI, zttE;
    double zlI, zlE;
    double zjI, zjE;
    double qcdI, qcdE;
    double ttI, ttE;
    double zhtautauI, zhtautauE;
    double whtautauI, whtautauE;
    double vbfhtautauI, vbfhtautauE;
    double glugluhtautauI, glugluhtautauE;
    double tthjetttI, tthjetttE;

    double zp600I, zp600E;
    double zp800I, zp800E;
    double zp1000I, zp1000E;
    double zp1200I, zp1200E;
    //double zp1400I, zp1400E;

    zp600I = zp600_->Integral(-1, zp600_->GetNbinsX()+1);
    zp600_->IntegralAndError(-1, zp600_->GetNbinsX()+1,zp600E);

    zp800I = zp800_->Integral(-1, zp800_->GetNbinsX()+1);
    zp800_->IntegralAndError(-1, zp800_->GetNbinsX()+1,zp800E);

    zp1000I = zp1000_->Integral(-1, zp1000_->GetNbinsX()+1);
    zp1000_->IntegralAndError(-1, zp1000_->GetNbinsX()+1,zp1000E);

    zp1200I = zp1200_->Integral(-1, zp1200_->GetNbinsX()+1);
    zp1200_->IntegralAndError(-1, zp1200_->GetNbinsX()+1,zp1200E);

    //zp1400I = zp1400_->Integral(-1, zp1400_->GetNbinsX()+1);
    //zp1400_->IntegralAndError(-1, zp1400_->GetNbinsX()+1,zp1400E);

    wI = w_->Integral(-1, w_->GetNbinsX()+1);
    w_->IntegralAndError(-1, w_->GetNbinsX()+1,wE);

    vvI = vv_->Integral(-1, vv_->GetNbinsX()+1);
    vv_->IntegralAndError(-1, vv_->GetNbinsX()+1,vvE);

    zttI = ztt_->Integral(-1, ztt_->GetNbinsX()+1);
    ztt_->IntegralAndError(-1, ztt_->GetNbinsX()+1,zttE);
    
    zlI = zl_->Integral(-1, zl_->GetNbinsX()+1);
    zl_->IntegralAndError(-1, zl_->GetNbinsX()+1,zlE);
    
    zjI = zj_->Integral(-1, zj_->GetNbinsX()+1);
    zj_->IntegralAndError(-1, zj_->GetNbinsX()+1,zjE);

    qcdI = qcd_->Integral(-1, qcd_->GetNbinsX()+1);
    qcd_->IntegralAndError(-1, qcd_->GetNbinsX()+1,qcdE);

    ttI = tt_->Integral(-1, tt_->GetNbinsX()+1);
    tt_->IntegralAndError(-1, tt_->GetNbinsX()+1,ttE);

    zhtautauI = zhtautau_->Integral(-1, zhtautau_->GetNbinsX()+1);
    zhtautau_->IntegralAndError(-1, zhtautau_->GetNbinsX()+1,zhtautauE);
    
    glugluhtautauI = glugluhtautau_->Integral(-1, glugluhtautau_->GetNbinsX()+1);
    glugluhtautau_->IntegralAndError(-1, glugluhtautau_->GetNbinsX()+1,glugluhtautauE);
    
    whtautauI = whtautau_->Integral(-1, whtautau_->GetNbinsX()+1);
    whtautau_->IntegralAndError(-1, whtautau_->GetNbinsX()+1,whtautauE);
    
    vbfhtautauI = vbfhtautau_->Integral(-1, vbfhtautau_->GetNbinsX()+1);
    vbfhtautau_->IntegralAndError(-1, vbfhtautau_->GetNbinsX()+1,vbfhtautauE);
    
    tthjetttI = tthjettt_->Integral(-1, tthjettt_->GetNbinsX()+1);
    tthjettt_->IntegralAndError(-1, tthjettt_->GetNbinsX()+1,tthjetttE);

    /* format the errors */

    if(wI>0.0){ wE = 1 + wE/wI; } else {wI = 0.0; wE = 1.0;}
    if(vvI>0.0){ vvE = 1 + vvE/vvI; } else {vvI = 0.0; vvE = 1.0;}
    if(zttI>0.0){ zttE = 1 + zttE/zttI; } else {zttI = 0.0; zttE = 1.0;}
    if(zlI>0.0){ zlE = 1 + zlE/zlI; } else {zlI = 0.0; zlE = 1.0;}
    if(zjI>0.0){ zjE = 1 + zjE/zjI; } else {zjI = 0.0; zjE = 1.0;}
    if(qcdI>0.0){ qcdE = 1 + qcdE/qcdI; } else {qcdI = 0.0; qcdE = 1.0;}
    if(ttI>0.0){ ttE = 1 + ttE/ttI; } else {ttI = 0.0; ttE = 1.0;}
    if(zhtautauI>0.0){ zhtautauE = 1 + zhtautauE/zhtautauI; } else {zhtautauI = 0.0; zhtautauE = 1.0;}
    if(whtautauI>0.0){ whtautauE = 1 + whtautauE/whtautauI; } else {whtautauI = 0.0; whtautauE = 1.0;}
    if(vbfhtautauI>0.0){ vbfhtautauE = 1 + vbfhtautauE/vbfhtautauI; } else {vbfhtautauI = 0.0; vbfhtautauE = 1.0;}
    if(glugluhtautauI>0.0){ glugluhtautauE = 1 + glugluhtautauE/glugluhtautauI; } else {glugluhtautauI = 0.0; glugluhtautauE = 1.0;}
    if(tthjetttI>0.0){ tthjetttE = 1 + tthjetttE/tthjetttI; } else {tthjetttI = 0.0; tthjetttE = 1.0;}
    if(zp600I>0.0){ zp600E = 1 + zp600E/zp600I; } else {zp600I = 0.0; zp600E = 1.0;}
    if(zp800I>0.0){ zp800E = 1 + zp800E/zp800I; } else {zp800I = 0.0; zp800E = 1.0;}
    if(zp1000I>0.0){ zp1000E = 1 + zp1000E/zp1000I; } else {zp1000I = 0.0; zp1000E = 1.0;}
    if(zp1200I>0.0){ zp1200E = 1 + zp1200E/zp1200I; } else {zp1200I = 0.0; zp1200E = 1.0;}
    //if(zp1400I>0.0){ zp1400E = 1 + zp1400E/zp1400I; } else {zp1400I = 0.0; zp1400E = 1.0;}

    if(comb_->Integral()!=0) std::cout<<" @ ZP = 600 s/rt(b) = "<<zp600I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 800 s/rt(b) = "<<zp800I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1000 s/rt(b) = "<<zp1000I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1200 s/rt(b) = "<<zp1200I/sqrt(comb_->Integral())<<"\n";
    //if(comb_->Integral()!=0) std::cout<<" @ ZP = 1400 s/rt(b) = "<<zp1400I/sqrt(comb_->Integral())<<"\n";

    
    printf("QUANTITY       %s %s %s %s %s %s %s %s %s %s %s %s %s \n","SIGNAL","W","VV","ZTT","ZJ","ZL","QCD","tt","ZHTauTau","WHTauTau","GluGluHTauTau","VBFHTauTau","ttHJetTT");

    printf("hiZP600 rate    %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp600I,wI,vvI,zttI,zjI,zlI,qcdI,ttI,zhtautauI,whtautauI,glugluhtautauI,vbfhtautauI,tthjetttI);
    printf("hiZP600 stat.err %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp600E,wE,vvE,zttE,zjE,zlE,qcdE,ttE,zhtautauE,whtautauE,glugluhtautauE,vbfhtautauE,tthjetttE);


    printf("hiZP800 rate     %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp800I,wI,vvI,zttI,zjI,zlI,qcdI,ttI,zhtautauI,whtautauI,glugluhtautauI,vbfhtautauI,tthjetttI);
    printf("hiZP800 stat.err %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp800E,wE,vvE,zttE,zjE,zlE,qcdE,ttE,zhtautauE,whtautauE,glugluhtautauE,vbfhtautauE,tthjetttE);

    printf("hiZP1000 rate     %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp1000I,wI,vvI,zttI,zjI,zlI,qcdI,ttI,zhtautauI,whtautauI,glugluhtautauI,vbfhtautauI,tthjetttI);
    printf("hiZP1000 stat.err %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp1000E,wE,vvE,zttE,zjE,zlE,qcdE,ttE,zhtautauE,whtautauE,glugluhtautauE,vbfhtautauE,tthjetttE);


    printf("hiZP1200 rate     %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp1200I,wI,vvI,zttI,zjI,zlI,qcdI,ttI,zhtautauI,whtautauI,glugluhtautauI,vbfhtautauI,tthjetttI);
    printf("hiZP1200 stat.err %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp1200E,wE,vvE,zttE,zjE,zlE,qcdE,ttE,zhtautauE,whtautauE,glugluhtautauE,vbfhtautauE,tthjetttE);

/*
    printf("ZP1400 rate     %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp1400I,wI,vvI,zttI,zjI,zlI,qcdI,ttI,zhtautauI,whtautauI,glugluhtautauI,vbfhtautauI,tthjetttI);
    printf("ZP1400 stat.err %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf %15.2lf\n",zp1400E,wE,vvE,zttE,zjE,zlE,qcdE,ttE,zhtautauE,whtautauE,glugluhtautauE,vbfhtautauE,tthjetttE);
*/
	// test

	if(signalRegionMETonly && parameter=="met")
	{
		/* create a file to help with S/sqrt(S+B) cut opt */

		std::cout<<" enter name for shape root file \n";
        std::string catName = "Category";
		std::string optName;
		cin>>optName;
        
		TFile sbOp(optName.c_str(),"RECREATE");
        TDirectory * catdir = sbOp.mkdir(catName.c_str());
        catdir->cd();
        
        vv_->Write("vv");
        tt_->Write("tt");
        ztt_->Write("ztt");
        zl_->Write("zl");
        zj_->Write("zj");
        w_->Write("w");
        qcd_->Write("qcd");
        zhtautau_->Write("zhtautau");
        glugluhtautau_->Write("glugluhtautau");
        vbfhtautau_->Write("vbfhtautau");
        whtautau_->Write("whtautau");
        tthjettt_->Write("tthjettt");
		comb_->Write("comb");
		zp600_->Write("zp600");
		zp800_->Write("zp800");
		zp1200_->Write("zp1200");
		zp1000_->Write("zp1000");
		//zp140
        sbOp.cd();
		sbOp.Close();
	}

	/* delete pointers */
	delete data_;
	delete vv_;
	delete tt_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;
	delete comb_;
	delete qcd_;
	delete zp600_;
	delete zp800_;
	delete zp1000_;
	delete zp1200_;
	//delete zp1400_;
	delete Signal_region;
	delete sigMTstack;

}

std::vector<std::vector<double>> countSignalRegion(TCut cut, double sf, TH1F * QCDshape, std::string parameter, float bin[3]) //Fill in only yield integrals
{
    std::vector<std::vector<double>> yields(5);
    
	/* check if want blinded signal region met tail */

    global_title = "Signal Region with Blind MET Tail";

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",bin[0],bin[1],bin[2]); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",bin[0],bin[1],bin[2]); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",bin[0],bin[1],bin[2]);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",bin[0],bin[1],bin[2]);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",bin[0],bin[1],bin[2]);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",bin[0],bin[1],bin[2]); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * tt_ = new TH1F("tt_","tt_",bin[0],bin[1],bin[2]); 
	tt_->Sumw2(); 
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",bin[0],bin[1],bin[2]);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",bin[0],bin[1],bin[2]);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",bin[0],bin[1],bin[2]);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",bin[0],bin[1],bin[2]);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",bin[0],bin[1],bin[2]);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);
    
	TH1F * zp600_ = new TH1F("zp600_","zp600_",bin[0],bin[1],bin[2]); 
	zp600_->Sumw2(); 

	TH1F * zp800_ = new TH1F("zp800_","zp800_",bin[0],bin[1],bin[2]); 
	zp800_->Sumw2(); 

	TH1F * zp1000_ = new TH1F("zp1000_","zp1000_",bin[0],bin[1],bin[2]); 
	zp1000_->Sumw2(); 

	TH1F * zp1200_ = new TH1F("zp1200_","zp1200_",bin[0],bin[1],bin[2]); 
	zp1200_->Sumw2(); 

	TH1F * zp1400_ = new TH1F("zp1400_","zp1400_",bin[0],bin[1],bin[2]); 
	zp1400_->Sumw2(); 

	/* sum of all bks */
	TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2();

	DATA->Draw((parameter+">>data_").c_str(),cut);

	/* apply blinding conditions */

	if(parameter=="met")
	{
		for(int i=0; i<data_->GetNbinsX()+1; ++i)
		{
			if(data_->GetBinLowEdge(i)>= met_blind) 
			{
				data_->SetBinContent(i,0);
				data_->SetBinError(i,0);
			}
		}
	}

	W->Draw((parameter+">>w_").c_str(),cut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),cut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),cut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),cut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),cut*weights["VV"].c_str());
	TT->Draw((parameter+">>tt_").c_str(),cut*weights["TT"].c_str());
	ZHTauTau->Draw((parameter+">>zh_").c_str(),cut*weights["ZH"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),cut*weights["ttHJetTT"].c_str());

	MZP600_MA0400->Draw((parameter+">>zp600_").c_str(),cut*weights["MONO"].c_str());
	MZP800_MA0400->Draw((parameter+">>zp800_").c_str(),cut*weights["MONO"].c_str());
	MZP1000_MA0400->Draw((parameter+">>zp1000_").c_str(),cut*weights["MONO"].c_str());
	MZP1200_MA0400->Draw((parameter+">>zp1200_").c_str(),cut*weights["MONO"].c_str());
	MZP1400_MA0700->Draw((parameter+">>zp1400_").c_str(),cut*weights["MONO"].c_str());

	qcd_->Add(QCDshape);
	qcd_->Scale(qcdOStoSS);
	w_->Scale(sf);

	data_->SetMaximum(DATA_MAX*data_->GetMaximum());
	data_->SetMinimum(DATA_MIN);

	/* get a sum of bks */

	comb_->Add(vv_);
	comb_->Add(tt_);
	comb_->Add(w_);
	comb_->Add(ztt_);
    comb_->Add(zj_);
    comb_->Add(zl_);
    comb_->Add(zhtautau_);
    comb_->Add(tthjettt_);
    comb_->Add(glugluhtautau_);
    comb_->Add(vbfhtautau_);
    comb_->Add(whtautau_);
	comb_->Add(qcd_);
    
	/* small fix for when blinded data is empty */

	if(data_->GetSumOfWeights()==0)
	{
		data_->Add(comb_);
	}

	// scale things to the projected lumi
	vv_->Scale(lumi_sf);
	tt_->Scale(lumi_sf);
	ztt_->Scale(lumi_sf);
    zl_->Scale(lumi_sf);
    zj_->Scale(lumi_sf);
	w_->Scale(lumi_sf);
	qcd_->Scale(lumi_sf);
    zhtautau_->Scale(lumi_sf);
    glugluhtautau_->Scale(lumi_sf);
    vbfhtautau_->Scale(lumi_sf);
    whtautau_->Scale(lumi_sf);
    tthjettt_->Scale(lumi_sf);
    
	zp600_->Scale(lumi_sf);
	zp800_->Scale(lumi_sf);
	zp1000_->Scale(lumi_sf);
	zp1200_->Scale(lumi_sf);
	zp1400_->Scale(lumi_sf);
	comb_->Scale(lumi_sf);
    
	double error = 0;

	error = 0;
	vv_->IntegralAndError(-1,1e3, error);

	error = 0;
	tt_->IntegralAndError(-1,1e3, error);

	error = 0;
	ztt_->IntegralAndError(-1,1e3, error);

    error = 0;
	zl_->IntegralAndError(-1,1e3, error);
    
    error = 0;
	zj_->IntegralAndError(-1,1e3, error);

	error = 0;
	w_->IntegralAndError(-1,1e3, error);
    
    error = 0;
	zhtautau_->IntegralAndError(-1,1e3, error);

    error = 0;
	glugluhtautau_->IntegralAndError(-1,1e3, error);
    
    error = 0;
	vbfhtautau_->IntegralAndError(-1,1e3, error);

    error = 0;
	whtautau_->IntegralAndError(-1,1e3, error);
    
    error = 0;
	tthjettt_->IntegralAndError(-1,1e3, error);

	error = 0;
	qcd_->IntegralAndError(-1,1e3, error);
	error = sqrt(qcd_->GetEntries()); /* since it is a sum the error acts odd */

	error = 0;
	zp600_->IntegralAndError(-1,1e3, error);

	error = 0;
	zp800_->IntegralAndError(-1,1e3, error);

	error = 0;
	zp1000_->IntegralAndError(-1,1e3, error);

	error = 0;
	zp1200_->IntegralAndError(-1,1e3, error);

	error = 0;
	zp1400_->IntegralAndError(-1,1e3, error);

	/* the sum */

	error = 0;
	comb_->IntegralAndError(-1,1e3, error);

	// test

    double wI, wE;
    double vvI, vvE;
    double zttI, zttE;
    double zlI, zlE;
    double zjI, zjE;
    double qcdI, qcdE;
    double ttI, ttE;
    double zhtautauI, zhtautauE;
    double whtautauI, whtautauE;
    double vbfhtautauI, vbfhtautauE;
    double glugluhtautauI, glugluhtautauE;
    double tthjetttI, tthjetttE;

    double zp600I, zp600E;
    double zp800I, zp800E;
    double zp1000I, zp1000E;
    double zp1200I, zp1200E;
    double zp1400I, zp1400E;

    zp600I = zp600_->Integral(-1, zp600_->GetNbinsX()+1);
    zp600_->IntegralAndError(-1, zp600_->GetNbinsX()+1,zp600E);

    zp800I = zp800_->Integral(-1, zp800_->GetNbinsX()+1);
    zp800_->IntegralAndError(-1, zp800_->GetNbinsX()+1,zp800E);

    zp1000I = zp1000_->Integral(-1, zp1000_->GetNbinsX()+1);
    zp1000_->IntegralAndError(-1, zp1000_->GetNbinsX()+1,zp1000E);

    zp1200I = zp1200_->Integral(-1, zp1200_->GetNbinsX()+1);
    zp1200_->IntegralAndError(-1, zp1200_->GetNbinsX()+1,zp1200E);

    zp1400I = zp1400_->Integral(-1, zp1400_->GetNbinsX()+1);
    zp1400_->IntegralAndError(-1, zp1400_->GetNbinsX()+1,zp1400E);

    wI = w_->Integral(-1, w_->GetNbinsX()+1);
    w_->IntegralAndError(-1, w_->GetNbinsX()+1,wE);

    vvI = vv_->Integral(-1, vv_->GetNbinsX()+1);
    vv_->IntegralAndError(-1, vv_->GetNbinsX()+1,vvE);

    zttI = ztt_->Integral(-1, ztt_->GetNbinsX()+1);
    ztt_->IntegralAndError(-1, ztt_->GetNbinsX()+1,zttE);
    
    zlI = zl_->Integral(-1, zl_->GetNbinsX()+1);
    zl_->IntegralAndError(-1, zl_->GetNbinsX()+1,zlE);
    
    zjI = zj_->Integral(-1, zj_->GetNbinsX()+1);
    zj_->IntegralAndError(-1, zj_->GetNbinsX()+1,zjE);

    qcdI = qcd_->Integral(-1, qcd_->GetNbinsX()+1);
    qcd_->IntegralAndError(-1, qcd_->GetNbinsX()+1,qcdE);

    ttI = tt_->Integral(-1, tt_->GetNbinsX()+1);
    tt_->IntegralAndError(-1, tt_->GetNbinsX()+1,ttE);

    zhtautauI = zhtautau_->Integral(-1, zhtautau_->GetNbinsX()+1);
    zhtautau_->IntegralAndError(-1, zhtautau_->GetNbinsX()+1,zhtautauE);
    
    glugluhtautauI = glugluhtautau_->Integral(-1, glugluhtautau_->GetNbinsX()+1);
    glugluhtautau_->IntegralAndError(-1, glugluhtautau_->GetNbinsX()+1,glugluhtautauE);
    
    whtautauI = whtautau_->Integral(-1, whtautau_->GetNbinsX()+1);
    whtautau_->IntegralAndError(-1, whtautau_->GetNbinsX()+1,whtautauE);
    
    vbfhtautauI = vbfhtautau_->Integral(-1, vbfhtautau_->GetNbinsX()+1);
    vbfhtautau_->IntegralAndError(-1, vbfhtautau_->GetNbinsX()+1,vbfhtautauE);
    
    tthjetttI = tthjettt_->Integral(-1, tthjettt_->GetNbinsX()+1);
    tthjettt_->IntegralAndError(-1, tthjettt_->GetNbinsX()+1,tthjetttE);

    /* format the errors */

    if(wI>0.0){ wE = 1 + wE/wI; } else {wI = 0.0; wE = 1.0;}
    if(vvI>0.0){ vvE = 1 + vvE/vvI; } else {vvI = 0.0; vvE = 1.0;}
    if(zttI>0.0){ zttE = 1 + zttE/zttI; } else {zttI = 0.0; zttE = 1.0;}
    if(zlI>0.0){ zlE = 1 + zlE/zlI; } else {zlI = 0.0; zlE = 1.0;}
    if(zjI>0.0){ zjE = 1 + zjE/zjI; } else {zjI = 0.0; zjE = 1.0;}
    if(qcdI>0.0){ qcdE = 1 + qcdE/qcdI; } else {qcdI = 0.0; qcdE = 1.0;}
    if(ttI>0.0){ ttE = 1 + ttE/ttI; } else {ttI = 0.0; ttE = 1.0;}
    if(zhtautauI>0.0){ zhtautauE = 1 + zhtautauE/zhtautauI; } else {zhtautauI = 0.0; zhtautauE = 1.0;}
    if(whtautauI>0.0){ whtautauE = 1 + whtautauE/whtautauI; } else {whtautauI = 0.0; whtautauE = 1.0;}
    if(vbfhtautauI>0.0){ vbfhtautauE = 1 + vbfhtautauE/vbfhtautauI; } else {vbfhtautauI = 0.0; vbfhtautauE = 1.0;}
    if(glugluhtautauI>0.0){ glugluhtautauE = 1 + glugluhtautauE/glugluhtautauI; } else {glugluhtautauI = 0.0; glugluhtautauE = 1.0;}
    if(tthjetttI>0.0){ tthjetttE = 1 + tthjetttE/tthjetttI; } else {tthjetttI = 0.0; tthjetttE = 1.0;}
    if(zp600I>0.0){ zp600E = 1 + zp600E/zp600I; } else {zp600I = 0.0; zp600E = 1.0;}
    if(zp800I>0.0){ zp800E = 1 + zp800E/zp800I; } else {zp800I = 0.0; zp800E = 1.0;}
    if(zp1000I>0.0){ zp1000E = 1 + zp1000E/zp1000I; } else {zp1000I = 0.0; zp1000E = 1.0;}
    if(zp1200I>0.0){ zp1200E = 1 + zp1200E/zp1200I; } else {zp1200I = 0.0; zp1200E = 1.0;}
    if(zp1400I>0.0){ zp1400E = 1 + zp1400E/zp1400I; } else {zp1400I = 0.0; zp1400E = 1.0;}

    yields[0].push_back(zp600I);yields[0].push_back(wI);yields[0].push_back(vvI);yields[0].push_back(zttI);yields[0].push_back(zjI);yields[0].push_back(zlI);yields[0].push_back(qcdI);yields[0].push_back(ttI);yields[0].push_back(zhtautauI);yields[0].push_back(whtautauI);yields[0].push_back(glugluhtautauI);yields[0].push_back(vbfhtautauI);yields[0].push_back(tthjetttI);
    yields[1].push_back(zp800I);yields[1].push_back(wI);yields[1].push_back(vvI);yields[1].push_back(zttI);yields[1].push_back(zjI);yields[1].push_back(zlI);yields[1].push_back(qcdI);yields[1].push_back(ttI);yields[1].push_back(zhtautauI);yields[1].push_back(whtautauI);yields[1].push_back(glugluhtautauI);yields[1].push_back(vbfhtautauI);yields[1].push_back(tthjetttI);
    yields[2].push_back(zp1000I);yields[2].push_back(wI);yields[2].push_back(vvI);yields[2].push_back(zttI);yields[2].push_back(zjI);yields[2].push_back(zlI);yields[2].push_back(qcdI);yields[2].push_back(ttI);yields[2].push_back(zhtautauI);yields[2].push_back(whtautauI);yields[2].push_back(glugluhtautauI);yields[2].push_back(vbfhtautauI);yields[2].push_back(tthjetttI);
    yields[3].push_back(zp1200I);yields[3].push_back(wI);yields[3].push_back(vvI);yields[3].push_back(zttI);yields[3].push_back(zjI);yields[3].push_back(zlI);yields[3].push_back(qcdI);yields[3].push_back(ttI);yields[3].push_back(zhtautauI);yields[3].push_back(whtautauI);yields[3].push_back(glugluhtautauI);yields[3].push_back(vbfhtautauI);yields[3].push_back(tthjetttI);
    yields[4].push_back(zp1400I);yields[4].push_back(wI);yields[4].push_back(vvI);yields[4].push_back(zttI);yields[4].push_back(zjI);yields[4].push_back(zlI);yields[4].push_back(qcdI);yields[4].push_back(ttI);yields[4].push_back(zhtautauI);yields[4].push_back(whtautauI);yields[4].push_back(glugluhtautauI);yields[4].push_back(vbfhtautauI);yields[4].push_back(tthjetttI);

	// test
    /*
	if(signalRegionMETonly && parameter=="met")
	{
		std::cout<<" enter name for S/B opt root file \n";
		std::string optName;
		cin>>optName;
		TFile sbOp(optName.c_str(),"RECREATE");


		sbOp.cd();
		comb_->Write();
		zp600_->Write();
		zp800_->Write();
		zp1200_->Write();
		zp1000_->Write();
		zp1400_->Write();
		sbOp.Close();
	}
    */

	/* delete pointers */
	delete data_;
	delete vv_;
	delete tt_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;
	delete comb_;
	delete qcd_;
	delete zp600_;
	delete zp800_;
	delete zp1000_;
	delete zp1200_;
	delete zp1400_;
    
    return yields;
}

void evalSysBaseline(std::vector<std::vector<double>> nomYields, TCut upSigCut, TCut downSigCut, TCut upSSwNormCut, TCut downSSwNormCut, TCut upOSwNormCut, TCut downOSwNormCut, TCut upSSCut, TCut downSSCut, std::string parameter, float bin[3], std::string systematicName)
{
    std::vector<std::vector<double>> upYieldsVect;
    double up_wSF_OS = wjetsNorm_NoPlots(upOSwNormCut);
    double up_wSF_SS = wjetsNorm_NoPlots(upSSwNormCut);
    TH1F * upQCD_met_ = new TH1F("upQCD_met_","upQCD_met_",bin[0],bin[1],bin[2]);
    fillQCD_Shape_NoPlots(upSSCut, up_wSF_SS, upQCD_met_, "met", bin);
    upYieldsVect = countSignalRegion(upSigCut, up_wSF_OS, upQCD_met_, "met", bin);
    
    std::vector<std::vector<double>> downYieldsVect;
    double down_wSF_OS = wjetsNorm_NoPlots(downOSwNormCut);
    double down_wSF_SS = wjetsNorm_NoPlots(downSSwNormCut);
    TH1F * downQCD_met_ = new TH1F("downQCD_met_","downQCD_met_",bin[0],bin[1],bin[2]);
    fillQCD_Shape_NoPlots(downSSCut, down_wSF_SS, downQCD_met_, "met", bin);
    downYieldsVect = countSignalRegion(downSigCut, down_wSF_OS, downQCD_met_, "met", bin);
    
    out_data << systematicName << std::endl;
    
    for (unsigned int i = 0; i < upYieldsVect.size(); i++)
    {
        for (int j = 0 ; j < 13; j++)
        {
            double diff = abs(upYieldsVect[i][j] - downYieldsVect[i][j]);
            double diffFrac = diff/(2.0 * nomYields[i][j]);
            out_data << diffFrac << "        ";
        }
        out_data << std::endl;
    }
}

void evalSysBaselineNoW(std::vector<std::vector<double>> nomYields, TCut upSigCut, TCut downSigCut, TCut upSSCut, TCut downSSCut, std::string parameter, float bin[3], std::string systematicName)
{
    std::vector<std::vector<double>> upYieldsVect;
    double up_wSF_OS = 1.0;
    double up_wSF_SS = 1.0;
    TH1F * upQCD_met_ = new TH1F("upQCD_met_","upQCD_met_",bin[0],bin[1],bin[2]);
    fillQCD_Shape_NoPlots(upSSCut, up_wSF_SS, upQCD_met_, "met", bin);
    upYieldsVect = countSignalRegion(upSigCut, up_wSF_OS, upQCD_met_, "met", bin);
    
    std::vector<std::vector<double>> downYieldsVect;
    double down_wSF_OS = 1.0;
    double down_wSF_SS = 1.0;
    TH1F * downQCD_met_ = new TH1F("downQCD_met_","downQCD_met_",bin[0],bin[1],bin[2]);
    fillQCD_Shape_NoPlots(downSSCut, down_wSF_SS, downQCD_met_, "met", bin);
    downYieldsVect = countSignalRegion(downSigCut, down_wSF_OS, downQCD_met_, "met", bin);
    
    out_data << systematicName << std::endl;
    
    for (unsigned int i = 0; i < upYieldsVect.size(); i++)
    {
        for (int j = 0 ; j < 13; j++)
        {
            //double diff = abs(upYieldsVect[i][j] - downYieldsVect[i][j]);
            double diff = 0.5;
            double diffFrac = diff/(2.0 * nomYields[i][j]);
            out_data << diffFrac << "        ";
        }
        out_data << std::endl;
    }
}

void fillQCD_Shape(TCut SScut, double WnormForQCD, TH1F * QCDshape, std::string parameter, float bin[3], std::string can_name, std::string chan)
{

	if(signalRegionMETonly && parameter!="met") return;

	/* create a TCanvas */
	TCanvas * QCD_SS = new TCanvas(can_name.c_str(),can_name.c_str(),canDim[0],canDim[1]);
	QCD_SS->Divide(1,2);

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",bin[0],bin[1],bin[2]); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",bin[0],bin[1],bin[2]); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",bin[0],bin[1],bin[2]);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",bin[0],bin[1],bin[2]);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",bin[0],bin[1],bin[2]);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",bin[0],bin[1],bin[2]); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * tt_ = new TH1F("tt_","tt_",bin[0],bin[1],bin[2]); 
	tt_->Sumw2(); 
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",bin[0],bin[1],bin[2]);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",bin[0],bin[1],bin[2]);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",bin[0],bin[1],bin[2]);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",bin[0],bin[1],bin[2]);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",bin[0],bin[1],bin[2]);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);

	TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2(); 

	TH1F * zp600_ = new TH1F("zp600_","zp600_",bin[0],bin[1],bin[2]); 
	zp600_->Sumw2(); 

	TH1F * zp800_ = new TH1F("zp800_","zp800_",bin[0],bin[1],bin[2]); 
	zp800_->Sumw2(); 

	TH1F * zp1000_ = new TH1F("zp1000_","zp1000_",bin[0],bin[1],bin[2]); 
	zp1000_->Sumw2(); 

	TH1F * zp1200_ = new TH1F("zp1200_","zp1200_",bin[0],bin[1],bin[2]); 
	zp1200_->Sumw2(); 

	//TH1F * zp1400_ = new TH1F("zp1400_","zp1400_",bin[0],bin[1],bin[2]);
	//zp1400_->Sumw2();

	/* fill the hists */
	QCD_SS->cd(1);

	DATA->Draw((parameter+">>data_").c_str(),SScut);
	W->Draw((parameter+">>w_").c_str(),SScut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),SScut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),SScut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),SScut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),SScut*weights["VV"].c_str());
	TT->Draw((parameter+">>tt_").c_str(),SScut*weights["TT"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),SScut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),SScut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),SScut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),SScut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),SScut*weights["ttHJetTT"].c_str());
    
	MZP600_MA0400->Draw((parameter+">>zp600_").c_str(),SScut*weights["MONO"].c_str());
	MZP800_MA0400->Draw((parameter+">>zp800_").c_str(),SScut*weights["MONO"].c_str());
	MZP1000_MA0400->Draw((parameter+">>zp1000_").c_str(),SScut*weights["MONO"].c_str());
	MZP1200_MA0400->Draw((parameter+">>zp1200_").c_str(),SScut*weights["MONO"].c_str());
	//MZP1400_MA0700->Draw((parameter+">>zp1400_").c_str(),SScut*weights["MONO"].c_str());

	/* QCD is data - all mc bks */

	w_->Scale(WnormForQCD); /* scale this */
	qcd_->Add(data_);
	qcd_->Add(w_,-1);
	qcd_->Add(ztt_,-1);
    qcd_->Add(zl_,-1);
    qcd_->Add(zj_,-1);
	qcd_->Add(tt_,-1);
	qcd_->Add(vv_,-1);
	qcd_->Add(zhtautau_,-1);
    qcd_->Add(whtautau_,-1);
    qcd_->Add(glugluhtautau_,-1);
    qcd_->Add(vbfhtautau_,-1);
    qcd_->Add(tthjettt_,-1);


	THStack * QCDStack  = new THStack();

    QCDStack->Add(zhtautau_);
    QCDStack->Add(whtautau_);
    QCDStack->Add(tthjettt_);
    QCDStack->Add(vbfhtautau_);
    QCDStack->Add(glugluhtautau_);
	QCDStack->Add(vv_);
	QCDStack->Add(tt_);
	QCDStack->Add(w_);
	QCDStack->Add(ztt_);
    QCDStack->Add(zl_);
    QCDStack->Add(zj_);
	QCDStack->Add(qcd_);

    QCD_SS->cd(1);data_->SetMaximum(DATA_MAX*data_->GetMaximum());data_->SetTitle(";XXX;Events/Bin");data_->GetXaxis()->SetTitle(x_axisLabels[parameter].c_str());data_->DrawCopy("PE");QCDStack->Draw("histsames");data_->DrawCopy("PEsames");QCD_SS->Update();

	comb_->Add(vv_);
	comb_->Add(tt_);
	comb_->Add(w_);
	comb_->Add(ztt_);
    comb_->Add(zl_);
    comb_->Add(zj_);
    comb_->Add(zhtautau_);
    comb_->Add(whtautau_);
    comb_->Add(glugluhtautau_);
    comb_->Add(vbfhtautau_);
    comb_->Add(tthjettt_);
	comb_->Add(qcd_);

    drawTcanvasAndLegendAndRatio(QCD_SS, data_, comb_,0);QCD_SS->DrawClone();std::string localSaveName = "QCD_"+saveName + parameter + "_" + chan + ".png";QCD_SS->cd()->SaveAs(localSaveName.c_str());QCD_SS->Close();

	/* eliminate negative bins */

	//std::cout<<" ***** "<<qcd_->Integral()<<"\n";
	for(int i = 0; i<qcd_->GetNbinsX()+1; i++)
	{
		if(qcd_->GetBinContent(i)<0) qcd_->SetBinContent(i,0);
	}
	//std::cout<<" ***** "<<qcd_->Integral()<<"\n";

	QCDshape->Add(qcd_);

	/* delete pointers */
	delete data_;
	delete vv_;
	delete tt_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;
	delete qcd_;
	delete zp600_;
	delete zp800_;
	delete zp1000_;
	delete zp1200_;
	//delete zp1400_;
	delete comb_;
	delete QCDStack;
	delete QCD_SS;
}

void fillQCD_Shape_NoPlots(TCut SScut, double WnormForQCD, TH1F * QCDshape, std::string parameter, float bin[3])
{

	if(signalRegionMETonly && parameter!="met") return;

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",bin[0],bin[1],bin[2]); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",bin[0],bin[1],bin[2]); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",bin[0],bin[1],bin[2]);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",bin[0],bin[1],bin[2]);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",bin[0],bin[1],bin[2]);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",bin[0],bin[1],bin[2]); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * tt_ = new TH1F("tt_","tt_",bin[0],bin[1],bin[2]); 
	tt_->Sumw2(); 
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",bin[0],bin[1],bin[2]);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",bin[0],bin[1],bin[2]);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",bin[0],bin[1],bin[2]);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",bin[0],bin[1],bin[2]);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",bin[0],bin[1],bin[2]);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);

	TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2(); 

	TH1F * zp600_ = new TH1F("zp600_","zp600_",bin[0],bin[1],bin[2]); 
	zp600_->Sumw2(); 

	TH1F * zp800_ = new TH1F("zp800_","zp800_",bin[0],bin[1],bin[2]); 
	zp800_->Sumw2(); 

	TH1F * zp1000_ = new TH1F("zp1000_","zp1000_",bin[0],bin[1],bin[2]); 
	zp1000_->Sumw2(); 

	TH1F * zp1200_ = new TH1F("zp1200_","zp1200_",bin[0],bin[1],bin[2]); 
	zp1200_->Sumw2(); 

	TH1F * zp1400_ = new TH1F("zp1400_","zp1400_",bin[0],bin[1],bin[2]); 
	zp1400_->Sumw2(); 

	/* fill the hists */

	DATA->Draw((parameter+">>data_").c_str(),SScut);
	W->Draw((parameter+">>w_").c_str(),SScut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),SScut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),SScut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),SScut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),SScut*weights["VV"].c_str());
	TT->Draw((parameter+">>tt_").c_str(),SScut*weights["TT"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),SScut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),SScut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),SScut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),SScut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),SScut*weights["ttHJetTT"].c_str());
    
	MZP600_MA0400->Draw((parameter+">>zp600_").c_str(),SScut*weights["MONO"].c_str());
	MZP800_MA0400->Draw((parameter+">>zp800_").c_str(),SScut*weights["MONO"].c_str());
	MZP1000_MA0400->Draw((parameter+">>zp1000_").c_str(),SScut*weights["MONO"].c_str());
	MZP1200_MA0400->Draw((parameter+">>zp1200_").c_str(),SScut*weights["MONO"].c_str());
	MZP1400_MA0700->Draw((parameter+">>zp1400_").c_str(),SScut*weights["MONO"].c_str());

	/* QCD is data - all mc bks */

	w_->Scale(WnormForQCD); /* scale this */
	qcd_->Add(data_);
	qcd_->Add(w_,-1);
	qcd_->Add(ztt_,-1);
    qcd_->Add(zl_,-1);
    qcd_->Add(zj_,-1);
	qcd_->Add(tt_,-1);
	qcd_->Add(vv_,-1);
	qcd_->Add(zhtautau_,-1);
    qcd_->Add(whtautau_,-1);
    qcd_->Add(glugluhtautau_,-1);
    qcd_->Add(vbfhtautau_,-1);
    qcd_->Add(tthjettt_,-1);

	/* eliminate negative bins */

	//std::cout<<" ***** "<<qcd_->Integral()<<"\n";
	for(int i = 0; i<qcd_->GetNbinsX()+1; i++)
	{
		if(qcd_->GetBinContent(i)<0) qcd_->SetBinContent(i,0);
	}
	//std::cout<<" ***** "<<qcd_->Integral()<<"\n";
    
	QCDshape->Add(qcd_);
    
	/* delete pointers */
	delete data_;
	delete vv_;
	delete tt_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;
	delete qcd_;
	delete zp600_;
	delete zp800_;
	delete zp1000_;
	delete zp1200_;
	delete zp1400_;
	delete comb_;

}


double wjetsNorm(TCut wNormCut, std::string can_name)
{

	/* create a TCanvas */
    TCanvas * wjetNorm_can = new TCanvas(can_name.c_str(),can_name.c_str(),canDim[0],canDim[1]);
    wjetNorm_can->Divide(1,2);

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",mtBinning[0],mtBinning[1],mtBinning[2]);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * tt_ = new TH1F("tt_","tt_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	tt_->Sumw2(); 
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",mtBinning[0],mtBinning[1],mtBinning[2]);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);

	TH1F * comb_ = new TH1F("comb_","comb_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	comb_->Sumw2(); 

	TH1F * combSUM_ = new TH1F("combSUM_","combSUM_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	combSUM_->Sumw2(); 

	TH1F * zp600_ = new TH1F("zp600_","zp600_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp600_->Sumw2(); 

	TH1F * zp800_ = new TH1F("zp800_","zp800_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp800_->Sumw2(); 

	TH1F * zp1000_ = new TH1F("zp1000_","zp1000_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp1000_->Sumw2(); 

	TH1F * zp1200_ = new TH1F("zp1200_","zp1200_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp1200_->Sumw2(); 

	//TH1F * zp1400_ = new TH1F("zp1400_","zp1400_",mtBinning[0],mtBinning[1],mtBinning[2]);
	//zp1400_->Sumw2();

	/* fill the hists */
	wjetNorm_can->cd(1);

	DATA->Draw("mt_1>>data_",wNormCut);
    
	W->Draw("mt_1>>w_",wNormCut*weights["W"].c_str());
	ZTT->Draw("mt_1>>ztt_",wNormCut*weights["ZTT"].c_str());
    ZJ->Draw("mt_1>>zj_",wNormCut*weights["ZJ"].c_str());
    ZL->Draw("mt_1>>zl_",wNormCut*weights["ZL"].c_str());
	VV->Draw("mt_1>>vv_",wNormCut*weights["VV"].c_str());
	TT->Draw("mt_1>>tt_",wNormCut*weights["TT"].c_str());
	ZHTauTau->Draw("mt_1>>zhtautau_",wNormCut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw("mt_1>>whtautau_",wNormCut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw("mt_1>>glugluhtautau_",wNormCut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw("mt_1>>vbfhtautau_",wNormCut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw("mt_1>>tthjettt_",wNormCut*weights["ttHJetTT"].c_str());

	MZP600_MA0400->Draw("mt_1>>zp600_",wNormCut*weights["MONO"].c_str());
	MZP800_MA0400->Draw("mt_1>>zp800_",wNormCut*weights["MONO"].c_str());
	MZP1000_MA0400->Draw("mt_1>>zp1000_",wNormCut*weights["MONO"].c_str());
	MZP1200_MA0400->Draw("mt_1>>zp1200_",wNormCut*weights["MONO"].c_str());
	//MZP1400_MA0700->Draw("mt_1>>zp1400_",wNormCut*weights["MONO"].c_str());

	THStack * wnormStack  = new THStack();

	/* data minus all non-W */
	comb_->Add(data_);
    comb_->Add(vv_,-1);
	comb_->Add(tt_,-1);
	comb_->Add(ztt_,-1);
    comb_->Add(zj_,-1);
    comb_->Add(zl_,-1);
    comb_->Add(zhtautau_,-1);
    comb_->Add(whtautau_,-1);
    comb_->Add(glugluhtautau_,-1);
    comb_->Add(vbfhtautau_,-1);
    comb_->Add(tthjettt_,-1);

	std::cout<<" for w norm,  data-(non-W) = "<<comb_->Integral()<<"\n";
	std::cout<<" while W mc raw norm = "<<w_->Integral()<<"\n";
	double sf = comb_->Integral()/w_->Integral();

	std::cout<<" sf is "<<sf<<"\n";
	w_->Scale(sf);

	std::cout<<" post sf W norm = "<<w_->Integral()<<"\n";

	wnormStack->Add(vv_);
	wnormStack->Add(tt_);
	wnormStack->Add(w_);
	wnormStack->Add(ztt_);
    wnormStack->Add(zj_);
    wnormStack->Add(zl_);
    wnormStack->Add(zhtautau_);
    wnormStack->Add(whtautau_);
    wnormStack->Add(glugluhtautau_);
    wnormStack->Add(vbfhtautau_);
    wnormStack->Add(tthjettt_);

    wjetNorm_can->cd(1); data_->SetMaximum(DATA_MAX*data_->GetMaximum());/*data_->SetTitle((can_name+";XXX;Events/Bin").c_str());*/data_->SetTitle(";XXX;Events/Bin");data_->GetXaxis()->SetTitle(x_axisLabels["mt_1"].c_str());data_->DrawCopy("PE");wnormStack->Draw("histsames");data_->DrawCopy("PEsames");wjetNorm_can->Update();

	combSUM_->Add(vv_);
	combSUM_->Add(tt_);
	combSUM_->Add(w_);
	combSUM_->Add(ztt_);
    combSUM_->Add(zl_);
    combSUM_->Add(zj_);
    combSUM_->Add(zhtautau_);
    combSUM_->Add(whtautau_);
    combSUM_->Add(glugluhtautau_);
    combSUM_->Add(vbfhtautau_);
    combSUM_->Add(tthjettt_);

    drawTcanvasAndLegendAndRatio(wjetNorm_can, data_, combSUM_,0);wjetNorm_can->DrawClone();std::string localSaveName = can_name+"_"+saveName + "MT.png";wjetNorm_can->cd()->SaveAs(localSaveName.c_str());wjetNorm_can->Close();

	/* delete pointers */
	delete data_;
    delete comb_;
	delete combSUM_;
	delete vv_;
	delete tt_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;

	delete zp600_;
	delete zp800_;
	delete zp1000_;
	delete zp1200_;
	//delete zp1400_;

	delete wnormStack;
	delete wjetNorm_can;


	return sf;
}

double wjetsNorm_NoPlots(TCut wNormCut)
{

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",mtBinning[0],mtBinning[1],mtBinning[2]);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * tt_ = new TH1F("tt_","tt_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	tt_->Sumw2(); 
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",mtBinning[0],mtBinning[1],mtBinning[2]);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",mtBinning[0],mtBinning[1],mtBinning[2]);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);

	TH1F * comb_ = new TH1F("comb_","comb_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	comb_->Sumw2();

	TH1F * zp600_ = new TH1F("zp600_","zp600_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp600_->Sumw2(); 

	TH1F * zp800_ = new TH1F("zp800_","zp800_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp800_->Sumw2(); 

	TH1F * zp1000_ = new TH1F("zp1000_","zp1000_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp1000_->Sumw2(); 

	TH1F * zp1200_ = new TH1F("zp1200_","zp1200_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp1200_->Sumw2(); 

	TH1F * zp1400_ = new TH1F("zp1400_","zp1400_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	zp1400_->Sumw2();

	/* fill the hists */

	DATA->Draw("mt_1>>data_",wNormCut);
	W->Draw("mt_1>>w_",wNormCut*weights["W"].c_str());
	ZTT->Draw("mt_1>>ztt_",wNormCut*weights["ZTT"].c_str());
    ZJ->Draw("mt_1>>zj_",wNormCut*weights["ZJ"].c_str());
    ZL->Draw("mt_1>>zl_",wNormCut*weights["ZL"].c_str());
	VV->Draw("mt_1>>vv_",wNormCut*weights["VV"].c_str());
	TT->Draw("mt_1>>tt_",wNormCut*weights["TT"].c_str());
	ZHTauTau->Draw("mt_1>>zhtautau_",wNormCut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw("mt_1>>whtautau_",wNormCut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw("mt_1>>glugluhtautau_",wNormCut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw("mt_1>>vbfhtautau_",wNormCut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw("mt_1>>tthjettt_",wNormCut*weights["ttHJetTT"].c_str());

	MZP600_MA0400->Draw("mt_1>>zp600_",wNormCut*weights["MONO"].c_str());
	MZP800_MA0400->Draw("mt_1>>zp800_",wNormCut*weights["MONO"].c_str());
	MZP1000_MA0400->Draw("mt_1>>zp1000_",wNormCut*weights["MONO"].c_str());
	MZP1200_MA0400->Draw("mt_1>>zp1200_",wNormCut*weights["MONO"].c_str());
	MZP1400_MA0700->Draw("mt_1>>zp1400_",wNormCut*weights["MONO"].c_str());

	/* data minus all non-W */
	comb_->Add(data_);
    comb_->Add(vv_,-1);
	comb_->Add(tt_,-1);
	comb_->Add(ztt_,-1);
    comb_->Add(zj_,-1);
    comb_->Add(zl_,-1);
    comb_->Add(zhtautau_,-1);
    comb_->Add(whtautau_,-1);
    comb_->Add(glugluhtautau_,-1);
    comb_->Add(vbfhtautau_,-1);
    comb_->Add(tthjettt_,-1);

	double sf = comb_->Integral()/w_->Integral();

	/* delete pointers */
	delete data_;
    delete comb_;
	delete vv_;
	delete tt_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;

	delete zp600_;
	delete zp800_;
	delete zp1000_;
	delete zp1200_;
	delete zp1400_;

	return sf;
}

void drawTcanvasAndLegendAndRatio(TCanvas * C, TH1F * num__, TH1F* den__, bool drawSignals)
{

	C->cd(1);

	gPad->SetGridx(0);
	gPad->SetGridy(0);
	gPad->SetLogy(setLog);

	TLegend leg(.75,.35,1.0,.85);
    leg.SetTextSize(.04);
    leg.SetTextFont(22);
    leg.SetBorderSize(0);
    leg.SetFillColor(0);

	TH1F * data__ = new TH1F("data__","data__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	data__->SetMarkerStyle(dataMarker);

	TH1F * ztt__ = new TH1F("ztt__","ztt__",mtBinning[0],mtBinning[1],mtBinning[2]);
	ztt__->SetFillColor(colors["ZTT"]);
    
    TH1F * zl__ = new TH1F("zl__","zl__",mtBinning[0],mtBinning[1],mtBinning[2]);
	zl__->SetFillColor(colors["ZL"]);
    
    TH1F * zj__ = new TH1F("zj__","zj__",mtBinning[0],mtBinning[1],mtBinning[2]);
	zj__->SetFillColor(colors["ZJ"]);
	
	TH1F * w__ = new TH1F("w__","w__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	w__->SetFillColor(colors["W"]);
	
	TH1F * tt__ = new TH1F("tt__","tt__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	tt__->SetFillColor(colors["TT"]);
	
	TH1F * vv__ = new TH1F("vv__","vv__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	vv__->SetFillColor(colors["VV"]);
	
	TH1F * zhtautau__ = new TH1F("zhtautau__","zhtautau__",mtBinning[0],mtBinning[1],mtBinning[2]);
	zhtautau__->SetFillColor(colors["ZHTauTau"]);
    
    TH1F * whtautau__ = new TH1F("whtautau__","whtautau__",mtBinning[0],mtBinning[1],mtBinning[2]);
	whtautau__->SetFillColor(colors["WHTauTau"]);
    
    TH1F * glugluhtautau__ = new TH1F("glugluhtautau__","glugluhtautau__",mtBinning[0],mtBinning[1],mtBinning[2]);
	glugluhtautau__->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau__ = new TH1F("vbfhtautau__","vbfhtautau__",mtBinning[0],mtBinning[1],mtBinning[2]);
	vbfhtautau__->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt__ = new TH1F("tthjettt__","tthjettt__",mtBinning[0],mtBinning[1],mtBinning[2]);
	tthjettt__->SetFillColor(colors["ttHJetTT"]);

	TH1F * qcd__ = new TH1F("qcd__","qcd__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	qcd__->SetFillColor(colors["QCD"]);

	TH1F * zp600__ = new TH1F("zp600__","zp600__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	TH1F * zp800__ = new TH1F("zp800__","zp800__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	TH1F * zp1000__ = new TH1F("zp1000__","zp1000__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	TH1F * zp1200__ = new TH1F("zp1200__","zp1200__",mtBinning[0],mtBinning[1],mtBinning[2]); 
	TH1F * zp1400__ = new TH1F("zp1400__","zp1400__",mtBinning[0],mtBinning[1],mtBinning[2]);

    leg.AddEntry(data__, "Observed","PE");
    leg.AddEntry(qcd__, "QCD","F");
    leg.AddEntry(w__, "W+jets","F");
    leg.AddEntry(ztt__, "ZTT","F");
    leg.AddEntry(zl__, "ZL","F");
    leg.AddEntry(zj__, "ZJ","F");
    leg.AddEntry(vv__, "ZZ,WZ,WW,SingleTop","F");
    leg.AddEntry(tt__, "t#bar{t}","F");
    leg.AddEntry(zhtautau__, "ZHTauTau(125 GeV)","F");
    leg.AddEntry(whtautau__, "WHTauTau(125 GeV)","F");
    leg.AddEntry(glugluhtautau__, "GluGluHTauTau(125 GeV)","F");
    leg.AddEntry(vbfhtautau__, "VBFHTauTau(125 GeV)","F");
    leg.AddEntry(tthjettt__, "ttHJetTT(125 GeV)","F");
    // leg.AddEntry(zp600__, "#tau^{+}#tau^{-}+#chi#bar{#chi}","LPE");
    // leg.AddEntry(zp800__, "#tau^{+}#tau^{-}+#chi#bar{#chi}","LPE");
    // leg.AddEntry(zp1000__, "#tau^{+}#tau^{-}+#chi#bar{#chi}","LPE");
    // leg.AddEntry(zp1200__, "#tau^{+}#tau^{-}+#chi#bar{#chi}","LPE");
    // leg.AddEntry(zp1400__, "#tau^{+}#tau^{-}+#chi#bar{#chi}","LPE");

    leg.DrawClone();

    TLatex L1;
    L1.DrawLatexNDC(0.12,0.83,"CMS (#it{Preliminary})");
    //L1.DrawLatexNDC(0.1,0.8,"#it{Preliminary}");

    TLatex L2;
    //L2.SetFont(42);
    L2.SetTextSize(0.06);
    L2.DrawLatexNDC(0.68,0.925,("#font[42]{#bf{"+lumiAndRtS+"}}").c_str());

    TLatex L3;
    L3.SetTextColor(4);
    L3.SetTextSize(1.2 * L1.GetTextSize());

    L3.DrawLatexNDC(0.12,0.76,chan_label.c_str());

    TLatex L4;
    //L2.SetFont(42);
    L4.SetTextSize(0.06);
    L4.DrawLatexNDC(0.15,0.925,("#font[42]{#bf{"+global_title+"}}").c_str());

    zp1000__->SetLineStyle(1);
	zp1400__->SetLineStyle(2);

	zp1000__->SetLineWidth(5);
	zp1400__->SetLineWidth(5);

	zp1000__->SetLineColor(6);
	zp1400__->SetLineColor(1);

	if(shouldIplotSignals && drawSignals)
	{
	    TLegend legDM(.45,.6,.65,.85);
	    legDM.SetTextSize(.03);
	    legDM.SetTextFont(22);
	    legDM.SetBorderSize(0);
	    legDM.SetFillColor(0);
	    legDM.AddEntry(zp1000__, "[m_{Z'},m_{A0},m_{#chi}] = [1000,400,100] GeV @ 1pb","L");
		legDM.DrawClone();
	}

    C->cd(2);

    TH1F * ratio__ = (TH1F*)num__->Clone("ratio__");
    ratio__ -> Reset();
    ratio__ -> Divide(num__, den__, 1, 1, "B");



    ratio__ -> SetTitle("");
    ratio__ -> GetYaxis()->SetTitle("Observed/Model-1");
    ratio__ -> SetMaximum(1.0);
    ratio__ -> SetMinimum(-1.0);


////////////////
    TH1F * shaded__ = (TH1F*)den__->Clone("shaded__");
	shaded__->Reset();

    TH1F * shadedD__ = (TH1F*)den__->Clone("shadedD__");
	shadedD__->Reset();

    for(int k=0; k<shaded__->GetNbinsX()+1; ++k) 
    	{

    		if(ratio__->GetBinContent(k)!=0) 
    		{

    			ratio__->SetBinContent(k, ratio__->GetBinContent(k)-1);

    		}
    		float z = 0;
    		if(den__->GetBinContent(k)>0)
    		{

  				double err_ratio =
				sqrt(num__->GetBinContent(k))/den__->GetBinContent(k);
				ratio__->SetBinError(k, err_ratio);

				//std::cout<<ratio__->GetBinContent(k)<<" +/- "<<err_ratio<<"\n";
    			// shaded__->SetBinContent(k,   0+den__->GetBinError(k)/den__->GetBinContent(k)  );
    			// shadedD__->SetBinContent(k,   0-den__->GetBinError(k)/den__->GetBinContent(k)  );

    		}

    		// if(den__->GetBinContent(k)<0) 
    		// {
    		// 	shaded__->SetBinContent(k,   0-den__->GetBinError(k)/den__->GetBinContent(k)  );
    		// 	shadedD__->SetBinContent(k,   0+den__->GetBinError(k)/den__->GetBinContent(k)  );
    		// }

    		double shaded_err = 0;
			if(den__->GetBinContent(k)!=0)
			{
				shaded_err = (den__->GetBinError(k))/(den__->GetBinContent(k));
				shaded__->SetBinContent(k,fabs(shaded_err));
				shadedD__->SetBinContent(k,-1*fabs(shaded_err));

			}     		
			// if(den__->GetBinContent(k)==0 && den__->GetBinError(k)!=0)
			// {
			// 	shaded__->SetBinContent(k,shaded__->GetBinContent(k-1));
			// 	shadedD__->SetBinContent(k,-1*shaded__->GetBinContent(k-1));
			// }




    	}

	// for(int k=0; k<shaded__->GetNbinsX()+1; ++k) 
 //    	{

 //    		if(shaded__->GetBinContent(k) <= 0)
 //    		{
 //    			std::cout<<" zero bkg err bin "<<shaded__->GetBinCenter(k);
 //    			std::cout<<" bkg = "<<den__->GetBinContent(k)<<" +/- "<<den__->GetBinError(k);
 //    			std::cout<<" d = "<<num__->GetBinContent(k)<<" +/- "<<num__->GetBinError(k);
 //    			std::cout<<" r = "<<ratio__->GetBinContent(k)<<" +/- "<<ratio__->GetBinError(k)<<"\n";

 //    		}
	// 	}    		

    //ratio__ -> SetMaximum(shaded__->GetMaximum()*1.5);
    //ratio__ -> SetMinimum(shadedD__->GetMinimum()*1.5);



	ratio__ -> DrawCopy("PE");


	shaded__->SetFillColor(4);
	shadedD__->SetFillColor(4);
	shaded__->SetLineColor(4);
	shadedD__->SetLineColor(4);
	gStyle->SetHatchesLineWidth(1);
	shaded__->SetFillStyle(3004);
	shadedD__->SetFillStyle(3004);

	shaded__ -> DrawCopy("hist sames");
	shadedD__->DrawCopy("hist sames");
	ratio__ -> DrawCopy("PEsames");


	// /* draw the signals */
 //    TH1F * ZP800__ = (TH1F*) ZP800->Clone("ZP800__");
	

	// for(int k=0; k<ZP800__->GetNbinsX()+1; ++k) 
 //    {

 //    	if(den__->GetBinContent(k)>0)
 //    	{
 //    		double cont = ((ZP800__->GetBinContent(k)+den__->GetBinContent(k))/den__->GetBinContent(k)) - 1;
 //    		double errS = ((ZP800__->GetBinError(k)+den__->GetBinContent(k))/den__->GetBinContent(k)) - 1;

 //    		ZP800__->SetBinContent(k, cont);	
 //    		ZP800__->SetBinError(k, errS);	

 //    	}

 //    }	    

 //    ZP800__->SetMarkerStyle(22);
 //    ZP800__->SetMarkerColor(2);
	// ZP800__->SetLineColor(2);


 //    ZP800__->DrawCopy("PE sames");
 //    ZP800__->DrawCopy("hist sames");

	TLine line1;
	line1.SetLineColor(1);
	line1.SetLineWidth(1);
	line1.DrawLine(ratio__->GetBinLowEdge(1),0,
	ratio__->GetBinLowEdge(ratio__->GetNbinsX())+ratio__->GetBinWidth(ratio__->GetNbinsX()),0);

    C->Update();

    C->cd(2);


	TLegend leg2(.13,.75,.32,.85);
    leg2.SetTextSize(.04);
    leg2.SetTextFont(22);
    leg2.SetBorderSize(0);
    leg2.SetFillColor(0);	

    leg2.AddEntry(ratio__, "Obs./Bkg.-1","PE");
    leg2.AddEntry(shaded__, "Bkg. #pm 1 #sigma (stat.)","F");

    leg2.DrawClone();

	gPad->RedrawAxis("XY");
	gPad->SetGridx(1);
	gPad->SetGridy(1);

	gPad->Update();
////////////////


    TLatex L5;
    //L2.SetFont(42);
    L5.SetTextSize(0.06);
    L5.DrawLatexNDC(0.1,0.925,"#font[42]{#bf{Ratio-1}}");


    C->Update();

    /* delete pointers */
	delete data__;
    delete vv__;
	delete tt__;
	delete ztt__;
    delete zl__;
    delete zj__;
	delete w__;
    delete zhtautau__;
    delete whtautau__;
    delete glugluhtautau__;
    delete vbfhtautau__;
    delete tthjettt__;
	delete qcd__;
    delete zp600__;
	delete zp800__;
	delete zp1000__;
	delete zp1200__;
	delete zp1400__;
	delete ratio__;
	//delete ZP800__;


}





// ////////////////
//     TH1F * shaded__ = (TH1F*)den__->Clone("shaded__");
// 	shaded__->Reset();

//     TH1F * shadedD__ = (TH1F*)den__->Clone("shadedD__");
// 	shadedD__->Reset();

//     for(int k=0; k<shaded__->GetNbinsX(); ++k) 
//     	{

//     		if(ratio__->GetBinContent(k)!=0) ratio__->SetBinContent(k, ratio__->GetBinContent(k)-1);
//     		float z = 0;
//     		if(den__->GetBinContent(k)>0)
//     		{
//     			shaded__->SetBinContent(k,   0+den__->GetBinError(k)/den__->GetBinContent(k)  );
//     			shadedD__->SetBinContent(k,   0-den__->GetBinError(k)/den__->GetBinContent(k)  );

//     		}
//     	}






// 	ratio__ -> DrawCopy("PE");


// 	shaded__->SetFillColor(3);
// 	shadedD__->SetFillColor(3);

// 	shaded__ -> DrawCopy("hist sames");
// 	shadedD__->DrawCopy("hist sames");
// 	ratio__ -> DrawCopy("PEsames");

// 	TLine line1;
// 	line1.SetLineColor(2);
// 	line1.SetLineWidth(2);
// 	line1.DrawLine(ratio__->GetBinLowEdge(1),0,
// 	ratio__->GetBinLowEdge(ratio__->GetNbinsX())+ratio__->GetBinWidth(ratio__->GetNbinsX()),0);


