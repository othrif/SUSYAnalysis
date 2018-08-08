#include <iostream>

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>
#include <TSystem.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>

#include <Utils/AtlasStyle.h>
#include <Utils/AtlasLabels.h>

int main( int argc, char* argv[] ) {

  if( argc != 5 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  TString file1 = argv[ 1 ];
  TString file2 = argv[ 2 ];
  TString file3 = argv[ 3 ];
  TString file4 = argv[ 4 ];
  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *f3 = new TFile( file3 );
  TFile *f4 = new TFile( file4 );
  TH1F  *hSyst = (TH1F*)f1->Get( "hSyst" );
  TH1F  *hSyst2 = (TH1F*)f2->Get( "hSyst" );
  TH1F  *hSyst3 = (TH1F*)f3->Get( "hSyst" );
  TH1F  *hSyst4 = (TH1F*)f4->Get( "hSyst" );

  for (int i=0; i<hSyst->GetNbinsX(); i++){
    std::cout << i << " " << std::sqrt( std::pow(hSyst->GetBinContent(i+1),2) + 
					std::pow(hSyst2->GetBinContent(i+1),2) + 
					std::pow(hSyst3->GetBinContent(i+1),2) + 
					std::pow(hSyst4->GetBinContent(i+1),2) ) << std::endl;
  }

}
