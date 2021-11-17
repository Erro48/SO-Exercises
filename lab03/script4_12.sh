#!/bin/bash

for file in `ls`; do
	echo "file is $file"
	ls -dl $file
	if (( $? != 0 )); then echo "ls produce errore"; fi
done
