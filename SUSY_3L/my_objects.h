#ifndef _MY_OBJECTS_H
#define _MY_OBJECTS_H

#include "TVector3.h"
#include "TVector2.h"
#include "myevt.h"
#include "TTree.h"

#include "DileptonTriggerTool.h"
#include "MissingETUtility/METUtility.h"

//Tools and corrections for muons
#include "MuonEfficiencyCorrections/AnalysisMuonConfigurableScaleFactors.h"
#include "MuonMomentumCorrections/SmearingClass.h"
#include "egammaAnalysisUtils/EnergyRescalerUpgrade.h"
#include "egammaAnalysisUtils/IsEMPlusPlusDefs.h"
#include "egammaEvent/egammaPIDdefs.h"

// 15 GeV cut-off on the minimum pT of signal leptons
#define LeptPt 20000. //25000.

//--------------------------------------------------------------------

struct lepton_info {
	int num_leptons; // leptons are counted at 18 GeV or higher
	int num_20GeV_leptons_noverlap; // 3 or more signal leptons && lepton-lepton overlap removed
	int num_10GeV_leptons_noverlap; // 3 or more signal leptons && lepton-lepton overlap removed
	float total_charge; // for the first three leptons
	int softest_ss; // the softest lepton that has the same sign as the three leptons
	bool is_tight_3rd_lep;

	bool has_Z;
	double MZ;
	double lowest_M;
	int ind1;
	int ind2;

	int index[2 * MAXLEPT];
	double pt[2 * MAXLEPT];
	bool is_electron[2 * MAXLEPT];
	bool lept_overlap[2 * MAXLEPT];
	float charge[2 * MAXLEPT];

	bool is_fake[2 * MAXLEPT];
	bool is_chmisid[2 * MAXLEPT];

	double delta_met_x; //recalculated when we smear or shirt momenta of the leptons
	double delta_met_y;
};

typedef struct lepton_info my_leptons;

//From SUSYTools

namespace SystErr {
typedef enum {
	NONE,
	JESDOWN,
	JESUP,
	JER,
	EESDOWN,
	EESUP,
	ERESDOWN,
	ERESUP,
	EEFFDOWN,
	EEFFUP,
	ETRGDOWN,
	ETRGUP,
	MMSLOW,
	MMSUP,
	MIDLOW,
	MIDUP,
	MEFFDOWN,
	MEFFUP,
	MTRGDOWN,
	MTRGUP,
	PESDOWN,
	PESUP,
	PRESDOWN,
	PRESUP,
	BJETDOWN,
	BJETUP,
	CJETDOWN,
	CJETUP,
	BMISTAGDOWN,
	BMISTAGUP,
	SCALESTUP,
	SCALESTDOWN,
	RESOSTUP,
	RESOSTDOWN
} Syste;
}

// Books  a set of Jet Histograms
void BookHistos(const char* tag);
void BookHistos_New(const char* tag);
void BookHistos_FS(const char* tag);
void BookHistos_SystSet(const char* tag);

// Fills a set of Jet Histograms
void FillJetHistos_FinalState(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap);
void FillJetHistos_New(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap);
void FillJetHistos_SetOfFinalStates(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap, DileptonTriggerTool* _dileptonTriggerTool);
void FillJetHistos_Kenematics(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap, DileptonTriggerTool* _dileptonTriggerTool);

void FillJetHistos(const char* tag, myevt *evt, calJet *jet, calJet *syst_jet, calJet *jet_D3PD, my_leptons *lep, my_leptons *lep_met, my_leptons *elec_4jetOverlap,
		SystErr::Syste whichsyste, METUtility* _metUtility, DileptonTriggerTool* _dileptonTriggerTool);
void FillJetHistos(const char* tag, myevt *evt, calJet *jet, my_leptons *lep, my_leptons *elec_4jetOverlap, DileptonTriggerTool* _dileptonTriggerTool);

//Fill a Histogram
void fillHist(const char* hname, const char* tag, float val, double weight);
void fillHist(const char* hname, float val, double weight);
void fillHistDiff(const char* hname, const char* tag, float val, double weight);
void fill2DHist(const char* hname, const char* tag, float x, float y, double weight);
void fill2DHist(const char* hname, float x, float y, double weight);
void fillTProfile(const char* hname, const char* tag, float x, float y, double weight);

double DeltaR(float eta1, float phi1, float eta2, float phi2);
double DeltaPhi(float phi1, float phi2);

