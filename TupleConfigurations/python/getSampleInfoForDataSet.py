#################################################
# helper function to get one PSet from the		#	
# sampleInfo VPSet based on DataSet parameter	#
# - S. Shalhout									#
#################################################

import FWCore.ParameterSet.Config as cms
from SampleMetaData_cfi import sampleInfo
import sys

def getSampleInfoForDataSet(argString):
	returnPSet = cms.PSet()
	for aPSet in sampleInfo:
		if aPSet.getParameter("DataSet") == argString:
			returnPSet = aPSet
			return returnPSet
	# if make it here it means an unknown dataset was requested
	print '\n\n ***************'
	print 'you have asked for an unknown dataset:\n'
	print  argString,'\n'
	print 'please make sure you have added info for this sample'
	print 'to DavisRunIITauTau/TupleConfigurations/python/SampleMetaData.py'
	print '***************\n\n'
	sys.exit()
	return returnPSet