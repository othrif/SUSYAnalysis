////////////////////////////////////////////////////////
// JetQuarkLabelD3PD.h
//   Header file for class JetQuarkLabelD3PD
////////////////////////////////////////////////////////
/**
 * original code in athena:
 *   http://acode-browser2.usatlas.bnl.gov/lxr-rel17/source/atlas/PhysicsAnalysis/AnalysisCommon/ParticleJetTools/ParticleJetTools/JetQuarkLabel.h
 *
 * <b>Purpose:</b> label jets with b or c quarks.<br>
 * <b>Author:</b> Jean-Baptiste de Vivie<br>
 * <b>Email:</b> devivie@cppm.in2p3.fr <br>
 * <b>Created:</b> 2005/02/25 <br>
 * Converted by Takashi Yamanaka 
 *
 * Usage:
 *     JetQuarkLabelD3PD jetquarklabel;
 *     ...
 *
 *     for (int i=0; i<jet_n; i++) {
 *       TLorentzVector jet_lv;
 *       jet_lv.SetPtEtaPhiE(jet_pt->at(i), jet_eta->at(i), jet_phi->at(i), jet_E->at(i));
 *
 *       if (jetquarklabel.matchJet(jet_lv, mc_n, mc_pt, mc_eta, mc_phi, mc_m, mc_pdgId, mc_status, mc_barcode, mc_vx_x, mc_vx_y, mc_vx_z, mc_parent_index, mc_child_index)) {
 *         // obtain result after matchJet(); 
 *         int    jet_flavor_truth_label = jetquarklabel.pdgCode();
 *         double jet_flavor_truth_dRminToB = jetquarklabel.deltaRMinTo("B");
 *         double jet_flavor_truth_dRminToC = jetquarklabel.deltaRMinTo("C");
 *         double jet_flavor_truth_dRminToT = jetquarklabel.deltaRMinTo("T");
 *         int    jet_flavor_truth_BHadronpdg = jetquarklabel.Bpdg();
 *         double jet_flavor_truth_vx_x     = jetquarklabel.BDecVtx().X();
 *         double jet_flavor_truth_vx_y     = jetquarklabel.BDecVtx().Y();
 *         double jet_flavor_truth_vx_z     = jetquarklabel.BDecVtx().Z();
 *       }
 *     }
 */

#ifndef JETQUARKLABELD3PD_H
#define JETQUARKLABELD3PD_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include <TLorentzVector.h>
#include <TVector3.h>

class JetQuarkLabelD3PD {

public:
	JetQuarkLabelD3PD();
	virtual ~JetQuarkLabelD3PD();

	enum verbosity {VERBOSE=0, DEBUG, INFO, WARNING, ERROR, FATAL};

	void initialize(const double deltaRCut, const double ptCut, const bool noDoc, const enum verbosity verb);

	/** Method to truth tag a jet.
	 NB: for this particular algorithm, matchJet is TRUE if the jet is matched
	 to a b-quark OR a c-quark. THe jetLabel is set accordingly and is no
	 longer a job option. */
	virtual bool matchJet(const TLorentzVector myJet,
			const int mc_n,
			const std::vector<float> *mc_pt,
			const std::vector<float> *mc_eta,
			const std::vector<float> *mc_phi,
			const std::vector<float> *mc_m,
			const std::vector<int> *mc_pdgId,
			const std::vector<int> *mc_status,
			const std::vector<int> *mc_barcode,
			const std::vector<float> *mc_vx_x,
			const std::vector<float> *mc_vx_y,
			const std::vector<float> *mc_vx_z,
			const std::vector<std::vector<int> > *mc_parent_index,
			const std::vector<std::vector<int> > *mc_child_index);

	/** NEXT METHODS ARE ONLY ACCESSIBLE AFTER CASTING!! */

	/** Return barcode */
	int barcode() const;

	/** Return pdg to match */
	int pdgCode() const;

	/** Return the predefined name to label the jets passing the matching: */
	inline const std::string& jetLabel() const {return m_jetLabel;}

	/** Return the min distance to quarks: */
	double deltaRMinTo(const std::string&) const;
	inline const std::map<std::string, double>& distanceToQuarks() const {return m_distanceToQuarks;}

	/** Return the B decay vertex position: */
	inline const TVector3 BDecVtx() const {return m_BDecVtx;}
	int Bpdg() const {return m_Bpdg;}

private:
	enum momentumSet {PtEtaPhiM=0, PtEtaPhiE, PxPyPzM, PxPyPzE};
	double m_deltaRCut; // !< deltaR cut value of the cone matching (max distance between Jet axis and momentum of truth particle)
	double m_ptCut;// !< pT cut for partons
	bool m_noDoc;
	int m_pdg;// !< pdg code of the parton/baryon the jet has been matched to (which was closes)
	int m_barcode;// !< barcode of the matched parton (to be able to find the parton in the McEventColl)
	bool m_testJet(const TLorentzVector myJet,
			const int mc_n,
			const std::vector<float> *mc_p1,
			const std::vector<float> *mc_p2,
			const std::vector<float> *mc_p3,
			const std::vector<float> *mc_p4,
			const std::vector<int> *mc_pdgId,
			const std::vector<int> *mc_status,
			const std::vector<int> *mc_barcode,
			const std::vector<float> *mc_vx_x,
			const std::vector<float> *mc_vx_y,
			const std::vector<float> *mc_vx_z,
			const std::vector<std::vector<int> > *mc_parent_index,
			const std::vector<std::vector<int> > *mc_child_index,
			const enum momentumSet mode);
	std::string m_jetLabel;// !< label to use for matching jets
	std::map<std::string, double> m_distanceToQuarks;// !< keep track of distance to quarks
	TVector3 m_BDecVtx;// !< position of the lowest lying B hadron vertex decay
	int m_Bpdg;
	enum verbosity m_verbosity;
};

/** Return barcode */
inline int JetQuarkLabelD3PD::barcode() const {return m_barcode;}

/** Return pdg to match */
inline int JetQuarkLabelD3PD::pdgCode() const {return m_pdg;}

class HadronClass {
public:
	static std::pair<short,short> type(int);
	static bool HeavyHadron(int);
};

#endif // JETQUARKLABELD3PD_H
