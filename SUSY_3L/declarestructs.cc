#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "myevt.h"

void declarestructs(TTree* tree, myevt* evt) {
  TBranch *b;

  if(b = tree->GetBranch("myevt")) {
    b->GetLeaf("runNumber")->SetAddress(&(evt->runNumber));
    b->GetLeaf("eventNumber")->SetAddress(&(evt->eventNumber));
    b->GetLeaf("lumiBlock")->SetAddress(&(evt->lumiBlock));
    b->GetLeaf("bcid")->SetAddress(&(evt->bcid));
    b->GetLeaf("weight")->SetAddress(&(evt->weight));
    b->GetLeaf("isMC")->SetAddress(&(evt->isMC));
    b->GetLeaf("larError")->SetAddress(&(evt->larError));
    b->GetLeaf("tileError")->SetAddress(&(evt->tileError));
    b->GetLeaf("coreFlags")->SetAddress(&(evt->coreFlags));
    b->GetLeaf("top_hfor_type")->SetAddress(&(evt->top_hfor_type));
    b->GetLeaf("mc_channel_number")->SetAddress(&(evt->mc_channel_number));
    b->GetLeaf("Eventshape_rhoKt4LC")->SetAddress(&(evt->Eventshape_rhoKt4LC));
    b->GetLeaf("averageIntPerXing")->SetAddress(&(evt->averageIntPerXing));
    b->GetLeaf("actualIntPerXing")->SetAddress(&(evt->actualIntPerXing));
    b->GetLeaf("mcevt_n")->SetAddress(&(evt->mcevt_n));
    b->GetLeaf("mcevt_signal_process_id")->SetAddress(&(evt->mcevt_signal_process_id));
    b->GetLeaf("mcevt_event_number")->SetAddress(&(evt->mcevt_event_number));
    b->GetLeaf("mcevt_event_scale")->SetAddress(&(evt->mcevt_event_scale));
    b->GetLeaf("mcevt_pdf_id1")->SetAddress(&(evt->mcevt_pdf_id1));
    b->GetLeaf("mcevt_pdf_id2")->SetAddress(&(evt->mcevt_pdf_id2));
    b->GetLeaf("mcevt_pdf_x1")->SetAddress(&(evt->mcevt_pdf_x1));
    b->GetLeaf("mcevt_pdf_x2")->SetAddress(&(evt->mcevt_pdf_x2));
    b->GetLeaf("mcevt_weight")->SetAddress(&(evt->mcevt_weight));
    b->GetLeaf("vxp_n")->SetAddress(&(evt->vxp_n));
    b->GetLeaf("vxp_vertx")->SetAddress(&(evt->vxp_vertx));
    b->GetLeaf("vxp_verty")->SetAddress(&(evt->vxp_verty));
    b->GetLeaf("vxp_vertz")->SetAddress(&(evt->vxp_vertz));
    b->GetLeaf("vxp_vertNtrk")->SetAddress(&(evt->vxp_vertNtrk));
    b->GetLeaf("vxp_vertSumPt")->SetAddress(&(evt->vxp_vertSumPt));
    b->GetLeaf("MET_Egamma10NoTau_RefFinal_etx")->SetAddress(&(evt->MET_Egamma10NoTau_RefFinal_etx));
    b->GetLeaf("MET_Egamma10NoTau_RefFinal_ety")->SetAddress(&(evt->MET_Egamma10NoTau_RefFinal_ety));
    b->GetLeaf("MET_Egamma10NoTau_RefFinal_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_RefFinal_sumet));
    b->GetLeaf("MET_Egamma10NoTau_RefGamma_etx")->SetAddress(&(evt->MET_Egamma10NoTau_RefGamma_etx));
    b->GetLeaf("MET_Egamma10NoTau_RefGamma_ety")->SetAddress(&(evt->MET_Egamma10NoTau_RefGamma_ety));
    b->GetLeaf("MET_Egamma10NoTau_RefGamma_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_RefGamma_sumet));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_etx")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_etx));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_ety")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_ety));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_sumet));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_Eflow_etx")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_Eflow_etx));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_Eflow_ety")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_Eflow_ety));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_Eflow_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_Eflow_sumet));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_Eflow_STVF_etx")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_Eflow_STVF_etx));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_Eflow_STVF_ety")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_Eflow_STVF_ety));
    b->GetLeaf("MET_Egamma10NoTau_CellOut_Eflow_STVF_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_CellOut_Eflow_STVF_sumet));
    b->GetLeaf("MET_Egamma10NoTau_STVF_RefFinal_etx")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_RefFinal_etx));
    b->GetLeaf("MET_Egamma10NoTau_STVF_RefFinal_ety")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_RefFinal_ety));
    b->GetLeaf("MET_Egamma10NoTau_STVF_RefFinal_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_RefFinal_sumet));
    b->GetLeaf("MET_Egamma10NoTau_STVF_RefGamma_etx")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_RefGamma_etx));
    b->GetLeaf("MET_Egamma10NoTau_STVF_RefGamma_ety")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_RefGamma_ety));
    b->GetLeaf("MET_Egamma10NoTau_STVF_RefGamma_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_RefGamma_sumet));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_etx")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_etx));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_ety")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_ety));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_sumet));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_Track_etx")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_Track_etx));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_Track_ety")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_Track_ety));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_Track_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_Track_sumet));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_TrackPV_etx")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_TrackPV_etx));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_TrackPV_ety")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_TrackPV_ety));
    b->GetLeaf("MET_Egamma10NoTau_STVF_CellOut_TrackPV_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_CellOut_TrackPV_sumet));
    b->GetLeaf("MET_Egamma10NoTau_STVF_SoftJets_etx")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_SoftJets_etx));
    b->GetLeaf("MET_Egamma10NoTau_STVF_SoftJets_ety")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_SoftJets_ety));
    b->GetLeaf("MET_Egamma10NoTau_STVF_SoftJets_sumet")->SetAddress(&(evt->MET_Egamma10NoTau_STVF_SoftJets_sumet));
    b->GetLeaf("MET_LocHadTopo_etx")->SetAddress(&(evt->MET_LocHadTopo_etx));
    b->GetLeaf("MET_LocHadTopo_ety")->SetAddress(&(evt->MET_LocHadTopo_ety));
    b->GetLeaf("MET_LocHadTopo_sumet")->SetAddress(&(evt->MET_LocHadTopo_sumet));
    b->GetLeaf("el_n")->SetAddress(&(evt->el_n));
    b->GetLeaf("el_E")->SetAddress(&(evt->el_E));
    b->GetLeaf("el_Et")->SetAddress(&(evt->el_Et));
    b->GetLeaf("el_pt")->SetAddress(&(evt->el_pt));
    b->GetLeaf("el_m")->SetAddress(&(evt->el_m));
    b->GetLeaf("el_eta")->SetAddress(&(evt->el_eta));
    b->GetLeaf("el_phi")->SetAddress(&(evt->el_phi));
    b->GetLeaf("el_px")->SetAddress(&(evt->el_px));
    b->GetLeaf("el_py")->SetAddress(&(evt->el_py));
    b->GetLeaf("el_pz")->SetAddress(&(evt->el_pz));
    b->GetLeaf("el_charge")->SetAddress(&(evt->el_charge));
    b->GetLeaf("el_author")->SetAddress(&(evt->el_author));
    b->GetLeaf("el_isEM")->SetAddress(&(evt->el_isEM));
    b->GetLeaf("el_convFlag")->SetAddress(&(evt->el_convFlag));
    b->GetLeaf("el_isConv")->SetAddress(&(evt->el_isConv));
    b->GetLeaf("el_type")->SetAddress(&(evt->el_type));
    b->GetLeaf("el_origin")->SetAddress(&(evt->el_origin));
    b->GetLeaf("el_typebkg")->SetAddress(&(evt->el_typebkg));
    b->GetLeaf("el_originbkg")->SetAddress(&(evt->el_originbkg));
    b->GetLeaf("el_OQ")->SetAddress(&(evt->el_OQ));
    b->GetLeaf("el_isfake")->SetAddress(&(evt->el_isfake));
    b->GetLeaf("el_ischmisid")->SetAddress(&(evt->el_ischmisid));
    b->GetLeaf("el_loosePP")->SetAddress(&(evt->el_loosePP));
    b->GetLeaf("el_mediumPP")->SetAddress(&(evt->el_mediumPP));
    b->GetLeaf("el_tightPP")->SetAddress(&(evt->el_tightPP));
    b->GetLeaf("el_weta2")->SetAddress(&(evt->el_weta2));
    b->GetLeaf("el_expectHitInBLayer")->SetAddress(&(evt->el_expectHitInBLayer));
    b->GetLeaf("el_reta")->SetAddress(&(evt->el_reta));
    b->GetLeaf("el_rphi")->SetAddress(&(evt->el_rphi));
    b->GetLeaf("el_etap")->SetAddress(&(evt->el_etap));
    b->GetLeaf("el_Etcone20")->SetAddress(&(evt->el_Etcone20));
    b->GetLeaf("el_Etcone30")->SetAddress(&(evt->el_Etcone30));
    b->GetLeaf("el_Etcone40")->SetAddress(&(evt->el_Etcone40));
    b->GetLeaf("el_Etcone45")->SetAddress(&(evt->el_Etcone45));
    b->GetLeaf("el_ptcone20")->SetAddress(&(evt->el_ptcone20));
    b->GetLeaf("el_ptcone30")->SetAddress(&(evt->el_ptcone30));
    b->GetLeaf("el_ptcone40")->SetAddress(&(evt->el_ptcone40));
    b->GetLeaf("el_nucone20")->SetAddress(&(evt->el_nucone20));
    b->GetLeaf("el_nucone30")->SetAddress(&(evt->el_nucone30));
    b->GetLeaf("el_nucone40")->SetAddress(&(evt->el_nucone40));
    b->GetLeaf("el_Etcone40_corrected")->SetAddress(&(evt->el_Etcone40_corrected));
    b->GetLeaf("el_Etcone40_ED_corrected")->SetAddress(&(evt->el_Etcone40_ED_corrected));
    b->GetLeaf("el_cl_E")->SetAddress(&(evt->el_cl_E));
    b->GetLeaf("el_cl_pt")->SetAddress(&(evt->el_cl_pt));
    b->GetLeaf("el_cl_eta")->SetAddress(&(evt->el_cl_eta));
    b->GetLeaf("el_cl_phi")->SetAddress(&(evt->el_cl_phi));
    b->GetLeaf("el_trackd0")->SetAddress(&(evt->el_trackd0));
    b->GetLeaf("el_trackz0")->SetAddress(&(evt->el_trackz0));
    b->GetLeaf("el_tracktheta")->SetAddress(&(evt->el_tracktheta));
    b->GetLeaf("el_trackphi")->SetAddress(&(evt->el_trackphi));
    b->GetLeaf("el_trackpt")->SetAddress(&(evt->el_trackpt));
    b->GetLeaf("el_tracketa")->SetAddress(&(evt->el_tracketa));
    b->GetLeaf("el_trackd0pv")->SetAddress(&(evt->el_trackd0pv));
    b->GetLeaf("el_tracksigd0pv")->SetAddress(&(evt->el_tracksigd0pv));
    b->GetLeaf("el_trackz0pv")->SetAddress(&(evt->el_trackz0pv));
    b->GetLeaf("el_tracksigz0pv")->SetAddress(&(evt->el_tracksigz0pv));
    b->GetLeaf("el_nBLHits")->SetAddress(&(evt->el_nBLHits));
    b->GetLeaf("el_nPixHits")->SetAddress(&(evt->el_nPixHits));
    b->GetLeaf("el_nSCTHits")->SetAddress(&(evt->el_nSCTHits));
    b->GetLeaf("el_nTRTHits")->SetAddress(&(evt->el_nTRTHits));
    b->GetLeaf("el_nTRTHighTHits")->SetAddress(&(evt->el_nTRTHighTHits));
    b->GetLeaf("el_nTRTOutliers")->SetAddress(&(evt->el_nTRTOutliers));
    b->GetLeaf("el_nTRTHighTOutliers")->SetAddress(&(evt->el_nTRTHighTOutliers));
    b->GetLeaf("el_nPixHoles")->SetAddress(&(evt->el_nPixHoles));
    b->GetLeaf("el_nSCTHoles")->SetAddress(&(evt->el_nSCTHoles));
    b->GetLeaf("el_hastrack")->SetAddress(&(evt->el_hastrack));
    b->GetLeaf("el_trackd0beam")->SetAddress(&(evt->el_trackd0beam));
    b->GetLeaf("el_etas2")->SetAddress(&(evt->el_etas2));
    b->GetLeaf("el_phis2")->SetAddress(&(evt->el_phis2));
    b->GetLeaf("el_Ethad")->SetAddress(&(evt->el_Ethad));
    b->GetLeaf("el_f1")->SetAddress(&(evt->el_f1));
    b->GetLeaf("el_f1core")->SetAddress(&(evt->el_f1core));
    b->GetLeaf("el_f3")->SetAddress(&(evt->el_f3));
    b->GetLeaf("el_f3core")->SetAddress(&(evt->el_f3core));
    b->GetLeaf("el_E233")->SetAddress(&(evt->el_E233));
    b->GetLeaf("el_E237")->SetAddress(&(evt->el_E237));
    b->GetLeaf("el_E277")->SetAddress(&(evt->el_E277));
    b->GetLeaf("el_Rconv")->SetAddress(&(evt->el_Rconv));
    b->GetLeaf("el_zconv")->SetAddress(&(evt->el_zconv));
    b->GetLeaf("el_deltaEs")->SetAddress(&(evt->el_deltaEs));
    b->GetLeaf("el_wstot")->SetAddress(&(evt->el_wstot));
    b->GetLeaf("el_ws3")->SetAddress(&(evt->el_ws3));
    b->GetLeaf("el_fside")->SetAddress(&(evt->el_fside));
    b->GetLeaf("el_Emax2")->SetAddress(&(evt->el_Emax2));
    b->GetLeaf("el_MET_Egamma10NoTau_STVF_wpx")->SetAddress(&(evt->el_MET_Egamma10NoTau_STVF_wpx));
    b->GetLeaf("el_MET_Egamma10NoTau_STVF_wpy")->SetAddress(&(evt->el_MET_Egamma10NoTau_STVF_wpy));
    b->GetLeaf("el_MET_Egamma10NoTau_STVF_wet")->SetAddress(&(evt->el_MET_Egamma10NoTau_STVF_wet));
    b->GetLeaf("el_MET_Egamma10NoTau_STVF_statusWord")->SetAddress(&(evt->el_MET_Egamma10NoTau_STVF_statusWord));
    b->GetLeaf("el_MET_Egamma10NoTau_wpx")->SetAddress(&(evt->el_MET_Egamma10NoTau_wpx));
    b->GetLeaf("el_MET_Egamma10NoTau_wpy")->SetAddress(&(evt->el_MET_Egamma10NoTau_wpy));
    b->GetLeaf("el_MET_Egamma10NoTau_wet")->SetAddress(&(evt->el_MET_Egamma10NoTau_wet));
    b->GetLeaf("el_MET_Egamma10NoTau_statusWord")->SetAddress(&(evt->el_MET_Egamma10NoTau_statusWord));
    b->GetLeaf("el_Ethad1")->SetAddress(&(evt->el_Ethad1));
    b->GetLeaf("el_emaxs1")->SetAddress(&(evt->el_emaxs1));
    b->GetLeaf("el_deltaeta1")->SetAddress(&(evt->el_deltaeta1));
    b->GetLeaf("el_trackd0_physics")->SetAddress(&(evt->el_trackd0_physics));
    b->GetLeaf("el_TRTHighTOutliersRatio")->SetAddress(&(evt->el_TRTHighTOutliersRatio));
    b->GetLeaf("el_nSiHits")->SetAddress(&(evt->el_nSiHits));
    b->GetLeaf("el_nSCTOutliers")->SetAddress(&(evt->el_nSCTOutliers));
    b->GetLeaf("el_nPixelOutliers")->SetAddress(&(evt->el_nPixelOutliers));
    b->GetLeaf("el_nBLayerOutliers")->SetAddress(&(evt->el_nBLayerOutliers));
    b->GetLeaf("el_trackqoverp")->SetAddress(&(evt->el_trackqoverp));
    b->GetLeaf("el_deltaphi2")->SetAddress(&(evt->el_deltaphi2));
    b->GetLeaf("el_Es0")->SetAddress(&(evt->el_Es0));
    b->GetLeaf("el_Es1")->SetAddress(&(evt->el_Es1));
    b->GetLeaf("el_Es2")->SetAddress(&(evt->el_Es2));
    b->GetLeaf("el_Es3")->SetAddress(&(evt->el_Es3));
    b->GetLeaf("el_topoEtcone20_corrected")->SetAddress(&(evt->el_topoEtcone20_corrected));
    b->GetLeaf("el_topoEtcone30_corrected")->SetAddress(&(evt->el_topoEtcone30_corrected));
    b->GetLeaf("el_topoEtcone40_corrected")->SetAddress(&(evt->el_topoEtcone40_corrected));
    b->GetLeaf("el_trackIPEstimate_d0_unbiasedpvunbiased")->SetAddress(&(evt->el_trackIPEstimate_d0_unbiasedpvunbiased));
    b->GetLeaf("el_trackIPEstimate_sigd0_unbiasedpvunbiased")->SetAddress(&(evt->el_trackIPEstimate_sigd0_unbiasedpvunbiased));
    b->GetLeaf("el_trackIPEstimate_z0_unbiasedpvunbiased")->SetAddress(&(evt->el_trackIPEstimate_z0_unbiasedpvunbiased));
    b->GetLeaf("el_trackIPEstimate_sigz0_unbiasedpvunbiased")->SetAddress(&(evt->el_trackIPEstimate_sigz0_unbiasedpvunbiased));
    b->GetLeaf("mu_staco_n")->SetAddress(&(evt->mu_staco_n));
    b->GetLeaf("mu_staco_E")->SetAddress(&(evt->mu_staco_E));
    b->GetLeaf("mu_staco_pt")->SetAddress(&(evt->mu_staco_pt));
    b->GetLeaf("mu_staco_m")->SetAddress(&(evt->mu_staco_m));
    b->GetLeaf("mu_staco_eta")->SetAddress(&(evt->mu_staco_eta));
    b->GetLeaf("mu_staco_phi")->SetAddress(&(evt->mu_staco_phi));
    b->GetLeaf("mu_staco_px")->SetAddress(&(evt->mu_staco_px));
    b->GetLeaf("mu_staco_py")->SetAddress(&(evt->mu_staco_py));
    b->GetLeaf("mu_staco_pz")->SetAddress(&(evt->mu_staco_pz));
    b->GetLeaf("mu_staco_charge")->SetAddress(&(evt->mu_staco_charge));
    b->GetLeaf("mu_staco_author")->SetAddress(&(evt->mu_staco_author));
    b->GetLeaf("mu_staco_matchchi2")->SetAddress(&(evt->mu_staco_matchchi2));
    b->GetLeaf("mu_staco_matchndof")->SetAddress(&(evt->mu_staco_matchndof));
    b->GetLeaf("mu_staco_etcone20")->SetAddress(&(evt->mu_staco_etcone20));
    b->GetLeaf("mu_staco_etcone30")->SetAddress(&(evt->mu_staco_etcone30));
    b->GetLeaf("mu_staco_etcone40")->SetAddress(&(evt->mu_staco_etcone40));
    b->GetLeaf("mu_staco_ptcone20")->SetAddress(&(evt->mu_staco_ptcone20));
    b->GetLeaf("mu_staco_ptcone30")->SetAddress(&(evt->mu_staco_ptcone30));
    b->GetLeaf("mu_staco_ptcone40")->SetAddress(&(evt->mu_staco_ptcone40));
    b->GetLeaf("mu_staco_energyLossPar")->SetAddress(&(evt->mu_staco_energyLossPar));
    b->GetLeaf("mu_staco_energyLossErr")->SetAddress(&(evt->mu_staco_energyLossErr));
    b->GetLeaf("mu_staco_bestMatch")->SetAddress(&(evt->mu_staco_bestMatch));
    b->GetLeaf("mu_staco_isStandAloneMuon")->SetAddress(&(evt->mu_staco_isStandAloneMuon));
    b->GetLeaf("mu_staco_isCombinedMuon")->SetAddress(&(evt->mu_staco_isCombinedMuon));
    b->GetLeaf("mu_staco_isSegmentTaggedMuon")->SetAddress(&(evt->mu_staco_isSegmentTaggedMuon));
    b->GetLeaf("mu_staco_isLowPtReconstructedMuon")->SetAddress(&(evt->mu_staco_isLowPtReconstructedMuon));
    b->GetLeaf("mu_staco_loose")->SetAddress(&(evt->mu_staco_loose));
    b->GetLeaf("mu_staco_isfake")->SetAddress(&(evt->mu_staco_isfake));
    b->GetLeaf("mu_staco_ischmisid")->SetAddress(&(evt->mu_staco_ischmisid));
    b->GetLeaf("mu_staco_truth_barcode")->SetAddress(&(evt->mu_staco_truth_barcode));
    b->GetLeaf("mu_staco_d0_exPV")->SetAddress(&(evt->mu_staco_d0_exPV));
    b->GetLeaf("mu_staco_z0_exPV")->SetAddress(&(evt->mu_staco_z0_exPV));
    b->GetLeaf("mu_staco_phi_exPV")->SetAddress(&(evt->mu_staco_phi_exPV));
    b->GetLeaf("mu_staco_theta_exPV")->SetAddress(&(evt->mu_staco_theta_exPV));
    b->GetLeaf("mu_staco_qoverp_exPV")->SetAddress(&(evt->mu_staco_qoverp_exPV));
    b->GetLeaf("mu_staco_cov_qoverp_exPV")->SetAddress(&(evt->mu_staco_cov_qoverp_exPV));
    b->GetLeaf("mu_staco_cov_d0_exPV")->SetAddress(&(evt->mu_staco_cov_d0_exPV));
    b->GetLeaf("mu_staco_cov_z0_exPV")->SetAddress(&(evt->mu_staco_cov_z0_exPV));
    b->GetLeaf("mu_staco_ms_d0")->SetAddress(&(evt->mu_staco_ms_d0));
    b->GetLeaf("mu_staco_ms_z0")->SetAddress(&(evt->mu_staco_ms_z0));
    b->GetLeaf("mu_staco_ms_phi")->SetAddress(&(evt->mu_staco_ms_phi));
    b->GetLeaf("mu_staco_ms_theta")->SetAddress(&(evt->mu_staco_ms_theta));
    b->GetLeaf("mu_staco_ms_qoverp")->SetAddress(&(evt->mu_staco_ms_qoverp));
    b->GetLeaf("mu_staco_id_d0")->SetAddress(&(evt->mu_staco_id_d0));
    b->GetLeaf("mu_staco_id_z0")->SetAddress(&(evt->mu_staco_id_z0));
    b->GetLeaf("mu_staco_id_phi")->SetAddress(&(evt->mu_staco_id_phi));
    b->GetLeaf("mu_staco_id_theta")->SetAddress(&(evt->mu_staco_id_theta));
    b->GetLeaf("mu_staco_id_qoverp")->SetAddress(&(evt->mu_staco_id_qoverp));
    b->GetLeaf("mu_staco_id_d0_exPV")->SetAddress(&(evt->mu_staco_id_d0_exPV));
    b->GetLeaf("mu_staco_id_z0_exPV")->SetAddress(&(evt->mu_staco_id_z0_exPV));
    b->GetLeaf("mu_staco_id_phi_exPV")->SetAddress(&(evt->mu_staco_id_phi_exPV));
    b->GetLeaf("mu_staco_id_theta_exPV")->SetAddress(&(evt->mu_staco_id_theta_exPV));
    b->GetLeaf("mu_staco_id_qoverp_exPV")->SetAddress(&(evt->mu_staco_id_qoverp_exPV));
    b->GetLeaf("mu_staco_id_cov_d0_exPV")->SetAddress(&(evt->mu_staco_id_cov_d0_exPV));
    b->GetLeaf("mu_staco_id_cov_z0_exPV")->SetAddress(&(evt->mu_staco_id_cov_z0_exPV));
    b->GetLeaf("mu_staco_id_cov_phi_exPV")->SetAddress(&(evt->mu_staco_id_cov_phi_exPV));
    b->GetLeaf("mu_staco_id_cov_theta_exPV")->SetAddress(&(evt->mu_staco_id_cov_theta_exPV));
    b->GetLeaf("mu_staco_id_cov_qoverp_exPV")->SetAddress(&(evt->mu_staco_id_cov_qoverp_exPV));
    b->GetLeaf("mu_staco_me_d0")->SetAddress(&(evt->mu_staco_me_d0));
    b->GetLeaf("mu_staco_me_z0")->SetAddress(&(evt->mu_staco_me_z0));
    b->GetLeaf("mu_staco_me_phi")->SetAddress(&(evt->mu_staco_me_phi));
    b->GetLeaf("mu_staco_me_theta")->SetAddress(&(evt->mu_staco_me_theta));
    b->GetLeaf("mu_staco_me_qoverp")->SetAddress(&(evt->mu_staco_me_qoverp));
    b->GetLeaf("mu_staco_me_d0_exPV")->SetAddress(&(evt->mu_staco_me_d0_exPV));
    b->GetLeaf("mu_staco_me_z0_exPV")->SetAddress(&(evt->mu_staco_me_z0_exPV));
    b->GetLeaf("mu_staco_me_phi_exPV")->SetAddress(&(evt->mu_staco_me_phi_exPV));
    b->GetLeaf("mu_staco_me_theta_exPV")->SetAddress(&(evt->mu_staco_me_theta_exPV));
    b->GetLeaf("mu_staco_me_qoverp_exPV")->SetAddress(&(evt->mu_staco_me_qoverp_exPV));
    b->GetLeaf("mu_staco_nBLHits")->SetAddress(&(evt->mu_staco_nBLHits));
    b->GetLeaf("mu_staco_nPixHits")->SetAddress(&(evt->mu_staco_nPixHits));
    b->GetLeaf("mu_staco_nSctHits")->SetAddress(&(evt->mu_staco_nSctHits));
    b->GetLeaf("mu_staco_nTrtHits")->SetAddress(&(evt->mu_staco_nTrtHits));
    b->GetLeaf("mu_staco_nBLSharedHits")->SetAddress(&(evt->mu_staco_nBLSharedHits));
    b->GetLeaf("mu_staco_nPixSharedHits")->SetAddress(&(evt->mu_staco_nPixSharedHits));
    b->GetLeaf("mu_staco_nPixHoles")->SetAddress(&(evt->mu_staco_nPixHoles));
    b->GetLeaf("mu_staco_nSCTSharedHits")->SetAddress(&(evt->mu_staco_nSCTSharedHits));
    b->GetLeaf("mu_staco_nSCTHoles")->SetAddress(&(evt->mu_staco_nSCTHoles));
    b->GetLeaf("mu_staco_nTRTHighTHits")->SetAddress(&(evt->mu_staco_nTRTHighTHits));
    b->GetLeaf("mu_staco_nTRTOutliers")->SetAddress(&(evt->mu_staco_nTRTOutliers));
    b->GetLeaf("mu_staco_nTRTHighTOutliers")->SetAddress(&(evt->mu_staco_nTRTHighTOutliers));
    b->GetLeaf("mu_staco_expectBLayerHit")->SetAddress(&(evt->mu_staco_expectBLayerHit));
    b->GetLeaf("mu_staco_nPixelDeadSensors")->SetAddress(&(evt->mu_staco_nPixelDeadSensors));
    b->GetLeaf("mu_staco_nSCTDeadSensors")->SetAddress(&(evt->mu_staco_nSCTDeadSensors));
    b->GetLeaf("mu_staco_trackd0")->SetAddress(&(evt->mu_staco_trackd0));
    b->GetLeaf("mu_staco_trackz0")->SetAddress(&(evt->mu_staco_trackz0));
    b->GetLeaf("mu_staco_tracktheta")->SetAddress(&(evt->mu_staco_tracktheta));
    b->GetLeaf("mu_staco_trackphi")->SetAddress(&(evt->mu_staco_trackphi));
    b->GetLeaf("mu_staco_hastrack")->SetAddress(&(evt->mu_staco_hastrack));
    b->GetLeaf("mu_staco_ptcone20_trkelstyle")->SetAddress(&(evt->mu_staco_ptcone20_trkelstyle));
    b->GetLeaf("mu_staco_ptcone30_trkelstyle")->SetAddress(&(evt->mu_staco_ptcone30_trkelstyle));
    b->GetLeaf("mu_staco_ptcone40_trkelstyle")->SetAddress(&(evt->mu_staco_ptcone40_trkelstyle));
    b->GetLeaf("mu_staco_trackIPEstimate_d0_unbiasedpvunbiased")->SetAddress(&(evt->mu_staco_trackIPEstimate_d0_unbiasedpvunbiased));
    b->GetLeaf("mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased")->SetAddress(&(evt->mu_staco_trackIPEstimate_sigd0_unbiasedpvunbiased));
    b->GetLeaf("mu_staco_trackIPEstimate_z0_unbiasedpvunbiased")->SetAddress(&(evt->mu_staco_trackIPEstimate_z0_unbiasedpvunbiased));
    b->GetLeaf("mu_staco_trackIPEstimate_sigz0_unbiasedpvunbiased")->SetAddress(&(evt->mu_staco_trackIPEstimate_sigz0_unbiasedpvunbiased));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_wpx1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_wpx1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_wpy1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_wpy1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_wet1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_wet1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_statusWord1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_statusWord1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_wpx2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_wpx2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_wpy2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_wpy2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_wet2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_wet2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_STVF_statusWord2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_STVF_statusWord2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_wpx1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_wpx1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_wpy1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_wpy1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_wet1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_wet1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_statusWord1")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_statusWord1));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_wpx2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_wpx2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_wpy2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_wpy2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_wet2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_wet2));
    b->GetLeaf("mu_staco_MET_Egamma10NoTau_statusWord2")->SetAddress(&(evt->mu_staco_MET_Egamma10NoTau_statusWord2));
    b->GetLeaf("muonTruth_n")->SetAddress(&(evt->muonTruth_n));
    b->GetLeaf("muonTruth_pt")->SetAddress(&(evt->muonTruth_pt));
    b->GetLeaf("muonTruth_m")->SetAddress(&(evt->muonTruth_m));
    b->GetLeaf("muonTruth_eta")->SetAddress(&(evt->muonTruth_eta));
    b->GetLeaf("muonTruth_phi")->SetAddress(&(evt->muonTruth_phi));
    b->GetLeaf("muonTruth_charge")->SetAddress(&(evt->muonTruth_charge));
    b->GetLeaf("muonTruth_PDGID")->SetAddress(&(evt->muonTruth_PDGID));
    b->GetLeaf("muonTruth_barcode")->SetAddress(&(evt->muonTruth_barcode));
    b->GetLeaf("muonTruth_type")->SetAddress(&(evt->muonTruth_type));
    b->GetLeaf("muonTruth_origin")->SetAddress(&(evt->muonTruth_origin));
    b->GetLeaf("mc_n")->SetAddress(&(evt->mc_n));
    b->GetLeaf("mc_pt")->SetAddress(&(evt->mc_pt));
    b->GetLeaf("mc_m")->SetAddress(&(evt->mc_m));
    b->GetLeaf("mc_eta")->SetAddress(&(evt->mc_eta));
    b->GetLeaf("mc_phi")->SetAddress(&(evt->mc_phi));
    b->GetLeaf("mc_pdgId")->SetAddress(&(evt->mc_pdgId));
    b->GetLeaf("mc_charge")->SetAddress(&(evt->mc_charge));
    b->GetLeaf("mc_status")->SetAddress(&(evt->mc_status));
    b->GetLeaf("mc_parent_index1")->SetAddress(&(evt->mc_parent_index1));
    b->GetLeaf("mc_parent_index2")->SetAddress(&(evt->mc_parent_index2));
    b->GetLeaf("mc_child_index1")->SetAddress(&(evt->mc_child_index1));
    b->GetLeaf("mc_child_index2")->SetAddress(&(evt->mc_child_index2));
    b->GetLeaf("mc_parents1")->SetAddress(&(evt->mc_parents1));
    b->GetLeaf("mc_parents2")->SetAddress(&(evt->mc_parents2));
    b->GetLeaf("mc_children1")->SetAddress(&(evt->mc_children1));
    b->GetLeaf("mc_children2")->SetAddress(&(evt->mc_children2));
    b->GetLeaf("mc_barcode")->SetAddress(&(evt->mc_barcode));
    b->GetLeaf("mc_index")->SetAddress(&(evt->mc_index));
    b->GetLeaf("parton_n")->SetAddress(&(evt->parton_n));
    b->GetLeaf("parton_pt")->SetAddress(&(evt->parton_pt));
    b->GetLeaf("parton_m")->SetAddress(&(evt->parton_m));
    b->GetLeaf("parton_eta")->SetAddress(&(evt->parton_eta));
    b->GetLeaf("parton_phi")->SetAddress(&(evt->parton_phi));
    b->GetLeaf("parton_pdgId")->SetAddress(&(evt->parton_pdgId));
    b->GetLeaf("parton_charge")->SetAddress(&(evt->parton_charge));
    b->GetLeaf("parton_status")->SetAddress(&(evt->parton_status));
    b->GetLeaf("parton_parent_index1")->SetAddress(&(evt->parton_parent_index1));
    b->GetLeaf("parton_parent_index2")->SetAddress(&(evt->parton_parent_index2));
    b->GetLeaf("parton_child_index1")->SetAddress(&(evt->parton_child_index1));
    b->GetLeaf("parton_child_index2")->SetAddress(&(evt->parton_child_index2));
    b->GetLeaf("parton_parents1")->SetAddress(&(evt->parton_parents1));
    b->GetLeaf("parton_parents2")->SetAddress(&(evt->parton_parents2));
    b->GetLeaf("parton_children1")->SetAddress(&(evt->parton_children1));
    b->GetLeaf("parton_children2")->SetAddress(&(evt->parton_children2));
    b->GetLeaf("parton_barcode")->SetAddress(&(evt->parton_barcode));
    b->GetLeaf("parton_index")->SetAddress(&(evt->parton_index));
    b->GetLeaf("EF_e24vhi_medium1")->SetAddress(&(evt->EF_e24vhi_medium1));
    b->GetLeaf("EF_e60_medium1")->SetAddress(&(evt->EF_e60_medium1));
    b->GetLeaf("EF_mu24i_tight")->SetAddress(&(evt->EF_mu24i_tight));
    b->GetLeaf("EF_mu36_tight")->SetAddress(&(evt->EF_mu36_tight));
    b->GetLeaf("EF_mu24_j65_a4tchad_EFxe40_tclcw")->SetAddress(&(evt->EF_mu24_j65_a4tchad_EFxe40_tclcw));
    b->GetLeaf("EF_e24vh_medium1_EFxe35_tclcw")->SetAddress(&(evt->EF_e24vh_medium1_EFxe35_tclcw));
    b->GetLeaf("EF_2e12Tvh_loose1")->SetAddress(&(evt->EF_2e12Tvh_loose1));
    b->GetLeaf("EF_2mu13")->SetAddress(&(evt->EF_2mu13));
    b->GetLeaf("EF_mu18_tight_mu8_EFFS")->SetAddress(&(evt->EF_mu18_tight_mu8_EFFS));
    b->GetLeaf("EF_e12Tvh_medium1_mu10")->SetAddress(&(evt->EF_e12Tvh_medium1_mu10));
    b->GetLeaf("EF_e24vhi_loose1_mu8")->SetAddress(&(evt->EF_e24vhi_loose1_mu8));
    b->GetLeaf("EF_e24vh_medium1_e7_medium1")->SetAddress(&(evt->EF_e24vh_medium1_e7_medium1));
    b->GetLeaf("EF_e12Tvh_medium1_mu8")->SetAddress(&(evt->EF_e12Tvh_medium1_mu8));
    b->GetLeaf("EF_mu18_tight_e7_medium1")->SetAddress(&(evt->EF_mu18_tight_e7_medium1));
    b->GetLeaf("EF_xe80T_tclcw_loose")->SetAddress(&(evt->EF_xe80T_tclcw_loose));
    b->GetLeaf("EF_xe80_tclcw_loose")->SetAddress(&(evt->EF_xe80_tclcw_loose));
    b->GetLeaf("trig_EF_el_n")->SetAddress(&(evt->trig_EF_el_n));
    b->GetLeaf("trig_EF_el_eta")->SetAddress(&(evt->trig_EF_el_eta));
    b->GetLeaf("trig_EF_el_phi")->SetAddress(&(evt->trig_EF_el_phi));
    b->GetLeaf("trig_EF_el_EF_2e12Tvh_loose1")->SetAddress(&(evt->trig_EF_el_EF_2e12Tvh_loose1));
    b->GetLeaf("trig_EF_el_EF_e60_medium1")->SetAddress(&(evt->trig_EF_el_EF_e60_medium1));
    b->GetLeaf("trig_EF_el_EF_e12Tvh_medium1_mu8")->SetAddress(&(evt->trig_EF_el_EF_e12Tvh_medium1_mu8));
    b->GetLeaf("trig_EF_trigmuonef_n")->SetAddress(&(evt->trig_EF_trigmuonef_n));
    b->GetLeaf("trig_EF_trigmuonef_track_CB_eta")->SetAddress(&(evt->trig_EF_trigmuonef_track_CB_eta));
    b->GetLeaf("trig_EF_trigmuonef_track_CB_phi")->SetAddress(&(evt->trig_EF_trigmuonef_track_CB_phi));
    b->GetLeaf("trig_EF_trigmuonef_track_CB_hasCB")->SetAddress(&(evt->trig_EF_trigmuonef_track_CB_hasCB));
    b->GetLeaf("trig_EF_trigmuonef_EF_mu36_tight")->SetAddress(&(evt->trig_EF_trigmuonef_EF_mu36_tight));
    b->GetLeaf("trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS")->SetAddress(&(evt->trig_EF_trigmuonef_EF_mu18_tight_mu8_EFFS));
    b->GetLeaf("trig_EF_trigmuonef_EF_mu8")->SetAddress(&(evt->trig_EF_trigmuonef_EF_mu8));
    b->GetLeaf("trig_EF_trigmuonef_EF_mu18_tight")->SetAddress(&(evt->trig_EF_trigmuonef_EF_mu18_tight));
    b->GetLeaf("AntiKt4LCTopo.n")->SetAddress(&(evt->AntiKt4LCTopo.n));
    b->GetLeaf("AntiKt4LCTopo.phi")->SetAddress(&(evt->AntiKt4LCTopo.phi));
    b->GetLeaf("AntiKt4LCTopo.eta")->SetAddress(&(evt->AntiKt4LCTopo.eta));
    b->GetLeaf("AntiKt4LCTopo.E")->SetAddress(&(evt->AntiKt4LCTopo.E));
    b->GetLeaf("AntiKt4LCTopo.m")->SetAddress(&(evt->AntiKt4LCTopo.m));
    b->GetLeaf("AntiKt4LCTopo.pt")->SetAddress(&(evt->AntiKt4LCTopo.pt));
    b->GetLeaf("AntiKt4LCTopo.px")->SetAddress(&(evt->AntiKt4LCTopo.px));
    b->GetLeaf("AntiKt4LCTopo.py")->SetAddress(&(evt->AntiKt4LCTopo.py));
    b->GetLeaf("AntiKt4LCTopo.pz")->SetAddress(&(evt->AntiKt4LCTopo.pz));
    b->GetLeaf("AntiKt4LCTopo.emscale_phi")->SetAddress(&(evt->AntiKt4LCTopo.emscale_phi));
    b->GetLeaf("AntiKt4LCTopo.emscale_eta")->SetAddress(&(evt->AntiKt4LCTopo.emscale_eta));
    b->GetLeaf("AntiKt4LCTopo.emscale_E")->SetAddress(&(evt->AntiKt4LCTopo.emscale_E));
    b->GetLeaf("AntiKt4LCTopo.emscale_m")->SetAddress(&(evt->AntiKt4LCTopo.emscale_m));
    b->GetLeaf("AntiKt4LCTopo.emscale_pt")->SetAddress(&(evt->AntiKt4LCTopo.emscale_pt));
    b->GetLeaf("AntiKt4LCTopo.emscale_px")->SetAddress(&(evt->AntiKt4LCTopo.emscale_px));
    b->GetLeaf("AntiKt4LCTopo.emscale_py")->SetAddress(&(evt->AntiKt4LCTopo.emscale_py));
    b->GetLeaf("AntiKt4LCTopo.emscale_pz")->SetAddress(&(evt->AntiKt4LCTopo.emscale_pz));
    b->GetLeaf("AntiKt4LCTopo.constscale_E")->SetAddress(&(evt->AntiKt4LCTopo.constscale_E));
    b->GetLeaf("AntiKt4LCTopo.constscale_pt")->SetAddress(&(evt->AntiKt4LCTopo.constscale_pt));
    b->GetLeaf("AntiKt4LCTopo.constscale_m")->SetAddress(&(evt->AntiKt4LCTopo.constscale_m));
    b->GetLeaf("AntiKt4LCTopo.constscale_eta")->SetAddress(&(evt->AntiKt4LCTopo.constscale_eta));
    b->GetLeaf("AntiKt4LCTopo.constscale_phi")->SetAddress(&(evt->AntiKt4LCTopo.constscale_phi));
    b->GetLeaf("AntiKt4LCTopo.ActiveAreaPx")->SetAddress(&(evt->AntiKt4LCTopo.ActiveAreaPx));
    b->GetLeaf("AntiKt4LCTopo.ActiveAreaPy")->SetAddress(&(evt->AntiKt4LCTopo.ActiveAreaPy));
    b->GetLeaf("AntiKt4LCTopo.ActiveAreaPz")->SetAddress(&(evt->AntiKt4LCTopo.ActiveAreaPz));
    b->GetLeaf("AntiKt4LCTopo.ActiveAreaE")->SetAddress(&(evt->AntiKt4LCTopo.ActiveAreaE));
    b->GetLeaf("AntiKt4LCTopo.hecf")->SetAddress(&(evt->AntiKt4LCTopo.hecf));
    b->GetLeaf("AntiKt4LCTopo.timing")->SetAddress(&(evt->AntiKt4LCTopo.timing));
    b->GetLeaf("AntiKt4LCTopo.quality")->SetAddress(&(evt->AntiKt4LCTopo.quality));
    b->GetLeaf("AntiKt4LCTopo.emfrac")->SetAddress(&(evt->AntiKt4LCTopo.emfrac));
    b->GetLeaf("AntiKt4LCTopo.n90")->SetAddress(&(evt->AntiKt4LCTopo.n90));
    b->GetLeaf("AntiKt4LCTopo.tgap3f")->SetAddress(&(evt->AntiKt4LCTopo.tgap3f));
    b->GetLeaf("AntiKt4LCTopo.BCH_CORR_CELL")->SetAddress(&(evt->AntiKt4LCTopo.BCH_CORR_CELL));
    b->GetLeaf("AntiKt4LCTopo.BCH_CORR_JET")->SetAddress(&(evt->AntiKt4LCTopo.BCH_CORR_JET));
    b->GetLeaf("AntiKt4LCTopo.BCH_CORR_DOTX")->SetAddress(&(evt->AntiKt4LCTopo.BCH_CORR_DOTX));
    b->GetLeaf("AntiKt4LCTopo.GCWJES")->SetAddress(&(evt->AntiKt4LCTopo.GCWJES));
    b->GetLeaf("AntiKt4LCTopo.GCWJES_EtaCorr")->SetAddress(&(evt->AntiKt4LCTopo.GCWJES_EtaCorr));
    b->GetLeaf("AntiKt4LCTopo.EMJES")->SetAddress(&(evt->AntiKt4LCTopo.EMJES));
    b->GetLeaf("AntiKt4LCTopo.EMJES_EtaCorr")->SetAddress(&(evt->AntiKt4LCTopo.EMJES_EtaCorr));
    b->GetLeaf("AntiKt4LCTopo.EMJESnooffset")->SetAddress(&(evt->AntiKt4LCTopo.EMJESnooffset));
    b->GetLeaf("AntiKt4LCTopo.Offset")->SetAddress(&(evt->AntiKt4LCTopo.Offset));
    b->GetLeaf("AntiKt4LCTopo.jvtxf")->SetAddress(&(evt->AntiKt4LCTopo.jvtxf));
    b->GetLeaf("AntiKt4LCTopo.jvtx_x")->SetAddress(&(evt->AntiKt4LCTopo.jvtx_x));
    b->GetLeaf("AntiKt4LCTopo.jvtx_y")->SetAddress(&(evt->AntiKt4LCTopo.jvtx_y));
    b->GetLeaf("AntiKt4LCTopo.jvtx_z")->SetAddress(&(evt->AntiKt4LCTopo.jvtx_z));
    b->GetLeaf("AntiKt4LCTopo.OriginIndex")->SetAddress(&(evt->AntiKt4LCTopo.OriginIndex));
    b->GetLeaf("AntiKt4LCTopo.nTrk")->SetAddress(&(evt->AntiKt4LCTopo.nTrk));
    b->GetLeaf("AntiKt4LCTopo.sumPtTrk")->SetAddress(&(evt->AntiKt4LCTopo.sumPtTrk));
    b->GetLeaf("AntiKt4LCTopo.isUgly")->SetAddress(&(evt->AntiKt4LCTopo.isUgly));
    b->GetLeaf("AntiKt4LCTopo.isBadLoose")->SetAddress(&(evt->AntiKt4LCTopo.isBadLoose));
    b->GetLeaf("AntiKt4LCTopo.isBadTight")->SetAddress(&(evt->AntiKt4LCTopo.isBadTight));
    b->GetLeaf("AntiKt4LCTopo.fracSamplingMax")->SetAddress(&(evt->AntiKt4LCTopo.fracSamplingMax));
    b->GetLeaf("AntiKt4LCTopo.SamplingMax")->SetAddress(&(evt->AntiKt4LCTopo.SamplingMax));
    b->GetLeaf("AntiKt4LCTopo.LArQuality")->SetAddress(&(evt->AntiKt4LCTopo.LArQuality));
    b->GetLeaf("AntiKt4LCTopo.HECQuality")->SetAddress(&(evt->AntiKt4LCTopo.HECQuality));
    b->GetLeaf("AntiKt4LCTopo.NegativeE")->SetAddress(&(evt->AntiKt4LCTopo.NegativeE));
    b->GetLeaf("AntiKt4LCTopo.AverageLArQF")->SetAddress(&(evt->AntiKt4LCTopo.AverageLArQF));
    b->GetLeaf("AntiKt4LCTopo.EtaOrigin")->SetAddress(&(evt->AntiKt4LCTopo.EtaOrigin));
    b->GetLeaf("AntiKt4LCTopo.PhiOrigin")->SetAddress(&(evt->AntiKt4LCTopo.PhiOrigin));
    b->GetLeaf("AntiKt4LCTopo.MOrigin")->SetAddress(&(evt->AntiKt4LCTopo.MOrigin));
    b->GetLeaf("AntiKt4LCTopo.EtaOriginEM")->SetAddress(&(evt->AntiKt4LCTopo.EtaOriginEM));
    b->GetLeaf("AntiKt4LCTopo.PhiOriginEM")->SetAddress(&(evt->AntiKt4LCTopo.PhiOriginEM));
    b->GetLeaf("AntiKt4LCTopo.MOriginEM")->SetAddress(&(evt->AntiKt4LCTopo.MOriginEM));
    b->GetLeaf("AntiKt4LCTopo.flavor_truth_label")->SetAddress(&(evt->AntiKt4LCTopo.flavor_truth_label));
    b->GetLeaf("AntiKt4LCTopo.flavor_weight_MV1")->SetAddress(&(evt->AntiKt4LCTopo.flavor_weight_MV1));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpx")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpx));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpy")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpy));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wet")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wet));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_statusWord")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_statusWord));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpx2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpx2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpy2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpy2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wet2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wet2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_statusWord2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_statusWord2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpx3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpx3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpy3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wpy3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wet3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_wet3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_STVF_statusWord3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_STVF_statusWord3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wpx")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wpx));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wpy")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wpy));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wet")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wet));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_statusWord")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_statusWord));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wpx2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wpx2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wpy2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wpy2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wet2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wet2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_statusWord2")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_statusWord2));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wpx3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wpx3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wpy3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wpy3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_wet3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_wet3));
    b->GetLeaf("AntiKt4LCTopo.MET_Egamma10NoTau_statusWord3")->SetAddress(&(evt->AntiKt4LCTopo.MET_Egamma10NoTau_statusWord3));
    b->GetLeaf("AntiKt4Truth.n")->SetAddress(&(evt->AntiKt4Truth.n));
    b->GetLeaf("AntiKt4Truth.phi")->SetAddress(&(evt->AntiKt4Truth.phi));
    b->GetLeaf("AntiKt4Truth.eta")->SetAddress(&(evt->AntiKt4Truth.eta));
    b->GetLeaf("AntiKt4Truth.pt")->SetAddress(&(evt->AntiKt4Truth.pt));
    b->GetLeaf("AntiKt4Truth.px")->SetAddress(&(evt->AntiKt4Truth.px));
    b->GetLeaf("AntiKt4Truth.py")->SetAddress(&(evt->AntiKt4Truth.py));
    b->GetLeaf("AntiKt4Truth.pz")->SetAddress(&(evt->AntiKt4Truth.pz));
    b->GetLeaf("AntiKt4Truth.E")->SetAddress(&(evt->AntiKt4Truth.E));
    b->GetLeaf("AntiKt4Truth.m")->SetAddress(&(evt->AntiKt4Truth.m));
    b->GetLeaf("AntiKt4Truth.charge")->SetAddress(&(evt->AntiKt4Truth.charge));
    b->GetLeaf("AntiKt4Truth.flavor_truth_label")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_label));
    b->GetLeaf("AntiKt4Truth.flavor_truth_dRminToB")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_dRminToB));
    b->GetLeaf("AntiKt4Truth.flavor_truth_dRminToC")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_dRminToC));
    b->GetLeaf("AntiKt4Truth.flavor_truth_dRminToT")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_dRminToT));
    b->GetLeaf("AntiKt4Truth.flavor_truth_BHadronpdg")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_BHadronpdg));
    b->GetLeaf("AntiKt4Truth.flavor_truth_vx_x")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_vx_x));
    b->GetLeaf("AntiKt4Truth.flavor_truth_vx_y")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_vx_y));
    b->GetLeaf("AntiKt4Truth.flavor_truth_vx_z")->SetAddress(&(evt->AntiKt4Truth.flavor_truth_vx_z));
  }


}
