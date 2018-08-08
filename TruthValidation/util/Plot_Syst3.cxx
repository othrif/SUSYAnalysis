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
  TString file4 = argv[ 4 ];
  TString Legend = argv[ 5 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *f3 = new TFile( file3 );
  TFile *fFinal = new TFile( file4 ,"recreate");

  TH1F  *h_Nom  = (TH1F*)f1->Get( "h_Acceptance" );
  TH1F  *h_Up   = (TH1F*)f2->Get( "h_Acceptance" );
  TH1F  *h_Down = (TH1F*)f3->Get( "h_Acceptance" );

  h_Nom->SetLineColor(kBlack);
  h_Up->SetLineColor(kRed+1);
  h_Up->SetMarkerColor(kRed+1);
  h_Down->SetLineColor(kBlue+2);
  h_Down->SetMarkerColor(kBlue+2);

  h_Nom->GetXaxis()->SetLabelOffset(0.045);
  h_Nom->SetTitle("");
  h_Nom->GetXaxis()->SetTitle("Signal Region");
  h_Nom->GetYaxis()->SetTitle("Acceptance");
  h_Nom->SetMaximum( std::max(h_Nom->GetMaximum(),
				     h_Up->GetMaximum() )*1.2 );
  TString Ax_SR[8] = {"SRVLQ0","SRVLQ1","SRVLQ2","SRVLQ3","SRVLQ4","SRVLQ5","SRVLQ6","SRVLQ7"};
  for (int i=1; i<=8; i++) {
    h_Nom->GetXaxis()->SetBinLabel(i,Ax_SR[i-1]);
  }

  TLegend *legend=new TLegend(0.70,0.65,0.90,0.85);
  legend->SetTextFont(62);
  legend->SetTextSize(0.05);
  legend->SetHeader(Legend+", Truth level");
  legend->AddEntry(h_Nom, "Nominal","lp");
  legend->AddEntry(h_Up, "#mu_{R/F}=2","lp");
  legend->AddEntry(h_Down, "#mu_{R/F}=1/2","lp");

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
  h_Up->Draw("HIST E SAME");
  h_Down->Draw("HIST E SAME");
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

  TH1F* hup = (TH1F*)h_Up->Clone("hup");
  hup->Divide( h_Nom );
  hup->Draw(" HIST SAME");

  TH1F* hdown = (TH1F*)h_Down->Clone("hdown");
  hdown->Divide( h_Nom );
  hdown->Draw("HIST SAME");
 
  // Write
  c->Print( "SystematicVariation_"+Legend+".png" );
  c->Write();

  TH1F *hSyst = (TH1F*)hup->Clone("hSyst");
  for (int i=0; i<hSyst->GetNbinsX(); i++){

    Double_t VarUp   = hup->GetBinContent(i+1)-1;
    Double_t VarDown = hdown->GetBinContent(i+1)-1;

    if(VarUp*VarDown >= 0){
      if( TMath::Abs(VarUp) > TMath::Abs(VarDown) )
  	hSyst->SetBinContent( i+1, TMath::Abs(VarUp) );
      else
  	hSyst->SetBinContent( i+1, TMath::Abs(VarDown) );
    }

    if(VarUp*VarDown < 0)
      hSyst->SetBinContent( i+1, (TMath::Abs(VarUp)+TMath::Abs(VarDown))/2 );

    hSyst->SetBinError( i+1, 0 );

  }
  hSyst->Write();

  fFinal->Close();

  

}
