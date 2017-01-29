#!/usr/bin/env python 
#################################
# multi-sample job submission
# based heavily on CMSSW tutorials for CRAB3
# issue ./runCrabSubmission.py -h for usage info
# - Shalhout
#
# updated for large MC samples that exceed the crab3 10,000 jobs/task limit
# and need to be split - S. Shalhout May24, 2016


import os
import sys
import argparse
import fileinput
import FWCore.ParameterSet.Config as cms
from DavisRunIITauTau.TupleConfigurations.getSampleInfoForDataSet import getSampleInfoForDataSet
import math


def DeleteCMSTypes(arg, type):
    temp = str(arg)
    temp = temp.replace("("," ")
    temp = temp.replace(")"," ")
    temp = temp.replace("\x27","")
    temp = temp.replace("\'","")
    temp = temp.replace("\"","")
    temp = temp.split(" ", 2)[1].replace(" ","")
    return type(temp)


###############################
# define a few variables here
###############################

MC_EVENTS_PER_JOB = 20000 # used for MC only (OK when SVFit is off )
MAX_JOBS_PER_TASK = 7000 # true crab limit is 10,000 we should be below this (~5000 is safe to avoid crab over-rounding issues on the last task)
DATA_UNITS_PER_JOB = 250
DATA_LUMI_MASK = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Final/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt'

############################
# basic crab config setup 
############################
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()
from multiprocessing import Process

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

parser.add_argument('--outputDatasetTag', nargs=1, required=True,
                   help='ex: --outputDatasetTag=\"Sub-Directory Name on EOS\"')

parser.add_argument('--dryRun', type=int, nargs=1, required=True,
                   help='ex: --dryRun=1 (if 1 crab sets up the jobs but does not actually submit, if 0 will submit)')


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

###########################
# is this a dry run ?

DRY_RUN = int(args.dryRun[0])

print 'DRY_RUN = ', DRY_RUN, args.dryRun[0]
print 'IS MC = ', int(args.isMC[0])


if DRY_RUN == 1 :
    print '************** DRY RUN MODE nothing will be submitted to CRAB **************'
    print '************** DRY RUN MODE nothing will be submitted to CRAB **************'

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

sampleNames = [] # list of lists [dataset, requestName, tempJobConfigName, EventTotal, NumberOfLumis]


for line in fileinput.input(str(args.dataSetList[0])):
    if '#' in line:
        continue 
    if line.strip() == '':
        continue
    sampleData = getSampleInfoForDataSet(str(line.strip()))

    # seems kind of clumsy, but works for now
    # version =  ((str(sampleData.getParameter("CodeVersion")).strip("cms.double('")).strip("')")).replace('.','_') 
    # requestName = ((str(sampleData.getParameter("KeyName")).strip("cms.string('")).strip("')"))
    # requestName = requestName+"_version_"+version
    # EventTotal =  int((str(sampleData.getParameter("EventTotal")).strip("cms.int32('")).strip("')"))
    # NumberOfLumis =  int((str(sampleData.getParameter("NumberOfLumis")).strip("cms.int32('")).strip("')"))

    # tempConfigName = crabJobLocation+"/"+requestName+".py"

    version = DeleteCMSTypes(sampleData.getParameter("CodeVersion"), str).replace('.','_')  
    requestName = DeleteCMSTypes(sampleData.getParameter("KeyName"), str)+"_v"+version
    EventTotal = DeleteCMSTypes(sampleData.getParameter("EventTotal"), int)
    NumberOfLumis = DeleteCMSTypes(sampleData.getParameter("NumberOfLumis"), int)
    MaxLumi = DeleteCMSTypes(sampleData.getParameter("MaxLumiBlock"), int)
    tempConfigName = crabJobLocation+"/"+requestName+".py"

    print 'version = ', version
    print 'requestName = ', requestName
    print 'EventTotal = ', EventTotal
    print 'NumberOfLumis = ', NumberOfLumis
    print 'MaxLumi =', MaxLumi
    print 'tempConfigName = ', tempConfigName



    # some sed swaps in the job config file (really just putting the dataset name in)
    sedHappySampleName = str(line.strip()).replace("/","\/")
    sed_command = "cat "+os.environ['CMSSW_BASE']+"/src/DavisRunIITauTau/CrabJobSubmissionHelper"
    sed_command = sed_command + "/Templates/V3/runIIoneStep_v1.py | "
    sed_command = sed_command + "sed \'s/DUMMY_DATASET_NAME/"+sedHappySampleName+"/g\'"+" >& "+tempConfigName

    os.system(sed_command)
  
    sampleNames.append([str(line.strip()), requestName, tempConfigName, EventTotal, NumberOfLumis, MaxLumi])


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
config.General.transferLogs = False # hurts debugging, but helps prevent hitting 500,000 EOS file limit
config.JobType.pluginName = 'Analysis'
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())

#####################################################
# these parameters may change, might want to move 
# them to dataSetList later on
#####################################################


config.Data.publication = False
config.Data.outputDatasetTag = str(args.outputDatasetTag[0])
config.Site.storageSite = 'T3_US_FNALLPC'
config.Data.inputDBS = 'global'

