// Othmane Rifki
// othrif@cern.ch 
// Apr 2015

// Read histograms from only signal and plot them

 #include "AtlasUtils.h"
 #include "AtlasStyle.C"

read_sig(){

#ifdef __CINT__
  gROOT->LoadMacro("AtlasUtils.C");
#endif
  
  SetAtlasStyle(); 

  const unsigned int N_SETS=10;
const unsigned int N_dist=5;

 const TString dist_sig[N_dist]={"num_bjets", "mT", "num_jets", "met", "meff"};
 const TString names[N_SETS] ={"G1250_T2500_L985", "G1150_T2500_L885", "G1050_T2500_L785", "G1050_T2500_L735" , "G950_T2500_L685" , "G950_T2500_L635" ,"G850_T2500_L585" , "G850_T2500_L535" ,"G750_T2500_L485","G750_T2500_L435" }; 
 const TString files[N_SETS] = {
   "user.othrif.mc12_8TeV.204171.MadGraphPythia_Gtt5body_G1250_T2500_L985.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426312_plots.root",
"user.othrif.mc12_8TeV.204170.MadGraphPythia_Gtt5body_G1150_T2500_L885.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426308_plots.root"
   ,
   "user.othrif.mc12_8TeV.204167.MadGraphPythia_Gtt5body_G1050_T2500_L785.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426238_plots.root",
"user.othrif.mc12_8TeV.204166.MadGraphPythia_Gtt5body_G1050_T2500_L735.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426213_plots.root"
   ,
   "user.othrif.mc12_8TeV.204163.MadGraphPythia_Gtt5body_G950_T2500_L685.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426187_plots.root",
   "user.othrif.mc12_8TeV.204162.MadGraphPythia_Gtt5body_G950_T2500_L635.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426086_plots.root",
   "user.othrif.mc12_8TeV.204159.MadGraphPythia_Gtt5body_G850_T2500_L585.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426029_plots.root",
   "user.othrif.mc12_8TeV.204158.MadGraphPythia_Gtt5body_G850_T2500_L535.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24426030_plots.root",
   "user.othrif.mc12_8TeV.204155.MadGraphPythia_Gtt5body_G750_T2500_L485.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24425993_plots.root",
"user.othrif.mc12_8TeV.204154.MadGraphPythia_Gtt5body_G750_T2500_L435.MINI.e2954_a220_a205_r4540_p1328.v17.15.0_out1.root.24425935_plots.root"
};
  TFile *f_data, *f_sig;
  TH1D* hist[N_SETS],* DATA;
  Int_t color[N_SETS]; //Fill colors of the histograms
  Int_t lineColor[N_SETS]; //Line colors of the histograms

 
  for (int dist; dist<N_dist; dist++){

  TCanvas * plots1;
  TPad* thePad1;
  plots1 = new TCanvas("c2", "c2", 50, 50, 600, 600);

  TLegend* leg;
  leg = new TLegend(0.6, 0.7, 0.8, 0.92); //65
  leg->SetTextAlign(12);
  leg->SetFillColor(0);
  leg->SetTextSize(0.02); //0.032
  leg->SetBorderSize(0);


  /*
  f_data = new TFile("/users/orifki/workarea/analysisarea/ttV_fakes/fake_study/data.root", "READ");
  DATA =(TH1D*) f_data->Get(dist_data[dist]+"_elmu_b1HTm_NOMINAL");
  DATA->SetDirectory(gROOT);
  DATA->SetLineColor(1);
  DATA->SetFillColor(0);
  DATA->SetLineWidth(1);
  Double_t norm = DATA->GetEntries();//->GetSumOfWeights();//->GetEntries();
  if (norm) DATA->Scale(1/norm);
  */


	for (int i = 0; i < N_SETS; i++) {
 	  color[i] = 0;
 	  lineColor[i] = 1+i;
 	}
	lineColor[N_SETS-1] = 11;
	lineColor[4] = 12;


	for (int i=0;i<N_SETS;i++){
	f_sig = new TFile("results/"+files[i], "READ");

	hist[i] =(TH1D*) f_sig->Get(dist_sig[dist]);
	hist[i]->SetDirectory(gROOT);
	hist[i]->SetLineColor(lineColor[i]);
	hist[i]->SetFillColor(color[i]);
	hist[i]->SetLineWidth(1);
	Double_t norm = hist[i]->GetEntries();//->GetSumOfWeights();//->GetEntries();
	if (norm) hist[i]->Scale(1/norm);

	hist[i]->SetMaximum( hist[i]->GetBinContent(hist[i]->GetMaximumBin())*1.2);
	hist[i]->GetYaxis()->SetTitle();
  

if (strstr(hist[i]->GetName(), "HT_") != NULL)
hist[i]->GetXaxis()->SetTitle("H_{T} [GeV]");
// 0 N(jets) NJETS
if (strstr(hist[i]->GetName(), "NJETS") != NULL)
hist[i]->GetXaxis()->SetTitle("N(jets)");
// 1 E_{T}^{miss} [GeV] MET
if (strstr(hist[i]->GetName(), "MET") != NULL)
hist[i]->GetXaxis()->SetTitle("E_{T}^{miss} [GeV]");
  hist[i]->GetXaxis()->SetLabelFont(43);
		hist[i]->GetXaxis()->SetLabelSize(25);
		hist[i]->GetYaxis()->SetLabelFont(43);
		hist[i]->GetYaxis()->SetLabelSize(25);

		hist[i]->GetXaxis()->SetTitleFont(43);
		hist[i]->GetXaxis()->SetTitleSize(29);
		hist[i]->GetYaxis()->SetTitleFont(43);
		hist[i]->GetYaxis()->SetTitleSize(29);

		hist[i]->GetYaxis()->SetTitleOffset(2.0);


 hist[i]->Draw("same hist 9");


  leg->AddEntry(hist[i], "Signal " + names[i], "l");
  leg->Draw("same");
  plots1->Update();
 
	}
 TString my_extension = "results/plots/"+dist_sig[dist]+".eps";
 plots1->Print(my_extension); 

  }

}


