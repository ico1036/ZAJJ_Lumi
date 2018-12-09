#include "TMath.h"


void draw() {

double XMIN = -1;
double XMAX = -1;
long YMAX   = 60000;
int   rebin = 5;

bool addDYJet = false ;
bool addZGToL = true  ;
bool addTTJet = true ;

//const double Lumi         = 100000.0;
const double Lumi         = 35900.0;

const double xsecSingleAntiTop    = 28.25;
const double xsecSingleTop    = 28.25;
const double xsecWW           = 65.46;
const double xsecWZm          = 9.322;
const double xsecWZp          = 15.45;
const double xsecZZ           = 9.339;
const double xsectta2jets     = 6.551 ;
const double xsecz2eea        = 8.571;
const double xsecz2eejj       = 1050.0 ;
//const double xseczajets       = 10.14 ;
const double xsecZA					= 7.650008	;
const double xsecZAj				= 2.633324933;
const double xsecZAjj_M120to600		= 0.500694208;
const double xsecZAjj_M600to1000	= 0.025923520;
const double xsecZAjj_M1000			= 0.008208708;

const double xsecSignal       = 0.01228 ;

addZGToL=false;
//TString dirname = "step1_v1"; addZGToL=false;
//TString dirname = "step1_v3"; addZGToL=false; YMAX=6000000000;
//TString dirname = "step1_v4"; addZGToL=false; YMAX=6000000000;
//TString dirname = "step2_v2";
//TString dirname = "step2_v2";   addDYJet = false; YMAX=6000000;
//TString dirname = "step2_v3";   addDYJet = false; YMAX=6000000;
//TString dirname = "step3_v1";
//TString dirname = "step3_v";
//TString dirname = "step3_noMjjcut";
TString dirname = "step3_Anal";

TFile *fSingleAntiTop = TFile::Open(dirname +"/SingleAntiTop.root") 	;
TFile *fSingleTop 	  = TFile::Open(dirname +"/SingleTop.root") 		;
TFile *fWW 			  = TFile::Open(dirname +"/WW.root") 				;
TFile *fWZp 		  = TFile::Open(dirname +"/WpZ.root") 				;
TFile *fWZm 		  = TFile::Open(dirname +"/WmZ.root") 				;
TFile *fZZ 			  = TFile::Open(dirname +"/ZZ.root") 				;
TFile *ftta2jets 	  = TFile::Open(dirname +"/tta2jets.root") 			;
//TFile *fzajets 	  = TFile::Open(dirname +"/ZAjets.root") 			;

TFile *fZA				= TFile::Open(dirname +"/bkg_main/bkg_ZA.root")					;	
TFile *fZAj				= TFile::Open(dirname +"/bkg_main/bkg_ZAj.root")					;
TFile *fZAjj_M120to600 	= TFile::Open(dirname +"/bkg_main/bkg_ZAjj_M120t0600.root") 		;
TFile *fZAjj_M600to1000 = TFile::Open(dirname +"/bkg_main/bkg_ZAjj_M600to1000.root") 	;
TFile *fZAjj_M1000		= TFile::Open(dirname +"/bkg_main/bkg_ZAjjM_1000.root") 			;

TFile *fSignal 	      = TFile::Open(dirname +"/Signal.root")		;

TString TitleName;
TString AxisTitleName;

//Electron//
//TString histname = "h1_ele1PT"; XMAX=300; XMIN=25; rebin=20; YMAX=100; 
//TString histname = "h1_ele2PT"; XMAX=300; XMIN=25; rebin=20;YMAX=100;
//TString histname = "h1_eePt"; XMAX=600; XMIN=0; rebin=30;YMAX = 1000;
//TString histname = "h1_eeM"; XMAX=120; XMIN=60; YMAX=10000; rebin=10; TitleName="Mass(Dilepton)";AxisTitleName="M_{ll} (GeV)";

//photon//
//TString histname = "h1_eeaM"; XMAX=200; XMIN=70; rebin =32 ;YMAX=10000; TitleName="Mass(Dilepton+photon)";AxisTitleName="M_{ll#gamma} (GeV)";
//TString histname = "h1_Njet"; XMAX=12; XMIN=0;YMAX=600;rebin =1;
//TString histname = "h1_jetPT"; XMAX=300; XMIN=0;YMAX=10000; rebin =10;

//Jet//
TString histname = "h1_jjM"; XMAX=4500; XMIN=0; rebin=70; YMAX=10000; TitleName="Mass(Dijets)";AxisTitleName="M_{jj} (GeV)"				;

//TString histname = "h1_jdEta"; XMAX=10; XMIN=0; YMAX=1000; rebin=50;TitleName="DeltaEta(Dijets)";AxisTitleName="#Delta#eta_{jj}"		;
//TString histname = "h1_jdPhi"; XMAX=3.14; XMIN=0; YMAX=10000; rebin=32;TitleName="DeltaPhi(Dijets)";AxisTitleName="#Delta#phi_{jj}"	;
//TString histname = "h1_ZpVal"; XMAX=6; XMIN=0; YMAX=1000; rebin=33; TitleName="ZeppenFeldVariable";AxisTitleName="ZeppenFeldVariable"	;


TH1F *hSingleAntiTop = (TH1F*)fSingleAntiTop->Get(histname); hSingleAntiTop->Scale(xsecSingleAntiTop/1000000*Lumi) ;  
TH1F *hSingleTop     = (TH1F*)fSingleTop 	->Get(histname); hSingleTop    ->Scale(xsecSingleTop    /1000000*Lumi) ;      
TH1F *hWW            = (TH1F*)fWW 			->Get(histname); hWW           ->Scale(xsecWW           /1000000*Lumi) ;  
TH1F *hWZp           = (TH1F*)fWZp 		 	->Get(histname); hWZp          ->Scale(xsecWZp          /1000000*Lumi) ; 
TH1F *hWZm           = (TH1F*)fWZm 		 	->Get(histname); hWZm          ->Scale(xsecWZm          /1000000*Lumi) ; 
TH1F *hZZ            = (TH1F*)fZZ 			->Get(histname); hZZ           ->Scale(xsecZZ           /1000000*Lumi) ; 
TH1F *htta2jets      = (TH1F*)ftta2jets 	->Get(histname); htta2jets     ->Scale(xsectta2jets     /1000000*Lumi) ; 
//TH1F *hzajets       = (TH1F*)fzajets 		->Get(histname); hzajets      ->Scale(xseczajets       /100000 *Lumi) ;  

TH1F *hZA				=(TH1F*)fZA					->Get(histname);	hZA				 ->Scale(xsecZA	/800000*Lumi);
TH1F *hZAj				=(TH1F*)fZAj				->Get(histname);	hZAj			 ->Scale(xsecZAj/100000*Lumi);					
TH1F *hZAjj_M120to600 	=(TH1F*)fZAjj_M120to600		->Get(histname);	hZAjj_M120to600  ->Scale(xsecZAjj_M120to600	/30000*Lumi);	
TH1F *hZAjj_M600to1000  =(TH1F*)fZAjj_M600to1000	->Get(histname);    hZAjj_M600to1000 ->Scale(xsecZAjj_M600to1000/30000*Lumi);
TH1F *hZAjj_M1000		=(TH1F*)fZAjj_M1000			->Get(histname);    hZAjj_M1000		 ->Scale(xsecZAjj_M1000		/30000*Lumi);

TH1F *hSignal        = (TH1F*)fSignal 		->Get(histname); hSignal       ->Scale(xsecSignal      /100000 *Lumi) ;  


cout << hSignal->Integral() << endl;



//TH1F* h1DYJet = new TH1F(*hz2eejj) ;   
//TH1F* h1zajjQCD = new TH1F(*hzajjQCD) ;   
TH1F* h1zajets = new TH1F(*hZA);   
	h1zajets->Add(hZAj); 
	h1zajets->Add(hZAjj_M120to600); 
	h1zajets->Add(hZAjj_M600to1000); 
	h1zajets->Add(hZAjj_M1000); 
TH1F* h1TTJet = new TH1F(*htta2jets);
TH1F* h1Dibos = new TH1F(*hWW); h1Dibos->Add(hWZp);h1Dibos->Add(hWZm); h1Dibos->Add(hZZ);
TH1F* h1STops = new TH1F(*hSingleAntiTop); h1STops->Add(hSingleTop); 
//TH1F* h1ZGToL = new TH1F(*hz2eea );
TH1F* hBKG = new TH1F(*h1zajets); hBKG->Add(htta2jets); hBKG->Add(h1Dibos); hBKG->Add(h1STops); 
//hBKG->Add(h1ZGToL); 

//h1DYJet->SetLineColor(28);h1DYJet->SetFillColor(28);
//h1zajjQCD->SetLineColor(28);h1zajjQCD->SetFillColor(28);
h1zajets->SetLineColor(8);h1zajets->SetFillColor(8);
h1TTJet->SetLineColor(6);h1TTJet->SetFillColor(6);
h1Dibos->SetLineColor(4);h1Dibos->SetFillColor(4);
h1STops->SetLineColor(15);h1STops->SetFillColor(15);
//h1ZGToL->SetLineColor(38);h1ZGToL->SetFillColor(38);
hSignal->SetLineColor(2);
hSignal->SetLineWidth(5);



//h1zajjQCD->Rebin(rebin);
h1zajets->Rebin(rebin);
//h1DYJet->Rebin(rebin);
h1TTJet->Rebin(rebin);
h1Dibos->Rebin(rebin);
h1STops->Rebin(rebin);
//h1ZGToL->Rebin(rebin);
hSignal->Rebin(rebin);

THStack* stkBkgs = new THStack("stkBkgs","stkBkgs");
                 stkBkgs->Add(h1STops); 
    if(addTTJet) stkBkgs->Add(h1TTJet);
                 stkBkgs->Add(h1Dibos);
  //  if(addZGToL) stkBkgs->Add(h1ZGToL);
//    if(addDYJet) stkBkgs->Add(h1DYJet);
    			 stkBkgs->Add(h1zajets);
//				 stkBkgs->Add(hSignal);

//TCanvas *c1 = new TCanvas();
//stkBkgs->Draw();

   gStyle->SetOptStat(0);
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetPadBorderMode(0);
   gStyle->SetPadColor(0);
   gStyle->SetFrameBorderMode(0);


//cout <<"Nevents h1DYJet"<< h1DYJet->Integral()<< endl;
cout <<"Nevents h1zajets"<< h1zajets->Integral(4,20)<< endl;
cout <<"Nevents h1TTJet" << h1TTJet->Integral()<< endl;
cout <<"Nevents h1Dibos" << h1Dibos->Integral()<< endl;
cout <<"Nevents h1STops" << h1STops->Integral()<< endl;
cout <<"Nevents Signal"  << hSignal->Integral(4,20)<< endl;
cout << hSignal->GetXaxis()->FindBin(500) << endl;
cout << hSignal->GetXaxis()->FindBin(1000) << endl;
cout << h1zajets->GetXaxis()->FindBin(1000) << endl;

//cout <<"Nevents h1ZGToL"<< h1ZGToL->Integral()<< endl;


//TString filename = "Mass(Dielectron)";
   TCanvas* c1 = new TCanvas("c1", "c1", 1500, 1500);
   TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.0001, 1.0, 1.0);
