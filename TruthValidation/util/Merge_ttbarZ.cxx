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

  if( argc != 8 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  SetAtlasStyle();

  TString file1 = argv[ 1 ];
  TString file2 = argv[ 2 ];
  TString file3 = argv[ 3 ];
  TString file4 = argv[ 4 ];
  TString file5 = argv[ 5 ];
  TString file6 = argv[ 6 ];
  TString file7 = argv[ 7 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *f3 = new TFile( file3 );
  TFile *f4 = new TFile( file4 );
  TFile *f5 = new TFile( file5 );
  TFile *f6 = new TFile( file6 );
  TFile *fFinal = new TFile( file7 ,"recreate");

  TH1F  *h_ttee_Np0 = (TH1F*)f1->Get( "h_Acceptance" );
  TH1F  *h_ttee_Np1 = (TH1F*)f2->Get( "h_Acceptance" );
  TH1F  *h_ttmumu_Np0 = (TH1F*)f3->Get( "h_Acceptance" );
  TH1F  *h_ttmumu_Np1 = (TH1F*)f4->Get( "h_Acceptance" );
  TH1F  *h_tttautau_Np0 = (TH1F*)f5->Get( "h_Acceptance" );
  TH1F  *h_tttautau_Np1 = (TH1F*)f6->Get( "h_Acceptance" );

  Double_t  Xs_ttee_Np0 = 0.0096235;
  Double_t  Xs_ttee_Np1 = 0.017344;
  Double_t  Xs_ttmumu_Np0 = 0.0096462;
  Double_t  Xs_ttmumu_Np1 = 0.017361;
  Double_t  Xs_tttautau_Np0 = 0.0098874;
  Double_t  Xs_tttautau_Np1 = 0.01779;
  Double_t Xs_ttbarZ_total = Xs_ttee_Np0 + Xs_ttee_Np1 + Xs_ttmumu_Np0 + Xs_ttmumu_Np1 + Xs_tttautau_Np0 + Xs_tttautau_Np1 ;

  TH1F *h_final = (TH1F*) h_ttee_Np0->Clone();

  // h_final->Scale( Xs_ttee_Np0 );
  // h_final->Add( h_ttee_Np1, Xs_ttee_Np1);
  // h_final->Add( h_ttmumu_Np0, Xs_ttmumu_Np0);
  // h_final->Add( h_ttmumu_Np1, Xs_ttmumu_Np1);
  // h_final->Add( h_tttautau_Np0, Xs_tttautau_Np0);
  // h_final->Add( h_tttautau_Np1, Xs_tttautau_Np1);

  // h_final->Scale( 1./Xs_ttbarZ_total );


  for (int i=0; i<h_final->GetNbinsX(); i++){
    
    Double_t A_ttee_Np0 = h_ttee_Np0->GetBinContent(i+1);
    Double_t A_ttee_Np1 = h_ttee_Np1->GetBinContent(i+1);
    Double_t A_ttmumu_Np0 = h_ttmumu_Np0->GetBinContent(i+1);
    Double_t A_ttmumu_Np1 = h_ttmumu_Np1->GetBinContent(i+1);
    Double_t A_tttautau_Np0 = h_tttautau_Np0->GetBinContent(i+1);
    Double_t A_tttautau_Np1 = h_tttautau_Np1->GetBinContent(i+1);

    Double_t dA_ttee_Np0 = h_ttee_Np0->GetBinError(i+1);
    Double_t dA_ttee_Np1 = h_ttee_Np1->GetBinError(i+1);
    Double_t dA_ttmumu_Np0 = h_ttmumu_Np0->GetBinError(i+1);
    Double_t dA_ttmumu_Np1 = h_ttmumu_Np1->GetBinError(i+1);
    Double_t dA_tttautau_Np0 = h_tttautau_Np0->GetBinError(i+1);
    Double_t dA_tttautau_Np1 = h_tttautau_Np1->GetBinError(i+1);

    h_final->SetBinContent( i+1, ( A_ttee_Np0*Xs_ttee_Np0 + 
				   A_ttee_Np1*Xs_ttee_Np1 + 
				   A_ttmumu_Np0*Xs_ttmumu_Np0 + 
				   A_ttmumu_Np1*Xs_ttmumu_Np1 + 
				   A_tttautau_Np0*Xs_tttautau_Np0 + 
				   A_tttautau_Np1*Xs_tttautau_Np1 )/Xs_ttbarZ_total );

    h_final->SetBinError( i+1, ( dA_ttee_Np0*Xs_ttee_Np0 + 
				 dA_ttee_Np1*Xs_ttee_Np1 + 
				 dA_ttmumu_Np0*Xs_ttmumu_Np0 + 
				 dA_ttmumu_Np1*Xs_ttmumu_Np1 + 
				 dA_tttautau_Np0*Xs_tttautau_Np0 + 
				 dA_tttautau_Np1*Xs_tttautau_Np1 )/Xs_ttbarZ_total );
  }

  h_final->Write();
  fFinal->Close();
}
