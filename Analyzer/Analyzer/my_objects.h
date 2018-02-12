/*****************************************************************************/
/*                                                                           */
/* File Name        : my_objects.h                                           */
/*                                                                           */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/*                                                                           */
/* Description      : Provides function declarations for my_objects.cxx      */
/*                                                                           */   
/*                    Code based on Sasha's Plotter package                  */   
/*                                                                           */   
/***** C 2015 ****************************************************************/

#ifndef _MY_OBJECTS_H
#define _MY_OBJECTS_H

// These are ROOT header files.
#include "TVector3.h"
#include "TVector2.h"
#include "TTree.h"

//here are the project-specific files
#include "Analyzer/myevt.h"

using namespace std;

//------------------------------------------------------------------------
//				-= Constants =-
//------------------------------------------------------------------------

#define muon_mass             105.6583715   // in MeV
#define electron_mass         0.510998928   // in MeV
#define LeptPt                20000 //10000.        // in MeV
#define LeptPt10                10000 //10000.        // in MeV
#define LargeNum              99999999999. 

//------------------------------------------------------------------------
//				-= Histograms =-
//------------------------------------------------------------------------
void muon_composition(myevt *evt, my_leptons *lep_signal, int lepi);
void BookHistos_Channel(const char* ftag, const char* tag);
void BookHistos_SystSet(const char* ftag, const char* tag);
void BookHistos_Regions(const char* ftag, const char* tag);
void BookHistos(const char* ftag, const char* tag);
void BookHistos_New(const char* ftag, const char* tag);
void BookHistos_FS(const char* tag);
void BookHistos_Comp(const char* tag);
void BookHistos_pt(const char* tag);
void BookHistos_Comp_FS(const char* tag);
void FillHistos_Regions(const char* ftag, const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet);
void FillHistos_Channels(const char* ftag, const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet);
void FillHistos_Composition(const char* ftag, const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet);
void FillHistos_Comp_Variables(const char* tag, myevt *evt, my_leptons *lep);
void FillHistos_Variables(const char* tag, myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet);
void fillHist(const char* hname, const char* tag, float val, double weight);
void fill2DHist(const char* hname, float x, float y, double weight);
void fill2DHist(const char* hname, const char* tag, float x, float y, double weight);
void fillTProfile(const char* hname, const char* tag, float x, float y, double weight);
//------------------------------------------------------------------------
//				-= Functions Declarations =-
//------------------------------------------------------------------------
// in the order they appear in my_objects.cxx

int jet_pt_comparator(const void * a, const void * b);
void sortLeptons(my_leptons *lep);
void sortLeptons(my_jets *jet);
double DeltaR(float eta1, float phi1, float eta2, float phi2);
double DeltaPhi(float phi1, float phi2);
void classify_jets(myevt *evt, my_jets  *jet);
void classify_leptons(myevt *evt, my_leptons *lep);
void classify_leptons_custom(myevt *evt, my_leptons *lep);

bool checkTriggerMatching(myevt *evt, my_leptons *lep);

bool jet_overlaps_electron(myevt *evt, int jeti);
bool electron_overlaps_jet(myevt *evt, int eli, my_jets *jet_4Overlap);
bool electron_overlapsdR_jet(myevt *evt, int eli, my_jets *jet);
bool muon_overlaps_jet(myevt *evt, int mui, my_jets *jet_4Overlap);
bool muon_overlapsdR_jet(myevt *evt, int mui, my_jets *jet);
bool jet_overlaps_muon(myevt *evt, int jeti, my_leptons *mu_4Overlap);
bool electron_overlaps_muon(myevt *evt, int eli, my_leptons *muon_4Overlap);
bool electron_overlaps_electron(myevt *evt, int eli, my_leptons *elec_4Overlap);
bool muon_overlaps_electron(myevt *evt, int mui, my_leptons *elec_4Overlap);

bool is_baseline_electron(myevt *evt, int eli);
bool is_baseline_muon(myevt *evt, int mui);
bool is_baseline_jet(myevt *evt, int jetk);

bool is_signal_electron(myevt *evt, int eli);
bool is_signal_muon(myevt *evt, int mui);
bool is_signal_jet(myevt *evt, int jeti);
bool is_signal_bjet(myevt *evt, int jeti);
bool is_signal_bjet(myevt *evt, int jeti, int cut);

void SetChannelSeparation(my_leptons *lep, float minpt1, float maxpt1,float minpt2, float maxpt2);
void SetChannelSeparation(my_leptons *lep);

bool NoCosmicMuon(myevt *evt, my_leptons * lep);
double dilepton_mass(myevt *evt, my_leptons *lep);
double dilepton_mass_ss(myevt *evt, my_leptons *lep);
double multilepton_mass(myevt *evt, my_leptons *lep);
void dilepton_mass_comb(myevt *evt, my_leptons *lep);
double dilepton_mass_lead(myevt *evt, my_leptons *lep);
double trilepton_mass_lead(myevt *evt, my_leptons *lep);
double dijet_mass(my_jets *jet);
double leading_dilepton_mass(myevt *evt, my_leptons *lep);
bool lepton_pt_good(my_leptons *lep, float minpt1, float maxpt1,float minpt2, float maxpt2);
double transverse_mass(myevt *evt, my_leptons *lep);
double transverse_mass_min(myevt *evt, my_leptons *lep);
void containsZ(myevt *evt, my_leptons *lep);

void debug_printall(myevt *evt);
void debug_lept(myevt *evt, my_leptons *lep);
void debug_truth_lept(myevt *evt, my_leptons *lep);
void debug_charge(myevt *evt, my_leptons *lep);
void debug_jet(myevt *evt, my_jets *jet);
void debug_lept(myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet);
void debug_objects(myevt *evt, my_leptons *lep, my_jets *jet, FILE* fp, bool record);
void debug_SR_VR(myevt *evt, my_leptons *lep, my_jets *jet, my_jets *bjet, FILE* fp, bool record);
bool is_CF_source(myevt *evt);
bool is_FullSim(myevt *evt);
// For Analyzer
extern const char* cut_name[28];

#endif

