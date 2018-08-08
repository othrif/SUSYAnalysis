#include <iostream>
#include <stdlib.h>

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>
#include <TSystem.h>
#include <TGraphAsymmErrors.h>

#include <Utils/AtlasStyle.h>
#include <Utils/AtlasLabels.h>

int main( int argc, char* argv[] ) {

  if( argc != 10 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  SetAtlasStyle();

  TString file_llvvjj_ss_EW4 = argv[ 1 ];
  Double_t Xs_llvvjj_ss_EW4  = atof(argv[ 2 ]);
  TString file_llvvjj_ss_EW6 = argv[ 3 ];
  Double_t Xs_llvvjj_ss_EW6  = atof(argv[ 4 ]);
  TString file_ggllll = argv[ 5 ];
  Double_t Xs_ggllll  = atof(argv[ 6 ]);
  TString file_llll = argv[ 7 ];
  Double_t Xs_llll  = atof(argv[ 8 ]);
  TString file_total = argv[ 9 ];

  TFile *f1 = new TFile( file_llvvjj_ss_EW4 );
  TFile *f2 = new TFile( file_llvvjj_ss_EW6 );
  TFile *f3 = new TFile( file_ggllll );
  TFile *f4 = new TFile( file_llll );
  TFile *fFinal = new TFile( file_total ,"recreate");

  TH1F  *h_llvvjj_ss_EW4 = (TH1F*)f1->Get( "h_Acceptance" );
  TH1F  *h_llvvjj_ss_EW6 = (TH1F*)f2->Get( "h_Acceptance" );
  TH1F  *h_ggllll        = (TH1F*)f3->Get( "h_Acceptance" );
  TH1F  *h_llll          = (TH1F*)f4->Get( "h_Acceptance" );

  TH1F *h_final = (TH1F*) h_llvvjj_ss_EW4->Clone();

  h_final->Scale( Xs_llvvjj_ss_EW4 );
  h_final->Add( h_llvvjj_ss_EW6, Xs_llvvjj_ss_EW6);
  h_final->Add( h_ggllll, Xs_ggllll);
  h_final->Add( h_llll, Xs_llll);

  Double_t Xs_VV_total = Xs_llvvjj_ss_EW4 + Xs_llvvjj_ss_EW6 + Xs_ggllll + Xs_llll; 
  h_final->Scale( 1./Xs_VV_total );

  h_final->Write();
  fFinal->Close();
}
