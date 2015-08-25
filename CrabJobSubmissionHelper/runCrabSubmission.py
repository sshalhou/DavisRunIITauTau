#!/usr/bin/env python 
#################################
# multi-sample job submission
# based heavily on CMSSW tutorials for CRAB3
# issue ./runCrabSubmission.py -h for usage info
# - Shalhout

import os
import sys
import argparse
import fileinput
import FWCore.ParameterSet.Config as cms
from DavisRunIITauTau.TupleConfigurations.getSampleInfoForDataSet import getSampleInfoForDataSet


############################
# basic crab config setup 
############################
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

############################
# setup an argument parser
############################
parser = argparse.ArgumentParser()

parser.add_argument('--isMC', type=int, nargs=1, required=True, 
                   help='ex: --isMC=1 for MC, --isMC=0 for data')

parser.add_argument('--dataSetList', nargs=1, required=True, 
                   help='ex: --dataSetList=\"A/B/C/file.txt\"')


parser.add_argument('--workAreaName', nargs=1, required=True,
                   help='ex: --workAreaName=\"~/A/B/C\"')


args = parser.parse_args(sys.argv[1:])

############################
# a couple of checks on the arguments 
############################

if int(args.isMC[0]) !=0 and int(args.isMC[0])!=1:
    print 'isMC should be 0 or 1'
    parser.print_usage()
    sys.exit()

if os.path.isfile(str(args.dataSetList[0])) is False:
    print 'unable to find sample file list : ',str(args.dataSetList[0])
    parser.print_usage()
    sys.exit()

############################
# some info to the screen
############################
print '***************\n'
print 'will create crab job directory', args.workAreaName[0]
if int(args.isMC[0]) == 1:
    print 'using crab setup for MC jobs'
elif int(args.isMC[0]) == 0:
    print 'using crab setup for Data jobs'
print 'for the samples in ', args.dataSetList[0]
print '***************\n'

###############
# prepare crab job directory to keep CMSSW_BASE/src from
# getting out of hand

shortDate = "date | awk \'{printf $2$3$6}\'"
getShortDate = os.popen(shortDate)
shortDate = getShortDate.read()

crabJobLocation = os.environ['CMSSW_BASE']+"/src/crab_configs"

if os.path.isdir(crabJobLocation) is False:
  makeCrabDir = "mkdir "+crabJobLocation
  os.system(makeCrabDir)

crabJobLocation += "/"+ shortDate

if os.path.isdir(crabJobLocation) is False:
  makeCrabDir = "mkdir "+crabJobLocation
  os.system(makeCrabDir)


############################
# begin reading in list of samples
# and check that the metadata is known to our code
#srcDir = os.environ['CMSSW_BASE']+"/src"
#crabConfigDir = srcDir+"/DavisRunIITauTau/CrabJobSubmissionHelper/"

sampleNames = [] # list of lists [dataset, requestName, tempJobConfigName]


for line in fileinput.input(str(args.dataSetList[0])):
    if '#' in line:
        continue 
    sampleData = getSampleInfoForDataSet(str(line.strip()))

    # seems kind of clumsy, but works for now
    version =  ((str(sampleData.getParameter("CodeVersion")).strip("cms.double('")).strip("')")).replace('.','_') 
    requestName = ((str(sampleData.getParameter("KeyName")).strip("cms.string('")).strip("')"))
    requestName = requestName+"_version_"+version

    tempConfigName = crabJobLocation+"/"+requestName+".py"

    # some sed swaps in the job config file (really just putting the dataset name in)
    sedHappySampleName = str(line.strip()).replace("/","\/")
    sed_command = "cat "+os.environ['CMSSW_BASE']+"/src/DavisRunIITauTau/CrabJobSubmissionHelper"
    sed_command = sed_command + "/Templates/V0/runIIoneStepFlatTuple_v0.py | "
    sed_command = sed_command + "sed \'s/DUMMY_DATASET_NAME/"+sedHappySampleName+"/g\'"+" >& "+tempConfigName

    os.system(sed_command)
    sampleNames.append([str(line.strip()), requestName, tempConfigName])
    


# ################################
# # print samples and request names
# ################################
# for s in sampleNames:
#     print '\n\n'
#     print s[0]
#     print '             as request: ', s[1], '\n'
#     print '             using config : ', s[2], '\n'

# ################################


#####################################################
# some crab parameters that should not really change
# often or at all 
#####################################################

config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())

#####################################################
# these parameters may change, might want to move 
# them to dataSetList later on
#####################################################


config.Data.publication = False
config.Data.publishDataName = 'Try2'
config.Site.storageSite = 'T3_US_FNALLPC'
config.Data.inputDBS = 'global'


#####################################################
# using the config template generate the jobs
# and submit them!
#####################################################

if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = str(args.workAreaName[0])

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    ######################
    # OK now bring it all together
    # and submit !
    ######################

    for samp in sampleNames:
        config.Data.splitting = 'EventAwareLumiBased'
        config.Data.unitsPerJob = 25000
        config.Data.inputDataset = samp[0]
        config.General.requestName = samp[1]  
        config.JobType.psetName = samp[2]
        print "################# -- setting up job as follows : -- ##################################"   
        print "################# ", samp[1], " #################"
        print config
        print "#######################################################################################"
        submit(config)

         