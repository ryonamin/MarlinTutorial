In this directory, we will see how to make a matching between reconstructed particles
and MC particles.

Note that you have to logout KEKCC if you did step2 or step3 on the current shell.   

1) Check `SimpleProcessor/src/MyProcessor.cc`.
	1) Note lines 3-5:  
		```
		#include <EVENT/MCParticle.h>
		#include <EVENT/ReconstructedParticle.h>
		#include "UTIL/LCRelationNavigator.h"
		```
	2) Have a look at `processEvent()`. You will learn how to get corresponding MCParticles. 
