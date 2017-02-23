/* to do -- add in signal curves with multiplyier option -- formatting needed */
/* to do -- add in option to not draw data on signal region plots */


///////////////////////////////////////////////////////////
// root -l
// .L miniAODv2_80X_analysisMacro.C+
// miniAODv2_80X_analysisMacro()
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
#include "loadTChains80X.C"

///////////////////////////////////////////////////////////
// global vars. & function decs. 
///////////////////////////////////////////////////////////

/* channel bools */
bool do_mTau = 0;
bool do_eTau = 0;
bool do_eMu = 0;
bool do_TauTau = 0;
bool do_All = 0;

/* interactive choices*/

int choice = -1;
int sigChoice = -1;
int nonMVAChoice = -1;
bool doControlTMVA;
bool doSyst = 0;
int choice2 = -1;
int choice3 = -1;
int choice4 = -1;
int allChanBothDR = -1;

std::string metCutVal = "";
std::string mtCutVal = "";
bool cRegion = 0;
bool signalRegionMETonly = 0;
bool evalBaselineSys = 0;
bool evalEnergyShiftSys = 0;
int drCut = 0;

/* DATA maximum factor on hists y-axis */

int DATA_MAX = 2;
float DATA_MIN = 1e-1;
int LOG_MAX = 1000;

/* set log y */
bool setLog  = 0;

/* plot signals */

bool shouldIplotSignals = 1;
bool splitPlotSMH = 0;

/* for safety blind met (in data) above this value, and m_vis between these */
double met_blind = 100;
std::string control_met_cutoff = "1000";

/* plotting region key requirement -- usually a cut on the met!
   for control region data usually choose met < 100
   if no cut is applied, make sure to set signalRegionMETonly to 1
   (no other dists. will be shown in that case)*/

std::map <int,std::string> drCutMap;
std::map <int,std::string> drCutNameMap;
std::map <std::string,std::string> met_options;
std::map <std::string,std::string> mt_options;
std::map <std::string,TCut> jetCutMap;
std::map <std::string,TCut> weightMap;
std::map <std::string,TCut> wNorm_cut_options;
std::map <std::string,TCut> TMVACutMap;

double lumi_sf = 1.0;

/* data marker style */

int dataMarker = 8;

/* some hist binnings */

float mtBinning[3] = {35.,0.,350.}; /* for mt in all regions */
float mt_totBinning[3] = {60.,0.,1500.};
float metBinning[3] = {50.,0.,1000.};  /* for met in all regions */
float m_visBinning[3] = {25.,0.,250.}; /* for m_vis in all regions */
float ptBinning[3] = {40.,0.,200.}; /* for pT in all regions */
float nbtagBinning[3] = {30.,0.,30.}; /* for nbtag in all regions */
float lptBinning[3] = {35.,0.,3500.};
float m_minBinning[3] = {20,0.,1000.};
float p_chiBinning[3] = {30,-150.,150.};
float tmvaBinning[3] = {50,-0.5,2.0};
float phiBinning[3] = {70,-3.5,3.5};

/* variable binning for mt_tot */

float mt_totVarBinning[] = {0,20,40,60,90,120,150,180,210,250,300,350,400,450,600,2000};
int binnum_mt_tot = sizeof(mt_totVarBinning)/sizeof(*mt_totVarBinning) - 1;

/* some hist x-axis labels */
std::map<std::string,std::string > x_axisLabels;

/* stack plot colors */

std::map<std::string,int> colors;

/* channel label */

std::string chan_label;

/* canvas dim */

int canDim[2] = {900,750};

/* lumi and sqrt(s) */

std::string lumiAndRtS = "[36.5/fb @ 13 TeV]";

/* sample weights (sample, weight) */

std::map<std::string,std::string> weights;

/* QCD OS to SS scale factor -- to be measured */

double qcdOStoSS = 1.06;

//txt file with sys
std::string saveNameValues = "YieldsSep811.output.txt";
ofstream out_data(saveNameValues.c_str());

/* string to hold main title for hists */

std::string global_title;

/* string for canvas save prefix */

std::string saveName;

/* given a TCut obtain a [data-(non-W)]/W scale factor */
/* args are cut, canvas name */

double wjetsNorm(TCut, std::string);

/* given a TCut and a w mc scale factor fill a TH1F with a qcd shape under the TCut */
/* args are cut, w sf, qcd hist to fill, string expression to fill (pt_1 m_vis etc.), binning array,
canvas name string */

void fillQCD_Shape(TCut, double, TH1F *, std::string, float[3], std::string, std::string, bool);
void fillQCD_ShapeVarBin(TCut, double, TH1F *, std::string, float[], std::string, std::string, bool);

/* given a TCut and a w mc scale factor and a qcd shape draw string under float[3] binning */
/* args are cut, w sf, qcd hist to draw, string expression to fill (pt_1 m_vis etc.), 
binning array, canvas name */

void drawSignalRegion(TCut, double, TH1F *, std::string, float[3], std::string, std::string, std::string, bool, bool, bool);
void drawSignalRegionVarBin(TCut, TCut, bool, double, TH1F *, std::string, float[], std::string, std::string, std::string, bool, bool);

void countTotalsVarBin(TCut, double, TH1F *, std::string, float[], std::string, std::string, std::string, bool, bool, bool);
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

