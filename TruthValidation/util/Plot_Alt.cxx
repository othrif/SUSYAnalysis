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

  SetAtlasStyle();
  gStyle->SetMarkerSize(0.9);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetTextSize(0.04);

  TString file1 = argv[ 1 ];
  TString file2 = argv[ 2 ];
  TString file3 = argv[ 3 ];
  TString Legend = argv[ 4 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *fFinal = new TFile( file3 ,"recreate");

  TH1F  *h_Nom  = (TH1F*)f1->Get( "h_Acceptance" );
  TH1F  *h_Alt   = (TH1F*)f2->Get( "h_Acceptance" );

  h_Nom->SetLineColor(kBlack);
  h_Alt->SetLineColor(kRed+1);
  h_Alt->SetMarkerColor(kRed+1);

  h_Nom->GetXaxis()->SetLabelOffset(0.045);
  h_Nom->SetTitle("");
  h_Nom->GetXaxis()->SetTitle("Signal Region");
  h_Nom->GetYaxis()->SetTitle("Acceptance");
  h_Nom->SetMaximum( std::max(h_Nom->GetMaximum(),
			      h_Alt->GetMaximum() )*1.2 );
  TString Ax_SR[8] = {"SRVLQ0","SRVLQ1","SRVLQ2","SRVLQ3","SRVLQ4","SRVLQ5","SRVLQ6","SRVLQ7"};
  for (int i=1; i<=8; i++) {
    h_Nom->GetXaxis()->SetBinLabel(i,Ax_SR[i-1]);
  }

  TLegend *legend=new TLegend(0.60,0.65,0.90,0.85);
  legend->SetTextFont(62);
  legend->SetTextSize(0.05);
  legend->SetHeader(Legend+", Truth level");
  legend->AddEntry(h_Nom, "Mg5+Py8 (Nominal)","lp");
  legend->AddEntry(h_Alt, "Sherpa","lp");

  TCanvas *c = new TCanvas( "SystVar" , "SystVar" );
  TPad* p1 = new TPad("p1","p1",0.0,0.25,1.0,1.0,-22);
  TPad* p2 = new TPad("p2","p2",0.0,0.0,1.0,0.25,-21);
  p1->SetBottomMargin(0.02);
  p2->SetTopMargin(0.05);
  p2->SetBottomMargin(0.5);
  p1->Draw();
  p2->Draw();

  // First Pad
  p1->cd();
  h_Nom->Draw("HIST E");
  h_Alt->Draw("HIST E SAME");
  ATLASLabel(0.20,0.87,true);
  legend->Draw();

  // Second Pad
  p2->cd();

  TH1F* href = (TH1F*)h_Nom->Clone("ref");
  href->Divide( h_Nom );

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

  TF1 *line = new TF1("line","1",-100000,100000);
  line->SetLineColor(kBlack);
  line->SetLineWidth(1);
  line->Draw("same");

  TH1F* halt = (TH1F*)h_Alt->Clone("halt");
  halt->Divide( h_Nom );
  halt->Draw(" HIST SAME");
 
  // Write
  c->Print( "SystematicAlternative_"+Legend+".png" );
  c->Print( "SystematicAlternative_"+Legend+".eps" );
  c->Write();

  TH1F *hSyst = (TH1F*)halt->Clone("hSyst");
  for (int i=0; i<hSyst->GetNbinsX(); i++){
    Double_t VarAlt   = TMath::Abs(halt->GetBinContent(i+1)-1);
    hSyst->SetBinContent( i+1, VarAlt );
  }
  hSyst->Write();

  fFinal->Close();

}
