#!/bin/bash

grepStr=""
while read surname name matr mark; do
	if [[ $mark -lt 18 ]]; then
		grepStr="${grepStr} ${matr}"
	fi
done < RisultatiProvaPratica2.txt

for matr2 in ${grepStr}; do
	foundFlag=0
	res=""
	while read sur name matr mark; do
		res="$matr $sur $name $mark"
		if [[ $matr2 -eq $matr ]]; then
			foundFlag=1
		fi
	done < RisultatiProvaPratica1.txt

	if (( foundFlag == 0 )); then echo $res; fi
done
