#include "MiniNtuple/RecoTruthMatch.h" 

using namespace std;

// useless, I think
RecoTruthMatch::RecoTruthMatch() {

	setVerbose(0);
	setDR(0.10);
	setIsSherpa(true);

}

//-----------------------------------------------------------------------------

RecoTruthMatch::RecoTruthMatch(float dR, int mcChannel, int mc_n, std::vector<int> *mc_barcode,
		std::vector<int> *mc_status, std::vector<int> *mc_pdgId, std::vector<std::vector<int> > *mc_parents,
		std::vector<std::vector<int> > *mc_children, std::vector<float> * mc_pt, std::vector<float> * mc_eta,
		std::vector<float> * mc_phi, std::vector<float> * mc_m, int verbose, bool StepUp, float dRTau) {

	setDR(dR);
	setDRTau(dRTau);
	setIsSherpa(IsSherpa(mcChannel));
	setVerbose(verbose);
	setStepUp(StepUp);

	setmc_n(mc_n);
	setmc_barcode(mc_barcode);
	setmc_status(mc_status);
	setmc_pdgId(mc_pdgId);
	setmc_parents(mc_parents);
	setmc_children(mc_children);
	setmc_pt(mc_pt);
	setmc_eta(mc_eta);
	setmc_phi(mc_phi);
	setmc_m(mc_m);

	SetTruthLeptons();

}

//-----------------------------------------------------------------------------

void RecoTruthMatch::printSettings() {

	cout << endl;
	cout << "*******************************************************" << endl;
	cout << "*" << endl;
	cout << "* Settings:" << endl;
	cout << "*    Delta R match: " << (dR()) << endl;
	cout << "*    IsSherpa:       " << IsSherpa() << endl;
	cout << "*    Verbosity:       " << verbose() << endl;
	cout << "*" << endl;
	cout << "*******************************************************" << endl;
	cout << endl;

	return;

}

//-----------------------------------------------------------------------------

///* parents and children variables in the D3PD return the barcode, we need the mc_index*
int RecoTruthMatch::GetMCIdxFromBarcode(int barcode) {
	int i_idx = -1;
	for (int jmc = 0; jmc < _mc_n; jmc++)
		if (_mc_barcode->at(jmc) == barcode)
			i_idx = jmc;
	return i_idx;
}

//-----------------------------------------------------------------------------

///* Navigates the D3PD truth info, list all available mothers *
std::vector<int> RecoTruthMatch::MothersIdxVector(int imc) {
	std::vector<int> v_parents_idx;
	v_parents_idx.clear();
	//cout<<"(_mc_parents->at(imc)).size() = "<<(_mc_parents->at(imc)).size()<<endl;
	for (unsigned int imother = 0; imother < (_mc_parents->at(imc)).size(); imother++) {
		int imother_idx = GetMCIdxFromBarcode((_mc_parents->at(imc)).at(imother));
		if (imother_idx != -1) {
			v_parents_idx.push_back(imother_idx);
		}
	}
	return v_parents_idx;
}

//-----------------------------------------------------------------------------

///* Navigates the D3PD truth info, list all available children *
std::vector<int> RecoTruthMatch::ChildrenIdxVector(int imc) {
	std::vector<int> v_children_idx;
	v_children_idx.clear();
	for (unsigned int ichild = 0; ichild < (_mc_children->at(imc)).size(); ichild++) {
		int ichild_idx = GetMCIdxFromBarcode((_mc_children->at(imc)).at(ichild));
		if (ichild_idx != -1) {
			v_children_idx.push_back(ichild_idx);
		}
	}
	return v_children_idx;
}

//-----------------------------------------------------------------------------

