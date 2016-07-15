#################
# simple script to merge (using hadd) all root files
# in a given EOS crab output directory
# and cleanup originals, logs, and failure directory
# run from a disk area with enough space to hold 1 merged subdirectory at a time


Run as :

nohup python merge_and_clean.py --DIR_FILE MergeList.txt > & log.txt &

where MergeList.txt contains lines formatted as follows :

# lines should be 3 columns:
# 1st column /eos/uscms/store path
# 2nd column max number of files to merge int one root file
# 3rd column TTree used to vaildate event counts with 
# 4th 1 if you wish to delete originals & log files on EOS, 0 if not
# lines starting with blank space or # are ignored

for example :

/eos/uscms/store/user/shalhout/SingleElectron/trigFilter_fall15_76Xsmall 40 Cumulative/CumulativeTuple 1


will merge FlatTuples in /eos/uscms/store/user/shalhout/SingleElectron/trigFilter_fall15_76Xsmall
40 at a time and will check the integrity of the merge based on event counts in the TTree 
Cumulative/CumulativeTuple, and if the counts pre and post merge match the '1' requests that the original
flatTuples and logs be deleted