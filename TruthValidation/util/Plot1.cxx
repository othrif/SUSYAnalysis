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

  if( argc != 3 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
    return 0;
  }

  SetAtlasStyle();
  gStyle->SetMarkerStyle(1);
  gStyle->SetLegendBorderSize(0);

  TString file1 = argv[ 1 ];
  TString file3 = argv[ 2 ];

  TFile *f1 = new TFile( file1 );
  // TFile *fFinal = new TFile( "test.root" ,"recreate");

  TString Legend = "test";

  // const int N_histo = 26;
  // tstring h_name[N_histo] = {"h_jetN","h_jetPt","h_jetE","h_jetEta","h_jetPhi",
  // 			     "h_bjetN","h_bjetPt","h_bjetE","h_bjetEta","h_bjetPhi",
  // 			     "h_electronN","h_electronPt","h_electronE","h_electronEta","h_electronPhi","h_electronQ",
  // 			     "h_muonN","h_muonPt","h_muonE","h_muonEta","h_muonPhi","h_muonQ",
  // 			     "h_met","h_metPhi","h_meff","h_HT"};

  // const int N_histo = 92;
  // TString h_name[N_histo] = {"h_jetN","h_jetPt","h_jetE","h_jetEta","h_jetPhi",
  // 			     "h_bjetN","h_bjetPt","h_bjetE","h_bjetEta","h_bjetPhi",
  // 			     "h_electronN","h_electronPt","h_electronE","h_electronEta","h_electronPhi","h_electronQ",
  // 			     "h_muonN","h_muonPt","h_muonE","h_muonEta","h_muonPhi","h_muonQ",
  // 			     "h_met","h_metPhi","h_meff","h_HT",
  // 			     "h_sd1Pt", "h_sd1E", "h_sd1Eta", "h_sd1Phi",
  // 			     "h_sd2Pt", "h_sd2E", "h_sd2Eta", "h_sd2Phi",
  // 			     "h_top1Pt", "h_top1E", "h_top1Eta", "h_top1Phi",
  // 			     "h_top2Pt", "h_top2E", "h_top2Eta", "h_top2Phi",
  // 			     "h_s1Pt", "h_s1E", "h_s1Eta", "h_s1Phi",
  // 			     "h_s2Pt", "h_s2E", "h_s2Eta", "h_s2Phi",
  // 			     "h_b1Pt", "h_b1E", "h_b1Eta", "h_b1Phi",
  // 			     "h_b2Pt", "h_b2E", "h_b2Eta", "h_b2Phi",
  // 			     "h_w1Pt", "h_w1E", "h_w1Eta", "h_w1Phi",
  // 			     "h_w2Pt", "h_w2E", "h_w2Eta", "h_w2Phi",
  // 			     "h_TrueElN", "h_TrueElPt", "h_TrueElE", "h_TrueElEta", "h_TrueElPhi", "h_TrueElQ",
  // 			     "h_TrueMuN", "h_TrueMuPt", "h_TrueMuE", "h_TrueMuEta", "h_TrueMuPhi", "h_TrueMuQ",
  // 			     "h_TrueJetN", "h_TrueJetPt", "h_TrueJetE", "h_TrueJetEta", "h_TrueJetPhi",
  // 			     "h_TrueBJetN", "h_TrueBJetPt", "h_TrueBJetE", "h_TrueBJetEta", "h_TrueBJetPhi",
  // 			     "h_TrueMET", "h_TruePhiMET", "h_TrueHT", "h_TrueMeff"};

  const int N_histo = 100;
  TString h_name[N_histo] = {"h_jetN","h_jetPt","h_jetE","h_jetEta","h_jetPhi",
			     "h_bjetN","h_bjetPt","h_bjetE","h_bjetEta","h_bjetPhi",
			     "h_electronN","h_electronPt","h_electronE","h_electronEta","h_electronPhi","h_electronQ",
			     "h_muonN","h_muonPt","h_muonE","h_muonEta","h_muonPhi","h_muonQ",
			     "h_met","h_metPhi","h_meff","h_HT",
			     "h_go1Pt", "h_go1E", "h_go1Eta", "h_go1Phi",
			     "h_go2Pt", "h_go2E", "h_go2Eta", "h_go2Phi",
			     "h_top1Pt", "h_top1E", "h_top1Eta", "h_top1Phi",
			     "h_top2Pt", "h_top2E", "h_top2Eta", "h_top2Phi",
			     "h_up1Pt", "h_up1E", "h_up1Eta", "h_up1Phi",
			     "h_up2Pt", "h_up2E", "h_up2Eta", "h_up2Phi",
			     "h_s1Pt", "h_s1E", "h_s1Eta", "h_s1Phi",
			     "h_s2Pt", "h_s2E", "h_s2Eta", "h_s2Phi",
			     "h_b1Pt", "h_b1E", "h_b1Eta", "h_b1Phi",
			     "h_b2Pt", "h_b2E", "h_b2Eta", "h_b2Phi",
			     "h_w1Pt", "h_w1E", "h_w1Eta", "h_w1Phi",
			     "h_w2Pt", "h_w2E", "h_w2Eta", "h_w2Phi",
			     "h_TrueElN", "h_TrueElPt", "h_TrueElE", "h_TrueElEta", "h_TrueElPhi", "h_TrueElQ",
			     "h_TrueMuN", "h_TrueMuPt", "h_TrueMuE", "h_TrueMuEta", "h_TrueMuPhi", "h_TrueMuQ",
			     "h_TrueJetN", "h_TrueJetPt", "h_TrueJetE", "h_TrueJetEta", "h_TrueJetPhi",
			     "h_TrueBJetN", "h_TrueBJetPt", "h_TrueBJetE", "h_TrueBJetEta", "h_TrueBJetPhi",
			     "h_TrueMET", "h_TruePhiMET", "h_TrueHT", "h_TrueMeff"};

  for(int i=0;i<N_histo;i++){

    // ************
    // Object
    // ************

    std::cout <<  h_name[i] << std::endl;

    TH1F  *h1 = (TH1F*)f1->Get( h_name[i] );
    h1->SetLineColor(kBlue+2);

    TLegend *legend=new TLegend(0.90,0.90,0.80,0.80);
    legend->SetTextFont(62);
    legend->SetTextSize(0.035);
    legend->AddEntry(h1, Legend,"l");

    // ************
    // Canvas
    // ************

    TCanvas *c = new TCanvas( h_name[i] , h_name[i] );
    h1->Draw("HIST E");
    legend->Draw();
    c->Draw();

    // c->Print( h_name[i] + ".png" );
    if(i==0) c->Print(file3+"(");
    else c->Print(file3);
    // c->Write();

    // ************
    // Canvas Log
    // ************

    TCanvas *clog = (TCanvas*)c->Clone(h_name[i]+"_log");
    h1->SetMinimum(.1);
    gPad->SetLogy();
    clog->Draw();

    // clog->Print( h_name[i] + "_log.png" );
    if(i==(N_histo-1)) clog->Print(file3+")");
    else clog->Print(file3);
    // clog->Write();

  }

}
