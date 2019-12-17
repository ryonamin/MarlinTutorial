In this directory, we will see how to read event data.

Let's run anyway before explaning details.

0) Logout KEKCC if you did step2 on the current shell. You must reset shell variables. 
	
1) Compile your processor
	1) Go to step3 directory.

	2) Set up your shell.  
		```source init_ilcsoft_v02-00-02.sh```

	3) Go to SimpleProcessor directory.  
		```cd SimpleProcessor```
	4) Make a directory for compilation.  
		```mkdir build```
	5) Go to build directory.  
		```cd build```
	6) Create makefile.  
		```cmake -C $ILCSOFT/ILCSoft.cmake ..```
	7) Check if you have created Makefile (+ other files).

	8) Compile.  
		```make```
	9) Check if you have created `libMyProcessor.so` in lib directory.  
		```ls lib```
	10) Install.  
		```make install```
	11) Check if you have created a new directory named lib in the parent directory.  
		```ls ../lib```

2) Run Marlin
	1) Go back step3 directory.

	2) Go to `run` directory.  
		```Marlin simple_test.xml```

	3) If you see following meassages, it should be fine.  
		```
		<!-- Loading shared library : /gpfs/group/ilc...
		<!-- Loading shared library : /cvmfs/ilc.desy.d...
		   .
		   .
		   .
		XMLParser::parse : no <constants/> section found in simple_test.xml
		[ VERBOSE "test"] init() called.
		[ VERBOSE "test"] processRunHeader() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] i = 0, pdg = 22, energy = 0.175117 [GeV], (px, py, pz) = (0.0011923, -3.41908e-05, 0.175113)
		[ VERBOSE "test"] i = 1, pdg = 22, energy = 0 [GeV], (px, py, pz) = (0, 0, 0)
		[ VERBOSE "test"] i = 2, pdg = 12, energy = 129.738 [GeV], (px, py, pz) = (41.3574, 42.0746, 115.548)
		[ VERBOSE "test"] i = 3, pdg = -12, energy = 142.727 [GeV], (px, py, pz) = (42.4519, -80.1583, -110.198)
		   .
		   .
		   .
		```  

That's it.

Now let's have a look at details.  
1) Check `src/SimpleProcessor.cc`.  
	1) Check that you have the following two lines at line 4 and 5. These are necessary to use LCCollection class and MCParticle class.   
	```#include <EVENT/LCCollection.h>```  
	```#include <EVENT/MCParticle.h>```  
	2) Have a look at `processEvent()`  
	When `Marlin` is executed, `Marlin` reads input files that are specified in your steering file (`.xml`) and set event data, which
you can access by `evt`. Event data (`LCEvent` object) contains `LCCollection`s which are collections of objects e.g. `MCParticles`, `ReconstructedParticles`, `TrackerHit`, `CalorimeerHit`. You can access each elements by calling `getElementAt()`.  
	Once you get any object e.g. MCParticle, you can call getter function implemented in each object (e.g. `getPDG()`, `getEnergy()`, `getMomentum()`).
	You can find all the methods of MCParticle in `/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01/include/EVENT/MCParticle.h`.
