#include <iostream>

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

  if( argc != 5 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  SetAtlasStyle();

  TString file1 = argv[ 1 ];
  TString file2 = argv[ 2 ];
  TString file3 = argv[ 3 ];
  TString file4 = argv[ 4 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *f3 = new TFile( file3 );
  TFile *fFinal = new TFile( file4 ,"recreate");

  TH1F  *h_ttbarW_Np0 = (TH1F*)f1->Get( "h_Acceptance" );
  TH1F  *h_ttbarW_Np1 = (TH1F*)f2->Get( "h_Acceptance" );
  TH1F  *h_ttbarW_Np2 = (TH1F*)f3->Get( "h_Acceptance" );

  Double_t Xs_ttbarW_Np0 = 0.17656 ;
  Double_t Xs_ttbarW_Np1 = 0.14062 ;
  Double_t Xs_ttbarW_Np2 = 0.1368 ;
  Double_t Xs_ttbarW_total = Xs_ttbarW_Np0 + Xs_ttbarW_Np1 + Xs_ttbarW_Np2 ;

  TH1F *h_final = (TH1F*) h_ttbarW_Np0->Clone();

  for (int i=0; i<h_final->GetNbinsX(); i++){
    
    Double_t A_ttbarW_Np0 = h_ttbarW_Np0->GetBinContent(i+1);
    Double_t A_ttbarW_Np1 = h_ttbarW_Np1->GetBinContent(i+1);
    Double_t A_ttbarW_Np2 = h_ttbarW_Np2->GetBinContent(i+1);

    Double_t dA_ttbarW_Np0 = h_ttbarW_Np0->GetBinError(i+1);
    Double_t dA_ttbarW_Np1 = h_ttbarW_Np1->GetBinError(i+1);
    Double_t dA_ttbarW_Np2 = h_ttbarW_Np2->GetBinError(i+1);

    h_final->SetBinContent( i+1, ( A_ttbarW_Np0*Xs_ttbarW_Np0 + 
				   A_ttbarW_Np1*Xs_ttbarW_Np1 + 
				   A_ttbarW_Np2*Xs_ttbarW_Np2 )/Xs_ttbarW_total );

    h_final->SetBinError( i+1, ( dA_ttbarW_Np0*Xs_ttbarW_Np0 + 
				 dA_ttbarW_Np1*Xs_ttbarW_Np1 + 
				 dA_ttbarW_Np2*Xs_ttbarW_Np2 )/Xs_ttbarW_total );
  }

  // h_final->Scale( Xs_ttbarW_Np0 );
  // h_final->Add( h_ttbarW_Np1, Xs_ttbarW_Np1);
  // h_final->Add( h_ttbarW_Np2, Xs_ttbarW_Np2);
  // h_final->Scale( 1./Xs_ttbarW_total );

  h_final->Write();
  fFinal->Close();
}
