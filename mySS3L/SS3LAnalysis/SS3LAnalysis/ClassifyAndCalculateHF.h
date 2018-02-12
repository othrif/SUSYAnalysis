#include <vector>
#include <map>
#include <string>

// xAOD
#include "xAODJet/Jet.h"
#include "xAODJet/JetContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleContainer.h"

#include "xAODRootAccess/TEvent.h"



#ifndef ClassifyAndCalculateHF_H_
#define ClassifyAndCalculateHF_H_


class ClassifyAndCalculateHF{

 public:
  
  ClassifyAndCalculateHF(xAOD::TEvent*& event,std::string truthcollName,std::string jetcollName);
  ~ClassifyAndCalculateHF();
    
  int ClassifyEvent(bool doPrompt);

  void apply(int &code, int &ext_code, int &prompt_code, std::map<int,int>& mapJetClassHF);


 protected:
  xAOD::TEvent *m_event; //!


 private:

  std::string m_truthcollName;
  std::string m_jetcollName;
  bool m_calculateVariables;
  int m_ext_code;
  int m_prompt_Code;

  std::vector<int> m_jet_trueflav; //jet flavor coming from association to hadrons
  std::vector<int> m_jet_count; //number of matched hadrons
  std::vector<int> m_jet_id; // origin of hadron matched to the jet
  std::vector<float> m_jet_pt; //internal use
  std::vector<float> m_jet_eta; //internal use
  std::vector<float> m_jet_phi; //internal use
  std::vector<float> m_jet_m; //internal use
  std::vector<int> m_jet_index; // index of jet in truth jet container
  ///MAPS JUST FOR HF DEDICATED STUDIES///
  std::map<int, int> m_FinalHadrons; //map hadron, origin
  std::map<int, int> m_HadronJets; //map hadron, jet
  std::map<int, int> m_JetClassHF; //map hadron, jet

  /////////////////

  void initEvent();
  void flagJets();
  int countJets(bool doPrompt);
  int hadronType(int pdgid);
  //functions


};

#endif

//-------------------------------------//
