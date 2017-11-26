#!/bin/bash
dirname="$1"
filename="$2"
if [ ${dirname: -1} != "/" ]; 
	then dirname="${dirname}/"; 
fi
rm -rf ${dirname}${filename}