#################
# simple script to load all root files
# in a given directory
# and print file & event counts in a TTree

Run as :

python count_events.py --DIR /store/user/shalhout/DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/trigFilter_fall15_76Xsmall --TTree Cumulative/CumulativeTuple

# NOTE: the script assumes a crab like directory structure 

so given --DIR 
it looks for all subdirectories corresponding to different task ID 
and then checks for the 1000 file divisions (0000, 0001, 0002, etc.) subdirectories




