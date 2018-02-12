// These are standard C++ header files.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <strstream>
#include <map>
#include <set>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>
#include <TSystem.h>
#include <TGraphAsymmErrors.h>
#include <TText.h>
#include <TKey.h>
#include <TTree.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TLine.h>
#include <TMath.h>


#include <Utils/AtlasStyle.h>
#include <Utils/AtlasLabels.h>

int main( int argc, char* argv[] ) {

  /*  if( argc != 4 ) {
    std::cout << " ERROR : WRONG NUMBER OF ARGUMENTS " << std::endl;
	std::cout << "usage: plotTest2 <path> <folder1> <folder2> <rootfilename>" << std::endl;
    return 0;
	}*/

  SetAtlasStyle();
  gStyle->SetMarkerStyle(1);
  gStyle->SetLegendBorderSize(0);

  TString filename;
  TString path = argv[1];
  TString file1 = argv[ 1+1 ]; 
  TString filePDF = argv[ 2+1 ];

  // create folder
  char fpath[512];
  sprintf(fpath, "~/workarea/tmp/plots");
  int res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }
  sprintf(fpath, "~/workarea/tmp/plots/%s", filePDF.Data());
  res = mkdir(fpath, 0700);
  if ( res == -1) {
	std::cout << "WARNING: Folder " << fpath  << " already exists!" << std::endl;
  }

  TFile *f1 = new TFile( path + "/" + file1 + "/" + filePDF + ".root");
  std::cout << "file1 " << file1 << std::endl;

  TIter nextkey( f1->GetListOfKeys() );
  TKey *key;
  int histocounter=0;
  while ( (key = (TKey*)nextkey()) ){
    TObject *obj = key->ReadObj();
	/*	if( obj->IsA()->InheritsFrom("TH1") ){
      histocounter++;
      TH1 *histo = (TH1*)(obj);
      TString histname = histo->GetName();
 
	  //	  if(!(histname.Contains("composition_el") && histname.Contains("mc_e") || histname.Contains("composition_mu") && (histname.Contains("mc_em") || histname.Contains("mc_mm"))  ))
	  if(!(histname.Contains("event_weight") || histname.Contains("event_weight_noXsec") || histname.Contains("btag_weight_noPRW")  || histname.Contains("btag_weight_PRW")  || histname.Contains("num_of_jets_noPRW") || histname.Contains("num_of_jets_PRW") || histname.Contains("num_of_jets_noPRW") || histname.Contains("num_of_leptons_PRW") || histname.Contains("num_of_leptons_noPRW") || histname.Contains("averageIntPerXing_PRW_SS3L") || histname.Contains("averageIntPerXing_PRW") || histname.Contains("averageIntPerXing_noPRW") || histname.Contains("num_vtx_PRW") || histname.Contains("num_vtx_noPRW") ))
		continue;
	  
	  TH1D  *h1 = (TH1D*)f1->Get( histname );
	  if(!h1)
		std::cout << "Problem with histogram 1" << std::endl;
	  
	  TString name; name.Form("%d",histocounter);
	  TCanvas *myCanvas = new TCanvas("myCanvas"+name, "",0,0,1600,800);
	  gStyle->SetOptStat(0);
	  gStyle->SetOptTitle(0);
	  myCanvas->SetHighLightColor(2);
	  myCanvas->Range(0,0,1,1);
	  myCanvas->SetFillColor(0);
	  myCanvas->SetBorderMode(0);
	  myCanvas->SetBorderSize(2);
	  myCanvas->SetTickx(1);
	  myCanvas->SetTicky(1);
	  myCanvas->SetLeftMargin(0.16);
	  myCanvas->SetRightMargin(0.05);
	  myCanvas->SetTopMargin(0.05);
	  myCanvas->SetBottomMargin(0.16);
	  myCanvas->SetFrameBorderMode(0);
   

	  TH1D *TH1Dplot1 = (TH1D*) h1->Clone();
	  TH1Dplot1->SetMaximum(TH1Dplot1->GetMaximum()*1.4);
	  TH1Dplot1->SetStats(0);
	  TH1Dplot1->SetLineWidth(2);
	  TH1Dplot1->SetLineColor(1);
	  TH1Dplot1->SetMarkerStyle(20);
	  TH1Dplot1->SetMarkerColor(1);
	  TH1Dplot1->GetXaxis()->SetLabelFont(42);
	  TH1Dplot1->GetXaxis()->SetLabelSize(0.05);
	  TH1Dplot1->GetXaxis()->SetTitleSize(0.05);
	  TH1Dplot1->GetXaxis()->SetTitleOffset(1.4);
	  TH1Dplot1->GetXaxis()->SetTitleFont(42);
	  TH1Dplot1->GetYaxis()->SetTitle("Events");
	  TH1Dplot1->GetYaxis()->SetLabelFont(42);
	  TH1Dplot1->GetYaxis()->SetLabelSize(0.057);
	  TH1Dplot1->GetYaxis()->SetTitleSize(0.057);
	  TH1Dplot1->GetYaxis()->SetTitleFont(42);
	  TH1Dplot1->GetZaxis()->SetLabelFont(42);
	  TH1Dplot1->GetZaxis()->SetLabelSize(0.05);
	  TH1Dplot1->GetZaxis()->SetTitleSize(0.05);
	  TH1Dplot1->GetZaxis()->SetTitleFont(42);
	
    TLegend* leg;
    leg = new TLegend(0.5, 0.85, 0.87, 0.92);
    leg->SetTextAlign(12);
    leg->SetFillColor(0);
    leg->SetTextSize(0.05);
    leg->SetTextFont(42);
    leg->SetBorderSize(0);
	std::string legendHeader = "";

	if (histname.Contains("composition_el"))
	  legendHeader += "El Composition";

	if (histname.Contains("composition_mu"))
	  legendHeader += "Mu Composition";

	if(histname.Contains("_SS3L"))
	  legendHeader += ", SS3L ";

	// channels
	if (histname.Contains("_comb_"))
	  legendHeader += ", ee+e#mu+#mu#mu";

	if (histname.Contains("_ee_"))
	  legendHeader += ", ee";
	
	if (histname.Contains("_em_"))
	  legendHeader += ", e#mu";
	
	if (histname.Contains("_mm_"))
	  legendHeader += ", #mu#mu";

	if (histname.Contains("_PRE_"))
	  legendHeader += ", Inclusive, ";

	if (histname.Contains("_CR0b_"))
	  legendHeader += ", CR0b, ";

	if (histname.Contains("_CR1b_"))
	  legendHeader += ", CR1b, ";

	if (histname.Contains("_SR3b_"))
	  legendHeader += ", SR3b";
	if (histname.Contains("_SR2b1_"))
	  legendHeader += ", SR2b1";
	if (histname.Contains("_SR2b2_"))
	  legendHeader += ", SR2b2";
	if (histname.Contains("_SR1b_"))
	  legendHeader += ", SR1b";
	if (histname.Contains("_SR0b1_"))
	  legendHeader += ", SR0b1";
	if (histname.Contains("_SR0b2_"))
	  legendHeader += ", SR0b2";
	if (histname.Contains("_SR0b5j_"))
	  legendHeader += ", SR0b5j";
	if (histname.Contains("_SR3L1_"))
	  legendHeader += ", SR3L1";
	if (histname.Contains("_SR3L2_"))
	  legendHeader += ", SR3L2";
	if (histname.Contains("_SR3l3b_"))
	  legendHeader += ", SR3l3b";
	if (histname.Contains("_SRrpv1b4j_"))
	  legendHeader += ", SRrpv1b4j";
	if (histname.Contains("_SRrpv2b4j_"))
	  legendHeader += ", SRrpv2b4j";
	if (histname.Contains("_SRrpv1b6j_"))
	  legendHeader += ", SRrpv1b6j";


	//(std::string) histname;
	leg->SetHeader(legendHeader.data());

	TH1Dplot1->SetBarWidth(1);
	TH1Dplot1->SetFillColor(kBlue);
	TH1Dplot1->Draw("hist bar");
	leg->Draw("same");

	myCanvas->SetSelected(myCanvas);
	myCanvas->SaveAs("~/workarea/tmp/plots/"+filePDF+"/"+histname+".pdf");
	}
	*/
	int histocounter2=0;
	if( obj->IsA()->InheritsFrom("TH2") ){
      histocounter2++;
      TH2 *histo2 = (TH2*)(obj);
      TString histname2 = histo2->GetName();
 
	  //	  if(!(histname.Contains("event_weight") || histname.Contains("event_weight_noXsec") || histname.Contains("btag_weight_noPRW")  || histname.Contains("btag_weight_PRW")  || histname.Contains("num_of_jets_noPRW") || histname.Contains("num_of_jets_PRW") || histname.Contains("num_of_jets_noPRW") || histname.Contains("num_of_leptons_PRW") || histname.Contains("num_of_leptons_noPRW") || histname.Contains("averageIntPerXing_PRW_SS3L") || histname.Contains("averageIntPerXing_PRW") || histname.Contains("averageIntPerXing_noPRW") || histname.Contains("num_vtx_PRW") || histname.Contains("num_vtx_noPRW") ))
	  //		continue;
	  
	  TH2D  *h2 = (TH2D*)f1->Get( histname2 );
	  if(!h2)
		std::cout << "Problem with histogram 1" << std::endl;

	  TString name2; name2.Form("%d",histocounter2);
	  TCanvas *myCanvas2 = new TCanvas("myCanvas2"+name2, "",0,0,1600,800);
	  gStyle->SetOptStat(0);
	  gStyle->SetOptTitle(0);
	  myCanvas2->SetHighLightColor(2);
	  myCanvas2->Range(0,0,1,1);
	  myCanvas2->SetFillColor(0);
	  myCanvas2->SetBorderMode(0);
	  myCanvas2->SetBorderSize(2);
	  myCanvas2->SetTickx(1);
	  myCanvas2->SetTicky(1);
	  myCanvas2->SetLeftMargin(0.16);
	  myCanvas2->SetRightMargin(0.05);
	  myCanvas2->SetTopMargin(0.05);
	  myCanvas2->SetBottomMargin(0.16);
	  myCanvas2->SetFrameBorderMode(0);

	h2->Draw("colz");
	std::cout << "histname2" << std::endl;
	myCanvas2->SetSelected(myCanvas2);
	myCanvas2->SaveAs("~/workarea/tmp/plots/"+filePDF+"/"+histname2+".pdf");

	}
  }
}
