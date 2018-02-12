///////////////////////////////////////////////////////
// JetQuarkLabelD3PD.cxx
//   Source file for class JetQuarkLabelD3PD
///////////////////////////////////////////////////////
/**
 * <b>Purpose:</b> label jets with b or c quarks.<br>
 * <b>Author:</b> Jean-Baptiste de Vivie<br>
 * <b>Email:</b> devivie@cppm.in2p3.fr <br>
 * <b>Created:</b> 2005/02/25 <br>
 */

#include "MiniNtuple/JetQuarkLabelD3PD.h"

JetQuarkLabelD3PD::JetQuarkLabelD3PD() :
		m_deltaRCut(0.3), m_ptCut(5000.), // MeV
		m_noDoc(true), m_jetLabel("N/A"), m_verbosity(FATAL) {
}

JetQuarkLabelD3PD::~JetQuarkLabelD3PD() {
}

void JetQuarkLabelD3PD::initialize(const double deltaRCut, const double ptCut, const bool noDoc,
		const enum verbosity verb) {
	m_deltaRCut = deltaRCut;
	m_ptCut = ptCut;
	m_noDoc = noDoc;
	m_verbosity = verb;
}

bool JetQuarkLabelD3PD::matchJet(const TLorentzVector myJet, const int mc_n, const std::vector<float> *mc_pt,
		const std::vector<float> *mc_eta, const std::vector<float> *mc_phi, const std::vector<float> *mc_m,
		const std::vector<int> *mc_pdgId, const std::vector<int> *mc_status, const std::vector<int> *mc_barcode,
		const std::vector<float> *mc_vx_x, const std::vector<float> *mc_vx_y, const std::vector<float> *mc_vx_z,
		const std::vector<std::vector<int> > *mc_parent_index, const std::vector<std::vector<int> > *mc_child_index) {
	m_jetLabel = "N/A";

	return m_testJet(myJet, mc_n, mc_pt, mc_eta, mc_phi, mc_m, mc_pdgId, mc_status, mc_barcode, mc_vx_x, mc_vx_y, mc_vx_z,
			mc_parent_index, mc_child_index, PtEtaPhiM);
}

