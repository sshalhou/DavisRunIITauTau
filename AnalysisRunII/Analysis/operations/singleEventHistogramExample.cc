#include "singleEventHistogramExample.h"


singleEventHistogramExample::singleEventHistogramExample(FlatTreeReader R_, bool run_)
{
	run = run_;
	R = R_;

	if(run)
	{

	outFile = new TFile("twoDhistograms.root","RECREATE");
	manyEvents = new TH2F("2D_manyEvents","2D_manyEvents",25,0,500,25,0,500);
	manyEvents->Sumw2();
	

	}

	else
	{
		outFile = nullptr;		
		manyEvents = nullptr;
	}

}



void singleEventHistogramExample::finish()
{
	if(run)
	{
		outFile->cd();
		for(std::size_t x = 0; x<the_histograms.size();++x )
		{
			the_histograms[x]->Write();

		} 
		manyEvents->Write();
		outFile->Close();
	}
}

singleEventHistogramExample::~singleEventHistogramExample()
{

	if(!run) /* Close on the outFile deletes the TH1F pointers */
	{
		delete manyEvents;

	}	
	delete outFile;

};	

void singleEventHistogramExample::handleEvent()
{

    // we will only do anything for the 1st 500 events
	if(the_histograms.size() > 500) return;

	// so now we have a new event; we will do the following 
    // (1) create a new 2D histogram
    // (2) make sure the name reflects the event number
    // (3) fill the quantities we are interested in
    // (4) push it to our vector of histogram pointers

	std::string histogram_name = std::to_string(R.getUI("run"))+"_"+std::to_string(R.getUI("event"));
	histogram_name = histogram_name + std::to_string(R.getUI("luminosityBlock")) + "_2D_histogram";


	if( R.getI("CandidateEventType") == 2)  histogram_name = histogram_name + "_eleMuon";
	if( R.getI("CandidateEventType") == 3)  histogram_name = histogram_name + "_eleTau";
	if( R.getI("CandidateEventType") == 5)  histogram_name = histogram_name + "_muTau";
	if( R.getI("CandidateEventType") == 6)  histogram_name = histogram_name + "_tauTau";


	TH2F * aHist = new TH2F(histogram_name.c_str(),histogram_name.c_str(),25,0,500,25,0,500);
	aHist->Sumw2();
	aHist->Fill(R.getD("pfMET"),R.getD("leg1_pt"));
	manyEvents->Fill(R.getD("pfMET"),R.getD("leg1_pt"));

    the_histograms.push_back((TH2F*)aHist->Clone(histogram_name.c_str()));
    delete aHist;
}



