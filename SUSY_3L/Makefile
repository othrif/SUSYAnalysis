# This is a sample automatic makefile to compile ROOT code with a typical C++
# compiler. It requires that $ROOTSYS/bin be added to $PATH and that 
# $ROOTSYS/lib be added to $LD_LIBRARY_PATH.
 

# -----------------------------------------------------------------

# Define the name of the project
# Make sure that this is the same name as the source file

NAME        = plotter

# -----------------------------------------------------------------

# Define Suffixes for diferent filetypes
ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
OutPutOpt     = -o # keep whitespace after "-o"

# -----------------------------------------------------------------

# Grab the flags required by ROOT when compiling using the
# root-config shell commands
ROOTCFLAGS    = $(shell root-config --cflags) -D__USE_XOPEN2K8 
ROOTLIBS      = $(shell root-config --libs)
ROOTGLIBS     = $(shell root-config --glibs)
ROOTINCS      = $(shell root-config --incdir)
INCLUDE	      = -I. -I$(ROOTINCS) 

# -----------------------------------------------------------------

# Compiler Information
CXX           = gcc
CXXFLAGS      = -g -Wall -Wno-deprecated -O2 -fPIC
#CXXFLAGS     = -O -Wall -fPIC   # Optimized

# Linker Information
LD            = gcc
LDFLAGS       = -g -O1 -m64 # Debug
#LDFLAGS       = -O1      # Optimized

SOFLAGS       = -c

CXXFLAGS     += $(ROOTCFLAGS)
LIBS          = $(ROOTLIBS) $(SYSLIBS) -luuid
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)

MY_LIBS	      = /users/aparamonov/testarea/17.7.0/

#------------------------------------------------------------------------------
MY_OBJECTS    = declarestructs.cc  my_objects.cc DileptonTriggerTool.cc BTagCalib.cc JESUncertaintyProvider.cc MultijetJESUncertaintyProvider.cc egammaSFclass.cc EnergyRescaler.cc
SRCS          = $(NAME).$(SrcSuf)  
OBJS          = $(NAME).$(ObjSuf) $(addsuffix .o, $(basename $(MY_OBJECTS)))
JETCORR       = $(MY_LIBS)DataQuality/GoodRunsLists/StandAlone/libGoodRunsLists.so $(MY_LIBS)PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonEfficiencyCorrections/x86_64-slc6-gcc46-opt/libMuonEfficiencyCorrections.so $(MY_LIBS)PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonMomentumCorrections/StandAlone/libMuonMomentumCorrections.so $(MY_LIBS)Reconstruction/Jet/JetResolution/StandAlone/libJERProvider.so $(MY_LIBS)PhysicsAnalysis/AnalysisCommon/PileupReweighting/StandAlone/libPileupReweighting.so $(MY_LIBS)Reconstruction/Jet/JetUncertainties/StandAlone/libJetUncertainties.so $(MY_LIBS)Reconstruction/MissingETUtility/StandAlone/libMETUtility.so $(MY_LIBS)Reconstruction/egamma/egammaAnalysis/egammaAnalysisUtils/x86_64-slc6-gcc46-opt/libegammaAnalysisUtils.so $(MY_LIBS)Reconstruction/Jet/ApplyJetCalibration/StandAlone/libApplyJetCalibration.so $(MY_LIBS)PhysicsAnalysis/JetTagging/JetTagPerformanceCalibration/CalibrationDataInterface/x86_64-slc6-gcc46-opt/libCalibrationDataInterfaceLib.so

PROGRAM       = $(NAME)$(ExeSuf)
HEADER 	      = myevt.h my_objects.h #EnergyRescaler.h  JERProvider.h  egammaSFclass.h
# -----------------------------------------------------------------

all:      $(PROGRAM)

%.$(ObjSuf): %.$(SrcSuf) $(HEADER)  
	@echo "Compiling Source Files into Objects Files"
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(SOFLAGS) $< 
	@echo "$@ succesfully created"

$(PROGRAM): $(OBJS)
	@echo "Linking $(PROGRAM) ..."
	$(LD) $(LDFLAGS) $^ $(LIBS)  $(JETCORR) $(OutPutOpt)$(PROGRAM)
	@echo "$(PROGRAM) done!"

clean:   
	rm *.$(ObjSuf)
	rm $(NAME)$(ExeSuf)
