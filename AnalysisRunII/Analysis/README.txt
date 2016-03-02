To Compile : 

    make clean        # ignore errors from this command related to files not found
    make dictOSX      # only needed if running on a mac 
    make 

OS X notes :   make sure XCode is installed, along with command line tools (xcode-select --install)

Compilation Notes : should work the same on OS X and SL6, except that the make command yields warnings on OS X
		    coming from the auto generated dictionary code : src/autoGENsynctreeLinkDef.cc
		    (no point in editing this since make dict will overwrite it)


To Run :

	./run_analysis "PASSCUTS/FlatTuple" "../../../FlatTuple_fullVBFsample1stGo.root"    

