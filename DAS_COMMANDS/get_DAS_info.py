#!/usr/bin/python

import sys
import os
import re



print "------------------------------------------------"
if len(sys.argv) is 2:
  print "Will generate crab and config files for sample :"
  print sys.argv[1]

else:
	print " run as ./get_DAS_info.py  DataSet"
print "------------------------------------------------"


command1 = "./das_client.py  --query \"summary dataset=" + sys.argv[1] + "\""

C1 = os.popen(command1)

command2 = "./das_client.py  --query \"run lumi dataset=" + sys.argv[1] + "\" --format=json"

C2 = os.popen(command2)

print command2
print C1.read()
print C2.read()


