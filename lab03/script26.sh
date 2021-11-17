#!/bin/bash

rm -r BUTTAMI
mkdir BUTTAMI
cd BUTTAMI
touch "*" "**" "***" ";;"
cd ..

for file in `ls BUTTAMI/*`; do
	echo ${file}
	touch ${file}".txt"
done
