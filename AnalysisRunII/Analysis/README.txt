Using operation_submit.py:

run with -h option for help message. 

run with -c to submit job to condor.

All command line options below must be used:

-t specify name of TTree accessed in input FlatTuple

-i specify path to FlatTuple and name of FlatTuple root file or txt file containing list of root files. The txt file must be in the Analysis directory and list files as (“<path>/<file.root>”)

-o specify list of operations to be performed. Must escape spaces with backslashes if using more than one operation.

-d specify path where output from condor job will go (must be specified if condor is used, locally running the operation does not use this path) 

Example:

python operation_submit.py -c -t "PASSCUTS/FlatTuple" -i /eos/uscms/store/user/gfunk/MonoH_Backgrounds/FlatTuple_Wjets.root -o generateH2TauSyncTree\ histogramLeptonQuantities -d /eos/uscms/store/user/gfunk/NewTest

or 

python operation_submit.py -c -t "PASSCUTS/FlatTuple" -i rootFiles.txt -o generateH2TauSyncTree\ histogramLeptonQuantities -d /eos/uscms/store/user/gfunk/NewTest

Using fullProdHelper.py:

completely configured inside the script. Run simply with ‘python fullProdHelper.py’. Submits generateH2TauSyncTree condor jobs for all background samples. 