///* shortcut *
bool RecoTruthMatch::IsBoson(int imc) {
	return (fabs(_mc_pdgId->at(imc)) == 23 || fabs(_mc_pdgId->at(imc)) == 24 || fabs(_mc_pdgId->at(imc)) == 25 // Higgs
	|| (fabs(_mc_pdgId->at(imc)) >= 35 && fabs(_mc_pdgId->at(imc)) <= 37) // SUSY Higgs
			|| (fabs(_mc_pdgId->at(imc)) >= 1000000 && fabs(_mc_pdgId->at(imc)) <= 2000017) // SUSY particles
	);
}

///* shortcut *
bool RecoTruthMatch::IsLepton(int imc) {
	return (fabs(_mc_pdgId->at(imc)) == 15 || fabs(_mc_pdgId->at(imc)) == 13 || fabs(_mc_pdgId->at(imc)) == 11);
}
///* shortcut *
bool RecoTruthMatch::IsNeutrino(int imc) {
	return (fabs(_mc_pdgId->at(imc)) == 16 || fabs(_mc_pdgId->at(imc)) == 14 || fabs(_mc_pdgId->at(imc)) == 12);
}
///* helper *
bool RecoTruthMatch::AlreadyInLepList(int mcidx) {
	for (unsigned int ilep = 0; ilep < _LepFromHS_McIdx.size(); ilep++)
		if (mcidx == _LepFromHS_McIdx.at(ilep))
			return true;
	return false;
}
///* print out *
void RecoTruthMatch::partInfo(int imc) {
	std::cout << " imc = " << imc << " mc_pdgId = " << _mc_pdgId->at(imc) << " status = " << _mc_status->at(imc)
			<< " barcode = " << _mc_barcode->at(imc) << " eta = " << _mc_eta->at(imc) << " phi = " << _mc_phi->at(imc)
			<< " pt = " << _mc_pt->at(imc) << std::endl;
}

///* shortcut *
bool RecoTruthMatch::DecaysIntoItself(int imc) {
	std::vector<int> childs = ChildrenIdxVector(imc);
	///  check if it decays into itself
	for (unsigned int ichild = 0; ichild < childs.size(); ichild++) {
		int ichild_idx = childs.at(ichild);
		/// If decays into itself return true
		if (_mc_pdgId->at(imc) == _mc_pdgId->at(ichild_idx))
			return true;
	}
	return false;
}

