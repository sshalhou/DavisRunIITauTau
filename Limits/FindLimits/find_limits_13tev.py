#!/usr/local/bin/python
import subprocess
import os

# This script calculates limits with the CombinedLimit tool, taking normalized event yields 
# from the output of plotStack4l.C

# Input yields file
yields = 'yields.txt'

#mass spectrum parameters
mass_0 = 600
mass_Increment = 200
mass_spec = 5

sig_yields_scale = [1,1,1,1,1]
channelMap = { 0:'et', 1:'mt', 2:'tt', 3:'em', 4:'hi_et', 5:'hi_mt', 6:'hi_tt', 7:'hi_em' }

yieldMat = [[[0 for x in range (7)] for x in range (mass_spec * 2)] for x in range (0, 8)]
infile = open(yields)

bkgtotals = [[0 for x in range (mass_spec)] for x in range (8)]

et_massIndex = 0
mt_massIndex = 0
tt_massIndex = 0
em_massIndex = 0
het_massIndex = 0
hmt_massIndex = 0
htt_massIndex = 0
hem_massIndex = 0


for line in infile:
  if 'lowET' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [0][et_massIndex][j] = float(line.split()[j + 2])
      et_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [0][et_massIndex - 1][j] = float(line.split()[j + 2])
  if 'lowMT' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [1][mt_massIndex][j] = float(line.split()[j + 2])
      mt_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [1][mt_massIndex - 1][j] = float(line.split()[j + 2])
  if 'lowTT' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [2][tt_massIndex][j] = float(line.split()[j + 2])
      tt_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [2][tt_massIndex - 1][j] = float(line.split()[j + 2])
  if 'lowEM' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [3][em_massIndex][j] = float(line.split()[j + 2])
      em_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [3][em_massIndex - 1][j] = float(line.split()[j + 2])
  if 'hiET' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [4][het_massIndex][j] = float(line.split()[j + 2])
      het_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [4][het_massIndex - 1][j] = float(line.split()[j + 2])
  if 'hiMT' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [5][hmt_massIndex][j] = float(line.split()[j + 2])
      hmt_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [5][hmt_massIndex - 1][j] = float(line.split()[j + 2])
  if 'hiTT' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [6][htt_massIndex][j] = float(line.split()[j + 2])
      htt_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [6][htt_massIndex - 1][j] = float(line.split()[j + 2])
  if 'hiEM' in line:
    if 'rate' in line:
      for j in range (0, 7):
        yieldMat [7][hem_massIndex][j] = float(line.split()[j + 2])
      hem_massIndex += 2
    if 'stat.err' in line:
      for j in range (0, 7):
        yieldMat [7][hem_massIndex - 1][j] = float(line.split()[j + 2])


print 'Yields and systematics from input:' + '\n'

for i in range (0, 8):
  for j in range (0, mass_spec * 2):
    print yieldMat[i][j]

print'BKG sums for temporary use in OBS counts:' + '\n'

for i in range (0, 8):
  for j in range (0, mass_spec):
    for k in range (1, 7):
      bkgtotals [i][j] += yieldMat [i][j*2][k]
  print bkgtotals [i]

for j in range (0,8):
  subprocess.call('rm limits_' + channelMap[j] + '_13tev.txt', shell=True)

