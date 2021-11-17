#!/bin/bash

LungNomiDirectory=0
nFiles=0

for elem in `ls`; do
	if [[ -d $elem ]]; then
		(( LungNomiDirectory=$LungNomiDirectory+${#elem} ))
	else
		(( nFiles=$nFiles+1 ))
	fi
done

echo "I file di tipo non-dir sono $nFiles"
echo "La lunghezza accumulata dei nomi delle dir è: $LungNomiDirectory"
