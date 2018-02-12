/*****************************************************************************/
/*                                                                           */
/* File Name        : FakeLepMCTemplate.cxx                                  */
/* Author           : Othmane Rifki			                                 */
/* Email            : othmane.rifki@cern.ch			                         */
/* Description      : Source file for the MCTemplateCorr class               */
/*                                                                           */
/***** C 2016 ****************************************************************/

/*
  http://acode-browser2.usatlas.bnl.gov/lxr-rel17/source/atlas/PhysicsAnalysis/MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h
  http://acode-browser2.usatlas.bnl.gov/lxr-rel17/source/atlas/PhysicsAnalysis/MCTruthClassifier/src/MCTruthClassifier.cxx

  type:
  IsoElectron     =  2
  NonIsoElectron  =  3
  BkgElectron     =  4
  IsoMuon         =  6
  NonIsoMuon      =  7

  origin:
  PhotonConv    = 5
  top           = 10
  WBoson        = 12
  ZBoson        = 13
  SUSY          = 22
  FSRPhot       = 40
  BottomMeson   = 26
  BBbarMeson    = 29  
  BottomBaryon  = 33
*/


#include "Analyzer/MCTemplateCorr.h"

MCTemplateCorr::MCTemplateCorr()
{

  Reset();
}

double MCTemplateCorr::GetFakeCorrection(double& unc)
{

  if(m_reset)
	{
	  std::cerr << "ERROR [MCTemplateCorr]: Come on, you must provide truth information about signal leptons first!!!!\n";
	  throw;
	}

  sortLeptons(&m_lepinfo);
  classify_leptons(&m_lepinfo);
  SetMCResult(m_lepinfo.channelNumber);

  if(debug_me)
	for (int ilep = 0; ilep <  m_lepinfo.num_leptons; ilep++)
	  {
		if(m_lepinfo.is_electron[ilep])
		  printf("lepton %d -> electron with pt=%.2fGeV charge=%+d type=%d origin=%d pdgid=%d -->  is_fake_HF=%d is_fake_LF=%d is_chmisid=%d\n",ilep, m_lepinfo.pT[ilep]/1000.,m_lepinfo.recoCharge[ilep], m_lepinfo.truthType[ilep],m_lepinfo.truthOrigin[ilep],m_lepinfo.truthPdgId[ilep], m_lepinfo.is_fake_HF[ilep], m_lepinfo.is_fake_LF[ilep], m_lepinfo.is_chmisid[ilep] );
		else
		  printf("lepton %d -> muon with pt=%.2fGeV charge=%+d type=%d origin=%d -->  is_fake_HF=%d is_fake_LF=%d is_chmisid=%d\n",ilep, m_lepinfo.pT[ilep]/1000.,m_lepinfo.recoCharge[ilep], m_lepinfo.truthType[ilep],m_lepinfo.truthOrigin[ilep], m_lepinfo.is_fake_HF[ilep], m_lepinfo.is_fake_LF[ilep], m_lepinfo.is_chmisid[ilep] );

	  }

  double fakeCorr = 1.;  

  int index_fake_HF = -1;
  int index_fake_LF = -1;
  int index_chmisid = -1;
  
  int num_lept = 0;
  for (int i = 0; i < m_lepinfo.num_leptons && num_lept < 3; i++) {
	num_lept++;
	if (m_lepinfo.is_fake_HF[i]) {
	  index_fake_HF = i;
	  break;
	}
	else if (m_lepinfo.is_fake_LF[i]){
	  index_fake_LF = i;
	  break;
	}
  }
  
  num_lept = 0;
  for (int i = 0; i < m_lepinfo.num_leptons && num_lept < 3; i++) {
	num_lept++;
	if (m_lepinfo.is_chmisid[i]) {
	  index_chmisid = i;
	  break;
	}
  }
  if (index_fake_HF >= 0) {
	if (m_lepinfo.is_electron[index_fake_HF]) {
	  fakeCorr = HF_EL_Correction;
	  unc = HF_EL_Uncert;
	}
	else {
	  fakeCorr = HF_MU_Correction;
	  unc = HF_MU_Uncert;
	}
  }
  else if (index_fake_LF >= 0){
	if (m_lepinfo.is_electron[index_fake_LF]) {
	  fakeCorr = LF_EL_Correction;
	  unc = LF_EL_Uncert;
	}
	else {
	  fakeCorr = LF_MU_Correction;
	  unc = LF_MU_Uncert;
	}
  }
  else if(index_chmisid >= 0){
	fakeCorr = chMisId_Correction;
	unc = chMisId_Uncert;
  }
  else {
	fakeCorr = 1.0;
	unc = 0.0;
  }

  if(debug_me)
	printf("MC Template Fake Correction = %f +- %f\n", fakeCorr, unc);

  Reset();
  return fakeCorr;

}