///* shortcut *
bool RecoTruthMatch::DecaysLeptonically(int imc) {
	std::vector<int> childs = ChildrenIdxVector(imc);
	/// check if it decays into charged leptons
	for (unsigned int ichild = 0; ichild < childs.size(); ichild++) {
		int ichild_idx = childs.at(ichild);
		/// If decays into charged leptons return true
		if (IsLepton(ichild_idx))
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------

/////* fill two vectors of indices (charged, neutral) for the tau decay products *
//std::pair<std::vector<int>, std::vector<int> > RecoTruthMatch::GetTauProngIdx(int imc){
//
//  std::vector<int> tau_had_idx; tau_had_idx.clear();
//  std::vector<int> tau_neu_idx; tau_neu_idx.clear();
//
//  Tau_StepDown(imc,&tau_neu_idx,&tau_had_idx,0);
//
//  if(_verbose>5){
//    cout<<"tau products neutral = "<<tau_neu_idx.size()<<" charged = "<<tau_had_idx.size()<<endl;
//    for (unsigned int ihad=0;ihad<tau_had_idx.size();ihad++) { cout<<"====>";partInfo(tau_had_idx.at(ihad)); }
//    for (unsigned int ihad=0;ihad<tau_neu_idx.size();ihad++) { cout<<"====>";partInfo(tau_neu_idx.at(ihad)); }
//  }
//
//  return make_pair(tau_had_idx, tau_neu_idx);
//}

///* we should exclude the neutrino from the hadronic tau tlv *
TLorentzVector RecoTruthMatch::GetTauVisTLV(int imc) {
	TLorentzVector tau_tlv;
	tau_tlv.SetPtEtaPhiM(_mc_pt->at(imc), _mc_eta->at(imc), _mc_phi->at(imc), _mc_m->at(imc));
	TLorentzVector vistau_tlv;
	std::vector<int> childs = ChildrenIdxVector(imc);
	/// First look for the neutrino
	std::vector < TLorentzVector > neu_tlv;
	neu_tlv.clear();
	std::vector < TLorentzVector > had_tlv;
	had_tlv.clear();
	std::vector<unsigned int> had_idx;
	had_idx.clear();

	for (unsigned int ichild = 0; ichild < childs.size(); ichild++) {
		int ichild_idx = childs.at(ichild);
		TLorentzVector ichild_tlv;
		ichild_tlv.SetPtEtaPhiM(_mc_pt->at(ichild_idx), _mc_eta->at(ichild_idx), _mc_phi->at(ichild_idx),
				_mc_m->at(ichild_idx));
		/// Put neutrinos in a different vector
		if (IsNeutrino(ichild_idx)) {
			neu_tlv.push_back(ichild_tlv);
		} else {
			had_tlv.push_back(ichild_tlv);
			had_idx.push_back(ichild_idx);
		}
	}

	for (unsigned int ihad = 0; ihad < had_tlv.size(); ihad++) {
		vistau_tlv = vistau_tlv + had_tlv.at(ihad);
		IsFromHardScattering_StepDown(had_idx.at(ihad), 0);
	}
	/// Check that sum (tau - neutrino) = sum (tau products, except neutrino). Keep tau-neutrino as default
	//if(neu_tlv.size()==1) cout<<"Tau number of daughters that are not neutrinos = "<<had_tlv.size()<<" sumtlv.eta = "<<vistau_tlv.Eta()<<" subtlv.Eta = "<<(tau_tlv - neu_tlv.at(0)).Eta()<<" --- DIFF = "<<vistau_tlv.Eta() - ((tau_tlv - neu_tlv.at(0)).Eta())<<endl;

	// The official matching uses the truth tau instead of the visible tau! We do the (hopefully correct?) thing
	//if(neu_tlv.size()==1) return tau_tlv  ;

	if (neu_tlv.size() == 1)
		return tau_tlv - neu_tlv.at(0);
	else if (neu_tlv.size() > 1)
		std::cout << "ERROR! More than one neutrino! (" << neu_tlv.size()
				<< ") Not expected in a hadronic tau decay! return NULL!!" << std::endl;
	else if (neu_tlv.size() < 1)
		std::cout << "ERROR! No neutrinos!  Not expected in a hadronic tau decay! return NULL!!!" << std::endl;
	return tau_tlv;
}

//-----------------------------------------------------------------------------

///* recursive function to navigate up *
bool RecoTruthMatch::IsFromHardScattering_StepUp(int imc, int step) {
	std::vector<int> mothers = MothersIdxVector(imc);
	for (unsigned int imother = 0; imother < mothers.size(); imother++) {
		int imother_idx = mothers.at(imother);
		//for (int istep=0;istep<step;istep++) cout<<"  "; cout<<"imother= "<<imother<<" / "<<mothers.size()<<" "; partInfo(imother_idx);
		// look for a W, Z or status 3 mother (Sherpa has not the W/Z info)
		if (_mc_status->at(imother_idx) == 3 || IsBoson(imother_idx))
			return true;
		// Navigate only through leptons and bosons
		if ((!IsBoson(imother_idx)) && (!IsLepton(imother_idx)))
			continue;
		if (IsFromHardScattering_StepUp(imother_idx, step + 1))
			return true;
		//else return IsFromHardScattering_StepUp(imother_idx, step+1);

	}
	return false;
}

//-----------------------------------------------------------------------------

///* recursive function to navigate down *
bool RecoTruthMatch::IsFromHardScattering_StepDown(int imc, int step) {
	//cout<<">";  partInfo(imc);
	std::vector<int> childs = ChildrenIdxVector(imc);
	/// First check if it decays into itself or tau
	for (unsigned int ichild = 0; ichild < childs.size(); ichild++) {
		int ichild_idx = childs.at(ichild);
		//for(int s = 0 ; s<step+1; s++) cout<<"-->"; partInfo(ichild_idx);
		/// If decays into itself or into tau, step down
		if (_mc_pdgId->at(imc) == _mc_pdgId->at(ichild_idx) || fabs(_mc_pdgId->at(ichild_idx)) == 15
				|| IsLepton(ichild_idx))
			return IsFromHardScattering_StepDown(ichild_idx, step + 1);
		//if ( _mc_pdgId->at(imc)==_mc_pdgId->at(ichild_idx) || fabs(_mc_pdgId->at(ichild_idx))==15 ) return IsFromHardScattering_StepDown(ichild_idx, step+1);
	}
	/// if it does not decay into itself or tau, check if the children are leptons
	for (unsigned int ichild = 0; ichild < childs.size(); ichild++) {
		int ichild_idx = childs.at(ichild);
		if (fabs(_mc_pdgId->at(ichild_idx)) == 11 || fabs(_mc_pdgId->at(ichild_idx)) == 13) {
			/// Save leptons mc_ index and TLorentzVector
			// if it is already in the vector, no dot save it again!
			if (AlreadyInLepList(ichild_idx))
				continue;
			_LepFromHS_McIdx.push_back(ichild_idx);
			TLorentzVector ichild_tlv;
			ichild_tlv.SetPtEtaPhiM(_mc_pt->at(ichild_idx), _mc_eta->at(ichild_idx), _mc_phi->at(ichild_idx),
					_mc_m->at(ichild_idx));
			_LepFromHS_TLV.push_back(ichild_tlv);
		}
	}
	if (_LepFromHS_McIdx.size() > 0)
		return true; // returned value does nothing for now
	return false;
}

/////* recursive function to navigate down *
//bool RecoTruthMatch::Tau_StepDown(int imc, std::vector<int> * childs_neutral, std::vector<int> * childs_charged, int step){
//  if (_verbose>5) cout<<">";  partInfo(imc);
//  std::vector<int> childs = ChildrenIdxVector(imc);
//  // if it has children, look for them, except if it only has a photon single-child, or is a pi0 which decays always to 2 photons
//  if (childs.size()!=0 && !( childs.size()==1 && _mc_pdgId->at(childs.at(0))==22) && _mc_pdgId->at(imc)!=111 ){
//    /// step down to the children
//    for (unsigned int ichild=0;ichild<childs.size();ichild++){
//      int ichild_idx = childs.at(ichild);
//      if (_verbose>5){ /// cout the decay chain
//        for(int s = 0 ; s<step+1; s++) cout<<"-->";
//        partInfo(ichild_idx);
//      }
//      /// the returned value is not currently used
//      bool isok = Tau_StepDown(ichild_idx, childs_neutral, childs_charged, step+1);
//    }
//  } else { // if it has no more children
//    /// define neutral prong as pi0, K0S, K0L
//    if ( _mc_pdgId->at(imc)== 111 || _mc_pdgId->at(imc)== 130 ||_mc_pdgId->at(imc)== 310) {
//      childs_neutral->push_back(imc);
//    }
//    /// if it is not neural, not a photon and not a neutrino, then it is charged
//    else if ( _mc_pdgId->at(imc)!=22 && fabs(_mc_pdgId->at(imc))!=16){
//      childs_charged->push_back(imc);
//    }
//  }
//  /// the return value is not currently used
//  if (childs_neutral->size() + childs_charged->size()) return true;
//  return false;
//}

//-----------------------------------------------------------------------------

///* Main function. Selects the truth leptons *
void RecoTruthMatch::SetTruthLeptons() {

	//if (IsSherpa()){  // use StepUp function
	if (_StepUp) { // use StepUp function
		for (int imc = 0; imc < _mc_n; imc++) {
			if (_verbose > 5) {
				if (imc < 50)
					partInfo(imc);
			}
			// avoid Warnings
			if (fabs(_mc_pt->at(imc)) == 0)
				continue;
			if (fabs(_mc_eta->at(imc)) > 6.)
				continue;

			if (_mc_status->at(imc) == 1 && (fabs(_mc_pdgId->at(imc)) == 11 || fabs(_mc_pdgId->at(imc)) == 13)
					&& _mc_barcode->at(imc) < 200000) {
				if (!IsFromHardScattering_StepUp(imc, 0))
					continue;
				_LepFromHS_McIdx.push_back(imc);
				TLorentzVector imc_tlv;
				imc_tlv.SetPtEtaPhiM(_mc_pt->at(imc), _mc_eta->at(imc), _mc_phi->at(imc), _mc_m->at(imc));
				_LepFromHS_TLV.push_back(imc_tlv);
			}
			if ((fabs(_mc_pdgId->at(imc)) == 15) && _mc_barcode->at(imc) < 200000) {
				if (DecaysIntoItself(imc))
					continue;
				if (DecaysLeptonically(imc))
					continue;
				if (!IsFromHardScattering_StepUp(imc, 0))
					continue;
				if ((_mc_children->at(imc)).size() == 0)
					continue;
				_TauFromHS_McIdx.push_back(imc);
				TLorentzVector imc_tlv = GetTauVisTLV(imc);
				_TauFromHS_TLV.push_back(imc_tlv);
				//_TauFromHS_Prongs.push_back(GetTauProngIdx(imc));
			}
		}
	} else { // use StepDown function
		for (int imc = 0; imc < _mc_n; imc++) {
			if (fabs(_mc_pdgId->at(imc)) == 23 || fabs(_mc_pdgId->at(imc)) == 24) {
				if (!IsFromHardScattering_StepDown(imc, 0))
					continue; /// returned value does nothing for now
			}
		}
	}
	/// for debugging puroses, print out list of selected leptons and their details
	if (_verbose > 4) {
		cout << "=====================" << endl;
		for (unsigned int ilep = 0; ilep < _LepFromHS_McIdx.size(); ilep++)
			partInfo(_LepFromHS_McIdx.at(ilep));
		for (unsigned int ilep = 0; ilep < _TauFromHS_McIdx.size(); ilep++)
			partInfo(_TauFromHS_McIdx.at(ilep));
	}
	return;
}

//-----------------------------------------------------------------------------

///* Actually does the DeltaR matching * 
int RecoTruthMatch::MatchedTruthLepton(TLorentzVector recolep_tlv, bool isTau) {

	if (isTau)
		return MatchedTruthTau(recolep_tlv);

	float dRmin = 999.;
	int imc_matched = -1;
	for (unsigned int itruthlep = 0; itruthlep < _LepFromHS_TLV.size(); itruthlep++) {
		if (_LepFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv) > _dR)
			continue;
		// if more than one mc particle match, take the closest
		if (_LepFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv) < dRmin) {
			dRmin = _LepFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv);
			imc_matched = _LepFromHS_McIdx.at(itruthlep);
		}
	}
	return imc_matched;
}

