In this directory, we will run a simplest Marlin example.

Let's run anyway before explaning details.

1) Compile your processor
	1) Go to step2 directory.

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
	1) Go back step2 directory.

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
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] processEvent() called.
		[ VERBOSE "test"] check() called.
		[ VERBOSE "test"] end() called.```  

That's it.

Now let's have a look at details.  
1) Check processor source codes.  
	1) Check that you have `src` and `include` directories in `SimpleProcessor` directory
	2) Have a look at `src/SimpleProcessor.cc` and `include/SimpleProcessor.h`
	3) Check that in each basic function, there are `std::cout << .. << std::endl;` so that we can recognize they are called in run time.

2) Check `CMakeLists.txt` in `SimpleProcessor`  
	This `CMakeLists.txt` is used to describe what we want CMake to do.
	CMake has many features and I can't describe them all.
	Here I just mention that we specified the project name at line.9 in `CMakeLists.txt` as below;

	```PROJECT( MyProcessor )```

	This will be used as the name of shared library that is produced after compilation.
	Recall that we have created `libMyProcessor.so`. Of course you can change the name. 

3) Check `init_ilcsoft_v02-00-02.sh`  
	This file originally comes from `/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/`. 
	The difference can be seen at line 66  

	```export MARLIN_DLL="$PWD/SimpleProcessor/lib/libMyProcessor.so:$MARLIN_DLL"```

	`MARLIN_DLL` is a variable indicating which directory Marlin should search processors 
	(which are compiled as shared library (`.so`)).
	Here we add a directory so that Marlin can find our shared library that contains our processor.

4) Check steering file in run directory.  
	The file you specified when you run `Marlin` is called steering file (`simple_test.xml`).
	It is descirbed in one of markup languages which realize to define several structures in documents.
	For instance, Marlin configuration should be written between `<marlin>` and `</marlin>`.
	Some explantions for typical tags :  
	1) `<excute>...</excute>`  
		Here you specify which processor to be used when `Marlin` excuted.
	
	2) `<global>...</global>`  
		Put global (independent of processors) parameters e.g. input file names, number of processing events.

	3) `<processor>...</processor>`  
		Describe prameters for each processsor. Note that name should be same as the one specifed in `<execute>` 
		tag, and type is the class name of your processor (See line 15 in `SimpleProcessor.cc`). 
