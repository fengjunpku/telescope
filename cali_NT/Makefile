###############################################################################
OBJ = caliNT.exe
MainFile = main_cali.cpp 
LinkFile = LinkDef.hh
UserDict = JunDict.cc
###############################################################################

SourceFile := $(wildcard $(shell pwd)/src/*.cc) 
IncludeFile := $(wildcard $(shell pwd)/include/*.hh) 

###############################################################################

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)
#ROOTGLIBS = $(shell root-config --glibs)

GXX = g++ -std=c++0x
DIR_INC = -I$(ROOTSYS)/include -I$(shell pwd)/include #-I$(TARTSYS)/include
CFLAGS = -Wall -O $(DIR_INC) -lTMVA -lSpectrum
# -L$(TARTSYS)/lib -lXMLParser -lanacore -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
###############################################################################

all:$(OBJ)
$(OBJ): $(MainFile) $(SourceFile) $(UserDict)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) $(ROOTLIBS) $(ROOTGLIBS) -o $@ $(MainFile) $(SourceFile) $(UserDict) 
	@echo "================================"
	@echo "   $@ Compiled !"
	@echo "================================"
	
$(UserDict): $(IncludeFile) $(LinkFile)
	@echo "================================"
	@echo "   Generating dictionary $@..."
	@echo "================================"
	rootcint -f $@ -c $(DIR_INC) $^
	@echo "================================"
	@echo "   Dictionary $@... is ready !"
	@echo "================================"
	
clean:
	rm -f *.o *.d *Dict.* $(OBJ)
###############################################################################