///* input kinematic variables separately * 
int RecoTruthMatch::MatchedTruthLepton(float reco_pt, float reco_eta, float reco_phi, float reco_m, bool isTau) {
	TLorentzVector recolep_tlv;
	recolep_tlv.SetPtEtaPhiM(reco_pt, reco_eta, reco_phi, reco_m);
	return MatchedTruthLepton(recolep_tlv, isTau);
}

///* The bool version of the matching * 
bool RecoTruthMatch::Matched2TruthLepton(TLorentzVector recolep_tlv, bool isTau) {
	if (MatchedTruthLepton(recolep_tlv, isTau) == -1)
		return false;
	else
		return true;
}

///* Actually does the DeltaR matchin and gets the index of the internal vector (not the mc index) * 
int RecoTruthMatch::MatchedTruthTauInternalIdx(TLorentzVector recolep_tlv) {
	float dRmin = 999.;
	int intIdx_matched = -1;
	for (unsigned int itruthlep = 0; itruthlep < _TauFromHS_TLV.size(); itruthlep++) {
		if (_TauFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv) > _dRTau)
			continue;
		// if more than one mc particle match, take the closest
		if (_TauFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv) < dRmin) {
			dRmin = _TauFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv);
			intIdx_matched = itruthlep;
		}
	}
	return intIdx_matched;
}

