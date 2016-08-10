################################
# script for hadd based merging + EOS output area cleanup
# given a text file containing lines 
# /eos/uscms/store/user/shalhout/X/Y N TTreeName clean
# where X = DataSet
# where Y = outputDatasetTag from the runCrabSubmission.py script
# where N = number of files to merge together to produce a new file (ex 200)
# where TTreeName is a TTree name used to validated pre and post merge event counts (ex Cumulative/CumulativeTuple)
# where clean is 1 if you wish to delete original root files and log directory 
# - S. Shalhout Jul 12, 2016



import time
import sys
import os
from ROOT import gROOT,TChain, TLorentzVector, TSelector, TTree, TF1, TH1F, TCanvas, gStyle, TFile
import math
import glob
import argparse
import subprocess
import FWCore.ParameterSet.Config as cms

def splitList(list, mergeCount):
    for l in range(0, len(list), mergeCount):
        yield list[l:l+mergeCount]


parser = argparse.ArgumentParser()

parser.add_argument('--DIR_FILE', type=str, nargs=1, required=True, 
                   help='ex: --DIR_FILE file.txt where file.txt contains lines like: /eos/uscms/store/user/shalhout/X/Y 200 Cumulative/CumulativeTuple 1 ')





# parser.add_argument('--TTree', type=str, nargs=1, required=True, 
#                    help='ex: --TTree Cumulative/CumulativeTuple')


args = parser.parse_args(sys.argv[1:])

dirFile_ = open(args.DIR_FILE[0], 'r')

print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "+++ merging root files listed in ", args.DIR_FILE[0], "...."
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
sys.stdout.flush() 