bool JetQuarkLabelD3PD::m_testJet(const TLorentzVector myJet, const int mc_n, const std::vector<float> *mc_p1,
		const std::vector<float> *mc_p2, const std::vector<float> *mc_p3, const std::vector<float> *mc_p4,
		const std::vector<int> *mc_pdgId, const std::vector<int> *mc_status, const std::vector<int> *mc_barcode,
		const std::vector<float> *mc_vx_x, const std::vector<float> *mc_vx_y, const std::vector<float> *mc_vx_z,
		const std::vector<std::vector<int> > *mc_parent_index, const std::vector<std::vector<int> > *mc_child_index,
		const enum momentumSet mode) {

	if (m_verbosity <= VERBOSE) {
		std::cerr << "Truth matching for jet " << myJet.Pt() << " " << myJet.Eta() << " " << myJet.Phi() << std::endl;
	}

	m_barcode = 0;
	m_pdg = 0;
	m_Bpdg = 0;
	m_BDecVtx = TVector3();
	m_distanceToQuarks.clear();
	// Tag only jet in the ID acceptance : not anymore...
	// Labeling might be usefull also outside ID acceptance if (fabs(myJet.Eta()) > 2.5) return false;
	//
	double deltaRC = 999.;
	double deltaRB = 999.;
	double deltaRT = 999.;
	double deltaR = 999.;
	int barcc = 0;
	int barcb = 0;

	//  unsigned int nLab = 0;
	TLorentzVector part_momentum_lv;
	int pdg;
	for (int i = 0; i < mc_n; i++) {
		//int
		pdg = mc_pdgId->at(i);

		// We want to use some special functions from TLorentzVector
		//TLorentzVector part_momentum_lv;
		if (mode == PtEtaPhiM) {
			part_momentum_lv.SetPtEtaPhiM(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
		} else if (mode == PtEtaPhiE) {
			part_momentum_lv.SetPtEtaPhiE(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
		} else if (mode == PxPyPzM) {
			part_momentum_lv.SetXYZM(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
		} else if (mode == PxPyPzE) {
			part_momentum_lv.SetPxPyPzE(mc_p1->at(i), mc_p2->at(i), mc_p3->at(i), mc_p4->at(i));
		} else {
			std::cerr << "unknown momentum set" << std::endl;
			return false;
		}

		// label b, c and light jets
		if (abs(pdg) == 5 || abs(pdg) == 4) {
			double pt = part_momentum_lv.Pt();
			if (pt > m_ptCut) {
				// Herwig! Do not use quark from Hadron decay !
				bool fromHadron = false;
				if (m_verbosity <= VERBOSE) {
					std::cerr << "MCTruth: part " << mc_barcode->at(i) << " PDG= " << pdg << " pT= " << part_momentum_lv.Pt()
							<< " eta= " << part_momentum_lv.Eta() << " phi= " << part_momentum_lv.Phi() << " dR= "
							<< part_momentum_lv.DeltaR(myJet) << std::endl;
				}

				//---------------------------------------------------------
				if (mc_parent_index->at(i).size() > 0) {
					std::vector < std::vector<int> > ancestor_index;

					for (unsigned int j = 0; j < mc_parent_index->at(i).size() && j < 1 && !fromHadron; j++) {
						std::vector<int> temp_vector;
						temp_vector.push_back(mc_parent_index->at(i).at(j));

						//Optimization from Sasha to prevent memory overflow
						if (HadronClass::HeavyHadron(mc_pdgId->at(mc_parent_index->at(i).at(j)))) {
							fromHadron = true;
							break;
						}
						ancestor_index.push_back(temp_vector);
					}

					for (unsigned int j = 0; j < ancestor_index.size() && !fromHadron; j++) {
						std::vector<int> temp_vector;
						for (unsigned int k = 0; k < ancestor_index.at(j).size() && !fromHadron; k++) {
							for (unsigned int l = 0;
									l < mc_parent_index->at(ancestor_index.at(j).at(k)).size() && l < 1 && !fromHadron; l++) {

								//Optimization from Sasha to prevent memory overflow
								if (HadronClass::HeavyHadron(mc_pdgId->at(mc_parent_index->at(ancestor_index.at(j).at(k)).at(l)))) {
									fromHadron = true;
									break;
								}
								temp_vector.push_back(mc_parent_index->at(ancestor_index.at(j).at(k)).at(l));
							}
						}
						if (temp_vector.size() > 0 && !fromHadron) {
							ancestor_index.push_back(temp_vector);
						}
					}

					for (unsigned int j = 0; j < ancestor_index.size() && !fromHadron; j++) {
						for (unsigned int k = 0; k < ancestor_index.at(j).size(); k++) {
							if (HadronClass::HeavyHadron(mc_pdgId->at(ancestor_index.at(j).at(k)))) {
								fromHadron = true;
								break;
							}
						}
					}
				}

				//---------------------------------------------------------
				// do not label by quark before FSR
				bool afterFSR = true;
				if (mc_child_index->at(i).size() > 0) {
					for (unsigned int j = 0; j < mc_child_index->at(i).size(); j++) {
						if (mc_pdgId->at(mc_child_index->at(i).at(j)) == pdg)
							afterFSR = false;
					}
				} else if ((mc_status->at(i) == 3 && m_noDoc) || (mc_status->at(i) == 10902)) {
					// do not label by documentary quark
					// (New 27/06/2006, for PYTHIA, with new Shower and maybe dependant on MSTP(128). What a mess !)
					afterFSR = false;
				}

				if (afterFSR && !fromHadron) {
					deltaR = part_momentum_lv.DeltaR(myJet);
					if (abs(pdg) == 4 && deltaR < deltaRC) {
						deltaRC = deltaR;
						barcc = mc_barcode->at(i);
					}
					if (abs(pdg) == 5 && deltaR < deltaRB) {
						deltaRB = deltaR;
						barcb = mc_barcode->at(i);
					}
				}
			}
		} // abs(pdg)==4 || abs(pdg)==5

		if (abs(pdg) == 15) {
			double pt = part_momentum_lv.Pt();
			if (pt > m_ptCut) {
				if (m_verbosity <= VERBOSE) {
					std::cerr << "MCTruth: part " << mc_barcode->at(i) << " PDG=" << pdg << " pT= " << part_momentum_lv.Pt()
							<< " eta= " << part_momentum_lv.Eta() << " phi= " << part_momentum_lv.Phi() << " dR= "
							<< part_momentum_lv.DeltaR(myJet) << std::endl;
				}
				deltaR = part_momentum_lv.DeltaR(myJet);
				if (deltaR < deltaRT) {
					deltaRT = deltaR;
				}
			}
		}
	} // for i

	m_distanceToQuarks.insert(std::make_pair("B", deltaRB));
	m_distanceToQuarks.insert(std::make_pair("C", deltaRC));
	m_distanceToQuarks.insert(std::make_pair("T", deltaRT)); // it is not a quark !

	if (m_verbosity <= VERBOSE)
		std::cerr << "DeltaR " << deltaRB << " " << deltaRC << " " << deltaRT << std::endl;
	if (deltaRB < m_deltaRCut) {
		m_pdg = 5;
		m_barcode = barcb;
		m_jetLabel = "B";
		if (m_verbosity <= VERBOSE)
			std::cerr << "Jet matched with a b " << m_barcode << " after FSR, dR: " << deltaRB << std::endl;
		// JBdV Try Herwig !!! If Bhadron --> quark, the corresponding decay vertex is the primary !!
		//                     (but the following Hadron vertices are OK)

		int theB = -1;
		for (int j = 0; j < mc_n; j++) {
			if (mc_barcode->at(j) == barcb)
				theB = j;
		}
		if (theB >= 0) {
			if (m_verbosity <= VERBOSE) {
				if (mode == PtEtaPhiM || mode == PtEtaPhiE) {
					std::cerr << " bquark pt = " << mc_p1->at(theB) << " eta = " << mc_p2->at(theB) << " phi = "
							<< mc_p3->at(theB) << std::endl;
				} else if (mode == PxPyPzM || mode == PxPyPzE) {
					std::cerr << " bquark px = " << mc_p1->at(theB) << " py = " << mc_p2->at(theB) << " pz = " << mc_p3->at(theB)
							<< std::endl;
				}
			}
			if (mc_child_index->at(theB).size() > 0) {
				double deltaRbBmin = 9999;
				int barB = -1;

				std::vector < std::vector<int> > descendant_index;
				for (unsigned int j = 0; j < mc_child_index->at(theB).size(); j++) {
					std::vector<int> temp_vector;
					temp_vector.push_back(mc_child_index->at(theB).at(j));
					descendant_index.push_back(temp_vector);
				}
				for (unsigned int j = 0; j < descendant_index.size(); j++) {
					std::vector<int> temp_vector;
					for (unsigned int k = 0; k < descendant_index.at(j).size(); k++) {
						for (unsigned int l = 0; l < mc_child_index->at(descendant_index.at(j).at(k)).size(); l++) {
							temp_vector.push_back(mc_child_index->at(descendant_index.at(j).at(k)).at(l));
						}
					}
					if (temp_vector.size()) {
						descendant_index.push_back(temp_vector);
					}
				}

				TLorentzVector theB_momentum_lv;
				TLorentzVector child_momentum_lv;
				for (unsigned int j = 0; j < descendant_index.size(); j++) {
					for (unsigned int k = 0; k < descendant_index.at(j).size(); k++) {
						int childindex = descendant_index.at(j).at(k);
						int pdg = mc_pdgId->at(childindex);
						short typeH = HadronClass::type(pdg).first;
						short typeP = HadronClass::type(pdg).second;
						if (m_verbosity <= VERBOSE)
							std::cerr << "pdg = " << pdg << " typeH = " << typeH << " typeP = " << typeP << std::endl;

						if (typeP == 5 && ((typeH == 1 && (abs(pdg) % 10) == 2) || (typeH == 0 && (abs(pdg) % 10) == 1))) {
							//TLorentzVector theB_momentum_lv;
							//TLorentzVector child_momentum_lv;
							if (mode == PtEtaPhiM) {
								theB_momentum_lv.SetPtEtaPhiM(mc_p1->at(theB), mc_p2->at(theB), mc_p3->at(theB), mc_p4->at(theB));
								child_momentum_lv.SetPtEtaPhiM(mc_p1->at(childindex), mc_p2->at(childindex), mc_p3->at(childindex),
										mc_p4->at(childindex));
							} else if (mode == PtEtaPhiE) {
								theB_momentum_lv.SetPtEtaPhiE(mc_p1->at(theB), mc_p2->at(theB), mc_p3->at(theB), mc_p4->at(theB));
								child_momentum_lv.SetPtEtaPhiE(mc_p1->at(childindex), mc_p2->at(childindex), mc_p3->at(childindex),
										mc_p4->at(childindex));
							} else if (mode == PxPyPzM) {
								theB_momentum_lv.SetXYZM(mc_p1->at(theB), mc_p2->at(theB), mc_p3->at(theB), mc_p4->at(theB));
								child_momentum_lv.SetXYZM(mc_p1->at(childindex), mc_p2->at(childindex), mc_p3->at(childindex),
										mc_p4->at(childindex));
							} else if (mode == PxPyPzE) {
								theB_momentum_lv.SetPxPyPzE(mc_p1->at(theB), mc_p2->at(theB), mc_p3->at(theB), mc_p4->at(theB));
								child_momentum_lv.SetPxPyPzE(mc_p1->at(childindex), mc_p2->at(childindex), mc_p3->at(childindex),
										mc_p4->at(childindex));
							} else {
								std::cerr << "unknown momentum set" << std::endl;
								return false;
							}

							double deltaRbB = theB_momentum_lv.DeltaR(child_momentum_lv);
							if (m_verbosity <= VERBOSE)
								std::cerr << "b quark child " << pdg << " barcode = " << mc_barcode->at(childindex) << std::endl;
							if (deltaRbB < deltaRbBmin) {
								if (mc_child_index->at(childindex).size() > 0) {
									m_BDecVtx.SetX(mc_vx_x->at(mc_child_index->at(childindex).at(0)));
									m_BDecVtx.SetY(mc_vx_y->at(mc_child_index->at(childindex).at(0)));
									m_BDecVtx.SetZ(mc_vx_z->at(mc_child_index->at(childindex).at(0)));
									m_Bpdg = pdg;

									for (unsigned int k = 0; k < mc_child_index->at(childindex).size(); k++) {
										int goodchildindex = mc_child_index->at(childindex).at(k);
										if (abs(mc_pdgId->at(goodchildindex)) == 5) {
											if (m_verbosity <= VERBOSE)
												std::cerr << "Decay vertex corrupted !" << std::endl;
											if (mc_child_index->at(goodchildindex).size() > 0) {
												int goodbchildindex = mc_child_index->at(goodchildindex).at(0);
												while (abs(mc_pdgId->at(goodbchildindex)) <= 4) {
													if (mc_child_index->at(goodbchildindex).size() > 0) {
														goodbchildindex = mc_child_index->at(goodbchildindex).at(0);
													} else {
														break;
													}
												}
												if (mc_child_index->at(goodbchildindex).size() > 0) {
													m_BDecVtx.SetX(mc_vx_x->at(mc_child_index->at(goodbchildindex).at(0)));
													m_BDecVtx.SetY(mc_vx_x->at(mc_child_index->at(goodbchildindex).at(0)));
													m_BDecVtx.SetZ(mc_vx_x->at(mc_child_index->at(goodbchildindex).at(0)));
													if (m_verbosity <= VERBOSE) {
														std::cerr << "Trying to recover pdg Good Child = " << mc_pdgId->at(goodbchildindex)
																<< " Decay vertex " << m_BDecVtx.X() << " " << m_BDecVtx.Y() << " " << m_BDecVtx.Z()
																<< std::endl;
													}
													break;
												}
											}
										}
									}
								}
								deltaRbBmin = deltaRbB;
								barB = mc_barcode->at(childindex);
							}
						}
					}
				} // descendant_index

				if (m_verbosity <= VERBOSE) {
					int theBHad = -1;
					for (int j = 0; j < mc_n; j++) {
						if (mc_barcode->at(j) == barB)
							theBHad = j;
					}
					if (theBHad >= 0) {
						std::cerr << "The nearest B hadron for a b-labelled jet " << std::endl;
						std::cerr << "barc = " << barB << " DR = " << deltaRbBmin << std::endl;
						if (mode == PtEtaPhiM || mode == PtEtaPhiE) {
							std::cerr << " pt = " << mc_p1->at(theBHad) << " eta = " << mc_p2->at(theBHad) << " phi = "
									<< mc_p3->at(theBHad) << std::endl;
						} else if (mode == PxPyPzM || mode == PxPyPzE) {
							std::cerr << " px = " << mc_p1->at(theBHad) << " py = " << mc_p2->at(theBHad) << " pz = "
									<< mc_p3->at(theBHad) << std::endl;
						}
					}
				}
			} // mc_child_index.size()>0
			else {
				if (m_verbosity <= VERBOSE)
					std::cerr << " bquark doesn't have child" << std::endl;
			}
		} // theB>=0
		else {
			if (m_verbosity <= VERBOSE)
				std::cerr << " arcode not found" << std::endl;
		}
		return true;
	} else if (deltaRC < m_deltaRCut) {
		m_pdg = 4;
		m_barcode = barcc;
		m_jetLabel = "C";
		if (m_verbosity <= VERBOSE)
			std::cerr << "Jet matched with a c " << m_barcode << " after FSR, dR: " << deltaRC << std::endl;
		return true;
	} else if (deltaRT < m_deltaRCut) {
		m_pdg = 15;
		m_jetLabel = "T";
		if (m_verbosity <= VERBOSE)
			std::cerr << "Jet matched with a tau dR: " << deltaRT << std::endl;
		return true;
	} else {
		m_pdg = 0;
		m_barcode = 0;
		m_jetLabel = "N/A";
		return false;
	}
	return false;

}

double JetQuarkLabelD3PD::deltaRMinTo(const std::string &key) const {
	double dR = 9999.;
	std::map<std::string, double>::const_iterator posI = m_distanceToQuarks.find(key);
	std::map<std::string, double>::const_iterator posE = m_distanceToQuarks.end();
	if (posI != posE)
		dR = posI->second;
	return dR;
}

std::pair<short, short> HadronClass::type(int pdg) {
	short typeP = 0; // Flavor
	short typeH = 2; // 0: meson ; 1 : baryon ; 2 : other
	std::ostringstream o;
	o << abs(pdg);
	std::string s = o.str();
	int ns = s.size();
	if (ns >= 4) {
		if (s.at(ns - 4) != '0') {
			typeH = 1;
			typeP = atoi(s.substr(ns - 4, 1).c_str());
		} else {
			typeH = 0;
			typeP = atoi(s.substr(ns - 3, 1).c_str());
		}
	} else if (ns == 3) {
		typeH = 0;
		typeP = atoi(s.substr(0, 1).c_str());
	}

	return std::make_pair(typeH, typeP);
}

bool HadronClass::HeavyHadron(int pdg) {
	short typ = type(pdg).second;
	short typh = type(pdg).first;
	return (typh < 2 && (typ == 4 || typ == 5));
}
