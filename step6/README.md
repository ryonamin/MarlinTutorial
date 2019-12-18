In this directory, we will see how to make a root output file. 

Note that you have to logout KEKCC if you did step2 or step3 on the current shell.   

1) Check `SimpleProcessor/include/MyProcessor.h`.
	1) Note line 7 and 8:
	```
	#include "TTree.h"
	#include "TFile.h"
	```

	2) Note line 32 - 36:
	```
	TFile* _file;       // output root file 
	TTree* _tree;       // output root tree
	int    _npfos;      // number of reconstructed particles
	double _pfo_e[500]; // reserve memory for energies. 500 : maximum number of reconstructed particles per event
	```

1) Check `SimpleProcessor/src/MyProcessor.cc`.

	1) Note lines 31 - 37, where you create `TFile` and `TTree`, and register variables (`_npfos`, `_pfo_e`) to `TTree` :  
		```
		// TFile creation
		_file = new TFile("output.root","RECREATE");
		// TTree creation
		_tree = new TTree("evt","");
		// Register variables to TTree 
		_tree->Branch( "npfos" , &_npfos , "npfos/I"        ); // I : integer, O : boolean, F : float, D : double
		_tree->Branch( "pfo_e" , _pfo_e  , "pfo_e[npfos]/D" ); // This is an example to set an Array
		```

	2) Note lines 60 and 69, where you set values : 
		```
		// set number of PFOs to the variable registered to TTree.
		_npfos = nPFO;
		
		...
		
			// Access its parameters
			double e = p->getEnergy();
		```

	3) Note lines 74, where you fill the variable you set above : 
		```
		_tree->Fill();
		```

	4) Note lines 92, where you write TTree to TFile : 
		```
		_file->Write();
		```