for dir_ in dirFile_:
	if '#' in dir_:
		continue
	if dir_.strip() == '':
		continue	
	print "++++++ looking for root file sub-directories in   " 
	print "++++++ ", dir_.split(" ")[0]
	print "++++++ merging ", dir_.split(" ")[1], " files at a time "
	print "++++++ validating event counts using TTree ", dir_.split(" ")[2]
	sys.stdout.flush() 

	SUB_DIRS = []
	split_dir_ = str(dir_).split(" ")
	
	if split_dir_[0].startswith("/eos/uscms"):
		split_dir_[0] = split_dir_[0][len("/eos/uscms"):]
	



	#####################################
	# search and find all subdirectories -- this assumes the usual CRAB job output dir structure 
	#####################################


	dirListtRaw = os.popen("eos root://cmseos.fnal.gov ls "+split_dir_[0]).read()
	dirListt = dirListtRaw.split("\n")
	print dirListt


	for name in dirListt:
		if name == '':
			continue
		print "... checking subdir .... ", name
		subDir = split_dir_[0] + "/" + name

		SUBdirListtRaw = os.popen("eos root://cmseos.fnal.gov ls "+subDir).read()
		SUBdirListt = SUBdirListtRaw.split("\n")
		print SUBdirListt


		for subSubDir in SUBdirListt:
			if subSubDir == "":
				continue
			print "... ... checking sub-subdir .... ", subSubDir
			SUB_DIRS.append(subDir+"/"+subSubDir)

		print SUB_DIRS

	#####################################
	# loop over sub-dirs and find ROOT FILES
	#####################################

	for d in range(0,len(SUB_DIRS)):
		print "... ... ... Searching for ROOT files in \n ---------- ", SUB_DIRS[d]
	
		formatt_fix = SUB_DIRS[d]	
		if formatt_fix.startswith("/eos/uscms"):
			formatt_fix = SUB_DIRS[d][len("/eos/uscms"):]
	
		print " format fix = ", formatt_fix
		# check which xrdfsls command as xrdfsls is an alias  
		command = 'xrdfs root://cmseos.fnal.gov ls -u ' + formatt_fix + ' | grep FlatTuple | grep root | grep -v merged | grep -v failed | grep -v log '
		fileListRaw = os.popen(command).read()
		fileList = fileListRaw.split("\n")
		if fileList[len(fileList)-1] == '':
			fileList = fileList[:len(fileList)-1]

		print "... ... ... .... found ", len(fileList), " ROOT files "
		sys.stdout.flush() 
		if len(fileList) == 0:
			continue

	#####################################
	# prepare merge lists and check file
	# counts to be sure split was OK
	#####################################
	 	
	 	check_total = 0
	 	total_splits = 0;
	 	master_split_list = []
	 	for split_list in splitList(fileList, int(split_dir_[1])):
		 	check_total += len(split_list)
		 	total_splits += 1
		 	master_split_list.append(split_list)
		if check_total != len(fileList):
			print "splitting FAIL ..."
			continue
		
		print len(fileList), "ROOT Files will be merged ~ ",  split_dir_[1], " at a time to produce ", 	total_splits, " new files"
		sys.stdout.flush() 
	#####################################
	# loop over merge lists, counting events in TTree
	# and perform merge
	#####################################
		tmpDir= SUB_DIRS[d].split("/")
		#print tmpDir
		tmpDirName =  "tempDir_"+tmpDir[len(tmpDir)-2]+"_"+tmpDir[len(tmpDir)-1]
		#print tmpDirName
		if os.path.isdir(tmpDirName) is False:
			makeDir = "mkdir "+tmpDirName
			os.system(makeDir)
		else:
			print "**** ABORT **** merge directory ", tmpDirName, " already exists "
			print "**** SKIPPING MERGE FOR ", SUB_DIRS[d]
			print "**** manually delete ", tmpDirName, " and try again "
			continue

		total_event_count_for_all = 0
		total_event_count_for_all_merged = 0

		for m in range(0,len(master_split_list)):
			print len(master_split_list[m])
			localName = tmpDirName + "/mergeJob"+str(m)
			makeDir = "mkdir "+localName
			os.system(makeDir)

	#####################################
	# 1st check event count before merge
	#####################################			

			tempChain = TChain(split_dir_[2])
			hadd_oldFiles = ''

			for file in master_split_list[m]:
				hadd_oldFiles += (" "+file)
			 	tempChain.Add(file)
			initial_count = tempChain.GetEntries()
			total_event_count_for_all += initial_count
			print initial_count, " events found in EOS location in TTree ", split_dir_[2]

			hadd_newFile = localName+"/FlatTuple_merged"+str(m)+".root"
			hadd_command = "hadd "+ hadd_newFile + " " + hadd_oldFiles
			print "Running hadd ... "
			os.system(hadd_command)
			sys.stdout.flush() 

	##############################
	# if you make really large file count merges, hadd may produce more than 1 new file		
	# when it hits the max TTree size 
	# so check the files created

			produced_files = [] 

			for prod_file in os.listdir(localName):
				if prod_file.endswith('.root'):
					produced_files.append(localName+"/"+prod_file)

			print "----> Merge has created ", len(produced_files), ' new files : '
			print produced_files

			print "verifying event count in new file ..."
			tempChainNEW = TChain(split_dir_[2])

			for xfile in produced_files:
				tempChainNEW.Add(xfile)

			final_count = tempChainNEW.GetEntries()
			total_event_count_for_all_merged += final_count
			print "found ", final_count, " events in new file "

			###############
			# check merge result

			if 	final_count != 	initial_count:	 
				print "**** ERORR **** event mis-match "
				print "**** FOR MERGE ATTEMPT IN ", SUB_DIRS[d], " split group # ", m , " in ", localName
				print "**** ABORT no files from this merge will be modified on EOS ***" 


			####################################################	
			#  obtain md5sum in prep for writing file to EOS   	 

			else :
				md5sum_local = []
				md5sum_eos = []
				for xfile in produced_files:
					command = "md5sum "+xfile
					md5sum_local.append((os.popen(command).read()).split(" ")[0])
					eos_file = (master_split_list[m][0]).split("FlatTuple")[0]+xfile.split("/")[2]
					copyCommand = "xrdcp "+ xfile + " " +eos_file
					print " copying merged file to EOS : ", copyCommand
					os.system(copyCommand)
					eos_total = ("/eos/uscms/store"+eos_file.split("store")[1])
					eos_base =  eos_total.split("FlatTuple")[0]
					eos_file = 	eos_total.split("FlatTuple")[1]
					md5sum_eos.append((os.popen(str("md5sum "+eos_total)).read()).split(" ")[0])


				print "----------------------------------------------------------"
				print "-----transfer check--------"
				print " MD5SUM LOCAL = ", md5sum_local
				print " MD5SUM EOS = ", md5sum_eos
				sys.stdout.flush() 

				print "----------------------------------------------------------"
				print "----------------------------------------------------------"
				print "TOTAL EVENT COUNTS ", total_event_count_for_all, " vs. ", total_event_count_for_all_merged
				print "----------------------------------------------------------"
				print "----------------------------------------------------------"
				sys.stdout.flush() 

				if md5sum_eos != md5sum_local:
					print " TRANSFER FAIL ... ABORT, PLEASE TRY AGAIN"
					print "**** FOR MERGE ATTEMPT IN ", SUB_DIRS[d], " split group # ", m , " in ", localName
					print "**** COPY TO EOS HAS FAILED no files from this merge will be modified on EOS ***" 
				else:
					print " TRANSFER SUCCESS"

				if int(split_dir_[3]) == 1:
					print " PERFORMING CLEANUP IN ", split_dir_[0]
					rm_commands = []
					rm_commands.append("eos root://cmseos.fnal.gov rm -r "+eos_base+"log")
					rm_commands.append("eos root://cmseos.fnal.gov rm -r "+eos_base+"failed")
					for rm_file in master_split_list[m]:
						file_suffix = rm_file.split("FlatTuple")[1]
						rm_commands.append("eos root://cmseos.fnal.gov rm "+eos_base+"FlatTuple"+file_suffix)

				if total_event_count_for_all == total_event_count_for_all_merged :	
					for do_rm in rm_commands:
						os.system(do_rm)
					for xfile in produced_files:
						os.system("rm -rf "+xfile)

				sys.stdout.flush() 