void MCTemplateCorr::AddElectron(int channelnumber, double pt, int charge, int type, int origin, int pdgid)
{

  if(debug_me){
	if (m_index == 0) 
	  printf("----------------Start of event----------------\n");

	printf("AddElectron::Added an electron with pt=%.2fGeV charge=%+d type=%d origin=%d pdgid=%d \n",pt/1000.,charge, type,origin,pdgid);
  }

  m_lepinfo.channelNumber = channelnumber;
  m_lepinfo.is_electron[m_index] = true;
  m_lepinfo.pT[m_index] = pt;
  m_lepinfo.recoCharge[m_index] = charge;
  m_lepinfo.truthType[m_index] = type;
  m_lepinfo.truthOrigin[m_index] = origin;
  m_lepinfo.truthPdgId[m_index] = pdgid;

  m_index++;
  m_lepinfo.num_leptons = m_index;
  m_reset = false;
}

void MCTemplateCorr::AddMuon(int channelnumber, double pt, int charge, int type, int origin)
{
  if(debug_me){
	if (m_index == 0) 
	  printf("----------------Start of event----------------\n");
	
	printf("AddMuon::Added a muon with pt=%.2fGeV charge=%+d type=%d origin=%d \n",pt/1000.,charge,type,origin);
  }

  m_lepinfo.channelNumber = channelnumber;
  m_lepinfo.is_electron[m_index] = false;
  m_lepinfo.pT[m_index] = pt;
  m_lepinfo.recoCharge[m_index] = charge;
  m_lepinfo.truthType[m_index] = type;
  m_lepinfo.truthOrigin[m_index] = origin;
  m_lepinfo.truthPdgId[m_index] = -1;

  m_index++;
  m_lepinfo.num_leptons = m_index;
  m_reset = false;
}

//------------------------------------------------------------------------
void MCTemplateCorr::classify_leptons(my_lep *lep){

  if (lep->num_leptons < 2 || lep->pT[0] < LeptPtMIN || lep->pT[1] < LeptPtMIN) {
	std::cerr << "ERROR [MCTemplateCorr]: Well, there is an incorrect usage of cuts!!!!\n";
	//	throw;
  }
  
  bool iso = true;
  bool HF_e = false;
  bool HF_m = false;
  bool chmisId = false;

  int num_lept = 0;
  for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) {
    lep->is_fake_HF[i] = false;
    lep->is_fake_LF[i] = false;
    lep->is_chmisid[i] = false;
    num_lept++;
  }
  
  num_lept = 0;
  for (int i = 0; i < lep->num_leptons && num_lept < 3; i++) {
    num_lept++;
	
    if(lep->is_electron[i]){

      // Prompt electron
      iso &= ( lep->truthType[i]==2 || (lep->truthOrigin[i] == 5 && fabs(lep->truthPdgId[i])==11));

	  // Charge flip electron
	  chmisId = ( lep->num_leptons==2 && (lep->recoCharge[i]*lep->truthPdgId[i] > 0) );              

      // electron from HF
      HF_e = ( lep->truthOrigin[i]==26 || lep->truthOrigin[i]==33 ); // el from b hadrons
	  // HF_e = ( lep->truthOrigin[i]==26 || lep->truthOrigin[i]==33 ||lep->truthOrigin[i]==25 || lep->truthOrigin[i]==32 ); // el from b or c hadrons

    }
    else {

	  // Prompt muon
      iso &= ( lep->truthType[i]==6 ); 

	  // muon from HF
      HF_m =  ( lep->truthOrigin[i]==26 || lep->truthOrigin[i]==33 ); // mu from b hadrons
	  //HF_m = ( lep->truthOrigin[i]==26 || lep->truthOrigin[i]==33 || lep->truthOrigin[i]==25 || lep->truthOrigin[i]==32 ); // mu from b or c hadrons

    }

    if( iso ){ // Prompt lepton
      lep->is_fake_HF[i] = false;
      lep->is_fake_LF[i] = false;
      lep->is_chmisid[i] = false;
	  if( chmisId){    // charge flipped electrons
		lep->is_fake_HF[i] = false;
		lep->is_fake_LF[i] = false;
		lep->is_chmisid[i] = true;
      } 
    } else if (HF_e || HF_m){ // non-prompt leptons from HF
      lep->is_fake_HF[i] = true;
      lep->is_fake_LF[i] = false;
      lep->is_chmisid[i] = false;
    }
    else { // everything else is LF
      lep->is_fake_HF[i] = false;
      lep->is_fake_LF[i] = true;
      lep->is_chmisid[i] = false;
    }


  }
  
  return;
}

