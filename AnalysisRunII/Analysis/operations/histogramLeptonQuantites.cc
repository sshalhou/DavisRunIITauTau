#include "histogramLeptonQuantites.h"


histogramLeptonQuantites::histogramLeptonQuantites(FlatTreeReader R_, bool run_)
{
	run = run_;
	R = R_;

	if(run)
	{

	outFile = new TFile("leptonQuantities.root","RECREATE");
	muon_pt = new TH1F("muon_pt"," pT of #mu for #mu+#tau_{h}; pT [GeV]; Events/10 GeV",25,0,250);
	electron_pt = new TH1F("electron_pt"," pT of e for e+#tau_{h}; pT [GeV]; Events/10 GeV",25,0,250);
	tau_pt_inETau  = new TH1F("tau_pt_inETau"," pT of #tau_{h} for e+#tau_{h}; pT [GeV]; Events/10 GeV",25,0,250);
	tau_pt_inMuTau = new TH1F("tau_pt_inMuTau"," pT of #tau_{h} for #mu+#tau_{h}; pT [GeV]; Events/10 GeV",25,0,250);

	muon_pt->Sumw2();
	electron_pt->Sumw2();
	tau_pt_inETau->Sumw2();
	tau_pt_inMuTau->Sumw2();
	
	}

	else
	{
		outFile = nullptr;
		muon_pt = nullptr;
		electron_pt = nullptr;
		tau_pt_inETau = nullptr;
		tau_pt_inMuTau = nullptr;
	}

}



void histogramLeptonQuantites::finish()
{
	if(run)
	{
		outFile->cd();
		muon_pt->Write();
		electron_pt->Write();
		tau_pt_inETau->Write();
		tau_pt_inMuTau->Write();
		outFile->Close();
	}
}

histogramLeptonQuantites::~histogramLeptonQuantites()
{
	if(!run) /* Close on the outFile deletes the TH1F pointers */
	{
		delete muon_pt;
		delete electron_pt;
		delete tau_pt_inETau;
		delete tau_pt_inMuTau;
	}	
	delete outFile;
	

};	

void histogramLeptonQuantites::handleEvent()
{

	if(R.getI("CandidateEventType")==5) /* see TupleCandidateEventTypes */
	{
		muon_pt->Fill(R.getD("leg1_pt"));	
		tau_pt_inMuTau->Fill(R.getD("leg2_pt"));	

	}

	else if(R.getI("CandidateEventType")==3)
	{
		electron_pt->Fill(R.getD("leg1_pt"));	
		tau_pt_inETau->Fill(R.getD("leg2_pt"));	

	}

}



