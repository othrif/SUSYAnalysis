/*****************************************************************************/
/*                                                                           */
/* File Name        : plotMC.cxx                                             */
/* Description      : Plot pure MC                                           */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/*                                                                           */
/* Description      :                                                        */
/*                                                                           */
/***** C 2016 ****************************************************************/

// These are standard C++ header files.
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

// These are ROOT header files.
#include "TMath.h"
#include "Rtypes.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TFile.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TH1D.h"
#include "THStack.h"
#include "TRandom.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TObjArray.h"
#include "TMinuit.h"
#include "RooStats/NumberCountingUtils.h"
#include "TPaveText.h"

//here are the project-specific files
#include "Plotter/plotter_MCSignal.h"
#include "Utils/AtlasUtils.h"
#include "Utils/AtlasStyle.h"

using namespace std;

//-----------------------------------------------------------------------------
// Main routine
//-----------------------------------------------------------------------------

int main(int argc, char **argv ) {
  
  /*  if (argc < 3) {
	std::cout << "Usage: " << argv[0] << " PATH FOLDER\n";
	return 1;
	}*/



  SetAtlasStyle(); 
  
  TString path = "/afs/cern.ch/user/o/othrif/workarea/results/v44/testing";
  TString tempname;
  TString ranges_ptmet[] = {"pt10","pt15","pt20","met0", "met150", "met200", "met250", "met300"};
  TString channels[] = {"comb", "ee", "em", "mm"};
  TH1F * hist;//[8*4];

  for (int i = 0; i<8; i++)
	for (int j = 0; j<4; j++){
	  tempname = Form("Canvas%d%d",i,j);
	  TCanvas* myPlots = new TCanvas(tempname, tempname, 50, 50, 600, 600);
	  THStack *hs = new THStack("hs",tempname);
	  TLegend *leg = new TLegend(0.7,0.7,0.9,0.9);
	  leg->SetHeader("");
	  TPaveText *pt = new TPaveText(0.16,0.86,0.5,.96,"brNDC");
	  TFile *f = new TFile(path+"/ttbar.root");
	  tempname = "triggers_"+channels[j]+"_"+ranges_ptmet[i]+"_Incl_SS3L";
	  std::cout << tempname << std::endl;
	  hist = (TH1F*) gDirectory->Get(tempname);
	  hist->SetDirectory(0); 
	  hist->SetFillColor(j+2);
	  hist->SetMarkerStyle(21);
	  hist->SetMarkerColor(j+2);
	  hist->Draw();
	  f->Close();	 
	  //	  myPlots->Update();
	}

  //  gSystem->Exit(0);
  return 0;
}