bool isCleanMet(calJet *jet, myevt *evt, my_leptons *elec_4jetOverlap);
bool HEC_Veto(calJet *jet, myevt *evt);

//bool IsLArHole(float eta, float phi);

double rapidity(double E, double pz);

bool Muon_IdHitReq(myevt *evt, int i);
double calc_d0(myevt *evt, int i);

//_____________________________________________________________
//This Collection is designed to sort jets easier
struct short_jet {
	double pt;
	int ind;
};

typedef struct short_jet srtJt;

//We need it to compare to jets
int jet_pt_comparator(const void * a, const void * b);

// muon selection
bool is_preselection_muon_noIso(myevt *evt, int i, float pt);
bool is_preselection_muon(myevt *evt, int i, float pt, my_leptons *elec_4jetOverlap);
bool is_tight_muon(myevt *evt, int i, float pt, my_leptons *elec_4jetOverlap, int Nvtx5Trk);

// electron selection
bool is_good_electron(myevt *evt, int i, double pt_cut);

bool is_preselection_electron_4met(myevt *evt, int i, float el_pt);
bool is_preselection_electron_nonIso(myevt *evt, int i, float el_pt);
bool is_preselection_electron(myevt *evt, int i, float el_pt, my_leptons *elec_4jetOverlap);
bool is_tight_electron(myevt *evt, int i, float el_pt, my_leptons *elec_4jetOverlap, int Nvtx5Trk);

void calcNum20GeVleptons(my_leptons *lep, myevt *evt, my_leptons *lep_baseline, my_leptons * elec_4jetOverlap);
void calcChargeLeptons(my_leptons *lep, myevt *evt);
void sortLeptons(my_leptons *lep);

float calcM_lept_jet(myevt *evt, my_leptons *lep, int j, int i);
bool jet_overlaps_electron(myevt *evt, my_leptons *elec_4jetOverlap, int i);

void containsZ(my_leptons *lep, myevt *evt);

double CalcMass(myevt *evt, int ind0, int ind1);

//Here we re-calculate missing-pT
TVector2 getMET(myevt *evt, calJet *jet, calJet *jet_D3PD, my_leptons *lep, SystErr::Syste whichsyste, METUtility* _metUtility);

void smearMuonPt(myevt *evt, my_leptons *lep, MuonSmear::SmearingClass *mcp_smear);
float smear_A_MuonPt(myevt *evt, int mu_ind, MuonSmear::SmearingClass *mcp_smear);

void smearElectronPt(myevt *evt, my_leptons *lep, egRescaler::EnergyRescalerUpgrade* eRescale);
float smear_An_ElectronPt(myevt *evt, int el_ind, egRescaler::EnergyRescalerUpgrade* eRescale);

void scaleElectronPt(myevt *evt, my_leptons *lep, egRescaler::EnergyRescalerUpgrade* eRescale, bool isATLFAST);
float scale_An_ElectronPt(myevt *evt, int el_ind, egRescaler::EnergyRescalerUpgrade* eRescale, bool isATLFAST);

void smearMuonPt_syst(myevt *evt, my_leptons *lep, MuonSmear::SmearingClass *mcp_smear, const char* type);

bool NoBadMuon(myevt *evt, my_leptons * lep_met, my_leptons * elec_4jetOverlap);
bool NoCosmicMuon(myevt *evt, my_leptons * lep_met, my_leptons * elec_4jetOverlap);

double dilepton_mass(my_leptons *lep, myevt *evt);
double trilepton_mass(my_leptons *lep, myevt *evt);
double transverse_mass(my_leptons *lep, myevt *evt);

bool SetChannelAlternate(my_leptons* lep, myevt *evt);
bool is_ee(my_leptons* lep, myevt *evt);
bool is_em(my_leptons* lep, myevt *evt);
bool is_mm(my_leptons* lep, myevt *evt);

bool trigger_ee(my_leptons *lep, myevt *evt, DileptonTriggerTool* _dileptonTriggerTool, double& triggerWeight);
bool trigger_em(my_leptons *lep, myevt *evt, DileptonTriggerTool* _dileptonTriggerTool, double& triggerWeight);
bool trigger_mm(my_leptons *lep, myevt *evt, DileptonTriggerTool* _dileptonTriggerTool, double& triggerWeight);
float Get_CrossSection(TString* filename);
float Get_CrossSection_13(TString* filename);
#endif

