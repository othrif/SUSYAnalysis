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
#include <TLine.h>

#include <Utils/AtlasStyle.h>
#include <Utils/AtlasLabels.h>

int main( int argc, char* argv[] ) {

  if( argc != 6 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  SetAtlasStyle();
  gStyle->SetMarkerSize(0.9);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetTextSize(0.04);

  TString file1 = argv[ 1 ];
  TString file2 = argv[ 2 ];
  TString file3 = argv[ 3 ];
  TString Legend = argv[ 4 ];
  TString hist = argv[ 5 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *fFinal = new TFile( file3 ,"recreate");

  TH1F  *h1  = (TH1F*)f1->Get( hist );
  TH1F  *h2   = (TH1F*)f2->Get( hist );

  h1->SetLineColor(kBlack);
  h2->SetLineColor(kRed+1);
  h2->SetMarkerColor(kRed+1);

  h1->GetXaxis()->SetLabelOffset(0.045);
  h1->SetTitle("");
  //  h1->GetXaxis()->SetTitle("SR/VR Regions");
  //  h1->GetYaxis()->SetTitle("Events");
  //  h1->SetMaximum( std::max(h1->GetMaximum(),
  h1->SetMaximum( 
				 0.2 * pow( std::max(h1->GetMaximum(),
									 h2->GetMaximum() )/ 0.2, 1.28));

  TLegend *legend=new TLegend(0.70,0.65,0.90,0.85);
  legend->SetTextFont(62);
  legend->SetTextSize(0.05);
  legend->SetHeader(Legend);
  legend->AddEntry(h1, "v52","lp");
  legend->AddEntry(h2, "v53","lp");

  TCanvas *c = new TCanvas( "SystVar" , "SystVar" );
  TPad* p1 = new TPad("p1","p1",0.0,0.25,1.0,1.0,-22);
  TPad* p2 = new TPad("p2","p2",0.0,0.0,1.0,0.25,-21);
  p1->SetBottomMargin(0.02);
  p2->SetTopMargin(0.05);
  p2->SetBottomMargin(0.5);
  p1->SetLogy();
  p1->Draw();
  p2->Draw();

  // First Pad
  p1->cd();
  h1->Draw("HIST E");
  h2->Draw("HIST E SAME");
  ATLASLabel(0.20,0.87,true);
  legend->Draw();

  // Second Pad
  p2->cd();

  TH1F* href = (TH1F*)h1->Clone("ref");
  href->Divide( h1 );

  href->SetMaximum(1.5);
  href->SetMinimum(0.5);

  href->GetYaxis()->SetTitle("Ratio");

  href->GetXaxis()->SetLabelSize(0.17);
  href->GetYaxis()->SetNdivisions(505);
  href->GetYaxis()->SetLabelSize(0.12);

  href->GetXaxis()->SetTitleSize(0.17);
  href->GetXaxis()->SetTitleOffset(1.35);
  href->GetYaxis()->SetTitleSize(0.12);
  href->GetYaxis()->SetTitleOffset(0.5);

  href->Draw("AXIS");

  TF1 *lineB = new TF1("lineB","1",-100000,100000);
  lineB->SetLineColor(kBlack);
  lineB->SetLineWidth(1);
  lineB->Draw("same");

  TH1F* hdiv = (TH1F*)h2->Clone("hdiv");
  hdiv->Divide( h1 );
  hdiv->Draw(" HIST SAME");

 
  // Write
  c->Print( "ratio_"+Legend+".pdf" );
  c->Write();


  fFinal->Close();  

}