/////* does the DeltaR matching, gets the products, returns the number of prongs (charged decay products) * 
//int RecoTruthMatch::MatchedTruthTauNProngs(TLorentzVector recolep_tlv){
//  int intIdx_matched = MatchedTruthTauInternalIdx(recolep_tlv);
//  if(intIdx_matched!=-1)return ( (_TauFromHS_Prongs.at(intIdx_matched)).first ).size() ;
//  else return 0;
//}

/////* does the DeltaR matching, gets the products, returns the number of neutral decay products * 
//int RecoTruthMatch::MatchedTruthTauNNeutral(TLorentzVector recolep_tlv){
//  int intIdx_matched = MatchedTruthTauInternalIdx(recolep_tlv);
//  if(intIdx_matched!=-1) return ( (_TauFromHS_Prongs.at(intIdx_matched)).second ).size() ;
//  else return 0;
//
//}

/////* does the DeltaR matching and gets the products * 
//std::pair<std::vector<int>, std::vector<int> > RecoTruthMatch::MatchedTruthTauProducts(TLorentzVector recolep_tlv){
//  int intIdx_matched = MatchedTruthTauInternalIdx(recolep_tlv);
//  if(intIdx_matched!=-1) return _TauFromHS_Prongs.at(intIdx_matched);
//  else {
//    std::vector<int> dummy; 
//    return make_pair(dummy, dummy);
//  }
//}

