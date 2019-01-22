#!/usr/bin/python
# -*- coding: UTF-8 -*-
import os

lsts = ['aps', 'idb', 'ncp', 'obj', 'pch', 'tmp', 'sbr',
'pdb', 'bsc', 'ilk', 'res', 'ncb', 'opt',
'suo', 'manifest', 'dep', 'iobj', 'log']

def fileDelete():
	path = os.getcwd()
	for root, dirs, files in os.walk(path):
		for file in files:
			if file.split('.')[-1] in lsts:
				filePath = root.replace('\\', '/') + '/' + file
				if os.path.exists(filePath):
					os.remove(filePath)
					print('delete file: ' + filePath)
			
			

if __name__ == "__main__":
	fileDelete()