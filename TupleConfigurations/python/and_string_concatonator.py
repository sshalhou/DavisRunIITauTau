import FWCore.ParameterSet.Config as cms



# take a list as input and return a && concatentated string

def and_string_concatonator(inputList):
	returnString = ''

	for i in range(0,len(inputList)):
		returnString += inputList[i]+" && "

	return returnString.rstrip(' && ')