///* Actually does the DeltaR matching * 
int RecoTruthMatch::MatchedTruthTau(TLorentzVector recolep_tlv) {
	int intIdx_matched = MatchedTruthTauInternalIdx(recolep_tlv);
	if (intIdx_matched != -1)
		return _TauFromHS_McIdx.at(intIdx_matched);
	else
		return -1;

	//float dRmin = 999.;
	//int imc_matched = -1;
	//for(unsigned int itruthlep=0;itruthlep<_TauFromHS_TLV.size();itruthlep++){
	//  if(_TauFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv)>_dR) continue;
	//  // if more than one mc particle match, take the closest
	//  if(_TauFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv)<dRmin) {
	//    dRmin = _TauFromHS_TLV.at(itruthlep).DeltaR(recolep_tlv);
	//    imc_matched = _TauFromHS_McIdx.at(itruthlep);
	//  }
	//}
	//return imc_matched;
}

///* input kinematic variables separately * 
int RecoTruthMatch::MatchedTruthTau(float reco_pt, float reco_eta, float reco_phi, float reco_m) {
	TLorentzVector recolep_tlv;
	recolep_tlv.SetPtEtaPhiM(reco_pt, reco_eta, reco_phi, reco_m);
	return MatchedTruthTau(recolep_tlv);
}

///* The bool version of the matching * 
bool RecoTruthMatch::Matched2TruthTau(TLorentzVector recolep_tlv) {
	if (MatchedTruthTau(recolep_tlv) == -1)
		return false;
	else
		return true;
}

//-----------------------------------------------------------------------------
///* Check if the charge from the reco and the truth matched particle is different *
bool RecoTruthMatch::isChargeFlip(TLorentzVector recolep_tlv, int recolep_charge) {
	int mc_idx = MatchedTruthLepton(recolep_tlv);
	if (mc_idx == -1)
		return false; // lepton not matched
	// if have opposite charge, is charge flip
	return (_mc_pdgId->at(mc_idx) * recolep_charge) > 0; // CAREFUL! e- has q=-1 and pdgid=11
}

