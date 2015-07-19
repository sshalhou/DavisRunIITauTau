To Compile : 

    make clean
    make dict
    make 

Compilation Notes : should work the same on OS X and SL6, except that the make command yields warnings on OS X
		    coming from the auto generated dictionary code : src/autoGENsynctreeLinkDef.cc
		    (no point in editing this since make dict will overwrite it)


To Run :

	./run_analysis "PASSCUTS/FlatTuple" "../../../FlatTuple_fullVBFsample1stGo.root"    

