In this directory, we will see how to use LCFIPlus, which contains jet clustering and flavor tagging. 
Note that you have to logout KEKCC if you did other steps on the current shell.   

1) Edit `init_ilcsoft_v02-00-02.sh` so that `Marlin` can find your LCFIPlus library, which you will compile next step below:
	1) Remove the default LCFIPlus libarary from `MARLIN_DLL` path (line 65) :
		- What is written (before editting) :  
		```export MARLIN_DLL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/LCFIPlus/v00-06-09/lib/libLCFIPlus.so:/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinDD4hep/v00-06/lib/libMarlinDD4hep.so: ... ```
		- What is to be written (after editting):  
		```export MARLIN_DLL="/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/MarlinDD4hep/v00-06/lib/libMarlinDD4hep.so: ... ```
	2) Add your (future) LCFIPlus libarary to `MARLIN_DLL` path :  
	```export MARLIN_DLL="$PWD/LCFIPlus/lib/libLCFIPlus.so:$MARLIN_DLL"```

1) Setup the latest LCFIPlus, which is equivalent to `/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/LCFIPlus` but includes some more updates.

	1) Download the latest LCFIPlus:      
		```git clone https://github.com/lcfiplus/LCFIPlus.git```

	2) Compile it:   
		```cd SimpleProcessor
		   mkdir build
		   cd build
		   cmake -C $ILCSOFT/ILCSoft.cmake ..
		   make install
		```

2) Check `SimpleProcessor/src/MyProcessor.cc`:
	1) Note lines 6:  
		```#include "UTIL/PIDHandler.h"```

	2) Note lines 49, where you see how to access jet collection that is formed in LCFIPlus processor :   
		```LCCollection* coljet     = evt->getCollection("RefinedJets") ;```

	3) Note lines 55 - 56, where you see how to access jet flavor that is tagged in LCFIPlus processor. 

3) Setup configuration files in `run` directory:   

	1) Go to `run` directory and get latest version of ILDConfig, which is equivalent to `/cvmfs/ilc.desy.de/sw/ILDConfig` but includes some more updates:   
		```git clone https://github.com/iLCSoft/ILDConfig.git```
	2) Untar weight files:  
		```tar xzvf ILDConfig/LCFIPlusConfig/lcfiweights/6q500_v04_p00_ildl5.tar.gz -C ILDConfig/LCFIPlusConfig/lcfiweights/```

	2) Check `run/simple_test.xml` : 
		1) Note line 3, where you register LCFIPlus processor to be run :  
		```<processor name="MyLcfiplusProcessor"/>```

		2) From line 17 - 135, there is a long description for LCFIPlus configuration.
           Usually you have to care about only some parameters (see below), the other parameters can be used as they are.
			1) What you want LCFIPlus to do (Most probably you don't have to change this part):
			```
    		<parameter name="Algorithms" type="stringVec"> 
        	  JetClustering 
        	  JetVertexRefiner 
        	  FlavorTag 
        	  ReadMVA
        	</parameter>
			```
			2) How many jet you enforce to be formed. If you specify 2, you will get always 2 jets in each event. (This type of jet clustering is called "Exclusive jet clustering".) 
			```
	    	<parameter name="JetClustering.NJetsRequested" type="intVec" value="2" /> <!-- Multiple NJets can be specified -->
			```
			3) Weight files that were produced in MVA training for flavor tagging. Usually you don't need to do training by yourself. LCFIPlus developpers provide weight files that are outputs from MVA trainings.
			```
       		<parameter name="FlavorTag.WeightsDirectory" type="string">
       		  ILDConfig/LCFIPlusConfig/lcfiweights/
       		</parameter>
			```
			4) Prefix for weight files (There are 4 different files with the same prefix).
			```
	   		<parameter name="FlavorTag.WeightsPrefix" type="string" >
       		  6q500_v04_p00_ildl5
       		</parameter>
			```
			5) Impact parameter distribution files that were produced for flavor tagging. 
			```
       		<parameter name="FlavorTag.D0ProbFileName" type="string"> 
       		  ILDConfig/LCFIPlusConfig/vtxprob/d0probv2_ildl5_6q500.root
       		</parameter>
       		<parameter name="FlavorTag.Z0ProbFileName" type="string"> 
       		  ILDConfig/LCFIPlusConfig/vtxprob/z0probv2_ildl5_6q500.root
       		</parameter>
			```