//Compare lep pt's
//----------------------------------------------------------------------------
int MCTemplateCorr::lep_pt_comparator(const void * a, const void * b) {
  float pt1 = ((srtLep*) a)->pT;
  float pt2 = ((srtLep*) b)->pT;
  if (pt1 < pt2)
    return 1;
  else if (pt1 == pt2)
    return 0;
  else
    return -1;
}

//----------------------------------------------------------------------------
void MCTemplateCorr::sortLeptons(my_lep *lep) {

  
  srtLep lep_srt[MAX_LEPT];
  my_lep temp_lep;

  for (int i = 0; i < lep->num_leptons; i++) {
    lep_srt[i].ind = i;
    lep_srt[i].pT = lep->pT[i];
  }

  qsort(lep_srt, lep->num_leptons, sizeof(srtLep), lep_pt_comparator);

  for (int i = 0; i < lep->num_leptons; i++) {
	temp_lep.is_electron[i] = lep->is_electron[lep_srt[i].ind];
	temp_lep.pT[i] = lep->pT[lep_srt[i].ind];
    temp_lep.recoCharge[i] = lep->recoCharge[lep_srt[i].ind];
	temp_lep.truthType[i] = lep->truthType[lep_srt[i].ind];
	temp_lep.truthOrigin[i] = lep->truthOrigin[lep_srt[i].ind];
	temp_lep.truthPdgId[i] = lep->truthPdgId[lep_srt[i].ind];
  }

  for (int i = 0; i < lep->num_leptons; i++) {
	lep->is_electron[i] = temp_lep.is_electron[i];
	lep->pT[i] = temp_lep.pT[i];
    lep->recoCharge[i] = temp_lep.recoCharge[i];
	lep->truthType[i] = temp_lep.truthType[i];
	lep->truthOrigin[i] = temp_lep.truthOrigin[i];
	lep->truthPdgId[i] = temp_lep.truthPdgId[i];
  }

  return;
}

void  MCTemplateCorr::SetMCResult(int channelnum)
{

  if(debug_me)
	std::cout << "Channel Number = " << channelnum << std::endl;

  double correction[NCorrections];
  double uncertainty[NCorrections];

 for(int i=0; i<NCorrections; i++)
   {
	 correction[i] = 1.0;
	 uncertainty[i] = 0.0;
   }


	  for(int i=0; i<NCorrections; i++){
	// Pythia
  if( channelnum == 410000 || channelnum == 407009 || channelnum == 407010 || channelnum == 407011 || (407200 <= channelnum && channelnum <= 407204) || channelnum == 343637 || (361100 <= channelnum && channelnum <= 361108) )
	{
	  if(debug_me)
		std::cout << "Pythia Setup!" << std::endl;
	  correction[i] = pythia_correction[i];
	  uncertainty[i] = pythia_uncertainty[i];
	}
  
	// Sherpa
  else if( channelnum == 410250 || channelnum == 410251 || channelnum == 410252 || (364156 <= channelnum &&  channelnum <= 364197) || (364100 <= channelnum && channelnum <= 364141)  || (361468 <= channelnum && channelnum <= 361491) )
  {
	  if(debug_me)
		std::cout << "sherpa Setup!" << std::endl;
	  correction[i] = sherpa_correction[i];
	  uncertainty[i] = sherpa_uncertainty[i];
  }

	  }

  SetMCResult(channelnum, correction, uncertainty);


}

void  MCTemplateCorr::SetMCResult(int channelnum, double *corr, double *unc)
{

  chMisId_Correction = corr[0];
  HF_EL_Correction = corr[1];
  HF_MU_Correction = corr[2];
  LF_EL_Correction = corr[3];
  LF_MU_Correction = corr[4];

  HF_EL_Uncert = unc[0];
  HF_MU_Uncert = unc[1];
  LF_EL_Uncert = unc[2];
  LF_MU_Uncert = unc[3];
  chMisId_Uncert = unc[4];


  return;
}

  void MCTemplateCorr::Reset()
  {

	if(debug_me)
	  printf("----------------End of event----------------\n\n");

	m_index = 0;
	m_reset = true;

	for (int i = 0; i < MAX_LEPT; i++){
	  m_lepinfo.is_fake_HF[i] = false;
	  m_lepinfo.is_fake_LF[i] = false;
	  m_lepinfo.is_chmisid[i] = false;
	}

  }

