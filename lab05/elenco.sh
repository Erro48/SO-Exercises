#!/bin/bash

LungNomeDir=0
fileCounter=0

for file in `ls`; do
	if [[ -d $file ]]; then
		(( LungNomeDir=$LungNomeDir+${#file} ))
	else
		(( fileCounter=$fileCounter+1 ))
	fi
done

echo "LungNomeDir=$LungNomeDir"
echo "# file=$fileCounter"
