#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "TH1D.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"

using namespace std;


int main(int argc, char** argv){

double Lumi = atoi(argv[1]);
double bkg  = atof(argv[2]);
double sig  = atof(argv[3]);

//double bkg = 38.05;
//double sig = 26.02;
//double Lumi = 1; // Lumi/100fb

  // bkg *= Lumi;
  // sig *= Lumi;

   double xMin = bkg - TMath::Sqrt(sig+bkg) * 10.0;
   double xMax = sig+bkg + TMath::Sqrt(sig+bkg) * 10.0;
   if(xMin < 0.0) xMin = 0.0;

   TF1 *f1 = new TF1("f1","TMath::Poisson(x,[0])",xMin,xMax);
   TF1 *f2 = new TF1("f2","TMath::Poisson(x,[0])",xMin,xMax);
   f1->SetParameter(0,bkg);
   f2->SetParameter(0,sig+bkg); f2->SetLineColor(kGreen);

   TH1D* h1 = new TH1D("h1","h1",10000, sig+bkg,xMax);
   h1->Eval(f1);
   h1->SetFillColor(kRed);
   h1->SetFillStyle(3001);

   TH1D* h2 = new TH1D("h2","h2",10000, xMin,bkg);
   h2->Eval(f2);
   h2->SetFillColor(kGreen);
   h2->SetFillStyle(3001);


   TCanvas* c1 = new TCanvas();
   //c1->SetLogy();
   f1->Draw(); // sig
   h1->Draw("sameHIST"); //sig

   f2->Draw("same");
   h2->Draw("sameHIST");
   c1->Print("01_poi_M400L35.png");

   double sum1 = 0.0;
   double sum2 = 0.0;

  cout << Lumi << "				" << f1->Integral(sig+bkg,xMax)<< endl;
  cout << f1->Integral(0,xMax) << endl;


   return 0;
}