//   pad1->SetBottomMargin(0.01);
   pad1->SetGrid();
   pad1->SetLogy();
   pad1->Draw();

pad1->cd();
   TH2F *null1 = new TH2F("null1","", 2, XMIN, XMAX, 2, 0.09,YMAX);
   null1->GetYaxis()->SetTitle("Events");
   null1->GetXaxis()->SetTitle(AxisTitleName);
   null1->GetYaxis()->SetTitleOffset(1.07);
   null1->GetXaxis()->SetTitleOffset(1.25);
   null1->GetYaxis()->SetTitleSize(0.04);
   null1->GetYaxis()->SetLabelSize(0.04);
   null1->Draw();
    stkBkgs->Draw("same hist");
	hSignal->Draw("same hist");
   //TLegend *l0 = new TLegend(0.5,0.89,0.80,0.65);
   TLegend *l0 = new TLegend(0.65,0.89,0.90,0.65);
   l0->SetFillStyle(0);
   l0->SetBorderSize(0);
   l0->SetTextSize(0.03);
   

//    if(addDYJet) { TLegendEntry* l02 = l0->AddEntry(h1DYJet,"DYJets "   ,"f"  ); l02->SetTextColor(h1DYJet->GetLineColor()); }
     TLegendEntry* l02 = l0->AddEntry(h1zajets,"Z#gammajj "   ,"f"  ); l02->SetTextColor(h1zajets->GetLineColor()); 
   // if(addZGToL) { TLegendEntry* l03 = l0->AddEntry(h1ZGToL,"Z+#gamma " ,"f"  ); l03->SetTextColor(h1ZGToL->GetLineColor()); }
                   TLegendEntry* l04 = l0->AddEntry(h1Dibos,"DiBoson"   ,"f"  ); l04->SetTextColor(h1Dibos->GetLineColor());
    if(addTTJet) { TLegendEntry* l05 = l0->AddEntry(h1TTJet,"TTJets"    ,"f"  ); l05->SetTextColor(h1TTJet->GetLineColor()); }
                   TLegendEntry* l07 = l0->AddEntry(h1STops,"STops"     ,"f"  ); l07->SetTextColor(h1STops->GetLineColor());
                   TLegendEntry* l08 = l0->AddEntry(hSignal,"Z#gammajj(signal)"     ,"l"  ); l08->SetTextColor(hSignal->GetLineColor());
 
 
 l0->Draw();
pad1->cd();
    TLatex latex;
   latex.SetNDC();
   latex.SetTextSize(0.04);
    latex.SetTextAlign(11);
    latex.DrawLatex(0.64,0.91,Form("%.1f fb^{-1} (13 TeV)", Lumi/1000.0));

   latex.SetTextSize(0.035);
    latex.DrawLatex(0.11,0.84,Form("(ee channel)"));

	//c1->Print(TitleName + ".png");



}
