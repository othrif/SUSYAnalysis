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

#include <Utils/AtlasStyle.h>
#include <Utils/AtlasLabels.h>

int main( int argc, char* argv[] ) {

  if( argc != 10 ) {
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
  TString file5 = argv[ 5 ];
  TString file6 = argv[ 6 ];
  TString file7 = argv[ 7 ];
  TString file8 = argv[ 8 ];
  TString Legend = argv[ 9 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *f3 = new TFile( file3 );
  TFile *f4 = new TFile( file4 );
  TFile *f5 = new TFile( file5 );
  TFile *f6 = new TFile( file6 );
  TFile *f7 = new TFile( file7 );
  TFile *fFinal = new TFile( file8 ,"recreate");

  TH1F  *h_Nom   = (TH1F*)f1->Get( "h_Acceptance" );
  TH1F  *h_FUp   = (TH1F*)f2->Get( "h_Acceptance" );
  TH1F  *h_FDown = (TH1F*)f3->Get( "h_Acceptance" );
  TH1F  *h_RUp   = (TH1F*)f4->Get( "h_Acceptance" );
  TH1F  *h_RDown = (TH1F*)f5->Get( "h_Acceptance" );
  TH1F  *h_QUp   = (TH1F*)f6->Get( "h_Acceptance" );
  TH1F  *h_QDown = (TH1F*)f7->Get( "h_Acceptance" );

  h_Nom->SetLineColor(kBlack);
  h_FUp->SetLineColor(kRed+1);
  h_FUp->SetMarkerColor(kRed+1);
  h_FDown->SetLineColor(kRed+1);
  h_FDown->SetMarkerColor(kRed+1);
  h_FDown->SetLineStyle(7);
  h_RUp->SetLineColor(kBlue+1);
  h_RUp->SetMarkerColor(kBlue+1);
  h_RDown->SetLineColor(kBlue+1);
  h_RDown->SetMarkerColor(kBlue+1);
  h_RDown->SetLineStyle(7);
  h_QUp->SetLineColor(kGreen+1);
  h_QUp->SetMarkerColor(kGreen+1);
  h_QDown->SetLineColor(kGreen+1);
  h_QDown->SetMarkerColor(kGreen+1);
  h_QDown->SetLineStyle(7);

  h_Nom->GetXaxis()->SetLabelOffset(0.045);
  h_Nom->SetTitle("");
  h_Nom->GetXaxis()->SetTitle("Signal Region");
  h_Nom->GetYaxis()->SetTitle("Acceptance");
  h_Nom->SetMaximum( std::max(h_Nom->GetMaximum(),
			      h_FUp->GetMaximum() )*1.2 );
  const int num = 3;
  TString Ax_SR[num] = {"3LSS","#geq 1 b-jets", ""}; //{"SRVLQ0","SRVLQ1","SRVLQ2","SRVLQ3","SRVLQ4","SRVLQ5","SRVLQ6","SRVLQ7"};
  for (int i=1; i<=num; i++) {
    h_Nom->GetXaxis()->SetBinLabel(i,Ax_SR[i-1]);
  }

  TLegend *legend=new TLegend(0.70,0.30,0.90,0.85);
  legend->SetTextFont(62);
  legend->SetTextSize(0.05);
  legend->SetHeader("#splitline{"+Legend+"}{Truth level}");
  legend->AddEntry(h_Nom, "Nominal","lp");
  legend->AddEntry(h_FUp, "#mu_{F}=2","lp");
  legend->AddEntry(h_FDown, "#mu_{F}=0.5","lp");
  legend->AddEntry(h_RUp, "#mu_{R}=2","lp");
  legend->AddEntry(h_RDown, "#mu_{R}=0.5","lp");
  legend->AddEntry(h_QUp, "#mu_{Q}=2","lp");
  legend->AddEntry(h_QDown, "#mu_{Q}=0.5","lp");

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
  h_FUp->Draw("HIST E SAME");
  h_FDown->Draw("HIST E SAME");
  h_RUp->Draw("HIST E SAME");
  h_RDown->Draw("HIST E SAME");
  h_QUp->Draw("HIST E SAME");
  h_QDown->Draw("HIST E SAME");
  ATLASLabel(0.20,0.87,true);
  legend->Draw();

  // Second Pad
  p2->cd();

  TH1F* href = (TH1F*)h_Nom->Clone("ref");
  href->Divide( h_Nom );

  href->SetMaximum(1.25);
  href->SetMinimum(0.75);

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

  TH1F* hFup = (TH1F*)h_FUp->Clone("hFup");
  hFup->Divide( h_Nom );
  hFup->Draw(" HIST SAME");

  TH1F* hFdown = (TH1F*)h_FDown->Clone("hFdown");
  hFdown->Divide( h_Nom );
  hFdown->Draw("HIST SAME");

  TH1F* hRup = (TH1F*)h_RUp->Clone("hRup");
  hRup->Divide( h_Nom );
  hRup->Draw(" HIST SAME");

  TH1F* hRdown = (TH1F*)h_RDown->Clone("hRdown");
  hRdown->Divide( h_Nom );
  hRdown->Draw("HIST SAME");

  TH1F* hQup = (TH1F*)h_QUp->Clone("hQup");
  hQup->Divide( h_Nom );
  hQup->Draw(" HIST SAME");

  TH1F* hQdown = (TH1F*)h_QDown->Clone("hQdown");
  hQdown->Divide( h_Nom );
  hQdown->Draw("HIST SAME");
 
  // Write
  // c->Print( h_name[i] + ".png" );
  c->Write();
  fFinal->Close();

}
