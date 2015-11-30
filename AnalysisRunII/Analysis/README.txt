Using operation_submit.py:

run with -h option for help message. 

run with -c to submit job to condor.

All command line options below must be used:

-t specify name of TTree accessed in input FlatTuple

-i specify name of FlatTuple root file or txt file containing list of root files. The txt file must be in the Analysis directory and list files as (“<path>/<file.root>”)

-o specify list of operations to be performed. Must escape spaces with backslashes if using more than one operation. 

Example:

python operation_submit.py -c -t "PASSCUTS/FlatTuple" -i “/eos/uscms/store/user/gfunk/MonoH_Backgrounds/FlatTuple_Wjets.root” -o generateH2TauSyncTree\ histogramLeptonQuantities

or 

python operation_submit.py -c -t "PASSCUTS/FlatTuple" -i rootFiles.txt -o generateH2TauSyncTree\ histogramLeptonQuantities