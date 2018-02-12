/*****************************************************************************/
/*                                                                           */
/* File Name        : FakeLepMCTemplate.cxx                                  */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/* Description      : Source file for the MCTemplateCorr class               */
/*                                                                           */
/* Example of usage:                                                         */
/*                                                                           */
/* In your analysis code, include the header: include "MCTemplateCorr.h"     */
/* Before the event loop, declare:  MCTemplateCorr fakeCorr;                 */
/*                                                                           */
/* In the event loop, for each event add the collection of signal leptons    */
/* The truth variables you need to pass are:                                 */
/* For electrons: El_truthType, El_truthOrigin, El_firstEgMotherPdgId        */
/* For muons: Mu_type, Mu_origin                                             */
/*
	  double fakeW=1;
	  // fake correction factors
	  for (int lepi = 0; lepi < lep_signal.num_leptons; lepi++)
		{
		  if(lep_signal.is_electron[lepi]) 
			fakeCorr.AddElectron(evt.ChannelNumber, lep_signal.pT[lepi], lep_signal.charge[lepi], evt.El_truthType[lep_signal.index[lepi]],  evt.El_truthOrigin[lep_signal.index[lepi]], evt.El_firstEgMotherPdgId[lep_signal.index[lepi]]);
		  else 
			fakeCorr.AddMuon(evt.ChannelNumber, lep_signal.pT[lepi], lep_signal.charge[lepi], evt.Mu_type[lep_signal.index[lepi]],  evt.Mu_origin[lep_signal.index[lepi]]);
			}
	  double uncertainty;
	  fakeW = fakeCorr.GetFakeCorrection(uncertainty);	  
*/
/*                                                                           */
/*                                                                           */
/***** C 2016 ****************************************************************/

#ifndef FakeLepMCTemplate_h
#define FakeLepMCTemplate_h

#include "TF1.h"

const int MAX_LEPT = 10;
const int LeptPtMIN = 20000;
const int NCorrections = 5;

  // defines the truth lepton collection in the event
struct my_lep {
  int channelNumber;
  int num_leptons;
  bool is_electron[MAX_LEPT];
  double pT[MAX_LEPT];
  int recoCharge[MAX_LEPT];
  int  truthType[MAX_LEPT];
  int  truthOrigin[MAX_LEPT];
  int  truthPdgId[MAX_LEPT];
  bool is_fake_HF[MAX_LEPT];
  bool is_fake_LF[MAX_LEPT];
  bool is_chmisid[MAX_LEPT];
}; 

// refers to individual lepton and not the collection 
struct srtLep {
  double pT;
  int ind;
};

class MCTemplateCorr
{
 public:
  
  MCTemplateCorr();
  ~MCTemplateCorr() {}
  void AddElectron(int channelnumber, double pt_in_mev, int charge, int type, int origin, int pdgid);
  void AddMuon(int channelnumber, double pt_in_mev, int charge, int type, int origin);
  double GetFakeCorrection(double& unc);
  void  SetMCResult(int channelnum);
  void SetMCResult(int channelnum, double *corr, double *err);
  void Reset();

 private:
  void classify_leptons(my_lep *lep);  
  static int lep_pt_comparator(const void * a, const void * b);
  void sortLeptons(my_lep *lep);

 protected:    
  bool m_reset;
  my_lep m_lepinfo;
  int m_index=0;
  bool debug_me = false;

  double chMisId_Correction = 1.0;
  double HF_EL_Correction = 1.0;
  double HF_MU_Correction = 1.0;
  double LF_EL_Correction = 1.0;
  double LF_MU_Correction = 1.0;

  double chMisId_Uncert = 0.0;
  double HF_EL_Uncert = 0.0;
  double HF_MU_Uncert = 0.0;
  double LF_EL_Uncert = 0.0;
  double LF_MU_Uncert = 0.0;

  const double pythia_correction[NCorrections] = {0.96,1.80,2.10,1.55,0.74};
  const double pythia_uncertainty[NCorrections] = {0.08,0.45,0.58,0.14,0.81};

  const double sherpa_correction[NCorrections] = {1.02,2.72,1.81,1.16,1.84};
  const double sherpa_uncertainty[NCorrections] = {0.09,0.57,0.75,0.18,1.16};

  const double no_correction[NCorrections] = {1.,1.,1.,1.,1.};
  const double no_uncertainty[NCorrections] = {0.,0.,0.,0.,0.};

};


#endif
