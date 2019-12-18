In this directory, we will see how to make a root output file. 

Note that you have to logout KEKCC if you did other steps on the current shell.   

1) Check `SimpleProcessor/include/MyProcessor.h`.
	1) Note line 29 - 31:
	```
	std::string _colname ;
	std::string _myparam1 ;
	float       _myparam2 ;
	```

2) Check `SimpleProcessor/src/MyProcessor.cc`.

	1) Note lines 24 - 42, where you see how to access variables from steering file :  
		```
		// See other examples for types /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/lcio/v02-12-01/include/EVENT/LCIO.h
		registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE, // type of input collection
		   "InputPFOCollection" , // define parameter name. You can change this parameter with this name in your steering file.
		   "Name of the PFOs collection" ,
		   _colname , // input value will be stored in this variable
		   std::string("PandoraPFOs") // default value
		) ;
		
		registerProcessorParameter( "TestStringParameterName", // define parameter name. You can change this parameter with this name in your steering file.
		       "Explain this parameter here",
		       _myparam1, // input value will be stored in this variable 
		       std::string("This_is_default.") // default value
		);
		
		registerProcessorParameter( "TestFloatParameterName", // define parameter name. You can change this parameter with this name in your steering file.
		       "Explain this parameter here",
		       _myparam2, // input value will be stored in this variable  
		       float(0.) // default value
		);
		```

3) Check `run/simple_test.xml` : 
	1) Note lines 17 - 21, where you control some variables :  
		```
        <parameter name="InputPFOCollection" type="string" lcioInType="ReconstructedParticle">
           PandoraPFOs
        </parameter>
        <parameter name="TestStringParameterName" value="Hello_world!"/>
        <parameter name="TestFloatParameterName" value="3.14"/>
		```