int miniAODv2_80X_analysisMacro()
{

	while(choice <1 || choice > 5)
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
		std::cout<<" 			enter 1 signal region dist. (above a cut) with blind tail \n";
		std::cout<<" 			enter 2 for many basic kinematic plots in control region \n";
		cin>>choice2;
	}
    
	if(choice2==1)
	{
        std::cout<< "Choose a parameter: \n";
        std::cout<<" 			enter 1 for MET dis. with blinded tail \n";
		std::cout<<" 			enter 2 for TMVA variable blinded above 0.5 (for EleTau and MuTau ONLY, EleMu and TauTau will remain in MET)\n";
        std::cout<<" 			enter 3 for Mt dis. with blinded tail\n";
        
        cin>>sigChoice;
        
        if (sigChoice==1)
        {
            metBinning[0] = 50;
            metBinning[1] = 0;
            metBinning[2] = 1000;
            std::cout<<" enter a met cut value: ";
            cin >> metCutVal;
            std::cout<<" enter a Mt cut value: ";
            cin >> mtCutVal;
            saveName += (("signalRegion_met_over_" + metCutVal + "_").c_str());
        }
        else if (sigChoice==2 )
        {
            
            std::cout<<" enter a met cut value: ";
            cin >> metCutVal;
            std::cout<<" enter a Mt_vis cut value: ";
            cin >> mtCutVal;
            if (choice==5 || choice==3 )
            {
            std::cout<<" enter a non-MVA variable: 1 for MET, 2 for Mt";
            cin>>nonMVAChoice;
            saveName += (("signalRegion_METChannelsOver" + metCutVal + "_TMVA").c_str());
            }
        }
        else if (sigChoice==3)
        {
            std::cout<<" enter a met cut value: ";
            cin >> metCutVal;
            std::cout<<" enter a Mt cut value: ";
            cin >> mtCutVal;
            saveName += (("signalRegion_Mt_over_" + mtCutVal + "_").c_str());
        }
		std::cout<<"    enter 1 to include systematics shapes \n";
        std::cout<<"    enter 0 to exclude systematics shapes \n";
        cin>>doSyst;
	}
	if(choice2==2)
	{
        cRegion = 1;
        std::cout<<" enter a Mt cut value: ";
        cin >> mtCutVal;
        if (choice==5||choice==1||choice==2||choice==4)
        {
            std::cout<< "Choose a parameter for channels with TMVA option: \n";
            std::cout<<" 			enter 1 for TMVA \n";
            std::cout<<" 			enter 0 for MET \n";
            cin>>doControlTMVA;
        }
		metBinning[0] = 25;
		metBinning[1] = 0;
		metBinning[2] = 150;
		saveName += ("controlRegion_");
	}
	while(choice4!=1 && choice4!=2 && choice4!=3 && choice!=5)
	{
		std::cout<<" enter DR range : \n";
		std::cout<<"	   enter 1 for low  [ dr(tau,tau)<1 ] \n";
		std::cout<<"	   enter 2 for medium  [ dr(tau,tau)>=1 && dr(tau,tau) < 2.0] \n";
        std::cout<<"	   enter 3 for all regions above minimum\n";
		cin>>choice4;

		if(choice4==1)
        {
         drCut = 1;
        }
		if(choice4==2)
        {
         drCut = 2;
        }
        if(choice4==3)
        {
         drCut = 3;
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

	if(choice2==1) {DATA_MIN = 1e-2; }

	/////////////////

	/* some formatting */
	setTDRStyle();
	/* int colors */
	colors["ZTT"] = 92;
    colors["ZL"] = 94;
    colors["ZJ"] = 96;
	colors["TTT"] = 2;
    colors["TTJ"] = 2;
    colors["VV"] = 8;
	colors["W"] = 634;
	colors["QCD"] = 606;
    colors["EWK"] = 650;
    colors["ZVV"] = 650;
    colors["GluGluHTauTau"] = 7;
    colors["VBFHTauTau"] = 9;
    colors["ttHJetTT"] = 11;
	colors["ZHTauTau"] = 52;
    colors["WHTauTau"] = 5;
	colors["MONO"] = 4;
    colors["SMH"] = 11;

	/* x - axis labels */

    x_axisLabels["mt_tot"] = "M_{T} Total [GeV]";
	x_axisLabels["m_vis"] = "Visible di-#tau Mass [GeV]";
	x_axisLabels["nbtag"] = "Number of Jets";
	x_axisLabels["mvamet"] = "Missing Transverse Energy [GeV]";
    x_axisLabels["met"] = "Missing Transverse Energy [GeV]";
    x_axisLabels["LPT"] = "Likelihood Transverse Momentum of Pair Mother [GeV]";
    x_axisLabels["DeltaPhi_leg1_leg2"] = "DeltaPhi between legs";
    x_axisLabels["DeltaPhi_PFMET_Higgs"] = "DeltaPhi between PFMET and pair";
    x_axisLabels["DeltaPhi_MVAMET_Higgs"] = "DeltaPhi between MVAMET and pair";
    
    x_axisLabels["mvaVar_et_MZP600A0400"] = "mvaVar_et_MZP600A0400";
    x_axisLabels["mvaVar_et_MZP800A0400"] = "mvaVar_et_MZP800A0400";
    x_axisLabels["mvaVar_et_MZP1000A0400"] = "mvaVar_et_MZP1000A0400";
    x_axisLabels["mvaVar_et_MZP1200A0400"] = "mvaVar_et_MZP1200A0400";
    x_axisLabels["mvaVar_mt_MZP600A0400"] = "mvaVar_mt_MZP600A0400";
    x_axisLabels["mvaVar_mt_MZP800A0400"] = "mvaVar_mt_MZP800A0400";
    x_axisLabels["mvaVar_mt_MZP1000A0400"] = "mvaVar_mt_MZP1000A0400";
    x_axisLabels["mvaVar_mt_MZP1200A0400"] = "mvaVar_mt_MZP1200A0400";
    x_axisLabels["mvaVar_tt_MZP600A0400"] = "mvaVar_tt_MZP600A0400";
    x_axisLabels["mvaVar_tt_MZP800A0400"] = "mvaVar_tt_MZP800A0400";
    x_axisLabels["mvaVar_tt_MZP1000A0400"] = "mvaVar_tt_MZP1000A0400";
    x_axisLabels["mvaVar_tt_MZP1200A0400"] = "mvaVar_tt_MZP1200A0400";

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
    drCutMap[3] = "DeltaR_leg1_leg2 > 0.0 && DeltaR_leg1_leg2 < 2.0";
    drCutNameMap[1] = "low";
    drCutNameMap[2] = "high";
    drCutNameMap[3] = "both";

    TMVACutMap["ET_600"] = TCut("mvaVar_et_MZP600A0400 > -0.5");
    TMVACutMap["ET_800"] =  TCut("mvaVar_et_MZP800A0400 > -0.5");
    TMVACutMap["ET_1000"] = TCut("mvaVar_et_MZP1000A0400 > -0.5");
    TMVACutMap["ET_1200"] = TCut("mvaVar_et_MZP1200A0400 > -0.5");
    
    TMVACutMap["MT_600"] = TCut("mvaVar_mt_MZP600A0400 > -0.5");
    TMVACutMap["MT_800"] = TCut("mvaVar_mt_MZP800A0400 > -0.5");
    TMVACutMap["MT_1000"] = TCut("mvaVar_mt_MZP1000A0400 > -0.5");
    TMVACutMap["MT_1200"] = TCut("mvaVar_mt_MZP1200A0400 > -0.5");
    
    TMVACutMap["TT_600"] = TCut("mvaVar_tt_MZP600A0400 > -0.5");
    TMVACutMap["TT_800"] = TCut("mvaVar_tt_MZP800A0400 > -0.5");
    TMVACutMap["TT_1000"] = TCut("mvaVar_tt_MZP1000A0400 > -0.5");
    TMVACutMap["TT_1200"] = TCut("mvaVar_tt_MZP1200A0400 > -0.5");

    met_options["NOM"] = "met > " + metCutVal;
    met_options["MET_UES_UP"] = "responseUP_mvaMET > " + metCutVal;
    met_options["MET_UES_DOWN"] = "responseDOWN_mvaMET > " + metCutVal;

    mt_options["NOM"] = "m_vis < " + mtCutVal;
    mt_options["MET_UES_UP"] = "responseUP_MTmvaMET_1 < " + mtCutVal;
    mt_options["MET_UES_DOWN"] = "responseDOWN_MTmvaMET_1 < " + mtCutVal;

    weightMap["ZUP"] = TCut("ZReWeight_WeightUp");
    weightMap["ZDOWN"] = TCut("ZReWeight_WeightDown");
    weightMap["KUP"] = TCut("KReWeight_WeightUp");
    weightMap["KDOWN"] = TCut("KReWeight_WeightDown");
    weightMap["JTFUP"] = TCut("JTF_WeightUp");
    weightMap["JTFDOWN"] = TCut("JTF_WeightDown");
    
    jetCutMap["NOM"] = TCut("nbtag==0 && njets <= 2");
    
    jetCutMap["NJECUP"] = TCut("nbtag_JECshiftedUp==0 && njets_JECshiftedUp <= 2");
    jetCutMap["NJECDOWN"] = TCut("nbtag_JECshiftedDown==0 && njets_JECshiftedDown <= 2");
    
    jetCutMap["NJERUP"] = TCut("nbtag_JERup==0 && njets_JERup <= 2");
    jetCutMap["NJERDOWN"] = TCut("nbtag_JERdown==0 && njets_JERdown <= 2");

    wNorm_cut_options["NOM"] = TCut("mt_1 > 80");
    wNorm_cut_options["MET_UES_UP"] = TCut("responseUP_MTmvaMET_1 > 80");
    wNorm_cut_options["MET_UES_DOWN"] = TCut("responseDOWN_MTmvaMET_1 > 80");
    
	/* max */
	if(setLog == 1) DATA_MAX = LOG_MAX;

	/* mc sample */
    weights["DY"] = " (36.8 * final_weight) ";
    weights["ZTT"] = " (36.8 * final_weight) ";
    weights["ZL"] = " (36.8 * final_weight) ";
    weights["ZJ"] = " (36.8 * final_weight) ";
    weights["EWK"] = " (36.8 * final_weight) ";
	weights["TTT"] = " (36.8 * final_weight) ";
    weights["TTJ"] = " (36.8 * final_weight) ";
    weights["VV"] = " (36.8 * final_weight) ";
	weights["W"] = " (36.8 * final_weight) ";
	weights["QCD"] = " (36.8 * final_weight) ";
    weights["ZVV"] = " (36.8 * final_weight) ";
    weights["GluGluHTauTau"] = " (36.8 * final_weight) ";
    weights["VBFHTauTau"] = " (36.8 * final_weight) ";
    weights["ttHJetTT"] = " (36.8 * final_weight) ";
	weights["ZHTauTau"] = " (36.8 * final_weight) ";
    weights["WHTauTau"] = " (36.8 * final_weight) ";
	weights["MONO"] = " (36.8 * final_weight) ";

	std::cout<<" NOTE ************** mono-Higgs normalized to "<<weights["MONO"]<<"\n";
	std::cout<<" event yields shown with extra (lumi) factor of "<<lumi_sf<<"\n";

	/* do channels */

	//std::cout<<saveName<<"\n";

    std::cout << "bin numbr mt_tot: " << binnum_mt_tot << std::endl;

	if(do_mTau) doMuTau();
	if(do_eTau) doEleTau();
	if(do_eMu) doEleMu();
	if(do_TauTau) doTauTau();
    if(do_All)
    {
        std::cout << "Enter 1 to separate DR Regions" << std::endl;
        std::cout << "Enter 2 to combine" << std::endl;
        cin>>allChanBothDR;
        if (allChanBothDR==1)
        {
            drCut=1;
            std::cout << "Low Region" << std::endl;
            doMuTau();
            doEleTau();
            //doEleMu();
            doTauTau();
            
            drCut=2;
            std::cout << "High Region" << std::endl;
            doMuTau();
            doEleTau();
            //doEleMu();
            doTauTau();
        }
        else
        {
            drCut=3;
            std::cout << "Combined DR Region" << std::endl;
            doMuTau();
            doEleTau();
            //doEleMu();
            doTauTau();
        }
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

    TCut SScut_TauTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && ((againstElectronTightMVA6_1 > 0.5 && againstMuonLoose3_1) || (againstElectronVLooseMVA6_1 > 0.5 && againstMuonTight3_1)) && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && byVTightIsolationMVArun2v1DBoldDMwLT_1 > 0.5 && byVTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && ((againstElectronTightMVA6_1 > 0.5 && againstMuonLoose3_1 > 0.5 ) || (againstElectronVLooseMVA6_1 > 0.5 && againstMuonTight3_1 > 0.5 )) && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && byVTightIsolationMVArun2v1DBoldDMwLT_1 > 0.5 && byVTightIsolationMVArun2v1DBoldDMwLT_2 > 0.5");

    std::string metCutTmp;
    if (cRegion) {metCutTmp = "met < " + control_met_cutoff;}
    else {metCutTmp = met_options["NOM"];}
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());
    cut_options_nom += jetCutMap["NOM"];
    
    //Systematic Cuts
    TCut cut_options_UESUp((drCutMap[drCut] + " && " + met_options["MET_UES_UP"] + " && " + mt_options["MET_UES_UP"] + " && pt_tt > 50").c_str()); cut_options_UESUp += jetCutMap["NOM"];
    TCut cut_options_UESDown((drCutMap[drCut] + " && " + met_options["MET_UES_DOWN"] + " && " + mt_options["MET_UES_DOWN"] + " && pt_tt > 50").c_str());cut_options_UESDown += jetCutMap["NOM"];
    
    TCut cut_options_VPtUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_VPtUp += jetCutMap["NOM"]; cut_options_VPtUp *= weightMap["ZUP"]; cut_options_VPtUp *= weightMap["KUP"];
    TCut cut_options_VPtDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_VPtDown += jetCutMap["NOM"]; cut_options_VPtDown *= weightMap["ZDOWN"]; cut_options_VPtDown *= weightMap["KDOWN"];
    
    TCut cut_options_TauFakeUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_TauFakeUp += jetCutMap["NOM"]; cut_options_TauFakeUp *= weightMap["JTFUP"];
    TCut cut_options_TauFakeDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_TauFakeDown += jetCutMap["NOM"]; cut_options_TauFakeDown *= weightMap["JTFDOWN"];
    
	chan_label = "#tau_{h} + #tau_{h}";

    /* declare the TauTau qcd shapes for each binning */

    /* mt_1 */
    TH1F * qcd_TauTau_mt = new TH1F("qcd_TauTau_mt","qcd_TauTau_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
    qcd_TauTau_mt->Sumw2(); 
    qcd_TauTau_mt->SetFillColor(colors["QCD"]);
    
    /* mt_tot */
    TH1F * qcd_TauTau_mt_tot = new TH1F("qcd_TauTau_mt_tot","qcd_TauTau_mt_tot", binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot->Sumw2();
    qcd_TauTau_mt_tot->SetFillColor(colors["QCD"]);
    
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
    
    /* deltaPhiLegs */
    TH1F * qcd_TauTau_DeltaPhi_leg1_leg2 = new TH1F("qcd_TauTau_DeltaPhi_leg1_leg2","qcd_TauTau_DeltaPhi_leg1_leg2",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_TauTau_DeltaPhi_leg1_leg2->Sumw2();
    qcd_TauTau_DeltaPhi_leg1_leg2->SetFillColor(colors["QCD"]);
    
    /* deltaPhiPFMET */
    TH1F * qcd_TauTau_DeltaPhi_PFMET_Higgs = new TH1F("qcd_TauTau_DeltaPhi_PFMET_Higgs","qcd_TauTau_DeltaPhi_PFMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_TauTau_DeltaPhi_PFMET_Higgs->Sumw2();
    qcd_TauTau_DeltaPhi_PFMET_Higgs->SetFillColor(colors["QCD"]);
    
    /* deltaPhiMVAMET */
    TH1F * qcd_TauTau_DeltaPhi_MVAMET_Higgs = new TH1F("qcd_TauTau_DeltaPhi_MVAMET_Higgs","qcd_TauTau_DeltaPhi_MVAMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_TauTau_DeltaPhi_MVAMET_Higgs->Sumw2();
    qcd_TauTau_DeltaPhi_MVAMET_Higgs->SetFillColor(colors["QCD"]);
    
    /*TMVA*/
    TH1F * qcd_TauTau_mvaVar_tt_MZP600A0400 = new TH1F("qcd_TauTau_mvaVar_tt_MZP600A0400","qcd_TauTau_mvaVar_tt_MZP600A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_MZP600A0400->Sumw2();
    qcd_TauTau_mvaVar_tt_MZP600A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_TauTau_mvaVar_tt_MZP800A0400 = new TH1F("qcd_TauTau_mvaVar_tt_MZP800A0400","qcd_TauTau_mvaVar_tt_MZP800A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_MZP800A0400->Sumw2();
    qcd_TauTau_mvaVar_tt_MZP800A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_TauTau_mvaVar_tt_MZP1000A0400 = new TH1F("qcd_TauTau_mvaVar_tt_MZP1000A0400","qcd_TauTau_mvaVar_tt_MZP1000A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_MZP1000A0400->Sumw2();
    qcd_TauTau_mvaVar_tt_MZP1000A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_TauTau_mvaVar_tt_MZP1200A0400 = new TH1F("qcd_TauTau_mvaVar_tt_MZP1200A0400","qcd_TauTau_mvaVar_tt_MZP1200A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_MZP1200A0400->Sumw2();
    qcd_TauTau_mvaVar_tt_MZP1200A0400->SetFillColor(colors["QCD"]);
    
    //ExpertMVA
    TH1F * qcd_TauTau_mvaVar_tt_EXP1 = new TH1F("qcd_TauTau_mvaVar_tt_EXP1","qcd_TauTau_mvaVar_tt_EXP1",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_EXP1->Sumw2();
    qcd_TauTau_mvaVar_tt_EXP1->SetFillColor(colors["QCD"]);
    TH1F * qcd_TauTau_mvaVar_tt_EXP2 = new TH1F("qcd_TauTau_mvaVar_tt_EXP2","qcd_TauTau_mvaVar_tt_EXP2",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_EXP2->Sumw2();
    qcd_TauTau_mvaVar_tt_EXP2->SetFillColor(colors["QCD"]);
    TH1F * qcd_TauTau_mvaVar_tt_EXP3 = new TH1F("qcd_TauTau_mvaVar_tt_EXP3","qcd_TauTau_mvaVar_tt_EXP3",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_TauTau_mvaVar_tt_EXP3->Sumw2();
    qcd_TauTau_mvaVar_tt_EXP3->SetFillColor(colors["QCD"]);
    
    //Systematic Variants

    TH1F * qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp = new TH1F("qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp","qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp->Sumw2();
    qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown = new TH1F("qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown","qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown->Sumw2();
    qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp = new TH1F("qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp","qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp->Sumw2();
    qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown = new TH1F("qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown","qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown->Sumw2();
    qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp = new TH1F("qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp","qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp->Sumw2();
    qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown = new TH1F("qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown","qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown->Sumw2();
    qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp = new TH1F("qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp","qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->Sumw2();
    qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown = new TH1F("qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown","qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->Sumw2();
    qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp = new TH1F("qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp","qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp->Sumw2();
    qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown = new TH1F("qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown","qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown->Sumw2();
    qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown->SetFillColor(colors["QCD"]);

    /* need to make this function more general for any dist. */	

    //nbtag==0 && njets <= 2 && deltar_(eta_1,phi_1,eta_2,phi_2) < 1 &&
    
    double wSF_SS_TauTau = 1.0; /* temp */
    double wSF_OS_TauTau = 1.0; /* temp */
    
    if (sigChoice==1)
    {
        /* setup files for TauTau channel */
        setup_files_TauTau();
        
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 1);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_met, "met", metBinning, "sig region (met<100) met", "tt", "", 1, 0, 1);
        
        reset_files();

    }
    else if (sigChoice==2)
    {
        /* setup files for TauTau channel */
        setup_files_TauTau();
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_600"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP600A0400,"mvaVar_tt_MZP600A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_800"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP800A0400,"mvaVar_tt_MZP800A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_1000"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP1000A0400,"mvaVar_tt_MZP1000A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
        fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_1200"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP1200A0400,"mvaVar_tt_MZP1200A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
        
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_600"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP600A0400, "mvaVar_tt_MZP600A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "600", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_800"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP800A0400, "mvaVar_tt_MZP800A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "800", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_1000"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP1000A0400, "mvaVar_tt_MZP1000A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "1000", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_1200"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP1200A0400, "mvaVar_tt_MZP1200A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "1200", 1, 0, 1);
        reset_files();
    }
    else if (sigChoice==3)
    {
        setup_files_TauTau_test();
        //findBkgFractions(signalCut_base * cut_options_nom, 1.0, "mt_tot", mt_totBinning);
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mt_tot, "mt_tot", mt_totVarBinning,  "QCD Mt total shape ext. in SS side band (TauTau)", "tt", 1);
        drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot, "mt_tot", mt_totVarBinning, "sig region Mt_total", "tt", "", 1, 1);
        
        if (doSyst)
        {
            std::cout << "syst for tt started" << std::endl;
            //syst
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_UESUp, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_UESDown, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_VPtUp, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_VPtDown, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_VPtUp, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_VPtDown, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_TauFakeUp, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_TauFakeDown, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);

            std::cout << "QCD Shapes for tt syst filled" << std::endl;
            
            drawSignalRegionVarBin(signalCut_base * cut_options_UESUp, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_scale_m_tt_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_UESDown, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_scale_m_tt_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_xtt_dyShape_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_xtt_dyShape_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_xtt_wShape_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_xtt_wShape_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeUp, signalCut_base * cut_options_nom, 1, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_xtt_jetToTauFake_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeDown, signalCut_base * cut_options_nom, 1, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_xtt_jetToTauFake_13TeVDown", 0, 1);
            
            reset_files();
            setup_files_TauTau_test();
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp, "mt_tot", mt_totVarBinning,  "", "tt", "_CMS_scale_t_tt_13TeVUp", 0, 1);
            
            reset_files();
            setup_files_TauTau_test();
            fillQCD_ShapeVarBin(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 0);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_TauTau, qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown, "mt_tot", mt_totVarBinning,  "", "tt","_CMS_scale_t_tt_13TeVDown", 0, 1);
        }
        reset_files();
        
    }
    else if (choice2==2)
    {
        setup_files_TauTau();
        
        if(doControlTMVA)
        {
                global_title = "QCD (Same Sign) Estimate Region";
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_EXP1,"mvaVar_tt_EXP1", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_EXP2,"mvaVar_tt_EXP2", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_EXP3,"mvaVar_tt_EXP3", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);

                global_title = "MET < " + control_met_cutoff + " GeV Control Region";
                drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_EXP1, "mvaVar_tt_EXP1", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
                drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_EXP2, "mvaVar_tt_EXP2", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
                drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_EXP3, "mvaVar_tt_EXP3", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
            
                global_title = "QCD (Same Sign) Estimate Region";
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_600"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP600A0400,"mvaVar_tt_MZP600A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_800"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP800A0400,"mvaVar_tt_MZP800A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_1000"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP1000A0400,"mvaVar_tt_MZP1000A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
                fillQCD_Shape(SScut_TauTau_base * cut_options_nom * TMVACutMap["TT_1200"], wSF_SS_TauTau, qcd_TauTau_mvaVar_tt_MZP1200A0400,"mvaVar_tt_MZP1200A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (TauTau)", "tt", 1);
            
                global_title = "MET < " + control_met_cutoff + " GeV Control Region";
                drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_600"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP600A0400, "mvaVar_tt_MZP600A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
                drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_800"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP1000A0400, "mvaVar_tt_MZP800A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
                drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_1000"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP1000A0400, "mvaVar_tt_MZP1000A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
                drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["TT_1200"], wSF_OS_TauTau, qcd_TauTau_mvaVar_tt_MZP1000A0400, "mvaVar_tt_MZP1200A0400", tmvaBinning, "sig region Function TMVA variable", "tt", "", 1, 0, 0);
        }
        else
        {
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "QCD Function DeltaPhi_leg1_leg2 shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "QCD Function DeltaPhi_MVAMET_Higgs shape ext. in SS side band (TauTau)", "tt", 1);
            fillQCD_Shape(SScut_TauTau_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "QCD Function DeltaPhi_PFMET_Higgs shape ext. in SS side band (TauTau)", "tt", 1);

            /* now draw the signal region in mt */

            global_title = "MET < "+ control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_mt, "mt_1", mtBinning, "sig region (met<100) mt", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_met, "met", metBinning, "sig region (met<100) met", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_TauTau, qcd_TauTau_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "sig region (met<100) Function DeltaPhi_leg1_leg2", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_MVAMET_Higgs", "tt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_TauTau, qcd_TauTau_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_PFMET_Higgs", "tt", "", 1, 0, 0);
        }
        reset_files();

    }
    
    delete qcd_TauTau_mt;
    delete qcd_TauTau_m_vis;
    delete qcd_TauTau_pt_1;
    delete qcd_TauTau_pt_2;
    delete qcd_TauTau_LPT;
    delete qcd_TauTau_nbtag;
    delete qcd_TauTau_met;
    delete qcd_TauTau_DeltaPhi_leg1_leg2;
    delete qcd_TauTau_DeltaPhi_PFMET_Higgs;
    delete qcd_TauTau_DeltaPhi_MVAMET_Higgs;
    
    delete qcd_TauTau_mvaVar_tt_MZP600A0400;
    delete qcd_TauTau_mvaVar_tt_MZP800A0400;
    delete qcd_TauTau_mvaVar_tt_MZP1000A0400;
    delete qcd_TauTau_mvaVar_tt_MZP1200A0400;
    delete qcd_TauTau_mvaVar_tt_EXP1;
    delete qcd_TauTau_mvaVar_tt_EXP2;
    delete qcd_TauTau_mvaVar_tt_EXP3;
    
    delete qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVUp;
    delete qcd_TauTau_mt_tot_CMS_scale_m_tt_13TeVDown;
    delete qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVUp;
    delete qcd_TauTau_mt_tot_CMS_xtt_dyShape_13TeVDown;
    delete qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVUp;
    delete qcd_TauTau_mt_tot_CMS_xtt_wShape_13TeVDown;
    delete qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp;
    delete qcd_TauTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown;
    delete qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVUp;
    delete qcd_TauTau_mt_tot_CMS_scale_t_tt_13TeVDown;
;


}


void doEleMu()
{

	/* set channel label */

    TCut SScut_eleMu_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0  && iso_1 < 0.15 && iso_2 < 0.15");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0  && iso_1 < 0.15 && iso_2 < 0.15");

    std::string metCutTmp;
    if (cRegion) {metCutTmp = "met < " + control_met_cutoff;}
    else {metCutTmp = met_options["NOM"];}
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());
    cut_options_nom += jetCutMap["NOM"];
    
    //Systematic Cuts
    TCut cut_options_UESUp((drCutMap[drCut] + " && " + met_options["MET_UES_UP"] + " && " + mt_options["MET_UES_UP"] + " && pt_tt > 50").c_str()); cut_options_UESUp += jetCutMap["NOM"];
    TCut cut_options_UESDown((drCutMap[drCut] + " && " + met_options["MET_UES_DOWN"] + " && " + mt_options["MET_UES_DOWN"] + " && pt_tt > 50").c_str());cut_options_UESDown += jetCutMap["NOM"];
    
    TCut cut_options_VPtUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_VPtUp += jetCutMap["NOM"]; cut_options_VPtUp *= weightMap["ZUP"]; cut_options_VPtUp *= weightMap["KUP"];
    TCut cut_options_VPtDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_VPtDown += jetCutMap["NOM"]; cut_options_VPtDown *= weightMap["ZDOWN"]; cut_options_VPtDown *= weightMap["KDOWN"];
    
    TCut cut_options_TauFakeUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_TauFakeUp += jetCutMap["NOM"]; cut_options_TauFakeUp *= weightMap["JTFUP"];
    TCut cut_options_TauFakeDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_TauFakeDown += jetCutMap["NOM"]; cut_options_TauFakeDown *= weightMap["JTFDOWN"];

	chan_label = "e + #mu";

    /* mt_1 */
    TH1F * qcd_eleMu_mt = new TH1F("qcd_eleMu_mt","qcd_eleMu_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
    qcd_eleMu_mt->Sumw2(); 
    qcd_eleMu_mt->SetFillColor(colors["QCD"]);
    
    /* mt_tot */
    TH1F * qcd_eleMu_mt_tot = new TH1F("qcd_eleMu_mt_tot","qcd_eleMu_mt_tot",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot->Sumw2();
    qcd_eleMu_mt_tot->SetFillColor(colors["QCD"]);
    
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
    
    /* deltaPhiLegs */
    TH1F * qcd_eleMu_DeltaPhi_leg1_leg2 = new TH1F("qcd_eleMu_DeltaPhi_leg1_leg2","qcd_eleMu_DeltaPhi_leg1_leg2",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_eleMu_DeltaPhi_leg1_leg2->Sumw2();
    qcd_eleMu_DeltaPhi_leg1_leg2->SetFillColor(colors["QCD"]);
    
    /* deltaPhiPFMET */
    TH1F * qcd_eleMu_DeltaPhi_PFMET_Higgs = new TH1F("qcd_eleMu_DeltaPhi_PFMET_Higgs","qcd_eleMu_DeltaPhi_PFMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_eleMu_DeltaPhi_PFMET_Higgs->Sumw2();
    qcd_eleMu_DeltaPhi_PFMET_Higgs->SetFillColor(colors["QCD"]);
    
    /* deltaPhiMVAMET */
    TH1F * qcd_eleMu_DeltaPhi_MVAMET_Higgs = new TH1F("qcd_eleMu_DeltaPhi_MVAMET_Higgs","qcd_eleMu_DeltaPhi_MVAMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_eleMu_DeltaPhi_MVAMET_Higgs->Sumw2();
    qcd_eleMu_DeltaPhi_MVAMET_Higgs->SetFillColor(colors["QCD"]);
    
    //Systematic Variants
    TH1F * qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp = new TH1F("qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp","qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp->Sumw2();
    qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown = new TH1F("qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown","qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown->Sumw2();
    qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp = new TH1F("qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp","qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp->Sumw2();
    qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown = new TH1F("qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown","qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown->Sumw2();
    qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp = new TH1F("qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp","qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp->Sumw2();
    qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown = new TH1F("qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown","qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown->Sumw2();
    qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp = new TH1F("qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp","qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->Sumw2();
    qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown = new TH1F("qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown","qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->Sumw2();
    qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVUp = new TH1F("qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVUp","qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVUp->Sumw2();
    qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVDown = new TH1F("qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVDown","qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVDown->Sumw2();
    qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVDown->SetFillColor(colors["QCD"]);
    
    /* need to make this function more general for any dist. */
    
    double wSF_SS_eleMu = 1.0; /* in eMu case W bkg is negligible */
    double wSF_OS_eleMu = 1.0; /* in eMu case W bkg is negligible */

    if (choice2==1)
    {
        if (sigChoice==1 || nonMVAChoice==1)
        {
            setup_files_eleMu();
            //setup_files_eleMu_test();
            
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_met, "met", metBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 1);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_met, "met", metBinning, "sig region (met<100) met", "em", "", 1, 0, 1);
            reset_files();
            
        }
        else if (sigChoice==3 || nonMVAChoice==2)
        {
            setup_files_eleMu();
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_mt_tot, "mt_tot", mt_totVarBinning,  "QCD Mt total shape ext. in SS side band (EleMu)", "em", 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot, "mt_tot", mt_totVarBinning, "sig region Mt_total", "em", "", 1, 1);
            if (doSyst)
            {
                std::cout << "syst for em started" << std::endl;
                //syst
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_UESUp, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_UESDown, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_VPtUp, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_VPtDown, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_VPtUp, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_VPtDown, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_TauFakeUp, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);
                fillQCD_ShapeVarBin(SScut_eleMu_base * cut_options_TauFakeDown, wSF_SS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 0);

                std::cout << "QCD Shapes for tt syst filled" << std::endl;
                
                drawSignalRegionVarBin(signalCut_base * cut_options_UESUp, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_scale_m_em_13TeVUp", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_UESDown, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_scale_m_em_13TeVDown", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_xtt_dyShape_13TeVUp", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_xtt_dyShape_13TeVDown", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_xtt_wShape_13TeVUp", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_xtt_wShape_13TeVDown", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeUp, signalCut_base * cut_options_nom, 1, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_xtt_jetToTauFake_13TeVUp", 0, 1);
                drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeDown, signalCut_base * cut_options_nom, 1, wSF_OS_eleMu, qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "", "em", "_CMS_xtt_jetToTauFake_13TeVDown", 0, 1);
                
            }
            reset_files();

        }
    }
    else if (choice2==2)
    {
        setup_files_eleMu();
        global_title = "QCD (Same Sign) Estimate Region";

        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_met, "met", metBinning,  "QCD met shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "QCD Function DeltaPhi_leg1_leg2 shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "QCD Function DeltaPhi_MVAMET_Higgs shape ext. in SS side band (eleMu)", "em", 1);
        fillQCD_Shape(SScut_eleMu_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "QCD Function DeltaPhi_PFMET_Higgs shape ext. in SS side band (eleMu)", "em", 1);

        /* now draw the signal region in mt */

        global_title = "MET < " + control_met_cutoff + " GeV Control Region";

        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_mt, "mt_1", mtBinning, "sig region (met<100) mt", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_met, "met", metBinning, "sig region (met<100) met", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleMu, qcd_eleMu_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "sig region (met<100) Function DeltaPhi_leg1_leg2", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_MVAMET_Higgs", "em", "", 1, 0, 0);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_eleMu, qcd_eleMu_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_PFMET_Higgs", "em", "", 1, 0, 0);

        reset_files();
    }
    
    delete qcd_eleMu_mt;
    delete qcd_eleMu_m_vis;
    delete qcd_eleMu_pt_1;
    delete qcd_eleMu_pt_2;
    delete qcd_eleMu_LPT;
    delete qcd_eleMu_nbtag;
    delete qcd_eleMu_met;
    delete qcd_eleMu_DeltaPhi_leg1_leg2;
    delete qcd_eleMu_DeltaPhi_PFMET_Higgs;
    delete qcd_eleMu_DeltaPhi_MVAMET_Higgs;
    
    delete qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVUp;
    delete qcd_eleMu_mt_tot_CMS_scale_m_em_13TeVDown;
    delete qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVUp;
    delete qcd_eleMu_mt_tot_CMS_xtt_dyShape_13TeVDown;
    delete qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVUp;
    delete qcd_eleMu_mt_tot_CMS_xtt_wShape_13TeVDown;
    delete qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVUp;
    delete qcd_eleMu_mt_tot_CMS_xtt_jetToTauFake_13TeVDown;
    delete qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVUp;
    delete qcd_eleMu_mt_tot_CMS_scale_t_em_13TeVDown;

}

void doEleTau()
{
	/* No WNorm in 76X */
    TCut OS_wNorm_eleTau_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && iso_1 < 0.1 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && byMediumIsolationMVArun2v1DBoldDMwLT_2 < 0.5 && byLooseIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut SS_wNorm_eleTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && iso_1 < 0.1 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && byMediumIsolationMVArun2v1DBoldDMwLT_2 < 0.5 && byLooseIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    
    TCut SScut_eleTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && iso_1 < 0.1 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && byMediumIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && iso_1 < 0.1 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && byMediumIsolationMVArun2v1DBoldDMwLT_2 > 0.5");

    std::string metCutTmp;
    if (cRegion)
    {
        if(doControlTMVA){metCutTmp = "met > 0.";}
        else{metCutTmp = "met < " + control_met_cutoff;}
    }
    else
    {
        metCutTmp = met_options["NOM"];
    }
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());
    cut_options_nom += jetCutMap["NOM"];
    
    
    //Systematic Cuts
    TCut cut_options_UESUp((drCutMap[drCut] + " && " + met_options["MET_UES_UP"] + " && " + mt_options["MET_UES_UP"] + " && pt_tt > 50").c_str()); cut_options_UESUp += jetCutMap["NOM"];
    TCut cut_options_UESDown((drCutMap[drCut] + " && " + met_options["MET_UES_DOWN"] + " && " + mt_options["MET_UES_DOWN"] + " && pt_tt > 50").c_str());cut_options_UESDown += jetCutMap["NOM"];
    
    TCut cut_options_VPtUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_VPtUp += jetCutMap["NOM"]; cut_options_VPtUp *= weightMap["ZUP"]; cut_options_VPtUp *= weightMap["KUP"];
    TCut cut_options_VPtDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_VPtDown += jetCutMap["NOM"]; cut_options_VPtDown *= weightMap["ZDOWN"]; cut_options_VPtDown *= weightMap["KDOWN"];
    
    TCut cut_options_TauFakeUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_TauFakeUp += jetCutMap["NOM"]; cut_options_TauFakeUp *= weightMap["JTFUP"];
    TCut cut_options_TauFakeDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_TauFakeDown += jetCutMap["NOM"]; cut_options_TauFakeDown *= weightMap["JTFDOWN"];
    
	chan_label = "e + #tau_{h}";

    //add options based on input: plots, sys3, sys4

    /* perform the OS W+jets normalization estimate (to be used in the signal region) */

    //global_title = "Opp. Sign high M_{T} Control Region";

    double wSF_OS_eleTau = 1.0;
    //double wSF_OS_eleTau  = wjetsNorm(OS_wNorm_eleTau_base * wNorm_cut_options["NOM"], "wjetsOS");

    /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */

    //global_title = "Same Sign high M_{T} Control Region";

    double wSF_SS_eleTau = 1.0;
    //double wSF_SS_eleTau = wjetsNorm(SS_wNorm_eleTau_base * wNorm_cut_options["NOM"], "wjetsSSforQCD");
    
    /* declare the eleTau qcd shapes for each binning */		

    /* mt_1 */
    TH1F * qcd_eleTau_mt = new TH1F("qcd_eleTau_mt","qcd_eleTau_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
    qcd_eleTau_mt->Sumw2(); 
    qcd_eleTau_mt->SetFillColor(colors["QCD"]);
    
    /* mt_tot */
    TH1F * qcd_eleTau_mt_tot = new TH1F("qcd_eleTau_mt_tot","qcd_eleTau_mt_tot",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot->Sumw2();
    qcd_eleTau_mt_tot->SetFillColor(colors["QCD"]);
    
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
    
    /* deltaPhiLegs */
    TH1F * qcd_eleTau_DeltaPhi_leg1_leg2 = new TH1F("qcd_eleTau_DeltaPhi_leg1_leg2","qcd_eleTau_DeltaPhi_leg1_leg2",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_eleTau_DeltaPhi_leg1_leg2->Sumw2();
    qcd_eleTau_DeltaPhi_leg1_leg2->SetFillColor(colors["QCD"]);
    
    /* deltaPhiPFMET */
    TH1F * qcd_eleTau_DeltaPhi_PFMET_Higgs = new TH1F("qcd_eleTau_DeltaPhi_PFMET_Higgs","qcd_eleTau_DeltaPhi_PFMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_eleTau_DeltaPhi_PFMET_Higgs->Sumw2();
    qcd_eleTau_DeltaPhi_PFMET_Higgs->SetFillColor(colors["QCD"]);
    
    /* deltaPhiMVAMET */
    TH1F * qcd_eleTau_DeltaPhi_MVAMET_Higgs = new TH1F("qcd_eleTau_DeltaPhi_MVAMET_Higgs","qcd_eleTau_DeltaPhi_MVAMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_eleTau_DeltaPhi_MVAMET_Higgs->Sumw2();
    qcd_eleTau_DeltaPhi_MVAMET_Higgs->SetFillColor(colors["QCD"]);
    
    /*TMVA*/
    TH1F * qcd_eleTau_mvaVar_et_MZP600A0400 = new TH1F("qcd_eleTau_mvaVar_et_MZP600A0400","qcd_eleTau_mvaVar_et_MZP600A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_MZP600A0400->Sumw2();
    qcd_eleTau_mvaVar_et_MZP600A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_eleTau_mvaVar_et_MZP800A0400 = new TH1F("qcd_eleTau_mvaVar_et_MZP800A0400","qcd_eleTau_mvaVar_et_MZP800A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_MZP800A0400->Sumw2();
    qcd_eleTau_mvaVar_et_MZP800A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_eleTau_mvaVar_et_MZP1000A0400 = new TH1F("qcd_eleTau_mvaVar_et_MZP1000A0400","qcd_eleTau_mvaVar_et_MZP1000A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_MZP1000A0400->Sumw2();
    qcd_eleTau_mvaVar_et_MZP1000A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_eleTau_mvaVar_et_MZP1200A0400 = new TH1F("qcd_eleTau_mvaVar_et_MZP1200A0400","qcd_eleTau_mvaVar_et_MZP1200A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_MZP1200A0400->Sumw2();
    qcd_eleTau_mvaVar_et_MZP1200A0400->SetFillColor(colors["QCD"]);
    
    //Expert
    TH1F * qcd_eleTau_mvaVar_et_EXP1 = new TH1F("qcd_eleTau_mvaVar_et_EXP1","qcd_eleTau_mvaVar_et_EXP1",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_EXP1->Sumw2();
    qcd_eleTau_mvaVar_et_EXP1->SetFillColor(colors["QCD"]);
    TH1F * qcd_eleTau_mvaVar_et_EXP2 = new TH1F("qcd_eleTau_mvaVar_et_EXP2","qcd_eleTau_mvaVar_et_EXP2",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_EXP2->Sumw2();
    qcd_eleTau_mvaVar_et_EXP2->SetFillColor(colors["QCD"]);
    TH1F * qcd_eleTau_mvaVar_et_EXP3 = new TH1F("qcd_eleTau_mvaVar_et_EXP3","qcd_eleTau_mvaVar_et_EXP3",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_eleTau_mvaVar_et_EXP3->Sumw2();
    qcd_eleTau_mvaVar_et_EXP3->SetFillColor(colors["QCD"]);
    
    //Systematic Variants
    TH1F * qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp = new TH1F("qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp","qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp->Sumw2();
    qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown = new TH1F("qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown","qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown->Sumw2();
    qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp = new TH1F("qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp","qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp->Sumw2();
    qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown = new TH1F("qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown","qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown->Sumw2();
    qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp = new TH1F("qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp","qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp->Sumw2();
    qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown = new TH1F("qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown","qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown->Sumw2();
    qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp = new TH1F("qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp","qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->Sumw2();
    qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown = new TH1F("qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown","qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->Sumw2();
    qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp = new TH1F("qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp","qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp->Sumw2();
    qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown = new TH1F("qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown","qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown->Sumw2();
    qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown->SetFillColor(colors["QCD"]);
    
    if (sigChoice==1)
    {
        /* setup files for eleTau channel */
        setup_files_eleTau();
        //setup_files_eleTau_test();
        
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 1);
        global_title = "MET < " + control_met_cutoff + " GeV Control Region";
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_met, "met", metBinning, "sig region (met<100) met", "et", "", 1, 0, 1);
        reset_files();
    }
    else if (sigChoice==2)
    {
        /* setup files for eleTau channel */
        setup_files_eleTau();
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom * TMVACutMap["ET_600"], wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP600A0400,"mvaVar_et_MZP600A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom * TMVACutMap["ET_800"], wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP800A0400,"mvaVar_et_MZP800A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom * TMVACutMap["ET_1000"], wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP1000A0400,"mvaVar_et_MZP1000A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
        fillQCD_Shape(SScut_eleTau_base * cut_options_nom * TMVACutMap["ET_1200"], wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP1200A0400,"mvaVar_et_MZP1200A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
        
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["ET_600"], wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP600A0400, "mvaVar_et_MZP600A0400", tmvaBinning, "sig region Function TMVA variable", "et", "600", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["ET_800"], wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP800A0400, "mvaVar_et_MZP800A0400", tmvaBinning, "sig region Function TMVA variable", "et", "800", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["ET_1000"], wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP1000A0400, "mvaVar_et_MZP1000A0400", tmvaBinning, "sig region Function TMVA variable", "et", "1000", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["ET_1200"], wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP1200A0400, "mvaVar_et_MZP1200A0400", tmvaBinning, "sig region Function TMVA variable", "et", "1200", 1, 0, 1);
        reset_files();
    }
    else if (sigChoice==3)
    {
        setup_files_eleTau_test();
        findBkgFractions(signalCut_base * cut_options_nom, 1.0, "mt_tot", mt_totVarBinning);
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mt_tot, "mt_tot", mt_totVarBinning,  "QCD Mt total shape ext. in SS side band (EleTau)", "et", 1);
        drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot, "mt_tot", mt_totVarBinning, "sig region Mt_total", "et", "", 1, 1);
        reset_files();
        
        if (doSyst)
        {
            std::cout << "syst for et started" << std::endl;
            //syst
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_UESUp, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_UESDown, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_VPtUp, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_VPtDown, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_VPtUp, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_VPtDown, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_TauFakeUp, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_TauFakeDown, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);

            std::cout << "QCD Shapes for tt syst filled" << std::endl;
            
            drawSignalRegionVarBin(signalCut_base * cut_options_UESUp, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_scale_m_et_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_UESDown, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_scale_m_et_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_xtt_dyShape_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_xtt_dyShape_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_xtt_wShape_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_xtt_wShape_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeUp, signalCut_base * cut_options_nom, 1, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_xtt_jetToTauFake_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeDown, signalCut_base * cut_options_nom, 1, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_xtt_jetToTauFake_13TeVDown", 0, 1);
            
            reset_files();
            setup_files_eleTau_test();
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp, "mt_tot", mt_totVarBinning,  "", "et", "_CMS_scale_t_et_13TeVUp", 0, 1);
            
            reset_files();
            setup_files_eleTau_test();
            fillQCD_ShapeVarBin(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 0);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_eleTau, qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown, "mt_tot", mt_totVarBinning,  "", "et","_CMS_scale_t_et_13TeVDown", 0, 1);
        }
        reset_files();
    }
    else if (choice2==2)
    {
        setup_files_eleTau();
        
        if (doControlTMVA)
        {
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP600A0400,"mvaVar_et_MZP600A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP800A0400,"mvaVar_et_MZP800A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP1000A0400,"mvaVar_et_MZP1000A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_MZP1200A0400,"mvaVar_et_MZP1200A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
            
            global_title = "MET < " + control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP600A0400, "mvaVar_et_MZP600A0400", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP800A0400, "mvaVar_et_MZP800A0400", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP1000A0400, "mvaVar_et_MZP1000A0400", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_MZP1200A0400, "mvaVar_et_MZP1200A0400", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);
            
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_EXP1,"mvaVar_et_EXP1", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_EXP2,"mvaVar_et_EXP2", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mvaVar_et_EXP3,"mvaVar_et_EXP3", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (eleTau)", "et", 1);

            global_title = "MET < " + control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_EXP1, "mvaVar_et_EXP1", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_EXP2, "mvaVar_et_EXP2", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mvaVar_et_EXP3, "mvaVar_et_EXP3", tmvaBinning, "sig region Function TMVA variable", "et", "", 1, 0, 0);

        }
        else
        {
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_m_min, "M_min", m_minBinning, "QCD Function M_min shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_p_chi, "P_chi", p_chiBinning, "QCD Function P_chi shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "QCD Function DeltaPhi_leg1_leg2 shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "QCD Function DeltaPhi_MVAMET_Higgs shape ext. in SS side band (eleTau)", "et", 1);
            fillQCD_Shape(SScut_eleTau_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "QCD Function DeltaPhi_PFMET_Higgs shape ext. in SS side band (eleTau)", "et", 1);
            global_title = "MET < " + control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_mt, "mt_1", mtBinning, "sig region (met<100) mt", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_met, "met", metBinning, "sig region (met<100) met", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_m_min, "M_min", m_minBinning, "sig region (met<100) Function M_min", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_eleTau, qcd_eleTau_p_chi, "P_chi", p_chiBinning, "sig region (met<100) Function P_chi", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "sig region (met<100) Function DeltaPhi_leg1_leg2", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_MVAMET_Higgs", "et", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_eleTau, qcd_eleTau_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_PFMET_Higgs", "et", "", 1, 0, 0);
            
        }
        reset_files();
    }

    delete qcd_eleTau_mt;
    delete qcd_eleTau_m_vis;
    delete qcd_eleTau_pt_1;
    delete qcd_eleTau_pt_2;
    delete qcd_eleTau_LPT;
    delete qcd_eleTau_nbtag;
    delete qcd_eleTau_met;
    delete qcd_eleTau_p_chi;
    delete qcd_eleTau_m_min;
    delete qcd_eleTau_DeltaPhi_leg1_leg2;
    delete qcd_eleTau_DeltaPhi_PFMET_Higgs;
    delete qcd_eleTau_DeltaPhi_MVAMET_Higgs;
    delete qcd_eleTau_mvaVar_et_MZP600A0400;
    delete qcd_eleTau_mvaVar_et_MZP800A0400;
    delete qcd_eleTau_mvaVar_et_MZP1000A0400;
    delete qcd_eleTau_mvaVar_et_MZP1200A0400;
    
    delete qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVUp;
    delete qcd_eleTau_mt_tot_CMS_scale_m_et_13TeVDown;
    delete qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVUp;
    delete qcd_eleTau_mt_tot_CMS_xtt_dyShape_13TeVDown;
    delete qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVUp;
    delete qcd_eleTau_mt_tot_CMS_xtt_wShape_13TeVDown;
    delete qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp;
    delete qcd_eleTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown;
    delete qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVUp;
    delete qcd_eleTau_mt_tot_CMS_scale_t_et_13TeVDown;
    
}

void doMuTau()
{

    TCut OS_wNorm_muTau_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && iso_1 < 0.1 && byMediumIsolationMVArun2v1DBoldDMwLT_2 < 0.5 && byLooseIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut SS_wNorm_muTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && iso_1 < 0.1 && byMediumIsolationMVArun2v1DBoldDMwLT_2 < 0.5 && byLooseIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    
    TCut SScut_muTau_base("isOsPair==0 && dilepton_veto==0 && extramuon_veto==0 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && iso_1 < 0.1 && byMediumIsolationMVArun2v1DBoldDMwLT_2 > 0.5");
    TCut signalCut_base("isOsPair==1 && dilepton_veto==0 && extramuon_veto==0 && ((againstElectronTightMVA6_2 > 0.5 && againstMuonLoose3_2 > 0.5 ) || (againstElectronVLooseMVA6_2 > 0.5 && againstMuonTight3_2 > 0.5 )) && iso_1 < 0.1 && byMediumIsolationMVArun2v1DBoldDMwLT_2 > 0.5");

    std::string metCutTmp;
    if (cRegion)
    {
        if(doControlTMVA){metCutTmp = "met > 0.";}
        else{metCutTmp = "met < " + control_met_cutoff;}
    }
    else
    {
       metCutTmp = met_options["NOM"];
    }
    TCut cut_options_nom((drCutMap[drCut] + " && " + metCutTmp + " && " + mt_options["NOM"] + " && pt_tt>50").c_str());
    cut_options_nom += jetCutMap["NOM"];
    
    //Systematic Cuts
    TCut cut_options_UESUp((drCutMap[drCut] + " && " + met_options["MET_UES_UP"] + " && " + mt_options["MET_UES_UP"] + " && pt_tt > 50").c_str()); cut_options_UESUp += jetCutMap["NOM"];
    TCut cut_options_UESDown((drCutMap[drCut] + " && " + met_options["MET_UES_DOWN"] + " && " + mt_options["MET_UES_DOWN"] + " && pt_tt > 50").c_str());cut_options_UESDown += jetCutMap["NOM"];
    
    TCut cut_options_VPtUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_VPtUp += jetCutMap["NOM"]; cut_options_VPtUp *= weightMap["ZUP"]; cut_options_VPtUp *= weightMap["KUP"];
    TCut cut_options_VPtDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_VPtDown += jetCutMap["NOM"]; cut_options_VPtDown *= weightMap["ZDOWN"]; cut_options_VPtDown *= weightMap["KDOWN"];
    
    TCut cut_options_TauFakeUp((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str()); cut_options_TauFakeUp += jetCutMap["NOM"]; cut_options_TauFakeUp *= weightMap["JTFUP"];
    TCut cut_options_TauFakeDown((drCutMap[drCut] + " && " + met_options["NOM"] + " && " + mt_options["NOM"] + " && pt_tt > 50").c_str());cut_options_TauFakeDown += jetCutMap["NOM"]; cut_options_TauFakeDown *= weightMap["JTFDOWN"];

	chan_label = "#mu+ #tau_{h}";

    /* perform the OS W+jets normalization estimate (to be used in the signal region) */

    //global_title = "Opp. Sign high M_{T} Control Region";
    //double wSF_OS_muTau =  0.870714;//wjetsNorm(OS_wNorm_muTau, "wjetsOS");
    //double wSF_OS_muTau =  wjetsNorm(OS_wNorm_muTau_base * wNorm_cut_options["NOM"], "wjetsOS");
    double wSF_OS_muTau =  1.0;
    
    /* perform the SS W+jets normalization estimate (to be used in the QCD control region) */
    //still has wjetsNorm calculation and plots...
    //global_title = "Same Sign high M_{T} Control Region";
    //double wSF_SS_muTau = 0.967438;//wjetsNorm(SS_wNorm_muTau, "wjetsSSforQCD");
    //double wSF_SS_muTau = wjetsNorm(SS_wNorm_muTau_base * wNorm_cut_options["NOM"], "wjetsSSforQCD");
    double wSF_SS_muTau = 1.0;
    
    /* declare the muTau qcd shapes for each binning */		

    /* mt_1 */
    TH1F * qcd_muTau_mt = new TH1F("qcd_muTau_mt","qcd_muTau_mt",mtBinning[0],mtBinning[1],mtBinning[2]); 
    qcd_muTau_mt->Sumw2(); 
    qcd_muTau_mt->SetFillColor(colors["QCD"]);
    
    /* mt_tot */
    TH1F * qcd_muTau_mt_tot = new TH1F("qcd_muTau_mt_tot","qcd_muTau_mt_tot",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot->Sumw2();
    qcd_muTau_mt_tot->SetFillColor(colors["QCD"]);
    
    /* m_vis */
    TH1F * qcd_muTau_m_vis = new TH1F("qcd_muTau_m_vis","qcd_muTau_m_vis",m_visBinning[0],m_visBinning[1],m_visBinning[2]);
    qcd_muTau_m_vis->Sumw2(); 
    qcd_muTau_m_vis->SetFillColor(colors["QCD"]);	

    /* pt_1 */
    TH1F * qcd_muTau_pt_1 = new TH1F("qcd_muTau_pt_1","qcd_muTau_pt_1",ptBinning[0],ptBinning[1],ptBinning[2]);
    qcd_muTau_pt_1->Sumw2(); 
    qcd_muTau_pt_1->SetFillColor(colors["QCD"]);	

    /* pt_2 */
    TH1F * qcd_muTau_pt_2 = new TH1F("qcd_muTau_pt_2","qcd_muTau_pt_2",ptBinning[0],ptBinning[1],ptBinning[2]);
    qcd_muTau_pt_2->Sumw2(); 
    qcd_muTau_pt_2->SetFillColor(colors["QCD"]);	

    /* LPT */
    TH1F * qcd_muTau_LPT = new TH1F("qcd_muTau_LPT","qcd_muTau_LPT",lptBinning[0],lptBinning[1],lptBinning[2]);
    qcd_muTau_LPT->Sumw2();
    qcd_muTau_LPT->SetFillColor(colors["QCD"]);
    
    /* M_min */
    TH1F * qcd_muTau_m_min = new TH1F("qcd_muTau_m_min","qcd_muTau_m_min",m_minBinning[0],m_minBinning[1],m_minBinning[2]);
    qcd_muTau_m_min->Sumw2();
    qcd_muTau_m_min->SetFillColor(colors["QCD"]);

    /* P_chi */
    TH1F * qcd_muTau_p_chi = new TH1F("qcd_muTau_p_chi","qcd_muTau_p_chi",p_chiBinning[0],p_chiBinning[1],p_chiBinning[2]);
    qcd_muTau_p_chi->Sumw2();
    qcd_muTau_p_chi->SetFillColor(colors["QCD"]);

    /* nbtag */
    TH1F * qcd_muTau_nbtag = new TH1F("qcd_muTau_nbtag","qcd_muTau_nbtag",nbtagBinning[0],nbtagBinning[1],nbtagBinning[2]);
    qcd_muTau_nbtag->Sumw2(); 
    qcd_muTau_nbtag->SetFillColor(colors["QCD"]);
    
    /* deltaPhiLegs */
    TH1F * qcd_muTau_DeltaPhi_leg1_leg2 = new TH1F("qcd_muTau_DeltaPhi_leg1_leg2","qcd_muTau_DeltaPhi_leg1_leg2",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_muTau_DeltaPhi_leg1_leg2->Sumw2();
    qcd_muTau_DeltaPhi_leg1_leg2->SetFillColor(colors["QCD"]);
    
    /* deltaPhiPFMET */
    TH1F * qcd_muTau_DeltaPhi_PFMET_Higgs = new TH1F("qcd_muTau_DeltaPhi_PFMET_Higgs","qcd_muTau_DeltaPhi_PFMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_muTau_DeltaPhi_PFMET_Higgs->Sumw2();
    qcd_muTau_DeltaPhi_PFMET_Higgs->SetFillColor(colors["QCD"]);
    
    /* deltaPhiMVAMET */
    TH1F * qcd_muTau_DeltaPhi_MVAMET_Higgs = new TH1F("qcd_muTau_DeltaPhi_MVAMET_Higgs","qcd_muTau_DeltaPhi_MVAMET_Higgs",phiBinning[0],phiBinning[1],phiBinning[2]);
    qcd_muTau_DeltaPhi_MVAMET_Higgs->Sumw2();
    qcd_muTau_DeltaPhi_MVAMET_Higgs->SetFillColor(colors["QCD"]);
    
    /* met */
    TH1F * qcd_muTau_met = new TH1F("qcd_muTau_met","qcd_muTau_met",metBinning[0],metBinning[1],metBinning[2]); 
    qcd_muTau_met->Sumw2(); 
    qcd_muTau_met->SetFillColor(colors["QCD"]);
    
    /*TMVA*/
    TH1F * qcd_muTau_mvaVar_mt_MZP600A0400 = new TH1F("qcd_muTau_mvaVar_mt_MZP600A0400","qcd_muTau_mvaVar_mt_MZP600A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_MZP600A0400->Sumw2();
    qcd_muTau_mvaVar_mt_MZP600A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_muTau_mvaVar_mt_MZP800A0400 = new TH1F("qcd_muTau_mvaVar_mt_MZP800A0400","qcd_muTau_mvaVar_mt_MZP800A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_MZP800A0400->Sumw2();
    qcd_muTau_mvaVar_mt_MZP800A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_muTau_mvaVar_mt_MZP1000A0400 = new TH1F("qcd_muTau_mvaVar_mt_MZP1000A0400","qcd_muTau_mvaVar_mt_MZP1000A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_MZP1000A0400->Sumw2();
    qcd_muTau_mvaVar_mt_MZP1000A0400->SetFillColor(colors["QCD"]);
    TH1F * qcd_muTau_mvaVar_mt_MZP1200A0400 = new TH1F("qcd_muTau_mvaVar_mt_MZP1200A0400","qcd_muTau_mvaVar_mt_MZP1200A0400",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_MZP1200A0400->Sumw2();
    qcd_muTau_mvaVar_mt_MZP1200A0400->SetFillColor(colors["QCD"]);
    
    //Expert
    TH1F * qcd_muTau_mvaVar_mt_EXP1 = new TH1F("qcd_muTau_mvaVar_mt_EXP1","qcd_muTau_mvaVar_mt_EXP1",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_EXP1->Sumw2();
    qcd_muTau_mvaVar_mt_EXP1->SetFillColor(colors["QCD"]);
    TH1F * qcd_muTau_mvaVar_mt_EXP2 = new TH1F("qcd_muTau_mvaVar_mt_EXP2","qcd_muTau_mvaVar_mt_EXP2",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_EXP2->Sumw2();
    qcd_muTau_mvaVar_mt_EXP2->SetFillColor(colors["QCD"]);
    TH1F * qcd_muTau_mvaVar_mt_EXP3 = new TH1F("qcd_muTau_mvaVar_mt_EXP3","qcd_muTau_mvaVar_mt_EXP3",tmvaBinning[0],tmvaBinning[1],tmvaBinning[2]);
    qcd_muTau_mvaVar_mt_EXP3->Sumw2();
    qcd_muTau_mvaVar_mt_EXP3->SetFillColor(colors["QCD"]);
    
    //Systematic Variants
    TH1F * qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp = new TH1F("qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp","qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp->Sumw2();
    qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown = new TH1F("qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown","qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown->Sumw2();
    qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp = new TH1F("qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp","qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp->Sumw2();
    qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown = new TH1F("qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown","qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown->Sumw2();
    qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp = new TH1F("qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp","qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp->Sumw2();
    qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown = new TH1F("qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown","qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown->Sumw2();
    qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown->SetFillColor(colors["QCD"]);

    TH1F * qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp = new TH1F("qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp","qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->Sumw2();
    qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown = new TH1F("qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown","qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->Sumw2();
    qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp = new TH1F("qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp","qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp->Sumw2();
    qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp->SetFillColor(colors["QCD"]);
    
    TH1F * qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown = new TH1F("qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown","qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown",binnum_mt_tot, mt_totVarBinning);
    qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown->Sumw2();
    qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown->SetFillColor(colors["QCD"]);
    
    global_title = "QCD (Same Sign) Estimate Region";

    //SScut_muTau_base * cut_options_nom; /* needs to match whatever we draw the full model in*/
    
    if (sigChoice==1)
    {
        setup_files_muTau();
        
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 1);
        drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning, "sig region (met<100) met", "mt", "", 1, 0, 1);
        
    }
    else if (sigChoice==2)
    {
        setup_files_muTau();
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_Shape(SScut_muTau_base * cut_options_nom * TMVACutMap["MT_600"], wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP600A0400,"mvaVar_mt_MZP600A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
        fillQCD_Shape(SScut_muTau_base * cut_options_nom * TMVACutMap["MT_800"], wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP800A0400,"mvaVar_mt_MZP800A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
        fillQCD_Shape(SScut_muTau_base * cut_options_nom * TMVACutMap["MT_1000"], wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP1000A0400,"mvaVar_mt_MZP1000A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
        fillQCD_Shape(SScut_muTau_base * cut_options_nom * TMVACutMap["MT_1200"], wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP1200A0400,"mvaVar_mt_MZP1200A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);

        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["MT_600"], wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP600A0400, "mvaVar_mt_MZP600A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "600", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["MT_800"], wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP800A0400, "mvaVar_mt_MZP800A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "800", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["MT_1000"], wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP1000A0400, "mvaVar_mt_MZP1000A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "1000", 1, 0, 1);
        drawSignalRegion(signalCut_base * cut_options_nom * TMVACutMap["MT_1200"], wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP1200A0400, "mvaVar_mt_MZP1200A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "1200", 1, 0, 1);
        reset_files();
    }
    else if (sigChoice==3)
    {
        setup_files_muTau_test();
        findBkgFractions(signalCut_base * cut_options_nom, 1.0, "mt_tot", mt_totVarBinning);
        global_title = "QCD (Same Sign) Estimate Region";
        fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mt_tot, "mt_tot", mt_totVarBinning,  "QCD Mt total shape ext. in SS side band (MuTau)", "mt", 1);
        drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot, "mt_tot", mt_totVarBinning, "sig region Mt_total", "mt", "", 1, 1);
        
        if (doSyst)
        {
            std::cout << "syst for mt started" << std::endl;
            //syst
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_UESUp, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_UESDown, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_VPtUp, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_VPtDown, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_VPtUp, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_VPtDown, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_TauFakeUp, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_TauFakeDown, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);

            std::cout << "QCD Shapes for tt syst filled" << std::endl;
            
            drawSignalRegionVarBin(signalCut_base * cut_options_UESUp, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_scale_m_mt_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_UESDown, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_scale_m_mt_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_xtt_dyShape_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_xtt_dyShape_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtUp, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_xtt_wShape_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_VPtDown, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_xtt_wShape_13TeVDown", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeUp, signalCut_base * cut_options_nom, 1, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_xtt_jetToTauFake_13TeVUp", 0, 1);
            drawSignalRegionVarBin(signalCut_base * cut_options_TauFakeDown, signalCut_base * cut_options_nom, 1, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_xtt_jetToTauFake_13TeVDown", 0, 1);
            
            reset_files();
            setup_files_muTau_test();
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp, "mt_tot", mt_totVarBinning,  "", "mt", "_CMS_scale_t_mt_13TeVUp", 0, 1);
            
            reset_files();
            setup_files_muTau_test();
            fillQCD_ShapeVarBin(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown, "mt_tot", mt_totVarBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 0);
            drawSignalRegionVarBin(signalCut_base * cut_options_nom, signalCut_base * cut_options_nom, 0, wSF_OS_muTau, qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown, "mt_tot", mt_totVarBinning,  "", "mt","_CMS_scale_t_mt_13TeVDown", 0, 1);
        }
        reset_files();

    }
    else if (choice2==2)
    {
        setup_files_muTau();
        if (doControlTMVA)
        {
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP600A0400,"mvaVar_mt_MZP600A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP800A0400,"mvaVar_mt_MZP800A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP1000A0400,"mvaVar_mt_MZP1000A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_MZP1200A0400,"mvaVar_mt_MZP1200A0400", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
            global_title = "MET < " + control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP600A0400, "mvaVar_mt_MZP600A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP800A0400, "mvaVar_mt_MZP800A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP1000A0400, "mvaVar_mt_MZP1000A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_MZP1200A0400, "mvaVar_mt_MZP1200A0400", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
            
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_EXP1,"mvaVar_mt_EXP1", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_EXP2,"mvaVar_mt_EXP2", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mvaVar_mt_EXP3,"mvaVar_mt_EXP3", tmvaBinning, "QCD Function TMVA variable shape ext. in SS side band (muTau)", "mt", 1);

            global_title = "MET < " + control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_EXP1, "mvaVar_mt_EXP1", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_EXP2, "mvaVar_mt_EXP2", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mvaVar_mt_EXP3, "mvaVar_mt_EXP3", tmvaBinning, "sig region Function TMVA variable", "mt", "", 1, 0, 0);
        }
        else
        {
            global_title = "QCD (Same Sign) Estimate Region";
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_mt, "mt_1", mtBinning, "QCD mt shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_m_vis, "m_vis", m_visBinning,  "QCD mvis shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_nbtag, "nbtag", nbtagBinning,  "QCD nbtag shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_met, "met", metBinning,  "QCD met shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_pt_1, "pt_1", ptBinning,  "QCD pt_1 shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_pt_2, "pt_2", ptBinning,  "QCD pt_2 shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_LPT, "LPT", lptBinning,  "QCD LPT shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_m_min, "M_min", m_minBinning, "QCD Function M_min shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_p_chi, "P_chi", p_chiBinning, "QCD Function P_chi shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "QCD Function DeltaPhi_leg1_leg2 shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "QCD Function DeltaPhi_MVAMET_Higgs shape ext. in SS side band (muTau)", "mt", 1);
            fillQCD_Shape(SScut_muTau_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "QCD Function DeltaPhi_PFMET_Higgs shape ext. in SS side band (muTau)", "mt", 1);
            
            global_title = "MET < " + control_met_cutoff + " GeV Control Region";
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_mt, "mt_1", mtBinning, "sig region (met<100) mt", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_m_vis, "m_vis", m_visBinning, "sig region (met<100) mvis", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_nbtag, "nbtag", nbtagBinning, "sig region (met<100) nbtag", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_met, "met", metBinning, "sig region (met<100) met", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_pt_1, "pt_1", ptBinning, "sig region (met<100) pt_1", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_pt_2, "pt_2", ptBinning, "sig region (met<100) pt_2", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_LPT, "LPT", lptBinning, "sig region (met<100) LPT", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_m_min, "M_min", m_minBinning, "sig region (met<100) Function M_min", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_OS_muTau, qcd_muTau_p_chi, "P_chi", p_chiBinning, "sig region (met<100) Function P_chi", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_DeltaPhi_leg1_leg2, "DeltaPhi_leg1_leg2", phiBinning, "sig region (met<100) Function DeltaPhi_leg1_leg2", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_DeltaPhi_MVAMET_Higgs, "DeltaPhi_MVAMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_MVAMET_Higgs", "mt", "", 1, 0, 0);
            drawSignalRegion(signalCut_base * cut_options_nom, wSF_SS_muTau, qcd_muTau_DeltaPhi_PFMET_Higgs, "DeltaPhi_PFMET_Higgs", phiBinning, "sig region (met<100) Function DeltaPhi_PFMET_Higgs", "mt", "", 1, 0, 0);
        }
        reset_files();
    }
    
    delete qcd_muTau_mt;
    delete qcd_muTau_m_vis;
    delete qcd_muTau_pt_1;
    delete qcd_muTau_pt_2;
    delete qcd_muTau_LPT;
    delete qcd_muTau_nbtag;
    delete qcd_muTau_met;
    delete qcd_muTau_p_chi;
    delete qcd_muTau_m_min;
    delete qcd_muTau_DeltaPhi_leg1_leg2;
    delete qcd_muTau_DeltaPhi_MVAMET_Higgs;
    delete qcd_muTau_DeltaPhi_PFMET_Higgs;
    delete qcd_muTau_mvaVar_mt_MZP600A0400;
    delete qcd_muTau_mvaVar_mt_MZP800A0400;
    delete qcd_muTau_mvaVar_mt_MZP1000A0400;
    delete qcd_muTau_mvaVar_mt_MZP1200A0400;
    
    delete qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVUp;
    delete qcd_muTau_mt_tot_CMS_scale_m_mt_13TeVDown;
    delete qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVUp;
    delete qcd_muTau_mt_tot_CMS_xtt_dyShape_13TeVDown;
    delete qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVUp;
    delete qcd_muTau_mt_tot_CMS_xtt_wShape_13TeVDown;
    delete qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVUp;
    delete qcd_muTau_mt_tot_CMS_xtt_jetToTauFake_13TeVDown;
    delete qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVUp;
    delete qcd_muTau_mt_tot_CMS_scale_t_mt_13TeVDown;
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


void drawSignalRegion(TCut cut, double sf, TH1F * QCDshape, std::string parameter, float bin[3], std::string can_name, std::string chan, std::string syst, bool plot, bool count, bool createOutputShapes)
{

    std::cout << "CUT: " << cut.GetTitle() << std::endl;

	/* check if want blinded signal region met tail */
    if (plot)
    {
        if(choice2==1 && (parameter=="mt_tot"))
        {
            global_title = "Signal Region with Blinded Tail";
        }
        if(choice2==1 && (parameter=="met" || parameter=="mvamet"))
        {
            global_title = "Signal Region with Blind MET Tail";
        }
        if(choice2==1 && sigChoice==2 && (chan=="mt"||chan=="et"))
        {
            global_title = "Signal Region in TMVA (blinded above 0.5)";
        }
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
	
	TH1F * ttt_ = new TH1F("ttt_","ttt_",bin[0],bin[1],bin[2]);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);

    TH1F * ttj_ = new TH1F("ttj_","ttj_",bin[0],bin[1],bin[2]);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);

	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",bin[0],bin[1],bin[2]);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",bin[0],bin[1],bin[2]);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
	
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
    
	TH1F * zp600a300_ = new TH1F("zp600a300_","zp600a300_",bin[0],bin[1],bin[2]); 
	zp600a300_->Sumw2(); 

	TH1F * zp800a300_ = new TH1F("zp800a300_","zp800a300_",bin[0],bin[1],bin[2]); 
	zp800a300_->Sumw2(); 

	TH1F * zp1000a300_ = new TH1F("zp1000a300_","zp1000a300_",bin[0],bin[1],bin[2]); 
	zp1000a300_->Sumw2(); 

	TH1F * zp1200a300_ = new TH1F("zp1200a300_","zp1200a300_",bin[0],bin[1],bin[2]); 
	zp1200a300_->Sumw2();
    
    TH1F * zp1400a300_ = new TH1F("zp1400a300_","zp1400a300_",bin[0],bin[1],bin[2]);
	zp1400a300_->Sumw2();
    
    TH1F * zp1700a300_ = new TH1F("zp1700a300_","zp1700a300_",bin[0],bin[1],bin[2]);
	zp1700a300_->Sumw2();
    
    TH1F * zp2000a300_ = new TH1F("zp2000a300_","zp2000a300_",bin[0],bin[1],bin[2]);
	zp2000a300_->Sumw2();
    
    TH1F * zp2500a300_ = new TH1F("zp2500a300_","zp2500a300_",bin[0],bin[1],bin[2]);
	zp2500a300_->Sumw2();

	/* sum of all bks */
	TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2(); 

	TH1F * smh_ = new TH1F("smh_","smh_",bin[0],bin[1],bin[2]);
	smh_->Sumw2();
    smh_->SetFillColor(colors["SMH"]);
    
    
	/* fill the hists */
	if (plot) {Signal_region->cd(1);}

	DATA->Draw((parameter+">>data_").c_str(),cut);

	/* apply blinding conditions */
    if (plot)
    {
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
        else if(parameter.substr(0,6)=="mvaVar")
        {
            for(int i=0; i<data_->GetNbinsX()+1; ++i)
            {
                if(data_->GetBinLowEdge(i)>= 0.5)
                {
                    data_->SetBinContent(i,0);
                    data_->SetBinError(i,0);
                }
            }
        }
        if(parameter=="mt_tot")
        {
            for(int i=0; i<data_->GetNbinsX()+1; ++i)
            {
                if(data_->GetBinLowEdge(i)>= 200)
                {
                    data_->SetBinContent(i,0);
                    data_->SetBinError(i,0);
                }
            }
        }
    }
    
	W->Draw((parameter+">>w_").c_str(),cut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),cut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),cut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),cut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),cut*weights["VV"].c_str());
    ZVV->Draw((parameter+">>zvv_").c_str(),cut*weights["ZVV"].c_str());
    EWK->Draw((parameter+">>ewk_").c_str(),cut*weights["EWK"].c_str());
	TTT->Draw((parameter+">>ttt_").c_str(),cut*weights["TTT"].c_str());
    TTJ->Draw((parameter+">>ttj_").c_str(),cut*weights["TTJ"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),cut*weights["ZHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),cut*weights["ttHJetTT"].c_str());
    
    smh_->Add(zhtautau_);
    smh_->Add(tthjettt_);
    smh_->Add(glugluhtautau_);
    smh_->Add(vbfhtautau_);
    smh_->Add(whtautau_);
    
	MZP600_MA0300->Draw((parameter+">>zp600a300_").c_str(),cut*weights["MONO"].c_str());
	MZP800_MA0300->Draw((parameter+">>zp800a300_").c_str(),cut*weights["MONO"].c_str());
	MZP1000_MA0300->Draw((parameter+">>zp1000a300_").c_str(),cut*weights["MONO"].c_str());
	MZP1200_MA0300->Draw((parameter+">>zp1200a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0300->Draw((parameter+">>zp1400a300_").c_str(),cut*weights["MONO"].c_str());
	MZP1700_MA0300->Draw((parameter+">>zp1700a300_").c_str(),cut*weights["MONO"].c_str());
	MZP2000_MA0300->Draw((parameter+">>zp2000a300_").c_str(),cut*weights["MONO"].c_str());
	MZP2500_MA0300->Draw((parameter+">>zp2500a300_").c_str(),cut*weights["MONO"].c_str());
    
	qcd_->Add(QCDshape);
	qcd_->Scale(qcdOStoSS);
	w_->Scale(sf);
    
    THStack * sigMTstack  = new THStack();
    
    if (plot)
    {
    
        sigMTstack->Add(ztt_);
        sigMTstack->Add(zj_);
        sigMTstack->Add(zl_);
        sigMTstack->Add(qcd_);
        sigMTstack->Add(vv_);
        sigMTstack->Add(zvv_);
        sigMTstack->Add(ewk_);
        sigMTstack->Add(ttt_);
        sigMTstack->Add(ttj_);
        sigMTstack->Add(w_);
        
        if(splitPlotSMH)
        {
            sigMTstack->Add(zhtautau_);
            sigMTstack->Add(tthjettt_);
            sigMTstack->Add(whtautau_);
            sigMTstack->Add(vbfhtautau_);
            sigMTstack->Add(glugluhtautau_);
        }
        else
        {
            sigMTstack->Add(smh_);
        }
        Signal_region->cd(1);

        data_->SetMaximum(max(DATA_MAX*data_->GetMaximum(),10000.0));
        data_->SetMinimum(DATA_MIN);

    //	data_->SetTitle((can_name+";XXX;Events/Bin").c_str());
        data_->SetTitle(";XXX;Events/Bin");
        data_->GetXaxis()->SetTitle(x_axisLabels[parameter].c_str());

        data_->DrawCopy("PE");
        sigMTstack->Draw("histsames");

        if(parameter.substr(0,6)=="mvaVar")
        {
            if (syst=="600"){zp600a300_->SetLineStyle(3); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");}
            else if (syst=="800"){zp800a300_->SetLineStyle(3); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");}
            else if (syst=="1000"){zp1000a300_->SetLineStyle(3); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");}
            else if (syst=="1200"){zp1200a300_->SetLineStyle(3); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");}
            else
            {
                zp600a300_->SetLineStyle(2); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
                zp800a300_->SetLineStyle(2); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
                zp1000a300_->SetLineStyle(2); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
                zp1200a300_->SetLineStyle(2); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
            }
        }
        else if (parameter == "mt_tot" || parameter == "met")
        {
            zp600a300_->SetLineStyle(2); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
            zp800a300_->SetLineStyle(2); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
            zp1000a300_->SetLineStyle(2); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
            zp1200a300_->SetLineStyle(2); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
            zp1400a300_->SetLineStyle(2); zp1400a300_->SetLineWidth(3); zp1400a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp1400a300_->DrawCopy("hist sames");
            zp1700a300_->SetLineStyle(2); zp1700a300_->SetLineWidth(3); zp1700a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp1700a300_->DrawCopy("hist sames");
            zp2000a300_->SetLineStyle(2); zp2000a300_->SetLineWidth(3); zp2000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp2000a300_->DrawCopy("hist sames");
            zp2500a300_->SetLineStyle(2); zp2500a300_->SetLineWidth(3); zp2500a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp2500a300_->DrawCopy("hist sames");
        }
        data_->DrawCopy("PEsames");

        /* update canvas */
        Signal_region->Update();
    }
	/* get a sum of bks */
	comb_->Add(vv_);
    comb_->Add(zvv_);
    comb_->Add(ewk_);
	comb_->Add(ttt_);
    comb_->Add(ttj_);
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
    if (plot)
    {
        if(data_->GetSumOfWeights()==0)
        {
            //data_->SetMarkerColor(2);
            //std::cout<<" **** EMPTY BLINDED DATA ****, setting eq to bkg total ****\n";
            data_->SetMaximum(10000.0);
            //data_->Add(comb_);
            //data_->DrawCopy("PE");
            sigMTstack->Draw("histsames");
            if(parameter=="met" || parameter=="mt_tot")
            {
            
                    zp600a300_->SetLineStyle(2); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
                    zp800a300_->SetLineStyle(2); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
                    zp1000a300_->SetLineStyle(2); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
                    zp1200a300_->SetLineStyle(2); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
                    zp1400a300_->SetLineStyle(2); zp1400a300_->SetLineWidth(3); zp1400a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp1400a300_->DrawCopy("hist sames");
                    zp1700a300_->SetLineStyle(2); zp1700a300_->SetLineWidth(3); zp1700a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp1700a300_->DrawCopy("hist sames");
                    zp2000a300_->SetLineStyle(2); zp2000a300_->SetLineWidth(3); zp2000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp2000a300_->DrawCopy("hist sames");
                    zp2500a300_->SetLineStyle(2); zp2500a300_->SetLineWidth(3); zp2500a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp2500a300_->DrawCopy("hist sames");
            }
            else
            {
                if (syst=="600"){zp600a300_->SetLineStyle(3); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");}
                else if (syst=="800"){zp800a300_->SetLineStyle(3); zp800a300_->SetLineWidth(5); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");}
                else if (syst=="1000"){zp1000a300_->SetLineStyle(3); zp1000a300_->SetLineWidth(5); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");}
                else if (syst=="1200"){zp1200a300_->SetLineStyle(3); zp1200a300_->SetLineWidth(5); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");}
                else if (parameter.substr(0,6)=="mvaVar")
                {
                    zp600a300_->SetLineStyle(3); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
                    zp800a300_->SetLineStyle(3); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
                    zp1000a300_->SetLineStyle(3); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
                    zp1200a300_->SetLineStyle(3); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
                }
            }
            data_->DrawCopy("PEsames");
        }

        drawTcanvasAndLegendAndRatio(Signal_region, data_, comb_, 1);

        Signal_region->DrawClone();

        std::string localSaveName = saveName + parameter + "_" + chan + "_" + drCutNameMap[drCut] + "Region.png";
        Signal_region->cd()->SaveAs(localSaveName.c_str());

        Signal_region->Close();
    }
    
	// scale things to the projected lumi
	vv_->Scale(lumi_sf);
    zvv_->Scale(lumi_sf);
    ewk_->Scale(lumi_sf);
	ttt_->Scale(lumi_sf);
    ttj_->Scale(lumi_sf);
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
    smh_->Scale(lumi_sf);
    
	zp600a300_->Scale(lumi_sf);
	zp800a300_->Scale(lumi_sf);
	zp1000a300_->Scale(lumi_sf);
	zp1200a300_->Scale(lumi_sf);
    zp1400a300_->Scale(lumi_sf);
	zp1700a300_->Scale(lumi_sf);
	zp2000a300_->Scale(lumi_sf);
	zp2500a300_->Scale(lumi_sf);
	comb_->Scale(lumi_sf);
    
    std::cout << "Editing Shape File" << std::endl;
    
	if(choice2==1 and createOutputShapes)
	{
		/* create a file to help with S/sqrt(S+B) cut opt */
        
        std::string paramName;
        if (parameter=="met" || parameter=="mvamet") {paramName = "met";}
        else if (parameter=="mt_tot" || parameter=="m_vis") {paramName = "mt";}
        else if (parameter.substr(0,6)=="mvaVar") {paramName = "mva";}
        
        std::string catName = chan + "_" + drCutNameMap[drCut];
		std::string optName = "htt_" + chan + ".inputs-13TeV-" + paramName + ".root";
		TFile sbOp(optName.c_str(),"UPDATE");
        
        TDirectory * catdir = sbOp.GetDirectory(catName.c_str());
        if (catdir){catdir->cd();}
        else {sbOp.mkdir(catName.c_str()); TDirectory * catdir = sbOp.GetDirectory(catName.c_str()); catdir->cd();}
        
        std::string DATAname = "data_obs" + syst;
        const char *DATAsave = DATAname.c_str();
        std::string VVname = "VV" + syst;
        const char *VVsave = VVname.c_str();
        std::string ZVVname = "ZVV" + syst;
        const char *ZVVsave = ZVVname.c_str();
        std::string EWKname = "EWK" + syst;
        const char *EWKsave = EWKname.c_str();
        std::string TTTname = "TTT" + syst;
        const char *TTTsave = TTTname.c_str();
        std::string TTJname = "TTJ" + syst;
        const char *TTJsave = TTJname.c_str();
        std::string ZTTname = "ZTT" + syst;
        const char *ZTTsave = ZTTname.c_str();
        std::string ZLname = "ZL" + syst;
        const char *ZLsave = ZLname.c_str();
        std::string ZJname = "ZJ" + syst;
        const char *ZJsave = ZJname.c_str();
        std::string Wname = "W" + syst;
        const char *Wsave = Wname.c_str();
        std::string QCDname = "QCD" + syst;
        const char *QCDsave = QCDname.c_str();
        std::string zhtautauname = "zhtautau" + syst;
        const char *zhtautausave = zhtautauname.c_str();
        std::string SMHname = "SMH" + syst;
        const char *SMHsave = SMHname.c_str();
        std::string glugluhtautauname = "glugluhtautau" + syst;
        const char *glugluhtautausave = glugluhtautauname.c_str();
        std::string vbfhtautauname = "vbfhtautau" + syst;
        const char *vbfhtautausave = vbfhtautauname.c_str();
        std::string whtautauname = "whtautau" + syst;
        const char *whtautausave = whtautauname.c_str();
        std::string tthjetttname = "tthjettt" + syst;
        const char *tthjetttsave = tthjetttname.c_str();
        std::string combname = "comb" + syst;
        const char *combsave = combname.c_str();
        
        std::string ZprimeA400Zname = "ZprimeA400Z" + syst;
        const char *ZprimeA400Zsave = ZprimeA400Zname.c_str();
        
        std::string ZprimeA400Z600name = "ZprimeA400Z600" + syst;
        const char *ZprimeA400Z600save = ZprimeA400Z600name.c_str();
        std::string ZprimeA400Z800name = "ZprimeA400Z800" + syst;
        const char *ZprimeA400Z800save = ZprimeA400Z800name.c_str();
        std::string ZprimeA400Z1000name = "ZprimeA400Z1000" + syst;
        const char *ZprimeA400Z1000save = ZprimeA400Z1000name.c_str();
        std::string ZprimeA400Z1200name = "ZprimeA400Z1200" + syst;
        const char *ZprimeA400Z1200save = ZprimeA400Z1200name.c_str();
        std::string ZprimeA400Z1400name = "ZprimeA400Z1400" + syst;
        const char *ZprimeA400Z1400save = ZprimeA400Z1400name.c_str();
        std::string ZprimeA400Z1700name = "ZprimeA400Z1700" + syst;
        const char *ZprimeA400Z1700save = ZprimeA400Z1700name.c_str();
        std::string ZprimeA400Z2000name = "ZprimeA400Z2000" + syst;
        const char *ZprimeA400Z2000save = ZprimeA400Z2000name.c_str();
        std::string ZprimeA400Z2500name = "ZprimeA400Z2500" + syst;
        const char *ZprimeA400Z2500save = ZprimeA400Z2500name.c_str();

        data_->Write(DATAsave);
        
        vv_->Write(VVsave);
        zvv_->Write(ZVVsave);
        ewk_->Write(EWKsave);
        ttt_->Write(TTTsave);
        ttj_->Write(TTJsave);
        ztt_->Write(ZTTsave);
        zl_->Write(ZLsave);
        zj_->Write(ZJsave);
        w_->Write(Wsave);
        qcd_->Write(QCDsave);
        zhtautau_->Write(zhtautausave);
        
        smh_->Write(SMHsave);
        
        glugluhtautau_->Write(glugluhtautausave);
        vbfhtautau_->Write(vbfhtautausave);
        whtautau_->Write(whtautausave);
        tthjettt_->Write(tthjetttsave);
		comb_->Write(combsave);

        if (syst == "600"){zp600a300_->Write(ZprimeA400Zsave);}
        else if (syst == "800"){zp800a300_->Write(ZprimeA400Zsave);}
        else if (syst == "1000"){zp1000a300_->Write(ZprimeA400Zsave);}
        else if (syst == "1200"){zp1200a300_->Write(ZprimeA400Zsave);}
        else
        {
            zp600a300_->Write(ZprimeA400Z600save);
            zp800a300_->Write(ZprimeA400Z800save);
            zp1000a300_->Write(ZprimeA400Z1000save);
            zp1200a300_->Write(ZprimeA400Z1200save);
            zp1400a300_->Write(ZprimeA400Z1400save);
            zp1700a300_->Write(ZprimeA400Z1700save);
            zp2000a300_->Write(ZprimeA400Z2000save);
            zp2500a300_->Write(ZprimeA400Z2500save);
        }

        sbOp.cd();
		sbOp.Close();
	}
    std::cout << "FINISHED editing shape file" << std::endl;
    
	/* delete pointers */
	delete data_;
	delete vv_;
    delete zvv_;
    delete ewk_;
	delete ttt_;
    delete ttj_;
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
    delete smh_;
	delete qcd_;
	delete zp600a300_;
	delete zp800a300_;
	delete zp1000a300_;
	delete zp1200a300_;
	delete zp1400a300_;
    delete zp1700a300_;
    delete zp2000a300_;
    delete zp2500a300_;
	delete Signal_region;
	delete sigMTstack;

}

void drawSignalRegionVarBin(TCut cut, TCut normCut, bool doNorm, double sf, TH1F * QCDshape, std::string parameter, float bin[], std::string can_name, std::string chan, std::string syst, bool plot, bool createOutputShapes)
{

    int  binnum = binnum_mt_tot;

    std::cout << "CUT: " << cut.GetTitle() << std::endl;

	/* check if want blinded signal region met tail */
    if (plot)
    {
        if(choice2==1 && (parameter=="mt_tot"))
        {
            global_title = "Signal Region with Blinded Tail";
        }
        if(choice2==1 && (parameter=="met" || parameter=="mvamet"))
        {
            global_title = "Signal Region with Blind MET Tail";
        }
        if(choice2==1 && sigChoice==2 && (chan=="mt"||chan=="et"))
        {
            global_title = "Signal Region in TMVA (blinded above 0.5)";
        }
    }
    
	/* create a TCanvas */
	TCanvas * Signal_region = new TCanvas(can_name.c_str(),can_name.c_str(),canDim[0],canDim[1]);
	Signal_region->Divide(1,2);

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",binnum,bin);
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",binnum,bin); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",binnum,bin);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",binnum,bin);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",binnum,bin);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",binnum,bin); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * ttj_ = new TH1F("ttj_","ttj_",binnum,bin);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);
    
    TH1F * ttt_ = new TH1F("ttt_","ttt_",binnum,bin);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);
    
    TH1F * tt_ = new TH1F("tt_","tt_",binnum,bin);
	tt_->Sumw2();
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",binnum,bin); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",binnum,bin);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",binnum,bin);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",binnum,bin);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",binnum,bin);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",binnum,bin);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",binnum,bin);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",binnum,bin);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);
    
    /* sum of SMH */
	TH1F * smh_ = new TH1F("smh_","smh_",binnum,bin);
	smh_->Sumw2();
    smh_->SetFillColor(colors["SMH"]);
    
	/* sum of all bks */
	TH1F * comb_ = new TH1F("comb_","comb_",binnum,bin); 
	comb_->Sumw2();
    
	TH1F * zp600a300_ = new TH1F("zp600a300_","zp600a300_",binnum,bin);
	zp600a300_->Sumw2();
    TH1F * zp600a400_ = new TH1F("zp600a400_","zp600a400_",binnum,bin);
	zp600a400_->Sumw2();

	TH1F * zp800a300_ = new TH1F("zp800a300_","zp800a300_",binnum,bin);
	zp800a300_->Sumw2();
    TH1F * zp800a400_ = new TH1F("zp800a400_","zp800a400_",binnum,bin);
	zp800a400_->Sumw2();
    TH1F * zp800a500_ = new TH1F("zp800a500_","zp800a500_",binnum,bin);
	zp800a500_->Sumw2();
    TH1F * zp800a600_ = new TH1F("zp800a600_","zp800a600_",binnum,bin);
	zp800a600_->Sumw2();

	TH1F * zp1000a300_ = new TH1F("zp1000a300_","zp1000a300_",binnum,bin);
	zp1000a300_->Sumw2();
    TH1F * zp1000a400_ = new TH1F("zp1000a400_","zp1000a400_",binnum,bin);
	zp1000a400_->Sumw2();
    TH1F * zp1000a500_ = new TH1F("zp1000a500_","zp1000a500_",binnum,bin);
	zp1000a500_->Sumw2();
    TH1F * zp1000a600_ = new TH1F("zp1000a600_","zp1000a600_",binnum,bin);
	zp1000a600_->Sumw2();
	TH1F * zp1000a700_ = new TH1F("zp1000a700_","zp1000a700_",binnum,bin);
	zp1000a700_->Sumw2();
    TH1F * zp1000a800_ = new TH1F("zp1000a800_","zp1000a800_",binnum,bin);
	zp1000a800_->Sumw2();
    
    TH1F * zp1200a300_ = new TH1F("zp1200a300_","zp1200a300_",binnum,bin);
	zp1200a300_->Sumw2();
    TH1F * zp1200a400_ = new TH1F("zp1200a400_","zp1200a400_",binnum,bin);
	zp1200a400_->Sumw2();
    TH1F * zp1200a500_ = new TH1F("zp1200a500_","zp1200a500_",binnum,bin);
	zp1200a500_->Sumw2();
    TH1F * zp1200a600_ = new TH1F("zp1200a600_","zp1200a600_",binnum,bin);
	zp1200a600_->Sumw2();
	TH1F * zp1200a700_ = new TH1F("zp1200a700_","zp1200a700_",binnum,bin);
	zp1200a700_->Sumw2();
    TH1F * zp1200a800_ = new TH1F("zp1200a800_","zp1200a800_",binnum,bin);
	zp1200a800_->Sumw2();
    
    TH1F * zp1400a300_ = new TH1F("zp1400a300_","zp1400a300_",binnum,bin);
	zp1400a300_->Sumw2();
    TH1F * zp1400a400_ = new TH1F("zp1400a400_","zp1400a400_",binnum,bin);
	zp1400a400_->Sumw2();
    TH1F * zp1400a500_ = new TH1F("zp1400a500_","zp1400a500_",binnum,bin);
	zp1400a500_->Sumw2();
    TH1F * zp1400a600_ = new TH1F("zp1400a600_","zp1400a600_",binnum,bin);
	zp1400a600_->Sumw2();
	TH1F * zp1400a700_ = new TH1F("zp1400a700_","zp1400a700_",binnum,bin);
	zp1400a700_->Sumw2();
    TH1F * zp1400a800_ = new TH1F("zp1400a800_","zp1400a800_",binnum,bin);
	zp1400a800_->Sumw2();
    
    TH1F * zp1700a300_ = new TH1F("zp1700a300_","zp1700a300_",binnum,bin);
	zp1700a300_->Sumw2();
    TH1F * zp1700a400_ = new TH1F("zp1700a400_","zp1700a400_",binnum,bin);
	zp1700a400_->Sumw2();
    TH1F * zp1700a500_ = new TH1F("zp1700a500_","zp1700a500_",binnum,bin);
	zp1700a500_->Sumw2();
    TH1F * zp1700a600_ = new TH1F("zp1700a600_","zp1700a600_",binnum,bin);
	zp1700a600_->Sumw2();
	TH1F * zp1700a700_ = new TH1F("zp1700a700_","zp1700a700_",binnum,bin);
	zp1700a700_->Sumw2();
    TH1F * zp1700a800_ = new TH1F("zp1700a800_","zp1700a800_",binnum,bin);
	zp1700a800_->Sumw2();
    
    TH1F * zp2000a300_ = new TH1F("zp2000a300_","zp2000a300_",binnum,bin);
	zp2000a300_->Sumw2();
    TH1F * zp2000a400_ = new TH1F("zp2000a400_","zp2000a400_",binnum,bin);
	zp2000a400_->Sumw2();
    TH1F * zp2000a500_ = new TH1F("zp2000a500_","zp2000a500_",binnum,bin);
	zp2000a500_->Sumw2();
    TH1F * zp2000a600_ = new TH1F("zp2000a600_","zp2000a600_",binnum,bin);
	zp2000a600_->Sumw2();
	TH1F * zp2000a700_ = new TH1F("zp2000a700_","zp2000a700_",binnum,bin);
	zp2000a700_->Sumw2();
    TH1F * zp2000a800_ = new TH1F("zp2000a800_","zp2000a800_",binnum,bin);
	zp2000a800_->Sumw2();
    
    TH1F * zp2500a300_ = new TH1F("zp2500a300_","zp2500a300_",binnum,bin);
	zp2500a300_->Sumw2();
    TH1F * zp2500a400_ = new TH1F("zp2500a400_","zp2500a400_",binnum,bin);
	zp2500a400_->Sumw2();
    TH1F * zp2500a500_ = new TH1F("zp2500a500_","zp2500a500_",binnum,bin);
	zp2500a500_->Sumw2();
    TH1F * zp2500a600_ = new TH1F("zp2500a600_","zp2500a600_",binnum,bin);
	zp2500a600_->Sumw2();
	TH1F * zp2500a700_ = new TH1F("zp2500a700_","zp2500a700_",binnum,bin);
	zp2500a700_->Sumw2();
    TH1F * zp2500a800_ = new TH1F("zp2500a800_","zp2500a800_",binnum,bin);
	zp2500a800_->Sumw2();

	/* apply blinding conditions */
    if (plot)
    {
        Signal_region->cd(1);
    
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
        else if(parameter.substr(0,6)=="mvaVar")
        {
            for(int i=0; i<data_->GetNbinsX()+1; ++i)
            {
                if(data_->GetBinLowEdge(i)>= 0.5)
                {
                    data_->SetBinContent(i,0);
                    data_->SetBinError(i,0);
                }
            }
        }
        if(parameter=="mt_tot")
        {
            for(int i=0; i<data_->GetNbinsX()+1; ++i)
            {
                if(data_->GetBinLowEdge(i)>= 200)
                {
                    data_->SetBinContent(i,0);
                    data_->SetBinError(i,0);
                }
            }
        }
    }

    double w_Norm = 1.; 
    double ztt_Norm = 1.; 
    double zl_Norm = 1.; 
    double zj_Norm = 1.; 
    double vv_Norm = 1.; 
    double zvv_Norm = 1.; 
    double ewk_Norm = 1.; 
    double ttt_Norm = 1.; 
    double ttj_Norm = 1.;
    double tt_Norm = 1.;
    double zhtautau_Norm = 1.; 
    double vbfhtautau_Norm = 1.; 
    double glugluhtautau_Norm = 1.; 
    double whtautau_Norm = 1.; 
    double tthjettt_Norm = 1.;
    
    double qcd_Norm = 1.;
    double smh_Norm = 1.;
    double comb_Norm = 1.;
    
    double zp600a300_Norm = 1.; 
    double zp600a400_Norm = 1.; 
    
    double zp800a300_Norm = 1.; 
    double zp800a400_Norm = 1.; 
    double zp800a500_Norm = 1.; 
    double zp800a600_Norm = 1.; 
    
    double zp1000a300_Norm = 1.; 
    double zp1000a400_Norm = 1.; 
    double zp1000a500_Norm = 1.; 
    double zp1000a600_Norm = 1.; 
    double zp1000a700_Norm = 1.; 
    double zp1000a800_Norm = 1.; 
    
    double zp1200a300_Norm = 1.; 
    double zp1200a400_Norm = 1.; 
    double zp1200a500_Norm = 1.; 
    double zp1200a600_Norm = 1.; 
    double zp1200a700_Norm = 1.; 
    double zp1200a800_Norm = 1.; 

    double zp1400a300_Norm = 1.; 
    double zp1400a400_Norm = 1.; 
    double zp1400a500_Norm = 1.; 
    double zp1400a600_Norm = 1.; 
    double zp1400a700_Norm = 1.; 
    double zp1400a800_Norm = 1.; 
    
    double zp1700a300_Norm = 1.; 
    double zp1700a400_Norm = 1.; 
    double zp1700a500_Norm = 1.; 
    double zp1700a600_Norm = 1.; 
    double zp1700a700_Norm = 1.; 
    double zp1700a800_Norm = 1.; 
    
    double zp2000a300_Norm = 1.; 
    double zp2000a400_Norm = 1.; 
    double zp2000a500_Norm = 1.; 
    double zp2000a600_Norm = 1.; 
    double zp2000a700_Norm = 1.; 
    double zp2000a800_Norm = 1.; 
    
    double zp2500a300_Norm = 1.; 
    double zp2500a400_Norm = 1.; 
    double zp2500a500_Norm = 1.; 
    double zp2500a600_Norm = 1.; 
    double zp2500a700_Norm = 1.; 
    double zp2500a800_Norm = 1.;

    if(doNorm)
    {
        W->Draw((parameter+">>w_").c_str(),normCut*weights["W"].c_str());
        ZTT->Draw((parameter+">>ztt_").c_str(),normCut*weights["ZTT"].c_str());
        ZL->Draw((parameter+">>zl_").c_str(),normCut*weights["ZL"].c_str());
        ZJ->Draw((parameter+">>zj_").c_str(),normCut*weights["ZJ"].c_str());
        VV->Draw((parameter+">>vv_").c_str(),normCut*weights["VV"].c_str());
        ZVV->Draw((parameter+">>zvv_").c_str(),normCut*weights["ZVV"].c_str());
        EWK->Draw((parameter+">>ewk_").c_str(),normCut*weights["EWK"].c_str());
        TTT->Draw((parameter+">>ttt_").c_str(),normCut*weights["TTT"].c_str());
        TTJ->Draw((parameter+">>ttj_").c_str(),normCut*weights["TTJ"].c_str());
        ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),normCut*weights["ZHTauTau"].c_str());
        VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),normCut*weights["VBFHTauTau"].c_str());
        GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),normCut*weights["GluGluHTauTau"].c_str());
        WHTauTau->Draw((parameter+">>whtautau_").c_str(),normCut*weights["WHTauTau"].c_str());
        ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),normCut*weights["ttHJetTT"].c_str());
        
        qcd_->Add(QCDshape);
        qcd_->Scale(qcdOStoSS);
        
        w_->Scale(sf);
        
        smh_->Add(zhtautau_);
        smh_->Add(tthjettt_);
        smh_->Add(glugluhtautau_);
        smh_->Add(vbfhtautau_);
        smh_->Add(whtautau_);
        
        tt_->Add(ttt_);
        tt_->Add(ttj_);
        
        /* get a sum of bks */
        comb_->Add(vv_);
        comb_->Add(zvv_);
        comb_->Add(ewk_);
        comb_->Add(ttt_);
        comb_->Add(ttj_);
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
        
        MZP600_MA0300->Draw((parameter+">>zp600a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP600_MA0400->Draw((parameter+">>zp600a400_").c_str(),normCut*weights["MONO"].c_str());
        
        MZP800_MA0300->Draw((parameter+">>zp800a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP800_MA0400->Draw((parameter+">>zp800a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP800_MA0500->Draw((parameter+">>zp800a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP800_MA0600->Draw((parameter+">>zp800a600_").c_str(),normCut*weights["MONO"].c_str());
        
        MZP1000_MA0300->Draw((parameter+">>zp1000a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP1000_MA0400->Draw((parameter+">>zp1000a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP1000_MA0500->Draw((parameter+">>zp1000a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP1000_MA0600->Draw((parameter+">>zp1000a600_").c_str(),normCut*weights["MONO"].c_str());
        MZP1000_MA0700->Draw((parameter+">>zp1000a700_").c_str(),normCut*weights["MONO"].c_str());
        MZP1000_MA0800->Draw((parameter+">>zp1000a800_").c_str(),normCut*weights["MONO"].c_str());
        
        MZP1200_MA0300->Draw((parameter+">>zp1200a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP1200_MA0400->Draw((parameter+">>zp1200a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP1200_MA0500->Draw((parameter+">>zp1200a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP1200_MA0600->Draw((parameter+">>zp1200a600_").c_str(),normCut*weights["MONO"].c_str());
        MZP1200_MA0700->Draw((parameter+">>zp1200a700_").c_str(),normCut*weights["MONO"].c_str());
        MZP1200_MA0800->Draw((parameter+">>zp1200a800_").c_str(),normCut*weights["MONO"].c_str());

        MZP1400_MA0300->Draw((parameter+">>zp1400a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP1400_MA0400->Draw((parameter+">>zp1400a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP1400_MA0500->Draw((parameter+">>zp1400a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP1400_MA0600->Draw((parameter+">>zp1400a600_").c_str(),normCut*weights["MONO"].c_str());
        MZP1400_MA0700->Draw((parameter+">>zp1400a700_").c_str(),normCut*weights["MONO"].c_str());
        MZP1400_MA0800->Draw((parameter+">>zp1400a800_").c_str(),normCut*weights["MONO"].c_str());
        
        MZP1700_MA0300->Draw((parameter+">>zp1700a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP1700_MA0400->Draw((parameter+">>zp1700a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP1700_MA0500->Draw((parameter+">>zp1700a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP1700_MA0600->Draw((parameter+">>zp1700a600_").c_str(),normCut*weights["MONO"].c_str());
        MZP1700_MA0700->Draw((parameter+">>zp1700a700_").c_str(),normCut*weights["MONO"].c_str());
        MZP1700_MA0800->Draw((parameter+">>zp1700a800_").c_str(),normCut*weights["MONO"].c_str());
        
        MZP2000_MA0300->Draw((parameter+">>zp2000a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP2000_MA0400->Draw((parameter+">>zp2000a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP2000_MA0500->Draw((parameter+">>zp2000a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP2000_MA0600->Draw((parameter+">>zp2000a600_").c_str(),normCut*weights["MONO"].c_str());
        MZP2000_MA0700->Draw((parameter+">>zp2000a700_").c_str(),normCut*weights["MONO"].c_str());
        MZP2000_MA0800->Draw((parameter+">>zp2000a800_").c_str(),normCut*weights["MONO"].c_str());
        
        MZP2500_MA0300->Draw((parameter+">>zp2500a300_").c_str(),normCut*weights["MONO"].c_str());
        MZP2500_MA0400->Draw((parameter+">>zp2500a400_").c_str(),normCut*weights["MONO"].c_str());
        MZP2500_MA0500->Draw((parameter+">>zp2500a500_").c_str(),normCut*weights["MONO"].c_str());
        MZP2500_MA0600->Draw((parameter+">>zp2500a600_").c_str(),normCut*weights["MONO"].c_str());
        MZP2500_MA0700->Draw((parameter+">>zp2500a700_").c_str(),normCut*weights["MONO"].c_str());
        MZP2500_MA0800->Draw((parameter+">>zp2500a800_").c_str(),normCut*weights["MONO"].c_str());
        
        w_Norm = w_->Integral();
        ztt_Norm = ztt_->Integral();
        zl_Norm = zl_->Integral();
        zj_Norm = zj_->Integral();
        vv_Norm = vv_->Integral();
        zvv_Norm = zvv_->Integral();
        ewk_Norm = ewk_->Integral();
        ttt_Norm = ttt_->Integral();
        ttj_Norm = ttj_->Integral();
        zhtautau_Norm = zhtautau_->Integral();
        vbfhtautau_Norm = vbfhtautau_->Integral();
        glugluhtautau_Norm = glugluhtautau_->Integral();
        whtautau_Norm = whtautau_->Integral();
        tthjettt_Norm = tthjettt_->Integral();
        
        qcd_Norm = qcd_->Integral();
        comb_Norm = comb_->Integral();
        smh_Norm = smh_->Integral();
        
        tt_Norm = tt_->Integral();
        
        zp600a300_Norm = zp600a300_->Integral(); 
        zp600a400_Norm = zp600a400_->Integral(); 
        
        zp800a300_Norm = zp800a300_->Integral(); 
        zp800a400_Norm = zp800a400_->Integral(); 
        zp800a500_Norm = zp800a500_->Integral(); 
        zp800a600_Norm = zp800a600_->Integral(); 
        
        zp1000a300_Norm = zp1000a300_->Integral(); 
        zp1000a400_Norm = zp1000a400_->Integral(); 
        zp1000a500_Norm = zp1000a500_->Integral(); 
        zp1000a600_Norm = zp1000a600_->Integral(); 
        zp1000a700_Norm = zp1000a700_->Integral(); 
        zp1000a800_Norm = zp1000a800_->Integral(); 
        
        zp1200a300_Norm = zp1200a300_->Integral(); 
        zp1200a400_Norm = zp1200a400_->Integral(); 
        zp1200a500_Norm = zp1200a500_->Integral(); 
        zp1200a600_Norm = zp1200a600_->Integral(); 
        zp1200a700_Norm = zp1200a700_->Integral(); 
        zp1200a800_Norm = zp1200a800_->Integral(); 

        zp1400a300_Norm = zp1400a300_->Integral(); 
        zp1400a400_Norm = zp1400a400_->Integral(); 
        zp1400a500_Norm = zp1400a500_->Integral(); 
        zp1400a600_Norm = zp1400a600_->Integral(); 
        zp1400a700_Norm = zp1400a700_->Integral(); 
        zp1400a800_Norm = zp1400a800_->Integral(); 
        
        zp1700a300_Norm = zp1700a300_->Integral(); 
        zp1700a400_Norm = zp1700a400_->Integral(); 
        zp1700a500_Norm = zp1700a500_->Integral(); 
        zp1700a600_Norm = zp1700a600_->Integral(); 
        zp1700a700_Norm = zp1700a700_->Integral(); 
        zp1700a800_Norm = zp1700a800_->Integral(); 
        
        zp2000a300_Norm = zp2000a300_->Integral(); 
        zp2000a400_Norm = zp2000a400_->Integral(); 
        zp2000a500_Norm = zp2000a500_->Integral(); 
        zp2000a600_Norm = zp2000a600_->Integral(); 
        zp2000a700_Norm = zp2000a700_->Integral(); 
        zp2000a800_Norm = zp2000a800_->Integral(); 
        
        zp2500a300_Norm = zp2500a300_->Integral(); 
        zp2500a400_Norm = zp2500a400_->Integral(); 
        zp2500a500_Norm = zp2500a500_->Integral(); 
        zp2500a600_Norm = zp2500a600_->Integral(); 
        zp2500a700_Norm = zp2500a700_->Integral(); 
        zp2500a800_Norm = zp2500a800_->Integral();
        
        w_->Reset();
        ztt_->Reset();
        zl_->Reset();
        zj_->Reset();
        vv_->Reset();
        zvv_->Reset();
        ewk_->Reset();
        ttt_->Reset();
        ttj_->Reset();
        zhtautau_->Reset();
        vbfhtautau_->Reset();
        glugluhtautau_->Reset();
        whtautau_->Reset();
        tthjettt_->Reset();
        
        qcd_->Reset();
        comb_->Reset();
        smh_->Reset();
        tt_->Reset();
        
        zp600a300_->Reset(); 
        zp600a400_->Reset(); 
        
        zp800a300_->Reset(); 
        zp800a400_->Reset(); 
        zp800a500_->Reset(); 
        zp800a600_->Reset(); 
        
        zp1000a300_->Reset(); 
        zp1000a400_->Reset(); 
        zp1000a500_->Reset(); 
        zp1000a600_->Reset(); 
        zp1000a700_->Reset(); 
        zp1000a800_->Reset(); 
        
        zp1200a300_->Reset(); 
        zp1200a400_->Reset(); 
        zp1200a500_->Reset(); 
        zp1200a600_->Reset(); 
        zp1200a700_->Reset(); 
        zp1200a800_->Reset(); 

        zp1400a300_->Reset(); 
        zp1400a400_->Reset(); 
        zp1400a500_->Reset(); 
        zp1400a600_->Reset(); 
        zp1400a700_->Reset(); 
        zp1400a800_->Reset(); 
        
        zp1700a300_->Reset(); 
        zp1700a400_->Reset(); 
        zp1700a500_->Reset(); 
        zp1700a600_->Reset(); 
        zp1700a700_->Reset(); 
        zp1700a800_->Reset(); 
        
        zp2000a300_->Reset(); 
        zp2000a400_->Reset(); 
        zp2000a500_->Reset(); 
        zp2000a600_->Reset(); 
        zp2000a700_->Reset(); 
        zp2000a800_->Reset(); 
        
        zp2500a300_->Reset(); 
        zp2500a400_->Reset(); 
        zp2500a500_->Reset(); 
        zp2500a600_->Reset(); 
        zp2500a700_->Reset(); 
        zp2500a800_->Reset();

    }
    
    /* fill the hists */

	DATA->Draw((parameter+">>data_").c_str(),cut);
    
	W->Draw((parameter+">>w_").c_str(),cut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),cut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),cut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),cut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),cut*weights["VV"].c_str());
    ZVV->Draw((parameter+">>zvv_").c_str(),cut*weights["ZVV"].c_str());
    EWK->Draw((parameter+">>ewk_").c_str(),cut*weights["EWK"].c_str());
	TTT->Draw((parameter+">>ttt_").c_str(),cut*weights["TTT"].c_str());
    TTJ->Draw((parameter+">>ttj_").c_str(),cut*weights["TTJ"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),cut*weights["ZHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),cut*weights["ttHJetTT"].c_str());
    
	MZP600_MA0300->Draw((parameter+">>zp600a300_").c_str(),cut*weights["MONO"].c_str());
    MZP600_MA0400->Draw((parameter+">>zp600a400_").c_str(),cut*weights["MONO"].c_str());
    
	MZP800_MA0300->Draw((parameter+">>zp800a300_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0400->Draw((parameter+">>zp800a400_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0500->Draw((parameter+">>zp800a500_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0600->Draw((parameter+">>zp800a600_").c_str(),cut*weights["MONO"].c_str());
    
	MZP1000_MA0300->Draw((parameter+">>zp1000a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0400->Draw((parameter+">>zp1000a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0500->Draw((parameter+">>zp1000a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0600->Draw((parameter+">>zp1000a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0700->Draw((parameter+">>zp1000a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0800->Draw((parameter+">>zp1000a800_").c_str(),cut*weights["MONO"].c_str());
    
    MZP1200_MA0300->Draw((parameter+">>zp1200a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0400->Draw((parameter+">>zp1200a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0500->Draw((parameter+">>zp1200a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0600->Draw((parameter+">>zp1200a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0700->Draw((parameter+">>zp1200a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0800->Draw((parameter+">>zp1200a800_").c_str(),cut*weights["MONO"].c_str());

	MZP1400_MA0300->Draw((parameter+">>zp1400a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0400->Draw((parameter+">>zp1400a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0500->Draw((parameter+">>zp1400a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0600->Draw((parameter+">>zp1400a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0700->Draw((parameter+">>zp1400a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0800->Draw((parameter+">>zp1400a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP1700_MA0300->Draw((parameter+">>zp1700a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0400->Draw((parameter+">>zp1700a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0500->Draw((parameter+">>zp1700a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0600->Draw((parameter+">>zp1700a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0700->Draw((parameter+">>zp1700a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0800->Draw((parameter+">>zp1700a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP2000_MA0300->Draw((parameter+">>zp2000a300_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0400->Draw((parameter+">>zp2000a400_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0500->Draw((parameter+">>zp2000a500_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0600->Draw((parameter+">>zp2000a600_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0700->Draw((parameter+">>zp2000a700_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0800->Draw((parameter+">>zp2000a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP2500_MA0300->Draw((parameter+">>zp2500a300_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0400->Draw((parameter+">>zp2500a400_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0500->Draw((parameter+">>zp2500a500_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0600->Draw((parameter+">>zp2500a600_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0700->Draw((parameter+">>zp2500a700_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0800->Draw((parameter+">>zp2500a800_").c_str(),cut*weights["MONO"].c_str());
    
	qcd_->Add(QCDshape);
	qcd_->Scale(qcdOStoSS);
	w_->Scale(sf);
    
    smh_->Add(zhtautau_);
    smh_->Add(tthjettt_);
    smh_->Add(glugluhtautau_);
    smh_->Add(vbfhtautau_);
    smh_->Add(whtautau_);
    
    tt_->Add(ttt_);
    tt_->Add(ttj_);
    
    /* get a sum of bks */
	comb_->Add(vv_);
    comb_->Add(zvv_);
    comb_->Add(ewk_);
	comb_->Add(ttt_);
    comb_->Add(ttj_);
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
    
    THStack * sigMTstack  = new THStack();
    
    if (plot)
    {
    
        sigMTstack->Add(ztt_);
        sigMTstack->Add(zj_);
        sigMTstack->Add(zl_);
        sigMTstack->Add(qcd_);
        sigMTstack->Add(vv_);
        sigMTstack->Add(zvv_);
        sigMTstack->Add(ewk_);
        //sigMTstack->Add(ttt_);
        //sigMTstack->Add(ttj_);
        sigMTstack->Add(tt_);
        sigMTstack->Add(w_);
        
        if(splitPlotSMH)
        {
            sigMTstack->Add(zhtautau_);
            sigMTstack->Add(tthjettt_);
            sigMTstack->Add(whtautau_);
            sigMTstack->Add(vbfhtautau_);
            sigMTstack->Add(glugluhtautau_);
        }
        else
        {
            sigMTstack->Add(smh_);
        }
        Signal_region->cd(1);

        data_->SetMaximum(max(DATA_MAX*data_->GetMaximum(),10000.0));
        data_->SetMinimum(DATA_MIN);

    //	data_->SetTitle((can_name+";XXX;Events/Bin").c_str());
        data_->SetTitle(";XXX;Events/Bin");
        data_->GetXaxis()->SetTitle(x_axisLabels[parameter].c_str());

        data_->DrawCopy("PE");
        sigMTstack->Draw("histsames");

        if(parameter.substr(0,6)=="mvaVar")
        {
            if (syst=="600"){zp600a300_->SetLineStyle(3); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");}
            else if (syst=="800"){zp800a300_->SetLineStyle(3); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");}
            else if (syst=="1000"){zp1000a300_->SetLineStyle(3); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");}
            else if (syst=="1200"){zp1200a300_->SetLineStyle(3); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");}
            else
            {
                zp600a300_->SetLineStyle(2); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
                zp800a300_->SetLineStyle(2); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
                zp1000a300_->SetLineStyle(2); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
                zp1200a300_->SetLineStyle(2); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
            }
        }
        else if (parameter == "mt_tot" || parameter == "met")
        {
            zp600a300_->SetLineStyle(2); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
            zp800a300_->SetLineStyle(2); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
            zp1000a300_->SetLineStyle(2); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
            zp1200a300_->SetLineStyle(2); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
        }
        data_->DrawCopy("PEsames");

        /* update canvas */
        Signal_region->Update();

        /* small fix for when blinded data is empty */
        if(data_->GetSumOfWeights()==0)
        {
            data_->SetMaximum(10000.0);
            sigMTstack->Draw("histsames");
            if(parameter=="met" || parameter=="mt_tot")
            {
            
                    zp600a300_->SetLineStyle(2); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
                    zp800a300_->SetLineStyle(2); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
                    zp1000a300_->SetLineStyle(2); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
                    zp1200a300_->SetLineStyle(2); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");

            }
            else
            {
                if (syst=="600"){zp600a300_->SetLineStyle(3); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");}
                else if (syst=="800"){zp800a300_->SetLineStyle(3); zp800a300_->SetLineWidth(5); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");}
                else if (syst=="1000"){zp1000a300_->SetLineStyle(3); zp1000a300_->SetLineWidth(5); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");}
                else if (syst=="1200"){zp1200a300_->SetLineStyle(3); zp1200a300_->SetLineWidth(5); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");}
                else if (parameter.substr(0,6)=="mvaVar")
                {
                    zp600a300_->SetLineStyle(3); zp600a300_->SetLineWidth(3); zp600a300_->SetLineColor(50); std::cout << "DRAWING" << std::endl; zp600a300_->DrawCopy("hist sames");
                    zp800a300_->SetLineStyle(3); zp800a300_->SetLineWidth(3); zp800a300_->SetLineColor(60); std::cout << "DRAWING" << std::endl; zp800a300_->DrawCopy("hist sames");
                    zp1000a300_->SetLineStyle(3); zp1000a300_->SetLineWidth(3); zp1000a300_->SetLineColor(70); std::cout << "DRAWING" << std::endl; zp1000a300_->DrawCopy("hist sames");
                    zp1200a300_->SetLineStyle(3); zp1200a300_->SetLineWidth(3); zp1200a300_->SetLineColor(80); std::cout << "DRAWING" << std::endl; zp1200a300_->DrawCopy("hist sames");
                }
            }
            data_->DrawCopy("PEsames");
        }

        drawTcanvasAndLegendAndRatio(Signal_region, data_, comb_, 1);

        Signal_region->DrawClone();

        std::string localSaveName = saveName + parameter + "_" + chan + "_" + drCutNameMap[drCut] + "Region.png";
        Signal_region->cd()->SaveAs(localSaveName.c_str());

        Signal_region->Close();
    }
    
	// scale things to the projected lumi
	vv_->Scale(lumi_sf);
    zvv_->Scale(lumi_sf);
    ewk_->Scale(lumi_sf);
	ttt_->Scale(lumi_sf);
    ttj_->Scale(lumi_sf);
	ztt_->Scale(lumi_sf);
    zl_->Scale(lumi_sf);
    zj_->Scale(lumi_sf);
	w_->Scale(lumi_sf);
    zhtautau_->Scale(lumi_sf);
    glugluhtautau_->Scale(lumi_sf);
    vbfhtautau_->Scale(lumi_sf);
    whtautau_->Scale(lumi_sf);
    tthjettt_->Scale(lumi_sf);
    
    tt_->Scale(lumi_sf);
    qcd_->Scale(lumi_sf);
    smh_->Scale(lumi_sf);
    
	comb_->Scale(lumi_sf);
    
	zp600a300_->Scale(lumi_sf);
    zp600a400_->Scale(lumi_sf);
	zp800a300_->Scale(lumi_sf);
    zp800a400_->Scale(lumi_sf);
    zp800a500_->Scale(lumi_sf);
    zp800a600_->Scale(lumi_sf);
	zp1000a300_->Scale(lumi_sf);
    zp1000a400_->Scale(lumi_sf);
    zp1000a500_->Scale(lumi_sf);
    zp1000a600_->Scale(lumi_sf);
    zp1000a700_->Scale(lumi_sf);
    zp1000a800_->Scale(lumi_sf);
	zp1200a300_->Scale(lumi_sf);
    zp1200a400_->Scale(lumi_sf);
    zp1200a500_->Scale(lumi_sf);
    zp1200a600_->Scale(lumi_sf);
    zp1200a700_->Scale(lumi_sf);
    zp1200a800_->Scale(lumi_sf);
    zp1400a300_->Scale(lumi_sf);
    zp1400a400_->Scale(lumi_sf);
    zp1400a500_->Scale(lumi_sf);
    zp1400a600_->Scale(lumi_sf);
    zp1400a700_->Scale(lumi_sf);
    zp1400a800_->Scale(lumi_sf);
	zp1700a300_->Scale(lumi_sf);
    zp1700a400_->Scale(lumi_sf);
    zp1700a500_->Scale(lumi_sf);
    zp1700a600_->Scale(lumi_sf);
    zp1700a700_->Scale(lumi_sf);
    zp1700a800_->Scale(lumi_sf);
	zp2000a300_->Scale(lumi_sf);
    zp2000a400_->Scale(lumi_sf);
    zp2000a500_->Scale(lumi_sf);
    zp2000a600_->Scale(lumi_sf);
    zp2000a700_->Scale(lumi_sf);
    zp2000a800_->Scale(lumi_sf);
	zp2500a300_->Scale(lumi_sf);
    zp2500a400_->Scale(lumi_sf);
    zp2500a500_->Scale(lumi_sf);
    zp2500a600_->Scale(lumi_sf);
    zp2500a700_->Scale(lumi_sf);
    zp2500a800_->Scale(lumi_sf);
    
    // scale things to the projected lumi
    if(doNorm)
    {
        double scale = 1.0;
        
        scale = vv_Norm/(vv_->Integral());
        vv_->Scale(scale);
        scale = zvv_Norm/(zvv_->Integral());
        zvv_->Scale(scale);
        scale = ewk_Norm/(ewk_->Integral());
        ewk_->Scale(scale);
        scale = ttt_Norm/(ttt_->Integral());
        ttt_->Scale(scale);
        scale = ttj_Norm/(ttj_->Integral());
        ttj_->Scale(scale);
        scale = ztt_Norm/(ztt_->Integral());
        ztt_->Scale(scale);
        scale = zl_Norm/(zl_->Integral());
        zl_->Scale(scale);
        scale = zj_Norm/(zj_->Integral());
        zj_->Scale(scale);
        scale = w_Norm/(w_->Integral());
        w_->Scale(scale);
        scale = zhtautau_Norm/(zhtautau_->Integral());
        zhtautau_->Scale(scale);
        scale = glugluhtautau_Norm/(glugluhtautau_->Integral());
        glugluhtautau_->Scale(scale);
        scale = vbfhtautau_Norm/(vbfhtautau_->Integral());
        vbfhtautau_->Scale(scale);
        scale = whtautau_Norm/(whtautau_->Integral());
        whtautau_->Scale(scale);
        scale = tthjettt_Norm/(tthjettt_->Integral());
        tthjettt_->Scale(scale);
        
        scale = qcd_Norm/(qcd_->Integral());
        qcd_->Scale(scale);
        
        scale = smh_Norm/(smh_->Integral());
        smh_->Scale(scale);
        scale = tt_Norm/(tt_->Integral());
        tt_->Scale(scale);
        scale = comb_Norm/(comb_->Integral());
        comb_->Scale(scale);
        
        scale = zp600a300_Norm/(zp600a300_->Integral());
        zp600a300_->Scale(scale);
        scale = zp600a400_Norm/(zp600a400_->Integral());
        zp600a400_->Scale(scale);
        scale = zp800a300_Norm/(zp800a300_->Integral());
        zp800a300_->Scale(scale);
        scale = zp800a400_Norm/(zp800a400_->Integral());
        zp800a400_->Scale(scale);
        scale = zp800a500_Norm/(zp800a500_->Integral());
        zp800a500_->Scale(scale);
        scale = zp800a600_Norm/(zp800a600_->Integral());
        zp800a600_->Scale(scale);
        scale = zp1000a300_Norm/(zp1000a300_->Integral());
        zp1000a300_->Scale(scale);
        scale = zp1000a400_Norm/(zp1000a400_->Integral());
        zp1000a400_->Scale(scale);
        scale = zp1000a500_Norm/(zp1000a500_->Integral());
        zp1000a500_->Scale(scale);
        scale = zp1000a600_Norm/(zp1000a600_->Integral());
        zp1000a600_->Scale(scale);
        scale = zp1000a700_Norm/(zp1000a700_->Integral());
        zp1000a700_->Scale(scale);
        scale = zp1000a800_Norm/(zp1000a800_->Integral());
        zp1000a800_->Scale(scale);
        scale = zp1200a300_Norm/(zp1200a300_->Integral());
        zp1200a300_->Scale(scale);
        scale = zp1200a400_Norm/(zp1200a400_->Integral());
        zp1200a400_->Scale(scale);
        scale = zp1200a500_Norm/(zp1200a500_->Integral());
        zp1200a500_->Scale(scale);
        scale = zp1200a600_Norm/(zp1200a600_->Integral());
        zp1200a600_->Scale(scale);
        scale = zp1200a700_Norm/(zp1200a700_->Integral());
        zp1200a700_->Scale(scale);
        scale = zp1200a800_Norm/(zp1200a800_->Integral());
        zp1200a800_->Scale(scale);
        scale = zp1400a300_Norm/(zp1400a300_->Integral());
        zp1400a300_->Scale(scale);
        scale = zp1400a400_Norm/(zp1400a400_->Integral());
        zp1400a400_->Scale(scale);
        scale = zp1400a500_Norm/(zp1400a500_->Integral());
        zp1400a500_->Scale(scale);
        scale = zp1400a600_Norm/(zp1400a600_->Integral());
        zp1400a600_->Scale(scale);
        scale = zp1400a700_Norm/(zp1400a700_->Integral());
        zp1400a700_->Scale(scale);
        scale = zp1400a800_Norm/(zp1400a800_->Integral());
        zp1400a800_->Scale(scale);
        scale = zp1700a300_Norm/(zp1700a300_->Integral());
        zp1700a300_->Scale(scale);
        scale = zp1700a400_Norm/(zp1700a400_->Integral());
        zp1700a400_->Scale(scale);
        scale = zp1700a500_Norm/(zp1700a500_->Integral());
        zp1700a500_->Scale(scale);
        scale = zp1700a600_Norm/(zp1700a600_->Integral());
        zp1700a600_->Scale(scale);
        scale = zp1700a700_Norm/(zp1700a700_->Integral());
        zp1700a700_->Scale(scale);
        scale = zp1700a800_Norm/(zp1700a800_->Integral());
        zp1700a800_->Scale(scale);
        scale = zp2000a300_Norm/(zp2000a300_->Integral());
        zp2000a300_->Scale(scale);
        scale = zp2000a400_Norm/(zp2000a400_->Integral());
        zp2000a400_->Scale(scale);
        scale = zp2000a500_Norm/(zp2000a500_->Integral());
        zp2000a500_->Scale(scale);
        scale = zp2000a600_Norm/(zp2000a600_->Integral());
        zp2000a600_->Scale(scale);
        scale = zp2000a700_Norm/(zp2000a700_->Integral());
        zp2000a700_->Scale(scale);
        scale = zp2000a800_Norm/(zp2000a800_->Integral());
        zp2000a800_->Scale(scale);
        scale = zp2500a300_Norm/(zp2500a300_->Integral());
        zp2500a300_->Scale(scale);
        scale = zp2500a400_Norm/(zp2500a400_->Integral());
        zp2500a400_->Scale(scale);
        scale = zp2500a500_Norm/(zp2500a500_->Integral());
        zp2500a500_->Scale(scale);
        scale = zp2500a600_Norm/(zp2500a600_->Integral());
        zp2500a600_->Scale(scale);
        scale = zp2500a700_Norm/(zp2500a700_->Integral());
        zp2500a700_->Scale(scale);
        scale = zp2500a800_Norm/(zp2500a800_->Integral());
        zp2500a800_->Scale(scale);
        
        scale = 1.0;
    }
   
    std::cout << "Editing Shape File" << std::endl;
    
	if(choice2==1 and createOutputShapes)
	{
		/* create a file to help with S/sqrt(S+B) cut opt */
        
        std::string paramName;
        if (parameter=="met" || parameter=="mvamet") {paramName = "met";}
        else if (parameter=="mt_tot" || parameter=="m_vis") {paramName = "mt";}
        else if (parameter.substr(0,6)=="mvaVar") {paramName = "mva";}
        
        std::string catName = chan + "_" + drCutNameMap[drCut];
		std::string optName = "htt_" + chan + ".inputs-13TeV-" + paramName + ".root";
		TFile sbOp(optName.c_str(),"UPDATE");
        
        TDirectory * catdir = sbOp.GetDirectory(catName.c_str());
        if (catdir){catdir->cd();}
        else {sbOp.mkdir(catName.c_str()); TDirectory * catdir = sbOp.GetDirectory(catName.c_str()); catdir->cd();}
        
        std::string DATAname = "data_obs" + syst;
        const char *DATAsave = DATAname.c_str();
        std::string VVname = "VV" + syst;
        const char *VVsave = VVname.c_str();
        std::string ZVVname = "ZVV" + syst;
        const char *ZVVsave = ZVVname.c_str();
        std::string EWKname = "EWK" + syst;
        const char *EWKsave = EWKname.c_str();
        std::string TTTname = "TTT" + syst;
        const char *TTTsave = TTTname.c_str();
        std::string TTJname = "TTJ" + syst;
        const char *TTJsave = TTJname.c_str();
        std::string ZTTname = "ZTT" + syst;
        const char *ZTTsave = ZTTname.c_str();
        std::string ZLname = "ZL" + syst;
        const char *ZLsave = ZLname.c_str();
        std::string ZJname = "ZJ" + syst;
        const char *ZJsave = ZJname.c_str();
        std::string Wname = "W" + syst;
        const char *Wsave = Wname.c_str();
        std::string QCDname = "QCD" + syst;
        const char *QCDsave = QCDname.c_str();
        std::string SMHname = "SMH" + syst;
        const char *SMHsave = SMHname.c_str();
        
        std::string combname = "comb" + syst;
        const char *combsave = combname.c_str();
        
        std::string ZprimeA300Zname = "Zprime" + syst + "A300";
        const char *ZprimeA300Zsave = ZprimeA300Zname.c_str();
        
        std::string Zprime600A300name = "Zprime600A300" + syst;
        const char *Zprime600A300save = Zprime600A300name.c_str();
        std::string Zprime600A400name = "Zprime600A400" + syst;
        const char *Zprime600A400save = Zprime600A400name.c_str();
        
        std::string Zprime800A300name = "Zprime800A300" + syst;
        const char *Zprime800A300save = Zprime800A300name.c_str();
        std::string Zprime800A400name = "Zprime800A400" + syst;
        const char *Zprime800A400save = Zprime800A400name.c_str();
        std::string Zprime800A500name = "Zprime800A500" + syst;
        const char *Zprime800A500save = Zprime800A500name.c_str();
        std::string Zprime800A600name = "Zprime800A600" + syst;
        const char *Zprime800A600save = Zprime800A600name.c_str();
        
        std::string Zprime1000A300name = "Zprime1000A300" + syst;
        const char *Zprime1000A300save = Zprime1000A300name.c_str();
        std::string Zprime1000A400name = "Zprime1000A400" + syst;
        const char *Zprime1000A400save = Zprime1000A400name.c_str();
        std::string Zprime1000A500name = "Zprime1000A500" + syst;
        const char *Zprime1000A500save = Zprime1000A500name.c_str();
        std::string Zprime1000A600name = "Zprime1000A600" + syst;
        const char *Zprime1000A600save = Zprime1000A600name.c_str();
        std::string Zprime1000A700name = "Zprime1000A700" + syst;
        const char *Zprime1000A700save = Zprime1000A700name.c_str();
        std::string Zprime1000A800name = "Zprime1000A800" + syst;
        const char *Zprime1000A800save = Zprime1000A800name.c_str();
        
        std::string Zprime1200A300name = "Zprime1200A300" + syst;
        const char *Zprime1200A300save = Zprime1200A300name.c_str();
        std::string Zprime1200A400name = "Zprime1200A400" + syst;
        const char *Zprime1200A400save = Zprime1200A400name.c_str();
        std::string Zprime1200A500name = "Zprime1200A500" + syst;
        const char *Zprime1200A500save = Zprime1200A500name.c_str();
        std::string Zprime1200A600name = "Zprime1200A600" + syst;
        const char *Zprime1200A600save = Zprime1200A600name.c_str();
        std::string Zprime1200A700name = "Zprime1200A700" + syst;
        const char *Zprime1200A700save = Zprime1200A700name.c_str();
        std::string Zprime1200A800name = "Zprime1200A800" + syst;
        const char *Zprime1200A800save = Zprime1200A800name.c_str();
        
        std::string Zprime1400A300name = "Zprime1400A300" + syst;
        const char *Zprime1400A300save = Zprime1400A300name.c_str();
        std::string Zprime1400A400name = "Zprime1400A400" + syst;
        const char *Zprime1400A400save = Zprime1400A400name.c_str();
        std::string Zprime1400A500name = "Zprime1400A500" + syst;
        const char *Zprime1400A500save = Zprime1400A500name.c_str();
        std::string Zprime1400A600name = "Zprime1400A600" + syst;
        const char *Zprime1400A600save = Zprime1400A600name.c_str();
        std::string Zprime1400A700name = "Zprime1400A700" + syst;
        const char *Zprime1400A700save = Zprime1400A700name.c_str();
        std::string Zprime1400A800name = "Zprime1400A800" + syst;
        const char *Zprime1400A800save = Zprime1400A800name.c_str();
        
        std::string Zprime1700A300name = "Zprime1700A300" + syst;
        const char *Zprime1700A300save = Zprime1700A300name.c_str();
        std::string Zprime1700A400name = "Zprime1700A400" + syst;
        const char *Zprime1700A400save = Zprime1700A400name.c_str();
        std::string Zprime1700A500name = "Zprime1700A500" + syst;
        const char *Zprime1700A500save = Zprime1700A500name.c_str();
        std::string Zprime1700A600name = "Zprime1700A600" + syst;
        const char *Zprime1700A600save = Zprime1700A600name.c_str();
        std::string Zprime1700A700name = "Zprime1700A700" + syst;
        const char *Zprime1700A700save = Zprime1700A700name.c_str();
        std::string Zprime1700A800name = "Zprime1700A800" + syst;
        const char *Zprime1700A800save = Zprime1700A800name.c_str();
        
        std::string Zprime2000A300name = "Zprime2000A300" + syst;
        const char *Zprime2000A300save = Zprime2000A300name.c_str();
        std::string Zprime2000A400name = "Zprime2000A400" + syst;
        const char *Zprime2000A400save = Zprime2000A400name.c_str();
        std::string Zprime2000A500name = "Zprime2000A500" + syst;
        const char *Zprime2000A500save = Zprime2000A500name.c_str();
        std::string Zprime2000A600name = "Zprime2000A600" + syst;
        const char *Zprime2000A600save = Zprime2000A600name.c_str();
        std::string Zprime2000A700name = "Zprime2000A700" + syst;
        const char *Zprime2000A700save = Zprime2000A700name.c_str();
        std::string Zprime2000A800name = "Zprime2000A800" + syst;
        const char *Zprime2000A800save = Zprime2000A800name.c_str();
        
        std::string Zprime2500A300name = "Zprime2500A300" + syst;
        const char *Zprime2500A300save = Zprime2500A300name.c_str();
        std::string Zprime2500A400name = "Zprime2500A400" + syst;
        const char *Zprime2500A400save = Zprime2500A400name.c_str();
        std::string Zprime2500A500name = "Zprime2500A500" + syst;
        const char *Zprime2500A500save = Zprime2500A500name.c_str();
        std::string Zprime2500A600name = "Zprime2500A600" + syst;
        const char *Zprime2500A600save = Zprime2500A600name.c_str();
        std::string Zprime2500A700name = "Zprime2500A700" + syst;
        const char *Zprime2500A700save = Zprime2500A700name.c_str();
        std::string Zprime2500A800name = "Zprime2500A800" + syst;
        const char *Zprime2500A800save = Zprime2500A800name.c_str();

        data_->Write(DATAsave);
        
        vv_->Write(VVsave);
        zvv_->Write(ZVVsave);
        ewk_->Write(EWKsave);
        ttt_->Write(TTTsave);
        ttj_->Write(TTJsave);
        ztt_->Write(ZTTsave);
        zl_->Write(ZLsave);
        zj_->Write(ZJsave);
        w_->Write(Wsave);
        qcd_->Write(QCDsave);
        
        smh_->Write(SMHsave);
        
		comb_->Write(combsave);

        if (syst == "600"){zp600a300_->Write(ZprimeA300Zsave);}
        else if (syst == "800"){zp800a300_->Write(ZprimeA300Zsave);}
        else if (syst == "1000"){zp1000a300_->Write(ZprimeA300Zsave);}
        else if (syst == "1200"){zp1200a300_->Write(ZprimeA300Zsave);}
        else
        {
            zp600a300_->Write(Zprime600A300save);
            zp600a400_->Write(Zprime600A400save);
            
            zp800a300_->Write(Zprime800A300save);
            zp800a400_->Write(Zprime800A400save);
            zp800a500_->Write(Zprime800A500save);
            zp800a600_->Write(Zprime800A600save);
            
            zp1000a300_->Write(Zprime1000A300save);
            zp1000a400_->Write(Zprime1000A400save);
            zp1000a500_->Write(Zprime1000A500save);
            zp1000a600_->Write(Zprime1000A600save);
            zp1000a700_->Write(Zprime1000A700save);
            zp1000a800_->Write(Zprime1000A800save);
            
            zp1200a300_->Write(Zprime1200A300save);
            zp1200a400_->Write(Zprime1200A400save);
            zp1200a500_->Write(Zprime1200A500save);
            zp1200a600_->Write(Zprime1200A600save);
            zp1200a700_->Write(Zprime1200A700save);
            zp1200a800_->Write(Zprime1200A800save);
            
            zp1400a300_->Write(Zprime1400A300save);
            zp1400a400_->Write(Zprime1400A400save);
            zp1400a500_->Write(Zprime1400A500save);
            zp1400a600_->Write(Zprime1400A600save);
            zp1400a700_->Write(Zprime1400A700save);
            zp1400a800_->Write(Zprime1400A800save);
            
            zp1700a300_->Write(Zprime1700A300save);
            zp1700a400_->Write(Zprime1700A400save);
            zp1700a500_->Write(Zprime1700A500save);
            zp1700a600_->Write(Zprime1700A600save);
            zp1700a700_->Write(Zprime1700A700save);
            zp1700a800_->Write(Zprime1700A800save);
            
            zp2000a300_->Write(Zprime2000A300save);
            zp2000a400_->Write(Zprime2000A400save);
            zp2000a500_->Write(Zprime2000A500save);
            zp2000a600_->Write(Zprime2000A600save);
            zp2000a700_->Write(Zprime2000A700save);
            zp2000a800_->Write(Zprime2000A800save);
            
            zp2500a300_->Write(Zprime2500A300save);
            zp2500a400_->Write(Zprime2500A400save);
            zp2500a500_->Write(Zprime2500A500save);
            zp2500a600_->Write(Zprime2500A600save);
            zp2500a700_->Write(Zprime2500A700save);
            zp2500a800_->Write(Zprime2500A800save);

        }

        sbOp.cd();
		sbOp.Close();
	}
    std::cout << "FINISHED editing shape file" << std::endl;
    
	/* delete pointers */
	delete data_;
	delete vv_;
    delete zvv_;
    delete ewk_;
	delete ttt_;
    delete ttj_;
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
    delete smh_;
	delete qcd_;
	delete zp600a300_;
    delete zp600a400_;
	delete zp800a300_;
    delete zp800a400_;
    delete zp800a500_;
    delete zp800a600_;
	delete zp1000a300_;
    delete zp1000a400_;
    delete zp1000a500_;
    delete zp1000a600_;
    delete zp1000a700_;
    delete zp1000a800_;
	delete zp1200a300_;
    delete zp1200a400_;
    delete zp1200a500_;
    delete zp1200a600_;
    delete zp1200a700_;
    delete zp1200a800_;
    delete zp1400a300_;
    delete zp1400a400_;
    delete zp1400a500_;
    delete zp1400a600_;
    delete zp1400a700_;
    delete zp1400a800_;
    delete zp1700a300_;
    delete zp1700a400_;
    delete zp1700a500_;
    delete zp1700a600_;
    delete zp1700a700_;
    delete zp1700a800_;
    delete zp2000a300_;
    delete zp2000a400_;
    delete zp2000a500_;
    delete zp2000a600_;
    delete zp2000a700_;
    delete zp2000a800_;
    delete zp2500a300_;
    delete zp2500a400_;
    delete zp2500a500_;
    delete zp2500a600_;
    delete zp2500a700_;
    delete zp2500a800_;

	delete Signal_region;
	delete sigMTstack;

}


void fillQCD_Shape(TCut SScut, double WnormForQCD, TH1F * QCDshape, std::string parameter, float bin[3], std::string can_name, std::string chan, bool plots)
{

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
	
	TH1F * ttt_ = new TH1F("ttt_","ttt_",bin[0],bin[1],bin[2]);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);
    
    TH1F * ttj_ = new TH1F("ttj_","ttj_",bin[0],bin[1],bin[2]);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",bin[0],bin[1],bin[2]);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",bin[0],bin[1],bin[2]);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
	
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

	/* fill the hists */
	if (plots) {QCD_SS->cd(1);}

	DATA->Draw((parameter+">>data_").c_str(),SScut);
	W->Draw((parameter+">>w_").c_str(),SScut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),SScut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),SScut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),SScut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),SScut*weights["VV"].c_str());
    ZVV->Draw((parameter+">>zvv_").c_str(),SScut*weights["ZVV"].c_str());
    EWK->Draw((parameter+">>ewk_").c_str(),SScut*weights["EWK"].c_str());
	TTT->Draw((parameter+">>ttt_").c_str(),SScut*weights["TTT"].c_str());
    TTJ->Draw((parameter+">>ttj_").c_str(),SScut*weights["TTJ"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),SScut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),SScut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),SScut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),SScut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),SScut*weights["ttHJetTT"].c_str());
    
	/* QCD is data - all mc bks */

	w_->Scale(WnormForQCD); /* scale this */
	qcd_->Add(data_);
	qcd_->Add(w_,-1);
	qcd_->Add(ztt_,-1);
    qcd_->Add(zl_,-1);
    qcd_->Add(zj_,-1);
	qcd_->Add(ttt_,-1);
    qcd_->Add(ttj_,-1);
	qcd_->Add(vv_,-1);
    qcd_->Add(zvv_,-1);
    qcd_->Add(ewk_,-1);
	qcd_->Add(zhtautau_,-1);
    qcd_->Add(whtautau_,-1);
    qcd_->Add(glugluhtautau_,-1);
    qcd_->Add(vbfhtautau_,-1);
    qcd_->Add(tthjettt_,-1);

    THStack * QCDStack  = new THStack();

    if (plots)
    {

        QCDStack->Add(zhtautau_);
        QCDStack->Add(whtautau_);
        QCDStack->Add(tthjettt_);
        QCDStack->Add(vbfhtautau_);
        QCDStack->Add(glugluhtautau_);
        QCDStack->Add(vv_);
        QCDStack->Add(zvv_);
        QCDStack->Add(ewk_);
        QCDStack->Add(ttt_);
        QCDStack->Add(ttj_);
        QCDStack->Add(w_);
        QCDStack->Add(ztt_);
        QCDStack->Add(zl_);
        QCDStack->Add(zj_);
        QCDStack->Add(qcd_);

        QCD_SS->cd(1);data_->SetMaximum(DATA_MAX*data_->GetMaximum());data_->SetTitle(";XXX;Events/Bin");data_->GetXaxis()->SetTitle(x_axisLabels[parameter].c_str());data_->DrawCopy("PE");QCDStack->Draw("histsames");data_->DrawCopy("PEsames");QCD_SS->Update();

        comb_->Add(vv_);
        comb_->Add(zvv_);
        comb_->Add(ewk_);
        comb_->Add(ttt_);
        comb_->Add(ttj_);
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

        drawTcanvasAndLegendAndRatio(QCD_SS, data_, comb_,0);QCD_SS->DrawClone();std::string localSaveName = "QCD_"+saveName + parameter + "_" + chan + "_" + drCutNameMap[drCut] + "Region.png";QCD_SS->cd()->SaveAs(localSaveName.c_str());QCD_SS->Close();
    }
    
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
	delete zvv_;
    delete ewk_;
    delete ttt_;
    delete ttj_;
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
	delete comb_;
	delete QCDStack;
	delete QCD_SS;
}

void fillQCD_ShapeVarBin(TCut SScut, double WnormForQCD, TH1F * QCDshape, std::string parameter, float bin[], std::string can_name, std::string chan, bool plots)
{
    int  binnum = binnum_mt_tot;

    /* create a TCanvas */
    TCanvas * QCD_SS = new TCanvas(can_name.c_str(),can_name.c_str(),canDim[0],canDim[1]);
    QCD_SS->Divide(1,2);
    
	/* create some histograms and format them */
	TH1F * data_ = new TH1F("data_","data_",binnum,bin); 
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",binnum,bin); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",binnum,bin);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",binnum,bin);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",binnum,bin);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",binnum,bin); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * ttt_ = new TH1F("ttt_","ttt_",binnum,bin);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);
    
    TH1F * ttj_ = new TH1F("ttj_","ttj_",binnum,bin);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",binnum,bin); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",binnum,bin);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",binnum,bin);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",binnum,bin);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",binnum,bin);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",binnum,bin);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",binnum,bin);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",binnum,bin);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);

	TH1F * comb_ = new TH1F("comb_","comb_",binnum,bin); 
	comb_->Sumw2();

	/* fill the hists */
	if (plots) {QCD_SS->cd(1);}

	DATA->Draw((parameter+">>data_").c_str(),SScut);
	W->Draw((parameter+">>w_").c_str(),SScut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),SScut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),SScut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),SScut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),SScut*weights["VV"].c_str());
    ZVV->Draw((parameter+">>zvv_").c_str(),SScut*weights["ZVV"].c_str());
    EWK->Draw((parameter+">>ewk_").c_str(),SScut*weights["EWK"].c_str());
	TTT->Draw((parameter+">>ttt_").c_str(),SScut*weights["TTT"].c_str());
    TTJ->Draw((parameter+">>ttj_").c_str(),SScut*weights["TTJ"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),SScut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),SScut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),SScut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),SScut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),SScut*weights["ttHJetTT"].c_str());

	/* QCD is data - all mc bks */

	w_->Scale(WnormForQCD); /* scale this */
	qcd_->Add(data_);
	qcd_->Add(w_,-1);
	qcd_->Add(ztt_,-1);
    qcd_->Add(zl_,-1);
    qcd_->Add(zj_,-1);
	qcd_->Add(ttt_,-1);
    qcd_->Add(ttj_,-1);
	qcd_->Add(vv_,-1);
    qcd_->Add(zvv_,-1);
    qcd_->Add(ewk_,-1);
	qcd_->Add(zhtautau_,-1);
    qcd_->Add(whtautau_,-1);
    qcd_->Add(glugluhtautau_,-1);
    qcd_->Add(vbfhtautau_,-1);
    qcd_->Add(tthjettt_,-1);

    THStack * QCDStack  = new THStack();

    if (plots)
    {

        QCDStack->Add(zhtautau_);
        QCDStack->Add(whtautau_);
        QCDStack->Add(tthjettt_);
        QCDStack->Add(vbfhtautau_);
        QCDStack->Add(glugluhtautau_);
        QCDStack->Add(vv_);
        QCDStack->Add(zvv_);
        QCDStack->Add(ewk_);
        QCDStack->Add(ttt_);
        QCDStack->Add(ttj_);
        QCDStack->Add(w_);
        QCDStack->Add(ztt_);
        QCDStack->Add(zl_);
        QCDStack->Add(zj_);
        QCDStack->Add(qcd_);

        QCD_SS->cd(1);data_->SetMaximum(DATA_MAX*data_->GetMaximum());data_->SetTitle(";XXX;Events/Bin");data_->GetXaxis()->SetTitle(x_axisLabels[parameter].c_str());data_->DrawCopy("PE");QCDStack->Draw("histsames");data_->DrawCopy("PEsames");QCD_SS->Update();

        comb_->Add(vv_);
        comb_->Add(zvv_);
        comb_->Add(ewk_);
        comb_->Add(ttt_);
        comb_->Add(ttj_);
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

        drawTcanvasAndLegendAndRatio(QCD_SS, data_, comb_,0);QCD_SS->DrawClone();std::string localSaveName = "QCD_"+saveName + parameter + "_" + chan + "_" + drCutNameMap[drCut] + "Region.png";QCD_SS->cd()->SaveAs(localSaveName.c_str());QCD_SS->Close();
    }
    
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
    delete zvv_;
    delete ewk_;
	delete ttt_;
    delete ttj_;
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
	delete comb_;
	delete QCDStack;
	delete QCD_SS;
}

double wjetsNorm(TCut wNormCut, std::string can_name)//not ready for 80X yet, may be used
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
	
	TH1F * ttj_ = new TH1F("ttj_","ttj_",mtBinning[0],mtBinning[1],mtBinning[2]);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);
    
    TH1F * ttt_ = new TH1F("ttt_","ttt_",mtBinning[0],mtBinning[1],mtBinning[2]);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",mtBinning[0],mtBinning[1],mtBinning[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",mtBinning[0],mtBinning[1],mtBinning[2]);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",mtBinning[0],mtBinning[1],mtBinning[2]);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
	
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

	/* fill the hists */
	wjetNorm_can->cd(1);

	DATA->Draw("mt_1>>data_",wNormCut);
    
	W->Draw("mt_1>>w_",wNormCut*weights["W"].c_str());
	ZTT->Draw("mt_1>>ztt_",wNormCut*weights["ZTT"].c_str());
    ZJ->Draw("mt_1>>zj_",wNormCut*weights["ZJ"].c_str());
    ZL->Draw("mt_1>>zl_",wNormCut*weights["ZL"].c_str());
	VV->Draw("mt_1>>vv_",wNormCut*weights["VV"].c_str());
    ZVV->Draw("mt_1>>zvv_",wNormCut*weights["ZVV"].c_str());
    EWK->Draw("mt_1>>ewk_",wNormCut*weights["EWK"].c_str());
	TTT->Draw("mt_1>>ttt_",wNormCut*weights["TTT"].c_str());
    TTJ->Draw("mt_1>>ttj_",wNormCut*weights["TTJ"].c_str());
	ZHTauTau->Draw("mt_1>>zhtautau_",wNormCut*weights["ZHTauTau"].c_str());
    WHTauTau->Draw("mt_1>>whtautau_",wNormCut*weights["WHTauTau"].c_str());
    GluGluHTauTau->Draw("mt_1>>glugluhtautau_",wNormCut*weights["GluGluHTauTau"].c_str());
    VBFHTauTau->Draw("mt_1>>vbfhtautau_",wNormCut*weights["VBFHTauTau"].c_str());
    ttHJetTT->Draw("mt_1>>tthjettt_",wNormCut*weights["ttHJetTT"].c_str());

	THStack * wnormStack  = new THStack();

	/* data minus all non-W */
	comb_->Add(data_);
    comb_->Add(vv_,-1);
    comb_->Add(zvv_,-1);
    comb_->Add(ewk_,-1);
	comb_->Add(ttt_,-1);
    comb_->Add(ttj_,-1);
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
    wnormStack->Add(zvv_);
    wnormStack->Add(ewk_);
	wnormStack->Add(ttt_);
    wnormStack->Add(ttj_);
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
    combSUM_->Add(zvv_);
    combSUM_->Add(ewk_);
	combSUM_->Add(ttt_);
    combSUM_->Add(ttj_);
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
    delete zvv_;
    delete ewk_;
	delete ttt_;
    delete ttj_;
	delete ztt_;
    delete zl_;
    delete zj_;
	delete w_;
    delete zhtautau_;
    delete whtautau_;
    delete glugluhtautau_;
    delete vbfhtautau_;
    delete tthjettt_;

	delete wnormStack;
	delete wjetNorm_can;

	return sf;
}


void countTotalsVarBin(TCut cut, double sf, TH1F * QCDshape, std::string parameter, float bin[], std::string can_name, std::string chan, std::string syst, bool plot, bool count, bool createOutputShapes)

{

    int  binnum = binnum_mt_tot;

    std::cout << "CUT: " << cut.GetTitle() << std::endl;

	/* check if want blinded signal region met tail */
    if (plot)
    {
        if(choice2==1 && (parameter=="mt_tot"))
        {
            global_title = "Signal Region with Blinded Tail";
        }
        if(choice2==1 && (parameter=="met" || parameter=="mvamet"))
        {
            global_title = "Signal Region with Blind MET Tail";
        }
        if(choice2==1 && sigChoice==2 && (chan=="mt"||chan=="et"))
        {
            global_title = "Signal Region in TMVA (blinded above 0.5)";
        }
    }
    
	/* create a TCanvas */
	TCanvas * Signal_region = new TCanvas(can_name.c_str(),can_name.c_str(),canDim[0],canDim[1]);
	Signal_region->Divide(1,2);

	/* create some histograms and format them */

	TH1F * data_ = new TH1F("data_","data_",binnum,bin);
	data_->Sumw2(); 
	data_->SetMarkerStyle(dataMarker);

	TH1F * qcd_ = new TH1F("qcd_","qcd_",binnum,bin); 
	qcd_->Sumw2(); 
	qcd_->SetFillColor(colors["QCD"]);

	TH1F * ztt_ = new TH1F("ztt_","ztt_",binnum,bin);
	ztt_->Sumw2();
	ztt_->SetFillColor(colors["ZTT"]);
    
    TH1F * zl_ = new TH1F("zl_","zl_",binnum,bin);
	zl_->Sumw2();
	zl_->SetFillColor(colors["ZL"]);
    
    TH1F * zj_ = new TH1F("zj_","zj_",binnum,bin);
	zj_->Sumw2();
	zj_->SetFillColor(colors["ZJ"]);
	
	TH1F * w_ = new TH1F("w_","w_",binnum,bin); 
	w_->Sumw2(); 
	w_->SetFillColor(colors["W"]);
	
	TH1F * ttj_ = new TH1F("ttj_","ttj_",binnum,bin);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);
    
    TH1F * ttt_ = new TH1F("ttt_","ttt_",binnum,bin);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);
    
    TH1F * tt_ = new TH1F("tt_","tt_",binnum,bin);
	tt_->Sumw2();
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",binnum,bin); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",binnum,bin);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",binnum,bin);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
	
	TH1F * zhtautau_ = new TH1F("zhtautau_","zhtautau_",binnum,bin);
	zhtautau_->Sumw2();
	zhtautau_->SetFillColor(colors["ZHTauTau"]);

	TH1F * glugluhtautau_ = new TH1F("glugluhtautau_","glugluhtautau_",binnum,bin);
	glugluhtautau_->Sumw2();
	glugluhtautau_->SetFillColor(colors["GluGluHTauTau"]);
    
    TH1F * vbfhtautau_ = new TH1F("vbfhtautau_","vbfhtautau_",binnum,bin);
	vbfhtautau_->Sumw2();
    vbfhtautau_->SetFillColor(colors["VBFHTauTau"]);
    
    TH1F * tthjettt_ = new TH1F("tthjettt_","tthjettt_",binnum,bin);
	tthjettt_->Sumw2();
    tthjettt_->SetFillColor(colors["ttHJetTT"]);
    
    TH1F * whtautau_ = new TH1F("whtautau_","whtautau_",binnum,bin);
	whtautau_->Sumw2();
    whtautau_->SetFillColor(colors["WHTauTau"]);
    
	TH1F * zp600a300_ = new TH1F("zp600a300_","zp600a300_",binnum,bin);
	zp600a300_->Sumw2();
    TH1F * zp600a400_ = new TH1F("zp600a400_","zp600a400_",binnum,bin);
	zp600a400_->Sumw2();

	TH1F * zp800a300_ = new TH1F("zp800a300_","zp800a300_",binnum,bin);
	zp800a300_->Sumw2();
    TH1F * zp800a400_ = new TH1F("zp800a400_","zp800a400_",binnum,bin);
	zp800a400_->Sumw2();
    TH1F * zp800a500_ = new TH1F("zp800a500_","zp800a500_",binnum,bin);
	zp800a500_->Sumw2();
    TH1F * zp800a600_ = new TH1F("zp800a600_","zp800a600_",binnum,bin);
	zp800a600_->Sumw2();

	TH1F * zp1000a300_ = new TH1F("zp1000a300_","zp1000a300_",binnum,bin);
	zp1000a300_->Sumw2();
    TH1F * zp1000a400_ = new TH1F("zp1000a400_","zp1000a400_",binnum,bin);
	zp1000a400_->Sumw2();
    TH1F * zp1000a500_ = new TH1F("zp1000a500_","zp1000a500_",binnum,bin);
	zp1000a500_->Sumw2();
    TH1F * zp1000a600_ = new TH1F("zp1000a600_","zp1000a600_",binnum,bin);
	zp1000a600_->Sumw2();
	TH1F * zp1000a700_ = new TH1F("zp1000a700_","zp1000a700_",binnum,bin);
	zp1000a700_->Sumw2();
    TH1F * zp1000a800_ = new TH1F("zp1000a800_","zp1000a800_",binnum,bin);
	zp1000a800_->Sumw2();
    
    TH1F * zp1200a300_ = new TH1F("zp1200a300_","zp1200a300_",binnum,bin);
	zp1200a300_->Sumw2();
    TH1F * zp1200a400_ = new TH1F("zp1200a400_","zp1200a400_",binnum,bin);
	zp1200a400_->Sumw2();
    TH1F * zp1200a500_ = new TH1F("zp1200a500_","zp1200a500_",binnum,bin);
	zp1200a500_->Sumw2();
    TH1F * zp1200a600_ = new TH1F("zp1200a600_","zp1200a600_",binnum,bin);
	zp1200a600_->Sumw2();
	TH1F * zp1200a700_ = new TH1F("zp1200a700_","zp1200a700_",binnum,bin);
	zp1200a700_->Sumw2();
    TH1F * zp1200a800_ = new TH1F("zp1200a800_","zp1200a800_",binnum,bin);
	zp1200a800_->Sumw2();
    
    TH1F * zp1400a300_ = new TH1F("zp1400a300_","zp1400a300_",binnum,bin);
	zp1400a300_->Sumw2();
    TH1F * zp1400a400_ = new TH1F("zp1400a400_","zp1400a400_",binnum,bin);
	zp1400a400_->Sumw2();
    TH1F * zp1400a500_ = new TH1F("zp1400a500_","zp1400a500_",binnum,bin);
	zp1400a500_->Sumw2();
    TH1F * zp1400a600_ = new TH1F("zp1400a600_","zp1400a600_",binnum,bin);
	zp1400a600_->Sumw2();
	TH1F * zp1400a700_ = new TH1F("zp1400a700_","zp1400a700_",binnum,bin);
	zp1400a700_->Sumw2();
    TH1F * zp1400a800_ = new TH1F("zp1400a800_","zp1400a800_",binnum,bin);
	zp1400a800_->Sumw2();
    
    TH1F * zp1700a300_ = new TH1F("zp1700a300_","zp1700a300_",binnum,bin);
	zp1700a300_->Sumw2();
    TH1F * zp1700a400_ = new TH1F("zp1700a400_","zp1700a400_",binnum,bin);
	zp1700a400_->Sumw2();
    TH1F * zp1700a500_ = new TH1F("zp1700a500_","zp1700a500_",binnum,bin);
	zp1700a500_->Sumw2();
    TH1F * zp1700a600_ = new TH1F("zp1700a600_","zp1700a600_",binnum,bin);
	zp1700a600_->Sumw2();
	TH1F * zp1700a700_ = new TH1F("zp1700a700_","zp1700a700_",binnum,bin);
	zp1700a700_->Sumw2();
    TH1F * zp1700a800_ = new TH1F("zp1700a800_","zp1700a800_",binnum,bin);
	zp1700a800_->Sumw2();
    
    TH1F * zp2000a300_ = new TH1F("zp2000a300_","zp2000a300_",binnum,bin);
	zp2000a300_->Sumw2();
    TH1F * zp2000a400_ = new TH1F("zp2000a400_","zp2000a400_",binnum,bin);
	zp2000a400_->Sumw2();
    TH1F * zp2000a500_ = new TH1F("zp2000a500_","zp2000a500_",binnum,bin);
	zp2000a500_->Sumw2();
    TH1F * zp2000a600_ = new TH1F("zp2000a600_","zp2000a600_",binnum,bin);
	zp2000a600_->Sumw2();
	TH1F * zp2000a700_ = new TH1F("zp2000a700_","zp2000a700_",binnum,bin);
	zp2000a700_->Sumw2();
    TH1F * zp2000a800_ = new TH1F("zp2000a800_","zp2000a800_",binnum,bin);
	zp2000a800_->Sumw2();
    
    TH1F * zp2500a300_ = new TH1F("zp2500a300_","zp2500a300_",binnum,bin);
	zp2500a300_->Sumw2();
    TH1F * zp2500a400_ = new TH1F("zp2500a400_","zp2500a400_",binnum,bin);
	zp2500a400_->Sumw2();
    TH1F * zp2500a500_ = new TH1F("zp2500a500_","zp2500a500_",binnum,bin);
	zp2500a500_->Sumw2();
    TH1F * zp2500a600_ = new TH1F("zp2500a600_","zp2500a600_",binnum,bin);
	zp2500a600_->Sumw2();
	TH1F * zp2500a700_ = new TH1F("zp2500a700_","zp2500a700_",binnum,bin);
	zp2500a700_->Sumw2();
    TH1F * zp2500a800_ = new TH1F("zp2500a800_","zp2500a800_",binnum,bin);
	zp2500a800_->Sumw2();

	/* sum of all bks */
	TH1F * comb_ = new TH1F("comb_","comb_",binnum,bin); 
	comb_->Sumw2(); 

	TH1F * smh_ = new TH1F("smh_","smh_",binnum,bin);
	smh_->Sumw2();
    smh_->SetFillColor(colors["SMH"]);

    
	W->Draw((parameter+">>w_").c_str(),cut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),cut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),cut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),cut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),cut*weights["VV"].c_str());
    ZVV->Draw((parameter+">>zvv_").c_str(),cut*weights["ZVV"].c_str());
    EWK->Draw((parameter+">>ewk_").c_str(),cut*weights["EWK"].c_str());
	TTT->Draw((parameter+">>ttt_").c_str(),cut*weights["TTT"].c_str());
    TTJ->Draw((parameter+">>ttj_").c_str(),cut*weights["TTJ"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),cut*weights["ZHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),cut*weights["ttHJetTT"].c_str());
    
    smh_->Add(zhtautau_);
    smh_->Add(tthjettt_);
    smh_->Add(glugluhtautau_);
    smh_->Add(vbfhtautau_);
    smh_->Add(whtautau_);
    
    tt_->Add(ttt_);
    tt_->Add(ttj_);
    
	MZP600_MA0300->Draw((parameter+">>zp600a300_").c_str(),cut*weights["MONO"].c_str());
    MZP600_MA0400->Draw((parameter+">>zp600a400_").c_str(),cut*weights["MONO"].c_str());
    
	MZP800_MA0300->Draw((parameter+">>zp800a300_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0400->Draw((parameter+">>zp800a400_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0500->Draw((parameter+">>zp800a500_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0600->Draw((parameter+">>zp800a600_").c_str(),cut*weights["MONO"].c_str());
    
	MZP1000_MA0300->Draw((parameter+">>zp1000a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0400->Draw((parameter+">>zp1000a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0500->Draw((parameter+">>zp1000a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0600->Draw((parameter+">>zp1000a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0700->Draw((parameter+">>zp1000a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0800->Draw((parameter+">>zp1000a800_").c_str(),cut*weights["MONO"].c_str());
    
    MZP1200_MA0300->Draw((parameter+">>zp1200a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0400->Draw((parameter+">>zp1200a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0500->Draw((parameter+">>zp1200a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0600->Draw((parameter+">>zp1200a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0700->Draw((parameter+">>zp1200a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0800->Draw((parameter+">>zp1200a800_").c_str(),cut*weights["MONO"].c_str());

	MZP1400_MA0300->Draw((parameter+">>zp1400a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0400->Draw((parameter+">>zp1400a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0500->Draw((parameter+">>zp1400a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0600->Draw((parameter+">>zp1400a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0700->Draw((parameter+">>zp1400a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0800->Draw((parameter+">>zp1400a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP1700_MA0300->Draw((parameter+">>zp1700a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0400->Draw((parameter+">>zp1700a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0500->Draw((parameter+">>zp1700a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0600->Draw((parameter+">>zp1700a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0700->Draw((parameter+">>zp1700a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0800->Draw((parameter+">>zp1700a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP2000_MA0300->Draw((parameter+">>zp2000a300_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0400->Draw((parameter+">>zp2000a400_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0500->Draw((parameter+">>zp2000a500_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0600->Draw((parameter+">>zp2000a600_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0700->Draw((parameter+">>zp2000a700_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0800->Draw((parameter+">>zp2000a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP2500_MA0300->Draw((parameter+">>zp2500a300_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0400->Draw((parameter+">>zp2500a400_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0500->Draw((parameter+">>zp2500a500_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0600->Draw((parameter+">>zp2500a600_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0700->Draw((parameter+">>zp2500a700_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0800->Draw((parameter+">>zp2500a800_").c_str(),cut*weights["MONO"].c_str());
    
	qcd_->Add(QCDshape);
	qcd_->Scale(qcdOStoSS);
	w_->Scale(sf);

    comb_->Add(vv_);
    comb_->Add(zvv_);
    comb_->Add(ewk_);
	comb_->Add(ttt_);
    comb_->Add(ttj_);
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
    
	// scale things to the projected lumi
	vv_->Scale(lumi_sf);
    zvv_->Scale(lumi_sf);
    ewk_->Scale(lumi_sf);
	ttt_->Scale(lumi_sf);
    ttj_->Scale(lumi_sf);
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
    smh_->Scale(lumi_sf);
    
	zp600a300_->Scale(lumi_sf);
    zp600a400_->Scale(lumi_sf);
	zp800a300_->Scale(lumi_sf);
    zp800a400_->Scale(lumi_sf);
    zp800a500_->Scale(lumi_sf);
    zp800a600_->Scale(lumi_sf);
	zp1000a300_->Scale(lumi_sf);
    zp1000a400_->Scale(lumi_sf);
    zp1000a500_->Scale(lumi_sf);
    zp1000a600_->Scale(lumi_sf);
    zp1000a700_->Scale(lumi_sf);
    zp1000a800_->Scale(lumi_sf);
	zp1200a300_->Scale(lumi_sf);
    zp1200a400_->Scale(lumi_sf);
    zp1200a500_->Scale(lumi_sf);
    zp1200a600_->Scale(lumi_sf);
    zp1200a700_->Scale(lumi_sf);
    zp1200a800_->Scale(lumi_sf);
    zp1400a300_->Scale(lumi_sf);
    zp1400a400_->Scale(lumi_sf);
    zp1400a500_->Scale(lumi_sf);
    zp1400a600_->Scale(lumi_sf);
    zp1400a700_->Scale(lumi_sf);
    zp1400a800_->Scale(lumi_sf);
	zp1700a300_->Scale(lumi_sf);
    zp1700a400_->Scale(lumi_sf);
    zp1700a500_->Scale(lumi_sf);
    zp1700a600_->Scale(lumi_sf);
    zp1700a700_->Scale(lumi_sf);
    zp1700a800_->Scale(lumi_sf);
	zp2000a300_->Scale(lumi_sf);
    zp2000a400_->Scale(lumi_sf);
    zp2000a500_->Scale(lumi_sf);
    zp2000a600_->Scale(lumi_sf);
    zp2000a700_->Scale(lumi_sf);
    zp2000a800_->Scale(lumi_sf);
	zp2500a300_->Scale(lumi_sf);
    zp2500a400_->Scale(lumi_sf);
    zp2500a500_->Scale(lumi_sf);
    zp2500a600_->Scale(lumi_sf);
    zp2500a700_->Scale(lumi_sf);
    zp2500a800_->Scale(lumi_sf);
    
	comb_->Scale(lumi_sf);
    
    // print signal region bkg yields (under whatever cut is provided)

    std::cout<<" bkg totals under "<<can_name<<"\n";

    double error = 0;

    error = 0;
    vv_->IntegralAndError(-1,1e3, error);
    std::cout<<" VV ... "<<vv_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zvv_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZVV ... "<< zvv_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    ewk_->IntegralAndError(-1,1e3, error);
    std::cout<<" EWK ... "<< ewk_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    ttt_->IntegralAndError(-1,1e3, error);
    std::cout<<" TTT ... "<<ttt_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    ttj_->IntegralAndError(-1,1e3, error);
    std::cout<<" TTJ ... "<<ttj_->Integral()<<" +/- "<<error<<"\n";

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
    error = sqrt(qcd_->GetEntries());
    std::cout<<" QCD ... "<<qcd_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp600a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP600 ... "<<zp600a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp800a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP800 ... "<<zp800a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp1000a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1000 ... "<<zp1000a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp1200a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1200 ... "<<zp1200a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp1400a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1400 ... "<<zp1400a300_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zp1700a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1700 ... "<<zp1700a300_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zp2000a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP2000 ... "<<zp2000a300_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zp2500a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP2500 ... "<<zp2500a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    comb_->IntegralAndError(-1,1e3, error);
    std::cout<<" totalBkg ... "<<comb_->Integral()<<" +/- "<<error<<"\n";

    // test

    double mvaChoiceI;
    double mvaChoiceE;

    double wI, wE;
    double vvI, vvE;
    double zvvI, zvvE;
    double ewkI, ewkE;
    double zttI, zttE;
    double zlI, zlE;
    double zjI, zjE;
    double qcdI, qcdE;
    double tttI, tttE;
    double ttjI, ttjE;
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
    double zp1700I, zp1700E;
    double zp2000I, zp2000E;
    double zp2500I, zp2500E;

    zp600I = zp600a300_->Integral(-1, zp600a300_->GetNbinsX()+1);
    zp600a300_->IntegralAndError(-1, zp600a300_->GetNbinsX()+1,zp600E);

    zp800I = zp800a300_->Integral(-1, zp800a300_->GetNbinsX()+1);
    zp800a300_->IntegralAndError(-1, zp800a300_->GetNbinsX()+1,zp800E);

    zp1000I = zp1000a300_->Integral(-1, zp1000a300_->GetNbinsX()+1);
    zp1000a300_->IntegralAndError(-1, zp1000a300_->GetNbinsX()+1,zp1000E);

    zp1200I = zp1200a300_->Integral(-1, zp1200a300_->GetNbinsX()+1);
    zp1200a300_->IntegralAndError(-1, zp1200a300_->GetNbinsX()+1,zp1200E);

    zp1400I = zp1400a300_->Integral(-1, zp1400a300_->GetNbinsX()+1);
    zp1400a300_->IntegralAndError(-1, zp1400a300_->GetNbinsX()+1,zp1400E);
    
    zp1700I = zp1700a300_->Integral(-1, zp1700a300_->GetNbinsX()+1);
    zp1700a300_->IntegralAndError(-1, zp1700a300_->GetNbinsX()+1,zp1700E);
    
    zp2000I = zp2000a300_->Integral(-1, zp2000a300_->GetNbinsX()+1);
    zp2000a300_->IntegralAndError(-1, zp2000a300_->GetNbinsX()+1,zp2000E);
    
    zp2500I = zp2500a300_->Integral(-1, zp2500a300_->GetNbinsX()+1);
    zp2500a300_->IntegralAndError(-1, zp2500a300_->GetNbinsX()+1,zp2500E);

    wI = w_->Integral(-1, w_->GetNbinsX()+1);
    w_->IntegralAndError(-1, w_->GetNbinsX()+1,wE);

    vvI = vv_->Integral(-1, vv_->GetNbinsX()+1);
    vv_->IntegralAndError(-1, vv_->GetNbinsX()+1,vvE);
    
    zvvI = zvv_->Integral(-1, zvv_->GetNbinsX()+1);
    zvv_->IntegralAndError(-1, zvv_->GetNbinsX()+1,zvvE);
    
    ewkI = ewk_->Integral(-1, ewk_->GetNbinsX()+1);
    ewk_->IntegralAndError(-1, ewk_->GetNbinsX()+1,ewkE);

    zttI = ztt_->Integral(-1, ztt_->GetNbinsX()+1);
    ztt_->IntegralAndError(-1, ztt_->GetNbinsX()+1,zttE);
    
    zlI = zl_->Integral(-1, zl_->GetNbinsX()+1);
    zl_->IntegralAndError(-1, zl_->GetNbinsX()+1,zlE);
    
    zjI = zj_->Integral(-1, zj_->GetNbinsX()+1);
    zj_->IntegralAndError(-1, zj_->GetNbinsX()+1,zjE);

    qcdI = qcd_->Integral(-1, qcd_->GetNbinsX()+1);
    qcd_->IntegralAndError(-1, qcd_->GetNbinsX()+1,qcdE);

    tttI = ttt_->Integral(-1, ttt_->GetNbinsX()+1);
    ttt_->IntegralAndError(-1, ttt_->GetNbinsX()+1,tttE);
    
    ttjI = ttj_->Integral(-1, ttj_->GetNbinsX()+1);
    ttj_->IntegralAndError(-1, ttj_->GetNbinsX()+1,ttjE);

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

    if(wI>0.0){ wE = 1 + wE/wI; } else {wI = 0.0; wE = 1.0;}
    if(vvI>0.0){ vvE = 1 + vvE/vvI; } else {vvI = 0.0; vvE = 1.0;}
    if(zvvI>0.0){ zvvE = 1 + zvvE/zvvI; } else {zvvI = 0.0; zvvE = 1.0;}
    if(ewkI>0.0){ ewkE = 1 + ewkE/ewkI; } else {ewkI = 0.0; ewkE = 1.0;}
    if(zttI>0.0){ zttE = 1 + zttE/zttI; } else {zttI = 0.0; zttE = 1.0;}
    if(zlI>0.0){ zlE = 1 + zlE/zlI; } else {zlI = 0.0; zlE = 1.0;}
    if(zjI>0.0){ zjE = 1 + zjE/zjI; } else {zjI = 0.0; zjE = 1.0;}
    if(qcdI>0.0){ qcdE = 1 + qcdE/qcdI; } else {qcdI = 0.0; qcdE = 1.0;}
    if(tttI>0.0){ tttE = 1 + tttE/tttI; } else {tttI = 0.0; tttE = 1.0;}
    if(ttjI>0.0){ ttjE = 1 + ttjE/ttjI; } else {ttjI = 0.0; ttjE = 1.0;}
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
    if(zp1700I>0.0){ zp1700E = 1 + zp1700E/zp1700I; } else {zp1700I = 0.0; zp1700E = 1.0;}
    if(zp2000I>0.0){ zp2000E = 1 + zp2000E/zp2000I; } else {zp2000I = 0.0; zp2000E = 1.0;}
    if(zp2500I>0.0){ zp2500E = 1 + zp2500E/zp2500I; } else {zp2500I = 0.0; zp2500E = 1.0;}
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 600 s/rt(b) = "<<zp600I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 800 s/rt(b) = "<<zp800I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1000 s/rt(b) = "<<zp1000I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1200 s/rt(b) = "<<zp1200I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1400 s/rt(b) = "<<zp1400I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1700 s/rt(b) = "<<zp1700I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 2000 s/rt(b) = "<<zp2000I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 2500 s/rt(b) = "<<zp2500I/sqrt(comb_->Integral())<<"\n";

    //out_data
    if (choice2==1 && sigChoice==2 && (chan=="mt" || chan=="et"))
    {
        if (parameter.substr(15,4)=="600A"){mvaChoiceI = zp600I; mvaChoiceE = zp600E; }
        if (parameter.substr(15,4)=="800A"){mvaChoiceI = zp800I; mvaChoiceE = zp800E; }
        if (parameter.substr(15,4)=="1000"){mvaChoiceI = zp1000I; mvaChoiceE = zp1000E; }
        if (parameter.substr(15,4)=="1200"){mvaChoiceI = zp1200I; mvaChoiceE = zp1200E; }
        
        out_data << "QUANTITY       SIGNAL     W     VV     ZVV     EWK     ZTT     ZJ     ZL     QCD     tt     ZHTauTau     WHTauTau     GluGluHTauTau     VBFHTauTau     ttHJetTT" << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + parameter.substr(10,16) + " rate        " << mvaChoiceI << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + parameter.substr(10,16) + " stat.err    " << mvaChoiceE << "     " << wE << "     " << vvE << "     " << zvvI << "     " << ewkI << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << ttjE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
    }
    else if (choice2==1)
    {
    
        out_data << "QUANTITY       SIGNAL     W     VV     ZVV     EWK     ZTT     ZJ     ZL     QCD     tt     ZHTauTau     WHTauTau     GluGluHTauTau     VBFHTauTau     ttHJetTT" << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP600 rate        " << zp600I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP600 stat.err    " << zp600E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP800 rate        " << zp800I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP800 stat.err    " << zp800E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP1000 rate        " << zp1000I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP1000 stat.err    " << zp1000E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP1200 rate        " << zp1200I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP1200 stat.err    " << zp1200E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        }
    }

void countTotals(TCut cut, double sf, TH1F * QCDshape, std::string parameter, float bin[3], std::string can_name, std::string chan, std::string syst, bool plot, bool count, bool createOutputShapes)
{
    std::cout << "CUT: " << cut.GetTitle() << std::endl;

	/* check if want blinded signal region met tail */
    if (plot)
    {
        if(choice2==1 && (parameter=="mt_tot"))
        {
            global_title = "Signal Region with Blinded Tail";
        }
        if(choice2==1 && (parameter=="met" || parameter=="mvamet"))
        {
            global_title = "Signal Region with Blind MET Tail";
        }
        if(choice2==1 && sigChoice==2 && (chan=="mt"||chan=="et"))
        {
            global_title = "Signal Region in TMVA (blinded above 0.5)";
        }
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
	
	TH1F * ttj_ = new TH1F("ttj_","ttj_",bin[0],bin[1],bin[2]);
	ttj_->Sumw2();
	ttj_->SetFillColor(colors["TTJ"]);
    
    TH1F * ttt_ = new TH1F("ttt_","ttt_",bin[0],bin[1],bin[2]);
	ttt_->Sumw2();
	ttt_->SetFillColor(colors["TTT"]);
    
    TH1F * tt_ = new TH1F("tt_","tt_",bin[0],bin[1],bin[2]);
	tt_->Sumw2();
	tt_->SetFillColor(colors["TT"]);
	
	TH1F * vv_ = new TH1F("vv_","vv_",bin[0],bin[1],bin[2]); 
	vv_->Sumw2(); 
	vv_->SetFillColor(colors["VV"]);
    
    TH1F * zvv_ = new TH1F("zvv_","zvv_",bin[0],bin[1],bin[2]);
	zvv_->Sumw2();
	zvv_->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk_ = new TH1F("ewk_","ewk_",bin[0],bin[1],bin[2]);
	ewk_->Sumw2();
	ewk_->SetFillColor(colors["EWK"]);
	
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
    
	TH1F * zp600a300_ = new TH1F("zp600a300_","zp600a300_",bin[0],bin[1],bin[2]);
	zp600a300_->Sumw2();
    TH1F * zp600a400_ = new TH1F("zp600a400_","zp600a400_",bin[0],bin[1],bin[2]);
	zp600a400_->Sumw2();

	TH1F * zp800a300_ = new TH1F("zp800a300_","zp800a300_",bin[0],bin[1],bin[2]);
	zp800a300_->Sumw2();
    TH1F * zp800a400_ = new TH1F("zp800a400_","zp800a400_",bin[0],bin[1],bin[2]);
	zp800a400_->Sumw2();
    TH1F * zp800a500_ = new TH1F("zp800a500_","zp800a500_",bin[0],bin[1],bin[2]);
	zp800a500_->Sumw2();
    TH1F * zp800a600_ = new TH1F("zp800a600_","zp800a600_",bin[0],bin[1],bin[2]);
	zp800a600_->Sumw2();

	TH1F * zp1000a300_ = new TH1F("zp1000a300_","zp1000a300_",bin[0],bin[1],bin[2]);
	zp1000a300_->Sumw2();
    TH1F * zp1000a400_ = new TH1F("zp1000a400_","zp1000a400_",bin[0],bin[1],bin[2]);
	zp1000a400_->Sumw2();
    TH1F * zp1000a500_ = new TH1F("zp1000a500_","zp1000a500_",bin[0],bin[1],bin[2]);
	zp1000a500_->Sumw2();
    TH1F * zp1000a600_ = new TH1F("zp1000a600_","zp1000a600_",bin[0],bin[1],bin[2]);
	zp1000a600_->Sumw2();
	TH1F * zp1000a700_ = new TH1F("zp1000a700_","zp1000a700_",bin[0],bin[1],bin[2]);
	zp1000a700_->Sumw2();
    TH1F * zp1000a800_ = new TH1F("zp1000a800_","zp1000a800_",bin[0],bin[1],bin[2]);
	zp1000a800_->Sumw2();
    
    TH1F * zp1200a300_ = new TH1F("zp1200a300_","zp1200a300_",bin[0],bin[1],bin[2]);
	zp1200a300_->Sumw2();
    TH1F * zp1200a400_ = new TH1F("zp1200a400_","zp1200a400_",bin[0],bin[1],bin[2]);
	zp1200a400_->Sumw2();
    TH1F * zp1200a500_ = new TH1F("zp1200a500_","zp1200a500_",bin[0],bin[1],bin[2]);
	zp1200a500_->Sumw2();
    TH1F * zp1200a600_ = new TH1F("zp1200a600_","zp1200a600_",bin[0],bin[1],bin[2]);
	zp1200a600_->Sumw2();
	TH1F * zp1200a700_ = new TH1F("zp1200a700_","zp1200a700_",bin[0],bin[1],bin[2]);
	zp1200a700_->Sumw2();
    TH1F * zp1200a800_ = new TH1F("zp1200a800_","zp1200a800_",bin[0],bin[1],bin[2]);
	zp1200a800_->Sumw2();
    
    TH1F * zp1400a300_ = new TH1F("zp1400a300_","zp1400a300_",bin[0],bin[1],bin[2]);
	zp1400a300_->Sumw2();
    TH1F * zp1400a400_ = new TH1F("zp1400a400_","zp1400a400_",bin[0],bin[1],bin[2]);
	zp1400a400_->Sumw2();
    TH1F * zp1400a500_ = new TH1F("zp1400a500_","zp1400a500_",bin[0],bin[1],bin[2]);
	zp1400a500_->Sumw2();
    TH1F * zp1400a600_ = new TH1F("zp1400a600_","zp1400a600_",bin[0],bin[1],bin[2]);
	zp1400a600_->Sumw2();
	TH1F * zp1400a700_ = new TH1F("zp1400a700_","zp1400a700_",bin[0],bin[1],bin[2]);
	zp1400a700_->Sumw2();
    TH1F * zp1400a800_ = new TH1F("zp1400a800_","zp1400a800_",bin[0],bin[1],bin[2]);
	zp1400a800_->Sumw2();
    
    TH1F * zp1700a300_ = new TH1F("zp1700a300_","zp1700a300_",bin[0],bin[1],bin[2]);
	zp1700a300_->Sumw2();
    TH1F * zp1700a400_ = new TH1F("zp1700a400_","zp1700a400_",bin[0],bin[1],bin[2]);
	zp1700a400_->Sumw2();
    TH1F * zp1700a500_ = new TH1F("zp1700a500_","zp1700a500_",bin[0],bin[1],bin[2]);
	zp1700a500_->Sumw2();
    TH1F * zp1700a600_ = new TH1F("zp1700a600_","zp1700a600_",bin[0],bin[1],bin[2]);
	zp1700a600_->Sumw2();
	TH1F * zp1700a700_ = new TH1F("zp1700a700_","zp1700a700_",bin[0],bin[1],bin[2]);
	zp1700a700_->Sumw2();
    TH1F * zp1700a800_ = new TH1F("zp1700a800_","zp1700a800_",bin[0],bin[1],bin[2]);
	zp1700a800_->Sumw2();
    
    TH1F * zp2000a300_ = new TH1F("zp2000a300_","zp2000a300_",bin[0],bin[1],bin[2]);
	zp2000a300_->Sumw2();
    TH1F * zp2000a400_ = new TH1F("zp2000a400_","zp2000a400_",bin[0],bin[1],bin[2]);
	zp2000a400_->Sumw2();
    TH1F * zp2000a500_ = new TH1F("zp2000a500_","zp2000a500_",bin[0],bin[1],bin[2]);
	zp2000a500_->Sumw2();
    TH1F * zp2000a600_ = new TH1F("zp2000a600_","zp2000a600_",bin[0],bin[1],bin[2]);
	zp2000a600_->Sumw2();
	TH1F * zp2000a700_ = new TH1F("zp2000a700_","zp2000a700_",bin[0],bin[1],bin[2]);
	zp2000a700_->Sumw2();
    TH1F * zp2000a800_ = new TH1F("zp2000a800_","zp2000a800_",bin[0],bin[1],bin[2]);
	zp2000a800_->Sumw2();
    
    TH1F * zp2500a300_ = new TH1F("zp2500a300_","zp2500a300_",bin[0],bin[1],bin[2]);
	zp2500a300_->Sumw2();
    TH1F * zp2500a400_ = new TH1F("zp2500a400_","zp2500a400_",bin[0],bin[1],bin[2]);
	zp2500a400_->Sumw2();
    TH1F * zp2500a500_ = new TH1F("zp2500a500_","zp2500a500_",bin[0],bin[1],bin[2]);
	zp2500a500_->Sumw2();
    TH1F * zp2500a600_ = new TH1F("zp2500a600_","zp2500a600_",bin[0],bin[1],bin[2]);
	zp2500a600_->Sumw2();
	TH1F * zp2500a700_ = new TH1F("zp2500a700_","zp2500a700_",bin[0],bin[1],bin[2]);
	zp2500a700_->Sumw2();
    TH1F * zp2500a800_ = new TH1F("zp2500a800_","zp2500a800_",bin[0],bin[1],bin[2]);
	zp2500a800_->Sumw2();

	/* sum of all bks */
	TH1F * comb_ = new TH1F("comb_","comb_",bin[0],bin[1],bin[2]); 
	comb_->Sumw2(); 

	TH1F * smh_ = new TH1F("smh_","smh_",bin[0],bin[1],bin[2]);
	smh_->Sumw2();
    smh_->SetFillColor(colors["SMH"]);

	W->Draw((parameter+">>w_").c_str(),cut*weights["W"].c_str());
	ZTT->Draw((parameter+">>ztt_").c_str(),cut*weights["ZTT"].c_str());
    ZL->Draw((parameter+">>zl_").c_str(),cut*weights["ZL"].c_str());
    ZJ->Draw((parameter+">>zj_").c_str(),cut*weights["ZJ"].c_str());
	VV->Draw((parameter+">>vv_").c_str(),cut*weights["VV"].c_str());
    ZVV->Draw((parameter+">>zvv_").c_str(),cut*weights["ZVV"].c_str());
    EWK->Draw((parameter+">>ewk_").c_str(),cut*weights["EWK"].c_str());
	TTT->Draw((parameter+">>ttt_").c_str(),cut*weights["TTT"].c_str());
    TTJ->Draw((parameter+">>ttj_").c_str(),cut*weights["TTJ"].c_str());
	ZHTauTau->Draw((parameter+">>zhtautau_").c_str(),cut*weights["ZHTauTau"].c_str());
    VBFHTauTau->Draw((parameter+">>vbfhtautau_").c_str(),cut*weights["VBFHTauTau"].c_str());
    GluGluHTauTau->Draw((parameter+">>glugluhtautau_").c_str(),cut*weights["GluGluHTauTau"].c_str());
    WHTauTau->Draw((parameter+">>whtautau_").c_str(),cut*weights["WHTauTau"].c_str());
    ttHJetTT->Draw((parameter+">>tthjettt_").c_str(),cut*weights["ttHJetTT"].c_str());
    
    smh_->Add(zhtautau_);
    smh_->Add(tthjettt_);
    smh_->Add(glugluhtautau_);
    smh_->Add(vbfhtautau_);
    smh_->Add(whtautau_);
    
    tt_->Add(ttt_);
    tt_->Add(ttj_);
    
	MZP600_MA0300->Draw((parameter+">>zp600a300_").c_str(),cut*weights["MONO"].c_str());
    MZP600_MA0400->Draw((parameter+">>zp600a400_").c_str(),cut*weights["MONO"].c_str());
    
	MZP800_MA0300->Draw((parameter+">>zp800a300_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0400->Draw((parameter+">>zp800a400_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0500->Draw((parameter+">>zp800a500_").c_str(),cut*weights["MONO"].c_str());
    MZP800_MA0600->Draw((parameter+">>zp800a600_").c_str(),cut*weights["MONO"].c_str());
    
	MZP1000_MA0300->Draw((parameter+">>zp1000a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0400->Draw((parameter+">>zp1000a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0500->Draw((parameter+">>zp1000a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0600->Draw((parameter+">>zp1000a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0700->Draw((parameter+">>zp1000a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1000_MA0800->Draw((parameter+">>zp1000a800_").c_str(),cut*weights["MONO"].c_str());
    
    MZP1200_MA0300->Draw((parameter+">>zp1200a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0400->Draw((parameter+">>zp1200a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0500->Draw((parameter+">>zp1200a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0600->Draw((parameter+">>zp1200a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0700->Draw((parameter+">>zp1200a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1200_MA0800->Draw((parameter+">>zp1200a800_").c_str(),cut*weights["MONO"].c_str());

	MZP1400_MA0300->Draw((parameter+">>zp1400a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0400->Draw((parameter+">>zp1400a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0500->Draw((parameter+">>zp1400a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0600->Draw((parameter+">>zp1400a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0700->Draw((parameter+">>zp1400a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1400_MA0800->Draw((parameter+">>zp1400a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP1700_MA0300->Draw((parameter+">>zp1700a300_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0400->Draw((parameter+">>zp1700a400_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0500->Draw((parameter+">>zp1700a500_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0600->Draw((parameter+">>zp1700a600_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0700->Draw((parameter+">>zp1700a700_").c_str(),cut*weights["MONO"].c_str());
    MZP1700_MA0800->Draw((parameter+">>zp1700a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP2000_MA0300->Draw((parameter+">>zp2000a300_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0400->Draw((parameter+">>zp2000a400_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0500->Draw((parameter+">>zp2000a500_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0600->Draw((parameter+">>zp2000a600_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0700->Draw((parameter+">>zp2000a700_").c_str(),cut*weights["MONO"].c_str());
    MZP2000_MA0800->Draw((parameter+">>zp2000a800_").c_str(),cut*weights["MONO"].c_str());
    
	MZP2500_MA0300->Draw((parameter+">>zp2500a300_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0400->Draw((parameter+">>zp2500a400_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0500->Draw((parameter+">>zp2500a500_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0600->Draw((parameter+">>zp2500a600_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0700->Draw((parameter+">>zp2500a700_").c_str(),cut*weights["MONO"].c_str());
    MZP2500_MA0800->Draw((parameter+">>zp2500a800_").c_str(),cut*weights["MONO"].c_str());
    
	qcd_->Add(QCDshape);
	qcd_->Scale(qcdOStoSS);
	w_->Scale(sf);

    comb_->Add(vv_);
    comb_->Add(zvv_);
    comb_->Add(ewk_);
	comb_->Add(ttt_);
    comb_->Add(ttj_);
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
    
	// scale things to the projected lumi
	vv_->Scale(lumi_sf);
    zvv_->Scale(lumi_sf);
    ewk_->Scale(lumi_sf);
	ttt_->Scale(lumi_sf);
    ttj_->Scale(lumi_sf);
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
    smh_->Scale(lumi_sf);
    
	zp600a300_->Scale(lumi_sf);
    zp600a400_->Scale(lumi_sf);
	zp800a300_->Scale(lumi_sf);
    zp800a400_->Scale(lumi_sf);
    zp800a500_->Scale(lumi_sf);
    zp800a600_->Scale(lumi_sf);
	zp1000a300_->Scale(lumi_sf);
    zp1000a400_->Scale(lumi_sf);
    zp1000a500_->Scale(lumi_sf);
    zp1000a600_->Scale(lumi_sf);
    zp1000a700_->Scale(lumi_sf);
    zp1000a800_->Scale(lumi_sf);
	zp1200a300_->Scale(lumi_sf);
    zp1200a400_->Scale(lumi_sf);
    zp1200a500_->Scale(lumi_sf);
    zp1200a600_->Scale(lumi_sf);
    zp1200a700_->Scale(lumi_sf);
    zp1200a800_->Scale(lumi_sf);
    zp1400a300_->Scale(lumi_sf);
    zp1400a400_->Scale(lumi_sf);
    zp1400a500_->Scale(lumi_sf);
    zp1400a600_->Scale(lumi_sf);
    zp1400a700_->Scale(lumi_sf);
    zp1400a800_->Scale(lumi_sf);
	zp1700a300_->Scale(lumi_sf);
    zp1700a400_->Scale(lumi_sf);
    zp1700a500_->Scale(lumi_sf);
    zp1700a600_->Scale(lumi_sf);
    zp1700a700_->Scale(lumi_sf);
    zp1700a800_->Scale(lumi_sf);
	zp2000a300_->Scale(lumi_sf);
    zp2000a400_->Scale(lumi_sf);
    zp2000a500_->Scale(lumi_sf);
    zp2000a600_->Scale(lumi_sf);
    zp2000a700_->Scale(lumi_sf);
    zp2000a800_->Scale(lumi_sf);
	zp2500a300_->Scale(lumi_sf);
    zp2500a400_->Scale(lumi_sf);
    zp2500a500_->Scale(lumi_sf);
    zp2500a600_->Scale(lumi_sf);
    zp2500a700_->Scale(lumi_sf);
    zp2500a800_->Scale(lumi_sf);
    
	comb_->Scale(lumi_sf);
    
    // print signal region bkg yields (under whatever cut is provided)

    std::cout<<" bkg totals under "<<can_name<<"\n";

    double error = 0;

    error = 0;
    vv_->IntegralAndError(-1,1e3, error);
    std::cout<<" VV ... "<<vv_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zvv_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZVV ... "<< zvv_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    ewk_->IntegralAndError(-1,1e3, error);
    std::cout<<" EWK ... "<< ewk_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    ttt_->IntegralAndError(-1,1e3, error);
    std::cout<<" TTT ... "<<ttt_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    ttj_->IntegralAndError(-1,1e3, error);
    std::cout<<" TTJ ... "<<ttj_->Integral()<<" +/- "<<error<<"\n";

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
    error = sqrt(qcd_->GetEntries());
    std::cout<<" QCD ... "<<qcd_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp600a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP600 ... "<<zp600a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp800a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP800 ... "<<zp800a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp1000a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1000 ... "<<zp1000a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp1200a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1200 ... "<<zp1200a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    zp1400a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1400 ... "<<zp1400a300_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zp1700a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP1700 ... "<<zp1700a300_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zp2000a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP2000 ... "<<zp2000a300_->Integral()<<" +/- "<<error<<"\n";
    
    error = 0;
    zp2500a300_->IntegralAndError(-1,1e3, error);
    std::cout<<" ZP2500 ... "<<zp2500a300_->Integral()<<" +/- "<<error<<"\n";

    error = 0;
    comb_->IntegralAndError(-1,1e3, error);
    std::cout<<" totalBkg ... "<<comb_->Integral()<<" +/- "<<error<<"\n";

    // test

    double mvaChoiceI;
    double mvaChoiceE;

    double wI, wE;
    double vvI, vvE;
    double zvvI, zvvE;
    double ewkI, ewkE;
    double zttI, zttE;
    double zlI, zlE;
    double zjI, zjE;
    double qcdI, qcdE;
    double tttI, tttE;
    double ttjI, ttjE;
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
    double zp1700I, zp1700E;
    double zp2000I, zp2000E;
    double zp2500I, zp2500E;

    zp600I = zp600a300_->Integral(-1, zp600a300_->GetNbinsX()+1);
    zp600a300_->IntegralAndError(-1, zp600a300_->GetNbinsX()+1,zp600E);

    zp800I = zp800a300_->Integral(-1, zp800a300_->GetNbinsX()+1);
    zp800a300_->IntegralAndError(-1, zp800a300_->GetNbinsX()+1,zp800E);

    zp1000I = zp1000a300_->Integral(-1, zp1000a300_->GetNbinsX()+1);
    zp1000a300_->IntegralAndError(-1, zp1000a300_->GetNbinsX()+1,zp1000E);

    zp1200I = zp1200a300_->Integral(-1, zp1200a300_->GetNbinsX()+1);
    zp1200a300_->IntegralAndError(-1, zp1200a300_->GetNbinsX()+1,zp1200E);

    zp1400I = zp1400a300_->Integral(-1, zp1400a300_->GetNbinsX()+1);
    zp1400a300_->IntegralAndError(-1, zp1400a300_->GetNbinsX()+1,zp1400E);
    
    zp1700I = zp1700a300_->Integral(-1, zp1700a300_->GetNbinsX()+1);
    zp1700a300_->IntegralAndError(-1, zp1700a300_->GetNbinsX()+1,zp1700E);
    
    zp2000I = zp2000a300_->Integral(-1, zp2000a300_->GetNbinsX()+1);
    zp2000a300_->IntegralAndError(-1, zp2000a300_->GetNbinsX()+1,zp2000E);
    
    zp2500I = zp2500a300_->Integral(-1, zp2500a300_->GetNbinsX()+1);
    zp2500a300_->IntegralAndError(-1, zp2500a300_->GetNbinsX()+1,zp2500E);

    wI = w_->Integral(-1, w_->GetNbinsX()+1);
    w_->IntegralAndError(-1, w_->GetNbinsX()+1,wE);

    vvI = vv_->Integral(-1, vv_->GetNbinsX()+1);
    vv_->IntegralAndError(-1, vv_->GetNbinsX()+1,vvE);
    
    zvvI = zvv_->Integral(-1, zvv_->GetNbinsX()+1);
    zvv_->IntegralAndError(-1, zvv_->GetNbinsX()+1,zvvE);
    
    ewkI = ewk_->Integral(-1, ewk_->GetNbinsX()+1);
    ewk_->IntegralAndError(-1, ewk_->GetNbinsX()+1,ewkE);

    zttI = ztt_->Integral(-1, ztt_->GetNbinsX()+1);
    ztt_->IntegralAndError(-1, ztt_->GetNbinsX()+1,zttE);
    
    zlI = zl_->Integral(-1, zl_->GetNbinsX()+1);
    zl_->IntegralAndError(-1, zl_->GetNbinsX()+1,zlE);
    
    zjI = zj_->Integral(-1, zj_->GetNbinsX()+1);
    zj_->IntegralAndError(-1, zj_->GetNbinsX()+1,zjE);

    qcdI = qcd_->Integral(-1, qcd_->GetNbinsX()+1);
    qcd_->IntegralAndError(-1, qcd_->GetNbinsX()+1,qcdE);

    tttI = ttt_->Integral(-1, ttt_->GetNbinsX()+1);
    ttt_->IntegralAndError(-1, ttt_->GetNbinsX()+1,tttE);
    
    ttjI = ttj_->Integral(-1, ttj_->GetNbinsX()+1);
    ttj_->IntegralAndError(-1, ttj_->GetNbinsX()+1,ttjE);

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

    if(wI>0.0){ wE = 1 + wE/wI; } else {wI = 0.0; wE = 1.0;}
    if(vvI>0.0){ vvE = 1 + vvE/vvI; } else {vvI = 0.0; vvE = 1.0;}
    if(zvvI>0.0){ zvvE = 1 + zvvE/zvvI; } else {zvvI = 0.0; zvvE = 1.0;}
    if(ewkI>0.0){ ewkE = 1 + ewkE/ewkI; } else {ewkI = 0.0; ewkE = 1.0;}
    if(zttI>0.0){ zttE = 1 + zttE/zttI; } else {zttI = 0.0; zttE = 1.0;}
    if(zlI>0.0){ zlE = 1 + zlE/zlI; } else {zlI = 0.0; zlE = 1.0;}
    if(zjI>0.0){ zjE = 1 + zjE/zjI; } else {zjI = 0.0; zjE = 1.0;}
    if(qcdI>0.0){ qcdE = 1 + qcdE/qcdI; } else {qcdI = 0.0; qcdE = 1.0;}
    if(tttI>0.0){ tttE = 1 + tttE/tttI; } else {tttI = 0.0; tttE = 1.0;}
    if(ttjI>0.0){ ttjE = 1 + ttjE/ttjI; } else {ttjI = 0.0; ttjE = 1.0;}
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
    if(zp1700I>0.0){ zp1700E = 1 + zp1700E/zp1700I; } else {zp1700I = 0.0; zp1700E = 1.0;}
    if(zp2000I>0.0){ zp2000E = 1 + zp2000E/zp2000I; } else {zp2000I = 0.0; zp2000E = 1.0;}
    if(zp2500I>0.0){ zp2500E = 1 + zp2500E/zp2500I; } else {zp2500I = 0.0; zp2500E = 1.0;}
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 600 s/rt(b) = "<<zp600I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 800 s/rt(b) = "<<zp800I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1000 s/rt(b) = "<<zp1000I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1200 s/rt(b) = "<<zp1200I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1400 s/rt(b) = "<<zp1400I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 1700 s/rt(b) = "<<zp1700I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 2000 s/rt(b) = "<<zp2000I/sqrt(comb_->Integral())<<"\n";
    if(comb_->Integral()!=0) std::cout<<" @ ZP = 2500 s/rt(b) = "<<zp2500I/sqrt(comb_->Integral())<<"\n";

    //out_data
    if (choice2==1 && sigChoice==2 && (chan=="mt" || chan=="et"))
    {
        if (parameter.substr(15,4)=="600A"){mvaChoiceI = zp600I; mvaChoiceE = zp600E; }
        if (parameter.substr(15,4)=="800A"){mvaChoiceI = zp800I; mvaChoiceE = zp800E; }
        if (parameter.substr(15,4)=="1000"){mvaChoiceI = zp1000I; mvaChoiceE = zp1000E; }
        if (parameter.substr(15,4)=="1200"){mvaChoiceI = zp1200I; mvaChoiceE = zp1200E; }
        
        out_data << "QUANTITY       SIGNAL     W     VV     ZVV     EWK     ZTT     ZJ     ZL     QCD     tt     ZHTauTau     WHTauTau     GluGluHTauTau     VBFHTauTau     ttHJetTT" << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + parameter.substr(10,16) + " rate        " << mvaChoiceI << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + parameter.substr(10,16) + " stat.err    " << mvaChoiceE << "     " << wE << "     " << vvE << "     " << zvvI << "     " << ewkI << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << ttjE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
    }
    else if (choice2==1)
    {
    
        out_data << "QUANTITY       SIGNAL     W     VV     ZVV     EWK     ZTT     ZJ     ZL     QCD     tt     ZHTauTau     WHTauTau     GluGluHTauTau     VBFHTauTau     ttHJetTT" << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP600 rate        " << zp600I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP600 stat.err    " << zp600E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP800 rate        " << zp800I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP800 stat.err    " << zp800E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP1000 rate        " << zp1000I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP1000 stat.err    " << zp1000E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
        
        out_data << drCutNameMap[drCut] + chan + "ZP1200 rate        " << zp1200I << "     " << wI << "     " << vvI << "     " << zvvI << "     " << ewkI << "     " << zttI << "     " << zjI << "     " << zlI << "     " << qcdI << "     " << tttI << "     " << ttjI << "     " << zhtautauI << "     " << whtautauI << "     " << glugluhtautauI << "     " << vbfhtautauI << "     " << tthjetttI << std::endl;
        out_data << drCutNameMap[drCut] + chan + "ZP1200 stat.err    " << zp1200E << "     " << wE << "     " << vvE << "     " << zvvE << "     " << ewkE << "     " << zttE << "     " << zjE << "     " << zlE << "     " << qcdE << "     " << tttE << "     " << ttjE << "     " << zhtautauE << "     " << whtautauE << "     " << glugluhtautauE << "     " << vbfhtautauE << "     " << tthjetttE << std::endl;
    }
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
    
    TH1F * zvv__ = new TH1F("zvv__","zvv__",mtBinning[0],mtBinning[1],mtBinning[2]);
	zvv__->SetFillColor(colors["ZVV"]);
    
    TH1F * ewk__ = new TH1F("ewk__","ewk__",mtBinning[0],mtBinning[1],mtBinning[2]);
	ewk__->SetFillColor(colors["EWK"]);
	
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
    
    TH1F * smh__ = new TH1F("smh__","smh__",mtBinning[0],mtBinning[1],mtBinning[2]);
    smh__->SetFillColor(colors["SMH"]);
    
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
    leg.AddEntry(zvv__, "Z invisible","F");
    leg.AddEntry(ewk__, "EWK","F");
    leg.AddEntry(tt__, "t#bar{t}","F");
    if (splitPlotSMH)
    {
        leg.AddEntry(zhtautau__, "ZHTauTau(125 GeV)","F");
        leg.AddEntry(whtautau__, "WHTauTau(125 GeV)","F");
        leg.AddEntry(glugluhtautau__, "GluGluHTauTau(125 GeV)","F");
        leg.AddEntry(vbfhtautau__, "VBFHTauTau(125 GeV)","F");
        leg.AddEntry(tthjettt__, "ttHJetTT(125 GeV)","F");
    }
    else {leg.AddEntry(smh__, "SM Higgs(125 GeV)","F");}\
    
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

    zp600__->SetLineStyle(2);
	zp800__->SetLineStyle(2);
	zp1000__->SetLineStyle(2);
	zp1200__->SetLineStyle(2);
	zp1400__->SetLineStyle(2);
    
    zp600__->SetLineWidth(3);
	zp800__->SetLineWidth(3);
	zp1000__->SetLineWidth(3);
	zp1200__->SetLineWidth(3);
	zp1400__->SetLineWidth(3);

	zp600__->SetLineColor(50);
	zp800__->SetLineColor(60);
	zp1000__->SetLineColor(70);
    zp1200__->SetLineColor(80);
	zp1400__->SetLineColor(6);

	if(shouldIplotSignals && drawSignals)
	{
	    TLegend legDM(.45,.55,.75,.85);
	    legDM.SetTextSize(.03);
	    legDM.SetTextFont(22);
	    legDM.SetBorderSize(0);
	    legDM.SetFillStyle(0);

        legDM.AddEntry(zp600__, "[m_{Z'},m_{A0},m_{#chi}] = [600,400,100] GeV @ 1pb","L");
        legDM.AddEntry(zp800__, "[m_{Z'},m_{A0},m_{#chi}] = [800,400,100] GeV @ 1pb","L");
        legDM.AddEntry(zp1000__, "[m_{Z'},m_{A0},m_{#chi}] = [1000,400,100] GeV @ 1pb","L");
        legDM.AddEntry(zp1200__, "[m_{Z'},m_{A0},m_{#chi}] = [1200,400,100] GeV @ 1pb","L");
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
    delete zvv__;
    delete ewk__;
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
    delete smh__;
	delete qcd__;
    delete zp600__;
	delete zp800__;
	delete zp1000__;
	delete zp1200__;
	delete zp1400__;
	delete ratio__;



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


