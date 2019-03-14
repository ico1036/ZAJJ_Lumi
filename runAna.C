#include <iostream>
#include "TClonesArray.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "classes/DelphesClasses.h"
using namespace std;
int main(int argc, char** argv) {

	 TFile* outFile = new TFile(argv[1],"create");
     TChain* inChain = new TChain("Delphes");
	
	 int    nttype = atoi(argv[2]) ;
     double ntxsec = atof(argv[3]) ;
     double ntgenN = atof(argv[4]) ;
	
	for(int iFile = 5; iFile<argc; iFile++) {
		std::cout << "### InFile " << iFile-4 << " " << argv[iFile] << std::endl;
		inChain->Add(argv[iFile]);
	}
	
	
	
	

	TClonesArray* eleTCA = new TClonesArray("Electron");inChain->SetBranchAddress("Electron",&eleTCA);
	TClonesArray *phoTCA = new TClonesArray("Photon"); inChain->SetBranchAddress("Photon",&phoTCA);
    TClonesArray *jetTCA = new TClonesArray("Jet"); inChain->SetBranchAddress("Jet",&jetTCA);

    TClonesArray *eleSelTCA =  new TClonesArray("Electron");
    TClonesArray *phoSelTCA =  new TClonesArray("Photon");
    TClonesArray *jetSelTCA =  new TClonesArray("Jet");

	//outFile->cd();
	TH1F * h1_ele1PT = new TH1F("h1_ele1PT","electron1PT",1000,0,300);
    TH1F * h1_ele2PT = new TH1F("h1_ele2PT","electron2PT",1000,0,300);
    TH1F * h1_eleEta = new TH1F("h1_eleEta","electronEta",100,-3,3);
    TH1F * h1_elePhi = new TH1F("h1_elePhi","electronPhi",100,-4,4);
    TH1F * h1_eleCharge = new TH1F("h1_eleCharge","electronCharge",100,-2,2);
    TH1F * h1_eeM = new TH1F("h1_eeM","Di-electronMass",1000,0,200);
    TH1F * h1_eeaM = new TH1F("h1_eeaM","Di-electron-photonMAss",1000,0,200);
    TH1F * h1_eePT = new TH1F("h1_eePt","Di-electronPT",1000,0,1000);

    TH1F * h1_phoPT = new TH1F("h1_phoPT","photonPT",1000,0,300);
    TH1F * h1_phoEta = new TH1F("h1_phoEta","photonEta",100,-3,3);
    TH1F * h1_phoPhi = new TH1F("h1_phoPhi","photonPhi",100,-4,4);

    TH1F * h1_jetPT = new TH1F("h1_jetPT","jetPT",1000,0,300);
    TH1F * h1_jetEta = new TH1F("h1_jetEta","jetEta",100,-3,3);
    TH1F * h1_jetPhi = new TH1F("h1_jetPhi","jetPhi",100,-4,4);
    TH1F * h1_Njet = new TH1F("h1_Njet","jetSize",15,0,15);

    TH1F * h1_jjM = new TH1F("h1_jjM","h1_jjM",1000,0,7000);
    TH1F * h1_jdEta = new TH1F("h1_jdEta","h1_jdEta",1000,0,10);
    TH1F * h1_jdPhi = new TH1F("h1_jdPhi","h1_jdPhi",1000,0,TMath::Pi());
    TH1F * h1_ZpVar = new TH1F("h1_ZpVal","Zppenfeld",1000,0,10);

	//outFile->cd();


	double ntzepp ;
    double ntmjj  ;
    double ntdEta ;
    double ntdPhi ;

	TTree* outTree = new TTree("tree","tree");
    outTree->Branch("nttype", &nttype);
    outTree->Branch("ntxsec", &ntxsec);
    outTree->Branch("ntgenN", &ntgenN);
    outTree->Branch("ntzepp", &ntzepp);
    outTree->Branch("ntmjj" , &ntmjj );
    outTree->Branch("ntdEta", &ntdEta);
    outTree->Branch("ntdPhi", &ntdPhi);

	
	int totalEvt = (int)inChain->GetEntries();
	int per99 = totalEvt/99;
	int per100 = 0;
	int step0num =0;
	int step1num =0;
    int step2num =0;
    int step3num =0;
	double VBFnum=0;


	for(int eventLoop=0; eventLoop < totalEvt; eventLoop++) {
		inChain->GetEntry(eventLoop);
		if((eventLoop%per99) == 0) std::cout << "Running " << per100++ << " %" << std::endl;

		eleSelTCA->Clear("C");
        phoSelTCA->Clear("C");
        jetSelTCA->Clear("C");
			
		step0num++;
////////////////////////////////////////////////////////////////

    	for(int eleLoop=0; eleLoop<eleTCA->GetEntries(); eleLoop++){
            Electron *elePtr = (Electron*)eleTCA->At(eleLoop);

			if (elePtr->PT < 25)            continue;
        	if(TMath::Abs(elePtr->Eta)>2.5) continue;

        	new ((*eleSelTCA)[(int)eleSelTCA->GetEntries()]) Electron(*elePtr);


    	}	 // ele Loop
    	if(eleSelTCA->GetEntries() != 2) continue;
    	Electron* elePtr1 = (Electron*)eleSelTCA->At(0);
    	Electron* elePtr2 = (Electron*)eleSelTCA->At(1);
    	if(elePtr1->Charge * elePtr2->Charge == 1 ) continue;

    step1num++;  // Electron Selection


	/*

    h1_ele1PT->Fill(elePtr1->PT);
    h1_ele2PT->Fill(elePtr2->PT);
    h1_eleEta->Fill(elePtr1->Eta);
    h1_elePhi->Fill(elePtr1->Phi);
    h1_eleCharge->Fill(elePtr1->Charge);
    TLorentzVector ele1Vec = elePtr1->P4();
    TLorentzVector ele2Vec = elePtr2->P4();
    TLorentzVector eeVec = ele1Vec + ele2Vec;
    h1_eeM->Fill(eeVec.M());
    h1_eePT->Fill(eeVec.Pt());
*/
/////////////////////////////////////////////////////////////////
	
		
		for(int phoLoop=0; phoLoop<phoTCA->GetEntries(); phoLoop++){
        	Photon *phoPtr = (Photon*)phoTCA->At(phoLoop);

        	if(phoPtr->PT <25) continue;
        	if(TMath::Abs(phoPtr->Eta)>2.5) continue;
        	
			double dPhi1 = (phoPtr->Phi)-(elePtr1->Phi);
			double dPhi2 = (phoPtr->Phi)-(elePtr2->Phi);
			double deltaPhi1 = ( dPhi1 > TMath::Pi() ) ? fabs(TMath::TwoPi() - dPhi1) : fabs(dPhi1);
			double deltaPhi2 = ( dPhi2 > TMath::Pi() ) ? fabs(TMath::TwoPi() - dPhi2) : fabs(dPhi2);
			double dEta1 = fabs(phoPtr->Eta - elePtr1->Eta);
			double dEta2 = fabs(phoPtr->Eta - elePtr2->Eta);
			double dR1 = TMath::Sqrt(deltaPhi1*deltaPhi1 + dEta1*dEta1);
			double dR2 = TMath::Sqrt(deltaPhi2*deltaPhi2 + dEta2*dEta2);
			if(dR1 <0.5 || dR2 < 0.5) continue;

		new ((*phoSelTCA)[(int)phoSelTCA->GetEntries()]) Photon(*phoPtr);


    	} // pho Loop
    	if(phoSelTCA->GetEntries()!=1 )  continue;


	    Photon* phoPtr = (Photon*)phoSelTCA->At(0);
	    TLorentzVector ele1Vec = elePtr1->P4();
	    TLorentzVector ele2Vec = elePtr2->P4();
	    TLorentzVector phoVec = phoPtr->P4();
	    TLorentzVector eeVec = ele1Vec + ele2Vec;
	    TLorentzVector eeaVec = ele1Vec + ele2Vec+phoVec;
		if(eeVec.M() < 60 || eeVec.M() > 120) continue;
	   // if(eeVec.M() < 70 || eeVec.M() > 110) continue;
	
	    step2num++; //   Photon Selection

	
   		 h1_ele1PT->Fill(elePtr1->PT);
   		 h1_ele2PT->Fill(elePtr2->PT);
   		 h1_eleEta->Fill(elePtr1->Eta);
   		 h1_elePhi->Fill(elePtr1->Phi);
   		 h1_eleCharge->Fill(elePtr1->Charge);
   		 h1_phoPT->Fill(phoPtr->PT); 
   		 h1_phoEta->Fill(phoPtr->Eta);   
   		 h1_phoPhi->Fill(phoPtr->Phi);   
   		 h1_eeM->Fill(eeVec.M());
   		 h1_eeaM->Fill(eeaVec.M());
   		 h1_eePT->Fill(eeVec.Pt());

   		 if(jetTCA->GetEntries() != 0 ) {
   		 Jet* jetPtr = (Jet*)jetTCA->At(0);
   		 h1_jetPT->Fill(jetPtr->PT);
   		 }

   		 h1_Njet->Fill(jetTCA->GetEntries());
	
////////////////////////////////////////////////////////////////

	for(int jetLoop=0; jetLoop<jetTCA->GetEntries(); jetLoop++){
        Jet *jetPtr = (Jet*)jetTCA->At(jetLoop);

        if(TMath::Abs(jetPtr->Eta)>4.7) continue;
        if(jetPtr->PT < 30) continue;
			

			double dPhi = (phoPtr->Phi)-(jetPtr->Phi);
			double deltaPhi = ( dPhi > TMath::Pi() ) ? fabs(TMath::TwoPi() - dPhi) : fabs(dPhi);
			double dEta = fabs(phoPtr->Eta - jetPtr->Eta);
			double dR = TMath::Sqrt(deltaPhi*deltaPhi + dEta*dEta);
			if(dR <0.5) continue;


	
	new ((*jetSelTCA)[(int)jetSelTCA->GetEntries()]) Jet(*jetPtr);


    } // Jet Loop
    if(jetSelTCA->GetEntries() < 2) continue;
    step3num++;  //  Jet Selection

	

    Jet* jetPtr1 = (Jet*)jetSelTCA->At(0);
    Jet* jetPtr2 = (Jet*)jetSelTCA->At(1);
	
	TLorentzVector jet1Vec = jetPtr1->P4();
    TLorentzVector jet2Vec = jetPtr2->P4();
    TLorentzVector jjVec = jet1Vec + jet2Vec;
	
	double jjM =jjVec.M();
	double dEta = fabs((jetPtr2->Eta) - (jetPtr1->Eta));
    double dPhi = fabs((jetPtr2->Phi) - (jetPtr1->Phi));
    double deltaPhi = ( dPhi > TMath::Pi() ) ? fabs(TMath::TwoPi() - dPhi) : fabs(dPhi);
    double rapZA = eeaVec.Rapidity();
    double rapJ1 = jet1Vec.Rapidity();
    double rapJ2 = jet2Vec.Rapidity();
    double zepp = fabs(rapZA - (rapJ1 + rapJ2) / 2.0);

///////////////////////////////////////////////////////  VBF cut 
	
	ntzepp  = zepp     ;
    ntmjj   = jjM      ;
    ntdEta  = dEta     ;
    ntdPhi  = deltaPhi ;



	
	h1_ele1PT->Fill(elePtr1->PT);
    h1_ele2PT->Fill(elePtr2->PT);
    h1_eleEta->Fill(elePtr1->Eta);
    h1_elePhi->Fill(elePtr1->Phi);
    h1_eleCharge->Fill(elePtr1->Charge);


    h1_phoPT->Fill(phoPtr->PT);
    h1_phoEta->Fill(phoPtr->Eta);
    h1_phoPhi->Fill(phoPtr->Phi);


    h1_jjM->Fill(jjM);
    h1_jdEta->Fill(dEta);

    h1_eeM->Fill(eeVec.M());
    h1_eeaM->Fill(eeaVec.M());
    h1_eePT->Fill(eeVec.Pt());





    h1_jdPhi->Fill(deltaPhi);
    h1_ZpVar->Fill(zepp);

	outTree->Fill();

	//if(jjM < 500 ) continue;
	
	
	} //evetLoop  End

	cout << "step0 :" << step0num << endl;
	cout << "step1 :" << step1num << endl;
    cout << "step2 :" << step2num << endl;
    cout << "step3 :" << step3num << endl;
	
	outFile->Write();
	return 0;
}
