#!/usr/bin/python

# To build the C file from the bvh skeleton motion

import sys

roots_name = []
offsets = []
channels = []

if len(sys.argv) < 3:
	print("need the source file name bvh and the destination file name C")
	sys.exit(0)

file_name = sys.argv[1]

file_ = open(file_name, "r")
liste = file_.readlines();
file_.close()

for line in liste:
	words = line.split()
	if "ROOT" in words or "JOINT" in words:
		roots_name.append(words[1])
		continue
	
	if "OFFSET" in words:
		offsets.append([words[1], words[2], words[3]])
		continue

	if "CHANNELS" in words:
		if words[1] == "6":
			channels.append("true")
		else:
			channels.append("false")
		
		continue
		
	if "End" in words:
		roots_name.append("End_Site")
		channels.append(0)

file_ = open(sys.argv[2], "w")

file_.write("// This file is generated from bvh_to_C.sh python script.\n");

i = 0
for root in roots_name:
	if "End_Site" in root:
		file_.write("#define Site_" + root_tmp + "_offset " + offsets[i][0] + ", " + offsets[i][1] + ", " + offsets[i][2] + "\n")
		i=i+1
		continue
	file_.write("#define " + root + "_offset " + offsets[i][0] + ", " + offsets[i][1] + ", " + offsets[i][2] + "\n")
	file_.write("#define " + root + "_channels " + channels[i] + "\n")
	i=i+1
	root_tmp = root

file_.close()