for i in range (0,8):
  print 'finding ' + str(channelMap[i]) + ' channel limits'
  for j in range(0, mass_spec):
    massName = str(mass_0 + j * mass_Increment) + 'GeV'
    print 'Editing datacards for mass point '+ massName + ' in ' + channelMap[i] + ' channel:'
    cardin = open('datacard_' + str(channelMap[i]) + '_template.txt')
    cardout = open('datacard_' + str(channelMap[i]) + '_' + str(massName) + '_out.txt','w')
    for line in cardin:
      if 'observation' in line:
        line = 'observation ' + str(bkgtotals [i][j]) + '\n'
        print line
      if 'rate' in line:
        line = 'rate        ' + str(yieldMat [i][j * 2][0]) + '    ' + str(yieldMat [i][j * 2][1]) + '    ' + str(yieldMat [i][j * 2][2]) + '    ' + str(yieldMat [i][j * 2][3]) + '    ' + str(yieldMat [i][j * 2][4]) + '    ' + str(yieldMat [i][j * 2][5]) + '    ' + str(yieldMat [i][j * 2][6]) + '\n'
        print line
      if 'Stat' in line:
        line = 'Stat lnN    ' + str(yieldMat [i][j * 2 + 1][0]) + '    ' + str(yieldMat [i][j * 2 + 1][1]) + '    ' + str(yieldMat [i][j * 2 + 1][2]) + '    ' + str(yieldMat [i][j * 2 + 1][3]) + '    ' + str(yieldMat [i][j * 2 + 1][4]) + '    ' + str(yieldMat [i][j * 2 + 1][5]) + '    ' + str(yieldMat [i][j * 2 + 1][6]) + '\n'
        print line
      cardout.write(line)
    cardin.close()
    cardout.close()
    cmd = 'combine -M Asymptotic datacard_' + channelMap[i] + '_' + str(massName) + '_out.txt -n _' + str(channelMap[i]) + '_' + str(massName) + '_ -m 125'
    outfile = open('limits_' + channelMap[i] + '_13tev.txt','a+')
    process = subprocess.Popen(cmd.split(), shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    outfile.write(process.communicate()[0])
    outfile.close()


# Parse the limits_13tev.txt log file to find the expected limits and error bands, outputting to
# simple rows in a file, multiplied by signal xsecs

for i in range (0, 8):
  limin = open('limits_' + channelMap[i] + '_13tev.txt','a+')
  limout = open('limits_' + channelMap[i] + '_13tev_out.txt','w')
  str25 = ''
  str16 = ''
  str50 = ''
  str84 = ''
  str975 = ''
  k = -1
  for line in limin:
    if 'Observed' in line:  k += 1
    if 'Expected' in line:
      if '2.5%' in line:
        str25 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
      if '16.0%' in line:
        str16 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
      if '50.0%' in line:
        str50 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
      if '84.0%' in line:
        str84 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
      if '97.5%' in line:
        str975 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
  limout.write(str25+'\n')
  limout.write(str16+'\n')
  limout.write(str50+'\n')
  limout.write(str84+'\n')
  limout.write(str975)
  limin.close()
  limout.close()

subprocess.call('rm limits_Combined_13tev.txt', shell=True)

for j in range (0, mass_spec):
  massName = str(mass_0 + j * mass_Increment) + 'GeV'
  print 'Creating datacard for combined channel limits at ' + massName
  subprocess.call('combineCards.py eTau=datacard_et_' + massName + '_out.txt muTau=datacard_mt_' + massName + '_out.txt tauTau=datacard_tt_' + massName + '_out.txt eMu=datacard_em_' + massName + '_out.txt hi_eTau=datacard_hi_et_' + massName + '_out.txt hi_muTau=datacard_hi_mt_' + massName + '_out.txt hi_tauTau=datacard_hi_tt_' + massName + '_out.txt hi_eMu=datacard_hi_em_' + massName + '_out.txt > datacard_' + massName + '_Combined_out.txt', shell = True )
  cmd = 'combine -M Asymptotic datacard_' + str(massName) + '_Combined_out.txt -n ' + str(massName) + ' -m 125'
  outfile = open('limits_Combined_13tev.txt','a+')
  process = subprocess.Popen(cmd.split(), shell=False, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
  outfile.write(process.communicate()[0])
  outfile.close()

limin = open('limits_Combined_13tev.txt','a+')
limout = open('limits_Combined_13tev_out.txt','w')
str25 = ''
str16 = ''
str50 = ''
str84 = ''
str975 = ''
k = -1
for line in limin:
  if 'Observed' in line:  k += 1
  if 'Expected' in line:
    if '2.5%' in line:
      str25 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
    if '16.0%' in line:
      str16 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
    if '50.0%' in line:
      str50 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
    if '84.0%' in line:
      str84 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
    if '97.5%' in line:
      str975 += str(float(line.split()[4]) * sig_yields_scale[k]) + ' '
limout.write(str25+'\n')
limout.write(str16+'\n')
limout.write(str50+'\n')
limout.write(str84+'\n')
limout.write(str975)
limin.close()
limout.close()

