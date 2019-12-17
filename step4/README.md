In this directory, we will see how to keep variables over different events
and how to define new functions.       

Note that you have to logout KEKCC if you did step2 or step3 on the current shell.   

1) Check `SimpleProcessor/include/MyProcessor.h`. Here you define a function and a variable. 
	1) Note `void printEventNumber();` at line 29.  

	2) Note `int _nevent;` at line 31.  


2) Check `SimpleProcessor/src/MyProcessor.cc`.
	1) Go to `init()` and find below:  
		```_nevent = 0;```

	2) Go to `processEvent()` and find below:    
		```_nevent++;
		```printEventNumber();```

	3) Go to line 69. This is a new function you defined.  
		```
		void MyProcessor::printEventNumber(){
		  std::cout << "Event Number = " << _nevent << std::endl;
		}
		```
