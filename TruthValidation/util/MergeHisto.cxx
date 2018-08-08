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

  if( argc != 4 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  SetAtlasStyle();


  TString file1 = argv[ 1 ];
  TString file2 = argv[ 2 ];
  TString file3 = argv[ 3 ];

  TFile *f1 = new TFile( file1 );
  TFile *f2 = new TFile( file2 );
  TFile *fFinal = new TFile( "test.root" ,"recreate");

  TString h_name[25] = {"h_jetN","h_jetPt","h_jetE","h_jetEta","h_jetPhi",
			"h_bjetN","h_bjetPt","h_bjetE","h_bjetEta","h_bjetPhi",
			"h_electronN","h_electronPt","h_electronE","h_electronEta","h_electronPhi","h_electronQ",
			"h_muonN","h_muonPt","h_muonE","h_muonEta","h_muonPhi","h_muonQ",
			"h_met","h_metPhi","h_meff"};

  for(int i=0;i<25;i++){

    // Object
    TH1F  *h1 = (TH1F*)f1->Get( h_name[i] );
    h1->SetLineColor(kBlue+2);
    h1->GetXaxis()->SetLabelOffset(0.05);

    TH1F  *h2 = (TH1F*)f2->Get( h_name[i] );
    h2->SetMarkerStyle(1);
    h2->SetLineColor(kRed+2);

    TLegend *legend=new TLegend(0.90,0.90,0.80,0.80);
    legend->SetTextFont(62);
    legend->SetTextSize(0.035);
    legend->AddEntry(h1, "mc12","l");
    legend->AddEntry(h2, "mc15","l");

    TCanvas *c = new TCanvas( h_name[i] , h_name[i] );
    TPad* p1 = new TPad("p1","p1",0.0,0.25,1.0,1.0,-22);
    TPad* p2 = new TPad("p2","p2",0.0,0.0,1.0,0.25,-21);
    p1->SetBottomMargin(0.02);
    p2->SetTopMargin(0.05);
    p2->SetBottomMargin(0.5);
    p1->Draw();
    p2->Draw();

    // First Pad
    p1->cd();
    h1->Draw("HIST");
    h2->Draw("HIST E SAME");
    legend->Draw();

    // Second Pad
    p2->cd();

    TH1F* href = (TH1F*)h2->Clone("ref");
    for (Int_t ik = 1; ik <= href->GetXaxis()->GetNbins(); ik++) href->SetBinContent( ik , 1. );

    href->SetLineColor(kBlack);
    href->SetLineWidth(1);
    href->SetLineStyle(2);

    href->SetMaximum(1.75);
    href->SetMinimum(0.25);

    href->GetYaxis()->SetTitle("MC15/MC12");

    href->GetXaxis()->SetLabelSize(0.17);
    href->GetYaxis()->SetNdivisions(505);
    href->GetYaxis()->SetLabelSize(0.12);

    href->GetXaxis()->SetTitleSize(0.17);
    href->GetXaxis()->SetTitleOffset(1.35);
    href->GetYaxis()->SetTitleSize(0.12);
    href->GetYaxis()->SetTitleOffset(0.5);

    href->Draw("HIST");

    TH1F* hR = (TH1F*)h2->Clone("ratio");
    hR->Divide(h1);
    hR->SetMarkerStyle(1);

    for (Int_t ik = 1; ik <= hR->GetXaxis()->GetNbins(); ik++) {
      if(h1->GetBinContent(ik)>0. && h2->GetBinContent(ik)>0.)
        hR->SetBinError( ik , hR->GetBinContent(ik) * ( (h1->GetBinError(ik)/h1->GetBinContent(ik)) + (h2->GetBinError(ik)/h2->GetBinContent(ik)) ) );
    }

    hR->Draw("HIST E SAME");

    // Write

    c->Print( h_name[i] + ".png" );

    // if(i==0) c->Print(file3+"(");
    // else c->Print(file3);

    // c->Write();

    TCanvas *clog = new TCanvas( h_name[i]+"_log" , h_name[i]+"_log" );

    TPad *p1log = (TPad*)p1->Clone();
    p1log->SetLogy(1);

    p1log->Draw();
    p2->Draw();

    clog->Print( h_name[i] + "_log.png" );

    // if(i==24) clog->Print(file3+")");
    // else clog->Print(file3);

    // clog->Write();

  }

}
