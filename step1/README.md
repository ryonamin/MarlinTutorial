`Marlin` is a framework for `LCIO` data format (https://github.com/iLCSoft/Marlin).  
(*`LCIO` is a data format dedecated to physics analysis for linear collider experiments.)  

It is centrally maintained in KEKCC and thus you can use it without installing by yourself.  
Several versions are available at the following directory:  
```/cvmfs/ilc.desy.de/sw```  
For instance, the current version (at the time of writing, Dec. 2019) can be found  
```/cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/```.  

Once you type on your login-shell,  
```source /cvmfs/ilc.desy.de/sw/x86_64_gcc49_sl6/v02-00-02/init_ilcsoft.sh```  
All the necessary setup (Path, Shell variables) are set and you can use Marlin.  


##### How Marlin works?
`Marlin` is the name of the framework but also the name of the executable command.  
`Marlin` basically drives several small, modularized programs in which a certain single (sometimes multiple) task is performed.
In Marlin framework, the small programs is called "processor".  
Here is an example :  
Suppose we are making cars. First, you need to produce several components, like engine, tires, steering wheel, etc.
Then you assemble all the components. At the end, probably you have to test if the product agrees what you wanted to make.
If you (virtually) do these processes in `Marlin`, you have to prepare following processors:  
1) `MakeComponensProcessor` (in which you make engine, tires, steering wheel, etc)  
2) `AssembleProcessor` (in which you assemble all the components)  
3) `CheckProcessor` (in which you check what you produced)  

`Marlin` excutes processors according to your request, which means
you have to describe your configuration file (so called steering XML file) which processors should be run.
We will see later how it looks like.

Each processor consists of basic functions that are invocated by `Marlin` :  
- init()  
- processRunHeader()  
- processEvent()  
- check()  
- end()  
`Marlin` executes each function at certain timings. See examples as follows:  
1) At the very beginninig...  
  1) `init()` of `MakeComponentsProcesser` 
  2) `init()` of `AssembleProcessor`
  3) `init()` of `CheckProcessor`.  

2) When `Marlin` starts processing Run data ...        
  1) `processRunHeader()` of `MakeComponentsProcesser` 
  2) `processRunHeader()` of `AssembleProcessor`
  3) `processRunHeader()` of `CheckProcessor`.  

3) When `Marlin` starts reading a new event data ...        
  1) `processEvent()` of `MakeComponentsProcesser` 
  2) `processEvent()` of `AssembleProcessor`
  3) `processEvent()` of `CheckProcessor`.
4) When `Marlin` ends processing...  
  1) `end()` of `MakeComponentsProcesser` 
  2) `end()` of `AssembleProcessor`
  3) `end()` of `CheckProcessor`.

Let's reinterpret "new event" as "new car" in our earlier example.  
The point is, each new car should be always processed in the same way as the first car.
Once you prepare for the first car, Marlin will take care of processing next car once the current car has been processed.

This is the basic philosophy of Marlin framework.  
I hope this helps when you want to implement your own processors!

