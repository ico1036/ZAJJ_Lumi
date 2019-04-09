#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "TH2F.h"
#include "TChain.h"
#include "TMath.h"
#include "TString.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"
using namespace std;


//void runSig(double CutDEta , double CutZepp, double num[2],double Lumi, double Mjjcut) {
void runSig(double CutDEta, double CutZepp, double num[2],double Lumi,double Mjjcut) {

	
	TChain* inChain = new TChain("tree");
	inChain->Add("Signal.root");
	inChain->Add("BKGs.root");


    int    nttype ;
    double ntxsec ;
    double ntgenN ;
    double ntzepp ;
    double ntmjj  ;
    double ntdEta ;
    double ntdPhi ;
    inChain->SetBranchAddress("nttype", &nttype);
    inChain->SetBranchAddress("ntxsec", &ntxsec);
    inChain->SetBranchAddress("ntgenN", &ntgenN);
    inChain->SetBranchAddress("ntzepp", &ntzepp);
    inChain->SetBranchAddress("ntmjj" , &ntmjj );
    inChain->SetBranchAddress("ntdEta", &ntdEta);
    inChain->SetBranchAddress("ntdPhi", &ntdPhi);

	double NumSig = 0.0;
	double NumBkg = 0.0;
	
// --Apply kinematic cuts and Normalize
	for(int i=0; i<inChain->GetEntries() ; i++) {
		inChain->GetEntry(i);
		
		if(ntmjj < Mjjcut) continue;
		if(ntdEta < CutDEta || ntzepp > CutZepp ) continue;

		if(nttype == 0) NumSig += ntxsec * Lumi / ntgenN ;
		if(nttype >  0) {NumBkg += ntxsec * Lumi / ntgenN ;
		}
	
	}
	
	//h2->Fill(CutDEta,CutZepp,nSig);
	num[0]=NumSig;
	num[1]=NumBkg;

}


int main(int argc, char** argv) {
	if(argc==1) { cout << "error no input" << endl;}

	double Lumi = atof(argv[1]); // --Set the Luminosity
	double Mjjcut=atof(argv[2]); // --Set the Mjj cut
	
	 

	TH2F *hNsig = new TH2F("hNsig","Number of Signal",20, 2.0, 4.0, 30, 0.0,3.0 );
	TH2F *hNBKG = new TH2F("hNBKG","Number of BKG",20, 2.0, 4.0, 30, 0.0,3.0 );
	TH2F *hSignificance = new TH2F("hSignificance","Significance",20, 2.0, 4.0, 30, 0.0,3.0 );
	
	for(int i=0; i<21; i++) {
		for(int j=0; j<31; j++) {
			
			double CutDEta = 2.0+i * 0.1; // 
			double Cutzepp = 0.1 * j;
		double num[2];
		//runSig(CutDEta,Cutzepp,num);
		runSig(CutDEta,Cutzepp,num,Lumi,Mjjcut);
		
		
		hNsig->SetBinContent(i, j, roundf(num[0]*100)/100);
		hNsig->GetYaxis()->SetTitle("ZeppCut");
	    hNsig->GetXaxis()->SetTitle("DeltaEtaCut");

		hNBKG->SetBinContent(i, j, roundf(num[1]*100)/100);
		hNBKG->GetYaxis()->SetTitle("ZeppCut");
   		hNBKG->GetXaxis()->SetTitle("DeltaEtaCut");
	
		//double Nsig = num[0]/TMath::Sqrt(num[1]+num[0]);  // --Calculate significance  (s)/sqrt(s+b)
		double Nsig = num[0]/TMath::Sqrt(num[1]);			// --Calculate significance  (s)/sqrt(b)
		if(num[1] > 0) {
		hSignificance->SetBinContent(i, j,roundf(Nsig*100)/100); 
		hSignificance->GetYaxis()->SetTitle("Zeppenfeld variable Cut");
   		hSignificance->GetXaxis()->SetTitle("#Delta#eta_{jj}Cut");
	
		}

		//Fill(CutDEta, Cutzepp-0.05, num[0]);
	 }
	}




/////////-- This code will find the maximum significance and following #ofBKG, #ofSignal, cutDEta, cutzepp
// --Calculate the max significance in the 2-D map
	double MaxSig = hSignificance->GetBinContent(hSignificance->GetMaximumBin()); 

// --You can pick the multiple Max points,
// By using the flag, you can pick one of them. (the first one)
// You can modify this algorithms for more performance
	bool flag=0;

	for(int i=0; i<21; i++) {
		for(int j=0; j<31; j++) {
			if(hSignificance->GetBinContent(i,j) == MaxSig){
			// Luminosity, #ofBKG, #ofSignal, cutDEta, cutzepp, Significance
			cout << Lumi/1000 << "				" << hNBKG->GetBinContent(i,j) << "				   " << hNsig->GetBinContent(i,j) << "				  " << 2+i *0.1 << "			" <<  0.1*j <<  "			"<< MaxSig << endl;
				flag=1;			
				break;
			}
		}
		if(flag==1) break;
	}
////////////////////////////////////


/*	
	TCanvas* c1 = new TCanvas();
	gStyle->SetOptStat(0);
	hNsig->Draw("colz text");
	TCanvas* c2 = new TCanvas();
	gStyle->SetOptStat(0);
	hNBKG->Draw("colz text");
	TCanvas* c3 = new TCanvas();
	gStyle->SetOptStat(0);
	hSignificance->Draw("colz text");


c1->cd();
	 TLatex latex;
     latex.SetNDC();
     latex.SetTextSize(0.04);
     latex.SetTextAlign(11);
     latex.DrawLatex(0.64,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));
c2->cd();
     latex.DrawLatex(0.64,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));
c3->cd();
     latex.DrawLatex(0.64,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));

c1->Print("NSignal_35.9_400.png");
c2->Print("NBKG_35.9_400.png");
c3->Print("NSignificance_35.9_400.png");
*/


}