#config.Site.blacklist = [ 'T1_US_FNAL' ]

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
    

    # define a function to reset sample based parameters 
    def resetConfig(config):
        config.Data.inputDataset = ''
        config.General.requestName = ''
        config.JobType.psetName = ''
        config.Data.splitting = ''
        config.Data.unitsPerJob = 1
        config.Data.lumiMask = ''


    ######################
    # OK now bring it all together
    # and submit !
    ######################
    submitCommandList = []

    for samp in sampleNames:
        resetConfig(config)

        if int(args.isMC[0]) == 0:
            config.Data.inputDataset = samp[0]
            config.General.requestName = samp[1]  
            config.JobType.psetName = samp[2]
            config.Data.splitting = 'LumiBased'
            config.Data.unitsPerJob = DATA_UNITS_PER_JOB
            config.Data.lumiMask = DATA_LUMI_MASK
            print "################# -- setting up job as follows : -- ##################################"   
            print "################# ", samp[1], " #################"

            cragConfigPYfile = crabJobLocation + '/crabConfig_' + samp[1]+".py"
            print config 
            print 'saved in crab config file ', cragConfigPYfile
            fi = open(cragConfigPYfile,'w')
            print >> fi, config
            fi.close()
            if DRY_RUN == 1 :
                submitCommandList.append("crab submit --dryrun  --skip-estimates --config="+cragConfigPYfile)
            else :
                submitCommandList.append("crab submit --config="+cragConfigPYfile)                
            resetConfig(config)

            print "#######################################################################################"

             

        if int(args.isMC[0]) == 1:
            config.Data.inputDataset = samp[0]
            config.General.requestName = samp[1]  
            config.JobType.psetName = samp[2]
            config.Data.splitting = 'EventAwareLumiBased'
            config.Data.unitsPerJob = MC_EVENTS_PER_JOB
            config.Data.lumiMask = ''
          
            requestedJobs = (1.0*samp[3])/config.Data.unitsPerJob
            if requestedJobs < MAX_JOBS_PER_TASK :
               
                print "################# -- setting up job as follows : -- ##################################"   
                print "################# ", samp[1], " #################"
               
                cragConfigPYfile = crabJobLocation + '/crabConfig_' + samp[1]+".py"
                print config 
                print 'saved in crab config file ', cragConfigPYfile               
                fi = open(cragConfigPYfile,'w')
                print >> fi, config
                fi.close()

                if DRY_RUN == 1 :
                    submitCommandList.append("crab submit --dryrun  --skip-estimates --config="+cragConfigPYfile)
                else :
                    submitCommandList.append("crab submit --config="+cragConfigPYfile)   
                resetConfig(config)

                print "#######################################################################################"

            else :
                # have a big MC sample, need to split the task up by LumiSections, generating the JSON files on-the-fly                    
                requestedTasks = math.ceil((1.0*requestedJobs)/MAX_JOBS_PER_TASK)
                print '------> task for ', samp[0]
                print '------> would require > ', (requestedJobs), ' jobs which is too high, will split into '
                print '------> ',(requestedTasks), ' tasks instead'
                print '------> sample has ', samp[4], 'LuminosityBlocks to be used for splitting ...'
                print '------> the max lumi block is # ', samp[5], '....'

                last_lumi = samp[5]

                if last_lumi < samp[4] :
                    print "+++++++++++++++++++++++++++++++++++ FAIL FAIL FAIL ---> ABORT SUBMISSION FOR "
                    print "+++++++++++++++++++++++++++++++++++ ", samp
                    print "+++++++++++++++++++++++++++++++++++ MAX LUMI BLOCK # is LESS THAN Total Count of Lumi Blocks"
                    print " setting max lumi block to 100 x Total lumi block count "
                    last_lumi = 100 *  samp[4]


                print "################# -- setting (split) MC job as follows : -- ##################################"   
                print "################# ", samp[1], " #################"

                start_ = 1
                end_ = 1
                for s in range(1,int(requestedTasks)+1):

                    print "************** split ", s , " of ", int(requestedTasks), "************************"

                    if s != 1:
                        start_ = end_ + 1

                    if s == int(requestedTasks):
                        end_ = last_lumi     

                    else :
                        end_ = start_ + math.ceil(samp[4]/requestedTasks)

                    config.Data.inputDataset = samp[0]
                    config.JobType.psetName = samp[2]
                    config.Data.splitting = 'EventAwareLumiBased'
                    config.Data.unitsPerJob = MC_EVENTS_PER_JOB

                    jsonLine_ = '{\"1\": [[' + str(int(start_))+', '+str(int(end_))+']]}'  
                    cragConfigPYfile = crabJobLocation + '/crabConfig_' + samp[1]+"_"+str(int(start_))+"_"+str(int(end_))+".py"
                    lumiSplitJSON_   = crabJobLocation + '/JSON_' + samp[1]+"_"+str(int(start_))+"_"+str(int(end_))+".txt"
                    config.General.requestName = samp[1] + "_"+str(int(start_))+"_"+str(int(end_))
                    config.Data.lumiMask = lumiSplitJSON_

                    li = open(lumiSplitJSON_,'w')
                    print >> li, jsonLine_
                    li.close()
                    
                    fi = open(cragConfigPYfile,'w')
                    print >> fi, config
                    fi.close()

                    print "***** will use JSON file ", lumiSplitJSON_
                    print "***** and config file ", cragConfigPYfile
                    print config 

                    if DRY_RUN == 1 :
                        submitCommandList.append("crab submit --dryrun  --skip-estimates --config="+cragConfigPYfile)
                    else :
                        submitCommandList.append("crab submit --config="+cragConfigPYfile)   
                    resetConfig(config)

        #submit(config) this line causes duplicate process fails on crab
        # trying my own fix instead (the wiki fix does not fix)
        # see https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3FAQ#Multiple_submission_fails_with_a
        # the next 3 lines are suggested alt.
        # p = Process(target=submit, args=(config,))
        # p.start()
        # p.join()

    print 'submitting jobs for ', len(submitCommandList), 'datasets'
    for com in submitCommandList:
        print 'issuing crab sumbit command: ', com
        os.system(com)





         
